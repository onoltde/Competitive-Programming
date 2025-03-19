#include "abc.h"

// you may find the definitions useful
const int OP_ZERO    = 0;  // f(OP_ZERO,    x0, x1) = 0
const int OP_NOR     = 1;  // f(OP_NOR,     x0, x1) = !(x0 || x1)
const int OP_GREATER = 2;  // f(OP_GREATER, x0, x1) = (x0 > x1)
const int OP_NOT_X1  = 3;  // f(OP_NOT_X1,  x0, x1) = !x1
const int OP_LESS    = 4;  // f(OP_LESS,    x0, x1) = (x0 < x1)
const int OP_NOT_X0  = 5;  // f(OP_NOT_X0,  x0, x1) = !x0
const int OP_XOR     = 6;  // f(OP_XOR,     x0, x1) = (x0 ^ x1)
const int OP_NAND    = 7;  // f(OP_NAND,    x0, x1) = !(x0 && x1)
const int OP_AND     = 8;  // f(OP_AND,     x0, x1) = (x0 && x1)
const int OP_EQUAL   = 9;  // f(OP_EQUAL,   x0, x1) = (x0 == x1)
const int OP_X0      = 10; // f(OP_X0,      x0, x1) = x0
const int OP_GEQ     = 11; // f(OP_GEQ,     x0, x1) = (x0 >= x1)
const int OP_X1      = 12; // f(OP_X1,      x0, x1) = x1
const int OP_LEQ     = 13; // f(OP_LEQ,     x0, x1) = (x0 <= x1)
const int OP_OR      = 14; // f(OP_OR,      x0, x1) = (x0 || x1)
const int OP_ONE     = 15; // f(OP_ONE,     x0, x1) = 1


// Alice
int alice(const int n, const char names[][5], const unsigned short numbers[], bool outputs_alice[]) {
    for(int i = 0; i < numbers[0]; i++) {
        outputs_alice[i] = 0;
    }
    return numbers[0];
}

int bob(const int m, const char senders[][5], const char recipients[][5], bool outputs_bob[]) {
    for(int i = 0; i < m; i++) {
        outputs_bob[i] = 0;
    }
    return m;
}

// Circuit
int circuit(const int la, const int lb, int operations[], int operands[][2], int outputs_circuit[][16]) {
    operations[la + lb] = 0;
    operations[la + lb + 1] = 1;
    for(int i = la + lb; i <= la + lb + 1; i++) {
        operands[i][0] = operands[i][1] = 1;
    }
    int ans = la * lb;
    for(int i = 0; i < 16; i++) {
        outputs_circuit[0][i] = la + lb + ((ans >> i) & 1);
    }
    return 2;
}
