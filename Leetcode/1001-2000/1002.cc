#include "../dependencies.h"
#include <string>
#include <vector>

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
      vector<string> answer = {};
      string chars = words[0];
      bool flag = true;
      for (auto c : chars) {
        flag = true;
        for (auto &s : words) {
          if (s.find(c) == string::npos) {
            flag = false;
            break;
          } else {
            s.erase(s.find(c), 1);
          }
        }
        if (flag) {
          answer.push_back("");
          answer.back().push_back(c);
        }
      }
      return answer;
    }
};

int main() {
  std::vector<std::string> strs = {"cool","lock","cook"};
  Solution sol;
  std::vector<std::string> ans = sol.commonChars(strs);
  for (auto i : ans) {
    std::cout << "\"" << i << "\", ";
  }
}