#include "../../../dependencies.h"
#include <unordered_map>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      unordered_map<int, int> hashtable;
      set<vector<int>> setAnswer;
      vector<vector<int>> answer;
      for (int i : nums) {
        hashtable[i]++;
      }
      for (size_t i = 0; i != nums.size() - 1; i++) {
        for (size_t j = i + 1; j != nums.size(); j++) {
          int remains = 0 - nums[i] - nums[j];
          if (remains == nums[i] && remains == nums[j]) {
            if (hashtable[remains] < 3) continue;;
          } else if (remains == nums[i] || remains == nums[j]) {
            if (hashtable[remains] < 2) continue;;
          } else if (hashtable.find(remains) == hashtable.end()) {
            continue;
          }
          vector<int> tempVec = {remains, nums[i], nums[j]};
          std::sort(tempVec.begin(), tempVec.end());
          setAnswer.insert(tempVec);
        }
      }
      for (auto i : setAnswer) {
        answer.push_back(i);
      }
      return answer;
    }
};

int main() {
  std::vector<int> nums = {-1,0,1,2,-1,-4,-2,-3,3,0,4};
  Solution sol;
  std::vector<std::vector<int>> ans = sol.threeSum(nums);
  for (auto i : ans) {
    for (auto j : i) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}