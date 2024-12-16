#include "../../../dependencies.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t maxLength = 0;
        unordered_set<char> charSet;
        for (size_t leftPtr = 0, rightPtr = 0; rightPtr != s.length(); ++rightPtr) {
            while(charSet.find(s[rightPtr]) != charSet.end()) {
                charSet.erase(s[leftPtr]);
                leftPtr++;
            }
            charSet.insert(s[rightPtr]);
            maxLength = max(maxLength, rightPtr - leftPtr + 1);
        }
        return maxLength;
    }
};

int main() {
    string s = "a";
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << endl;
}