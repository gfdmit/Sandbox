#include "../../../dependencies.h"
#include <vector>

class Solution {
public:
  int maxArea(vector<int> &height) {
    size_t maxim = 0, leftPtr = 0, rightPtr = height.size() - 1;
    while (leftPtr < rightPtr) {
      maxim = max(maxim, (rightPtr - leftPtr) * min(height[leftPtr], height[rightPtr]));
      if (height[leftPtr] < height[rightPtr]) {
        leftPtr++;
      } else if (height[leftPtr] > height[rightPtr]) {
        rightPtr--;
      } else {
        leftPtr++;
        rightPtr--;
      }
    }
    return maxim;
  }
};

int main() {
  vector<int> v = {1,8,6,2,5,4,8,3,7};
  Solution sol;
  std::cout << sol.maxArea(v) << std::endl;
}