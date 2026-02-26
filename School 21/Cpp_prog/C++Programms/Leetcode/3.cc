#include "dependencies.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t leftPtr = 0, rightPtr = 0, maxLength = 0;
        while (rightPtr != s.length()) {
            rightPtr++;
            while(isCharInStr(s[rightPtr], s.substr(leftPtr, rightPtr - leftPtr))) {
                leftPtr++;
            }
            if ((rightPtr - leftPtr) > maxLength) {
                maxLength = rightPtr - leftPtr;
            }
        }
        return maxLength;
    }
private:
    bool isCharInStr(char c, string s) {
        for (auto i : s) {
            if (i == c) return true;
        }
        return false;
    }
};

int main() {
    string s = "pwkew";
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << endl;
}