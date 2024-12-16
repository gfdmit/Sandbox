#include "../../../dependencies.h"

class Solution {
public:
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
  int x = -1534236469;
  Solution sol;
  std::cout << sol.reverse(x) << std::endl;
}