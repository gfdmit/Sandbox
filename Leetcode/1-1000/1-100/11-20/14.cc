#include "../../../dependencies.h"
#include <vector>

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
      string prefix = strs.front();
      for (size_t i = 1; i != strs.size(); i++) {
        string tempPrefix = "";
        auto prefIter = prefix.begin(), strIter = strs[i].begin();
        while (*prefIter == *strIter && prefIter != prefix.end() && strIter != strs[i].end()) {
          tempPrefix.push_back(*prefIter);
          prefIter++;
          strIter++;
        }
        prefix = tempPrefix;
      }
    return prefix;
    }
};

int main() {
  vector<string> s = {"", ""};
  Solution sol;
  std::cout << "|" << sol.longestCommonPrefix(s) << "|" << std::endl;
}