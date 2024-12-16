#include "../../../dependencies.h"

class Solution {
public:
  int myAtoi(string s) {
    bool sign;
    long int number = 0;
    removeWhitespace(s);
    sign = defineSign(s);
    removeZero(s);
    while (s.front() >= '0' && s.front() <= '9') {
      number = number * 10 + (s.front() - 48);
      if (number > INT32_MAX) {
        return sign ? INT32_MAX : INT32_MIN;
      }
      s.erase(0, 1);
    }
    return sign ? number : 0 - number;
  }

private:
  void removeWhitespace(string &s) {
    while(s.front() == ' ') {
      s.erase(0, 1);
    }
  }

  bool defineSign(string &s) {
    if (s.front() == '-') {
      s.erase(0, 1);
      return false;
    } else if (s.front() == '+') {
      s.erase(0, 1);
      return true;
    }
    return true;
  }

  void removeZero(string &s) {
    while (s.front() == '0') {
      s.erase(0, 1);
    }
  }
};

int main() {
  string s = "-1111111111111111111111111111111";
  Solution sol;
  cout << sol.myAtoi(s) << endl;
}