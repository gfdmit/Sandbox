#include "../dependencies.h"

class Solution {
public:
    int appendCharacters(string s, string t) {
      while (s != "" && t != "") {
        if (s.front() == t.front()) {
          t.erase(0, 1);
        }
        s.erase(0, 1);
      }
      return t.size();
    }
};

int main() {
  string s = "z", t = "abcde";
  Solution sol;
  std::cout << sol.appendCharacters(s, t) << std::endl;
}