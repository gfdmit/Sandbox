#include "../../../dependencies.h"

class Solution {
public:
  bool isPalindrome(int x) {
    if (x >= 0 && x == reverse(x))
      return true;
    return false;
  }

private:
  int reverse(int x) {
    int retVal = 0;
    while (x != 0) {
      if (abs(retVal) > INT32_MAX / 10) return 0;
      retVal = retVal * 10 + x % 10;
      x /= 10;
    }
    return retVal;
  }
};

int main() {
  int x = -121;
  Solution sol;
  std::cout << sol.isPalindrome(x) << std::endl;
}