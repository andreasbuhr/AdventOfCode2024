#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

int main() {
  std::ifstream file("../input_07.txt");
  std::string line;
  int64_t total_calibration = 0;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string word;
    std::getline(iss, word, ':');
    int64_t test_value = std::stoll(word);
    std::vector<int64_t> operands;
    while (std::getline(iss, word, ' ')) {
      if (word.empty())
        continue;
      operands.push_back(std::stoll(word));
    }

    // using the bit values of an int as operators
    // bit set is multiplication, bit unset is addition
    for (size_t ops = 0;; ops++) {
      int64_t result = operands[0];
      int next_operand = 1;
      while (next_operand < operands.size()) {
        int op = (ops >> (2 * (next_operand - 1))) & 3;
        switch (op) {
        case 0: {
          result += operands[next_operand];
        } break;
        case 1: {
          result *= operands[next_operand];
        } break;
        case 2: {
          // break here for part1
          result = std::stoll(std::to_string(result) + std::to_string(operands[next_operand]));
        } break;
        case 3: {
          goto nextops;
        } break;
        }
        if (result > test_value)
          break;
        next_operand++;
      }
      if (result == test_value) {
        total_calibration += test_value;
        break;
      }
      if (ops & (1 << (2 * (operands.size() - 1))))
        break;
    nextops:
      int foo;
    }
  }

  std::cout << total_calibration << std::endl;

  return 0;
}
