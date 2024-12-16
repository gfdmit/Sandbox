#include "../../../dependencies.h"

class Solution {
public:
  int romanToInt(string s) {
    unordered_map<char, int> dict = {
      {'I', 1},
      {'V', 5},
      {'X', 10},
      {'L', 50},
      {'C', 100},
      {'D', 500},
      {'M', 1000}};
    int number = 0, prev = 0;
    for (auto i = s.rbegin(); i != s.rend(); i++) {
      if (dict[*i] < prev) {
        number -= dict[*i];
      } else {
        number += dict[*i];
      }
      prev = dict[*i];
    }
    return number;
  }
};

int main() {
  string s = "MCMXCIV";
  Solution sol;
  std::cout << sol.romanToInt(s) << std::endl;
}