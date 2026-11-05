class Solution {
public:
    int minLength(string s) {
        vector<int> hidup;

        for (size_t i = 0; i < s.size(); i++) {
            hidup.push_back(i);

            int n = hidup.size();

            if (n >= 2) {
                char a = s[hidup[n - 2]];
                char b = s[hidup[n - 1]];

                if ((a == 'A' && b == 'B') ||
                    (a == 'C' && b == 'D')) {
                    
                    s[hidup[n - 2]] = '_';
                    s[hidup[n - 1]] = '_';

                    hidup.pop_back();
                    hidup.pop_back();
                }
            }
        }

        return hidup.size();
    }
};
