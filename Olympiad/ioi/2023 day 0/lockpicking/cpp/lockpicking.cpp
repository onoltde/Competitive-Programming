#include "lockpicking.h"

void construct_card(int N, std::vector<int> A, std::vector<std::vector<int>> S) {
	define_states(2, {0, 1}, {{1, 1}, {0, 0}}, 0);
}
