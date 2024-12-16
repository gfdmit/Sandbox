#include "../../../dependencies.h"

class Solution {
public:
    void reverseString(vector<char>& s) {
        size_t strSize = s.size();
        for (size_t i = 0; i != strSize / 2; ++i) {
            swap(s[i], s[strSize - i - 1]);
        }
    }
};

int main() {
    vector<char> s({'h', 'e', 'l', 'l', 'o'});
    for (auto i = s.begin(); i != s.end(); ++i) {
        cout << *i;
    }
    cout << endl;
    Solution sol;
    sol.reverseString(s);
    for (auto i = s.begin(); i != s.end(); ++i) {
        cout << *i;
    }
    cout << endl;
}

