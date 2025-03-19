#!/usr/bin/env python

from math import inf
from enum import Enum
import os
import signal
from sys import argv
from PySide6.QtCore import Qt
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Device:
    def __init__(self, device_file):
        self.N = int.from_bytes(device_file.read(2), 'big')
        self._cparam = int.from_bytes(device_file.read(2), 'big')
        self.A = [ 0 ] * self.N
        self.S = [ [0, 0] for _ in range(self.N) ]
        for i in range(self.N):
            self.A[i] = int.from_bytes(device_file.read(1), 'big')
            self.S[i][0] = int.from_bytes(device_file.read(2), 'big')
            self.S[i][1] = int.from_bytes(device_file.read(2), 'big')
            assert 0 <= self.A[i] <= 1
            assert 0 <= self.S[i][0] < self.N and 0 <= self.S[i][1] < self.N
        self.initial_state = 0

    def get_total_states(self):
        return self.N

    def get_state(self):
        return self.state

    def get_initial_state(self):
        return self.initial_state

    def get_output(self):
        return self.A[self.state]

    def get_state_description(self, st):
        return (st, self.A[st], self.S[st])

    def set_initial_state(self, state):
        self.initial_state = state

    def reset(self):
        self.state = self.initial_state

    def step(self, input_bit):
        self.state = self.S[self.state][input_bit]

class Lock(Device):
    def __init__(self, lock_file):
        Device.__init__(self, lock_file)
        self.K = self._cparam
        assert 2 <= self.N <= 150
        assert self.K >= 1
        self.state = self.initial_state

class Keycard(Device):
    def __init__(self, keycard_file):
        Device.__init__(self, keycard_file)
        self.initial_state = self._cparam
        assert 1 <= self.N <= 50000
        assert 0 <= self.initial_state < self.N
        self.state = self.initial_state


class Result(Enum):
    SUCCESS = 1
    FAILURE = 2


class Simulation:
    def __init__(self, input_file):
        file = open(input_file, "rb")
        self.lock = Lock(file)
        self.keycard = Keycard(file)
        assert next(file, None) is None
        file.close()

        self.fail_treshold = self.lock.K
        self.max_steps = 10**7
        self.simulate()

    def simulate(self, lock_initial_state = 0):
        self.lock.set_initial_state(lock_initial_state)
        self.lock.reset()
        self.keycard.reset()
        lock_state, keycard_state = self.lock.get_state(), self.keycard.get_state()
        lock_out, keycard_out = self.lock.get_output(), self.keycard.get_output()
        last_err = -1 if lock_out == keycard_out else 0
        state_map = {(lock_state, keycard_state) : 0}
        self._states = [ (lock_state, keycard_state, 0 if lock_out == keycard_out else 1) ]
        while len(self._states) < self.max_steps and self._states[-1][2] < self.fail_treshold:
            self.lock.step(keycard_out)
            self.keycard.step(lock_out)
            lock_state, keycard_state = self.lock.get_state(), self.keycard.get_state()
            lock_out, keycard_out = self.lock.get_output(), self.keycard.get_output()
            errs_until = self._states[-1][2]
            last_err = last_err if lock_out == keycard_out else len(self._states)
            if (lock_state, keycard_state) in state_map and state_map[(lock_state, keycard_state)] > last_err:
                self.result = Result.SUCCESS
                self._period_from = state_map[(lock_state, keycard_state)]
                return
            else:
                state_map[(lock_state, keycard_state)] = len(self._states)
            self._states.append((lock_state, keycard_state, errs_until + (0 if lock_out == keycard_out else 1)))
        self.result = Result.FAILURE

    def steps(self):
        return len(self._states) if self.result == Result.FAILURE else self.max_steps

    def status_at(self, t):
        assert 0 <= t < self.steps()
        if t >= len(self._states):
            t = self._period_from + ((t - self._period_from) % (len(self._states) - self._period_from))
        lock_st, keycard_st, errs = self._states[t]
        return (self.lock.get_state_description(lock_st), self.keycard.get_state_description(keycard_st), errs)

    def get_result(self):
        if self.result == Result.SUCCESS:
            res = ("SUCCESS", "'LimeGreen'")
        else:
            res = ("FAILURE", "'Red'")
        return res


class SimulationGui(QWidget):
    def __init__(self, input_file, sim):
        super().__init__()
        self.setWindowTitle("lockpicking")
        self.input_file = input_file

        bold_font = QFont()
        bold_font.setBold(True)
        demi_bold_font = QFont()
        demi_bold_font.setWeight(QFont.Weight.DemiBold)

        layout = QVBoxLayout(self)
        layout.setSizeConstraint(QLayout.SizeConstraint.SetFixedSize)
        button_frame = QHBoxLayout()
        layout.addLayout(button_frame)
        steps_frame = QHBoxLayout()
        layout.addLayout(steps_frame)

        layout.addItem(QSpacerItem(20, 10, QSizePolicy.Minimum, QSizePolicy.Expanding))

        main_layout = QGridLayout()
        layout.addLayout(main_layout)
        lock_header = QLabel("Lock")
        lock_header.setFont(bold_font)
        keycard_header = QLabel("Keycard")
        keycard_header.setFont(bold_font)
        main_layout.addWidget(lock_header,                 0, 0, Qt.AlignCenter)
        main_layout.addWidget(keycard_header,              0, 2, Qt.AlignCenter)
        main_layout.addWidget(QLabel("Current state"),     1, 1, Qt.AlignCenter)
        main_layout.addWidget(QLabel("Output"),            2, 1, Qt.AlignCenter)
        main_layout.addWidget(QLabel("State transitions"), 3, 1, 2, 1, Qt.AlignCenter)
        self.lock_state_label = QLabel()
        main_layout.addWidget(self.lock_state_label,       1, 0, Qt.AlignCenter)
        self.keycard_state_label = QLabel()
        main_layout.addWidget(self.keycard_state_label,    1, 2, Qt.AlignCenter)
        self.lock_output_label = QLabel()
        main_layout.addWidget(self.lock_output_label,      2, 0, Qt.AlignCenter)
        self.keycard_output_label = QLabel()
        main_layout.addWidget(self.keycard_output_label,   2, 2, Qt.AlignCenter)
        lock_trans_box = QHBoxLayout()
        self.lock_trans_b0 = QLabel()
        lock_trans_box.addWidget(self.lock_trans_b0)
        self.lock_trans_b1 = QLabel()
        lock_trans_box.addWidget(self.lock_trans_b1)
        main_layout.addWidget(self.lock_trans_b0,          3, 0, Qt.AlignCenter)
        main_layout.addWidget(self.lock_trans_b1,          4, 0, Qt.AlignCenter)
        keycard_trans_box = QHBoxLayout()
        self.keycard_trans_b0 = QLabel()
        keycard_trans_box.addWidget(self.keycard_trans_b0)
        self.keycard_trans_b1 = QLabel()
        keycard_trans_box.addWidget(self.keycard_trans_b1)
        main_layout.addWidget(self.keycard_trans_b0,       3, 2, Qt.AlignCenter)
        main_layout.addWidget(self.keycard_trans_b1,       4, 2, Qt.AlignCenter)

        def step_handler(delta):
            return lambda event: self.set_time(self.time + delta)

        buttons = [
            ("⏮", "Home", 30,
             step_handler(-inf), "Go to start (Home)"),
            ("⏪", "PgUp", 30,
             step_handler(-10), "Backward 10 steps (PageUp)"),
            ("⏴", "Left", 30,
             step_handler(-1), "Previous step (Left)"),
            ("⏵", "Right", 30,
             step_handler(+1), "Next step (Right)"),
            ("⏩", "PgDown", 30,
             step_handler(+10), "Forward 10 steps (PageDown)"),
            ("⏭", "End", 30,
             step_handler(+inf), "Go to end (End)"),
            ("Init Lock", "S", 75,
             lambda event: self.set_init_lock_state(), "Set initial lock state (S)"),
            ("Reload", "R", 65,
             lambda event: self.reload(), f"Reload {self.input_file} (R)")
        ]
        for text, key, size, handler, desc in buttons:
            button = QPushButton(text)
            button.clicked.connect(handler)
            button.setShortcut(key)
            button.setFixedSize(size, 30)
            button.setToolTip(desc)
            button.setAutoRepeat(True)
            button_frame.addWidget(button)
        button_frame.addStretch()
        steps_frame.addWidget(QLabel("Step"))
        self.time_textbox = QLineEdit()
        self.time_textbox.setFixedWidth(75)
        self.time_textbox.setValidator(QRegularExpressionValidator(r"\d*"))
        self.time_textbox.editingFinished.connect(self.time_edit_handler)
        steps_frame.addWidget(self.time_textbox)
        self.max_time_label = QLabel()
        steps_frame.addWidget(self.max_time_label, 0)
        steps_frame.addSpacing(30)
        self.error_label = QLabel()
        steps_frame.addWidget(self.error_label)
        steps_frame.addStretch()

        layout.addItem(QSpacerItem(20, 20, QSizePolicy.Minimum, QSizePolicy.Expanding))

        self.res_area = QWidget()
        layout.addWidget(self.res_area)
        result_box = QHBoxLayout(self.res_area)
        self.result_label = QLabel()
        #self.result_label.setFont(demi_bold_font)
        result_box.addWidget(self.result_label, alignment = Qt.AlignCenter)
        
        self.sim = sim
        self.reset()

    def display_status(self, status):
        self.lock_state_label.setText(str(status[0][0]))
        self.keycard_state_label.setText(str(status[1][0]))
        self.lock_output_label.setText(str(status[0][1]))
        self.keycard_output_label.setText(str(status[1][1]))
        self.lock_trans_b0.setText(f"bit 0: {status[0][2][0]}")
        self.lock_trans_b1.setText(f"bit 1: {status[0][2][1]}")
        if status[1][1] == 0:
            self.lock_trans_b0.setStyleSheet("border: 1px solid black;")
            self.lock_trans_b1.setStyleSheet("")
        else:
            self.lock_trans_b0.setStyleSheet("")
            self.lock_trans_b1.setStyleSheet("border: 1px solid black;")
        self.keycard_trans_b0.setText(f"bit 0: {status[1][2][0]}")
        self.keycard_trans_b1.setText(f"bit 1: {status[1][2][1]}")
        if status[0][1] == 0:
            self.keycard_trans_b0.setStyleSheet("border: 1px solid black;")
            self.keycard_trans_b1.setStyleSheet("")
        else:
            self.keycard_trans_b0.setStyleSheet("")
            self.keycard_trans_b1.setStyleSheet("border: 1px solid black;")
        self.error_label.setText(f"Error count: {status[2]} / {sim.fail_treshold}")

    def set_time(self, t):
        self.time = max(0, min(t, self.sim.steps() - 1))
        self.display_status(self.sim.status_at(self.time))
        self.time_textbox.setText(str(self.time))

    def time_edit_handler(self):
        self.set_time(int("0" + self.time_textbox.text()))
        self.setFocus()

    def set_init_lock_state(self):
        init_state_editor = InitStatePicker(self.sim.lock.get_total_states())
        init_state_editor.exec()
        if init_state_editor.selected_initial_state is not None:
            if init_state_editor.selected_initial_state != self.sim.lock.get_initial_state():
                self.sim.simulate(init_state_editor.selected_initial_state)
            self.reset()

    def reset(self):
        self.set_time(0)
        self.max_time_label.setText(f"/ {self.sim.steps() - 1}")
        result = self.sim.get_result()
        self.result_label.setText(f"VERIFICATION: {result[0]}")
        self.res_area.setStyleSheet(f"background: {result[1]}")

    def reload(self):
        try:
            self.sim = Simulation(self.input_file)
        except:
            QMessageBox.critical(
                self, "lockpicking", f"Cannot load '{self.input_file}'.")
        else:
            self.reset()


class InitStatePicker(QDialog):
    def __init__(self, total_states):
        super().__init__()
        self.state = 0
        self.total_states = total_states
        self.setWindowTitle("lockpicking")
        self.finished.connect(self.finished_handler)
        layout = QVBoxLayout(self)
        layout.setSizeConstraint(QLayout.SizeConstraint.SetFixedSize)
        layout.addWidget(QLabel(text=f"Choose a new initial state for the lock between 0 and {self.total_states}:"))
        selection_frame = QHBoxLayout()
        layout.addLayout(selection_frame)
        self.state_textbox = QLineEdit(text="0")
        self.state_textbox.setFixedWidth(50)
        self.state_textbox.setValidator(QRegularExpressionValidator(r"\d*"))
        self.state_textbox.editingFinished.connect(self.update_textbox_handler)
        selection_frame.addWidget(self.state_textbox)
        set_button = QPushButton("Set initial state")
        set_button.clicked.connect(lambda event: self.accept())
        selection_frame.addWidget(set_button)
        self.state_textbox.setFocus()

    def update_textbox_handler(self):
        self.state = int("0" + self.state_textbox.text())
        self.state = max(0, min(self.state, self.total_states - 1))
        self.state_textbox.setText(str(self.state))
        self.setFocus()

    def finished_handler(self, _):
        self.selected_initial_state = self.state


if __name__ == "__main__":
    input_file = "lockpicking.bin"
    if not os.path.exists(input_file):
        print("Use 'run_cpp.sh' first, and make sure that 'lockpicking.bin' is in the working directory.")
        exit(1)
    try:
        sim = Simulation(input_file)
    except:
        print(f"Cannot load '{input_file}'.")
        exit(1)

    signal.signal(signal.SIGINT, signal.SIG_DFL)
    app = QApplication(argv)
    app.setStyleSheet("QLabel{font-size: 12pt;}")
    app.setStyleSheet("QLineEdit{font-size: 12pt;}")
    app.setStyleSheet("QPushButton{font-size: 12pt;}")
    window = SimulationGui(input_file, sim)
    window.show()
    app.exec()
