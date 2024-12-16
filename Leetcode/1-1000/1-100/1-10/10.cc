#include "../../../dependencies.h"
#include <string>

class Solution {
public:
  bool isMatch(string s, string p) {
    if (p.find('*') == string::npos && p.find('.') == string::npos) {
      if (p.size() > s.size()) {
        return false;
      }
      return s == p;
    }
    for (size_t i = 0; i != p.size() - 1; i++) {
      if (p[i] == '*' && p[i + 1] == '*') {
        p.erase(i, 1);
        i--;
      }
    }
    if (p.find('*') != string::npos) {
      string beg = p.substr(0, p.find('*'));
      string end = p.substr(p.find('*') + 1, p.size());
      if (isMatch(s, beg.substr(0, beg.size() - 1) + end)) {
          return true;
        }
      for (size_t i = p.size(); i != 21; i++) {
        if (isMatch(s, beg + end)) {
          return true;
        }
        beg.push_back(beg.back());
      }
    }
    if (p.find('.') != string::npos) {
      if (p.size() <= s.size()) {
        p.replace(p.find('.'), 1, string(1, s[p.find('.')]));
        if (isMatch(s, p)) {
            return true;
        }
      }
    }
    return false;
  }
};

int main() {
  string s = "acaabbaccbbacaabbbb", p = "a*.*b*.*a*aa*a*";
  Solution sol;
  std::cout << sol.isMatch(s, p) << std::endl;
}