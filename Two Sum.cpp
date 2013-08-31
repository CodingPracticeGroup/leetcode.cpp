class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        multimap<int, int> m;
        int len = numbers.size();
        for (int i=0; i<len; i++) {
            m.insert(pair<int, int>(numbers[i], i));
        }
        vector<int> r;
        for (int i=0; i<len; i++) {
            multimap<int, int>::iterator it = m.find(target-numbers[i]);
            if (it != m.end()) {
                int idx1 = it->second+1;
                m.erase(it);
                it = m.find(numbers[i]);
                if (it != m.end()) {
                    int idx2 = it->second+1;
                    r.push_back(idx1<idx2 ? idx1 : idx2);
                    r.push_back(idx1>idx2 ? idx1 : idx2);
                    break;
                }
            }
        }
        return r;
    }
};