
class trie
int max_len;
vector<unordered_map<char,int>> t; //t[0]['a']=1  means that e(0,1)='a'.
vector<ll> cnt;
int szT;

public:
trie(int max_len):max_len(max_len){
    szT=0;
    t=vector<unordered_map<char,int>>(max_len);
    cnt=vector<ll>(max_len);
}

void add(const string& s) {
    int len = s.size();
    int v = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i];
        // c key in map t[v] is exist or created here.
        if (t[v][c] == 0) t[v][c] = ++szT;
        v = t[v][c];
    }
    ++cnt[v];
}
int find(const string& s) {
    int len = s.size();
    int v = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i];
        if (t[v][c] == 0) return 0;
        v = t[v][c];
    }
    return cnt[v];
}
};

int main()
{
    ios::sync_with_stdio(0);
    trie t(100000);
    t.add("aviram");
    t.add("aviram");
    t.add("avi");
    cout<<t.find("aviram");
}