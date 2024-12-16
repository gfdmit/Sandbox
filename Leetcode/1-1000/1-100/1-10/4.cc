#include "../../../dependencies.h"

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      size_t median = nums1.size() + nums2.size();
      auto ptr1 = nums1.begin(), ptr2 = nums2.begin();
      vector<int> sum;
      while (ptr1 != nums1.end() && ptr2 != nums2.end() && sum.size() <= median / 2) {
        if (*ptr1 <= *ptr2) {
          sum.push_back(*ptr1);
          ptr1++;
        } else {
          sum.push_back(*ptr2);
          ptr2++;
        }
      }
      while (ptr1 != nums1.end() && sum.size() <= median / 2) {
        sum.push_back(*ptr1);
        ptr1++;
      }
      while (ptr2 != nums2.end() && sum.size() <= median / 2) {
        sum.push_back(*ptr2);
        ptr2++;
      }
      return median % 2 == 0 ? (sum[median / 2] + sum[median / 2 - 1]) / 2.0 : sum[median / 2];
      }
};

int main() {
  Solution sol;
}