#include "../../../dependencies.h"
#include <unordered_map>

class Solution {
public:
    int longestPalindrome(string s) {
      unordered_map<char, int> m;
      int maxPal = 0, maxOdd = 0;
      for (auto i : s) {
        m[i]++;
      }
      for (auto i : m) {
        if (i.second % 2 == 0) {
          maxPal += i.second;
        } else {
          maxPal += i.second - 1;
          maxOdd = 1;
        }
      }
      return maxPal + maxOdd;
    }
};

int main() {
  string s = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
  Solution sol;
  std::cout << sol.longestPalindrome(s) << std::endl;
}