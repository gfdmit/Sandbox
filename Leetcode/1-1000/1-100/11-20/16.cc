#include "../../../dependencies.h"
#include <cstdint>

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
      int minim = INT32_MAX;
      int answer = 0;
      for (size_t i = 0; i != nums.size() - 2; i++) {
        for (size_t j = i + 1; j != nums.size() - 1; j++) {
          for (size_t k = j + 1; k != nums.size(); k++) {
            if (minim > abs(target - (nums[i] + nums[j] + nums[k]))) {
              minim = abs(target - (nums[i] + nums[j] + nums[k]));
              answer = nums[i] + nums[j] + nums[k];
            }
          }
        }
      }
      return answer;
    }
};

int main() {
  std::vector<int> nums = {1, 1, 1, 0};
  Solution sol;
  std::cout << sol.threeSumClosest(nums, -100) << std::endl;
  
}