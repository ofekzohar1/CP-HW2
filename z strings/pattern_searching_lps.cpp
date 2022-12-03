//KMP Algorithm – Linear Time Pattern Searching O(n+m)
template <typename T>
class KMP {
public:
    vector<T>& pattern;
    vector<int> lps;

    KMP(vector<T>& pattern) : pattern(pattern) {
        computeLPS();
    }

    void computeLPS() {
        int m = pattern.size();
        lps = vector<int>(m);

        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    vector<int> search(const vector<T>& txt) {
        int m = pattern.size();
        int n = txt.size();
        vector<int> res;

        int i = 0; // index for txt
        int j = 0; // index for pattern
        while (i < n) {
            if (pattern[j] == txt[i]) {
                j++;
                i++;
            }

            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != txt[i]) {
                if (j != 0) j = lps[j - 1];
                else i = i + 1;
            }
        }

        return res;
    }
};
