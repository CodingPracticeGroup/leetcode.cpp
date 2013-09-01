class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        set<char> check;
        int begin = 0;
        int end = 0;
        int ret = end-begin;
        int len = s.size();
        while (end < len) {
            end ++;
            if (check.find(s[end-1]) != check.end()) {
                while (s[begin] != s[end-1]) {
                    check.erase(s[begin]);
                    begin ++;
                }
                begin ++;
            } else {
                check.insert(s[end-1]);
                if (ret < end-begin)
                    ret = end-begin;
            }
        }
        return ret;
    }
};