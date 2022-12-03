bool isPalindrome(string s)
{
    int l=0;
    int h=s.size()-1;
    while (l<h) {
        if(s[l]!=s[h])
            return false;
        l++,h--;
    }
    return true;
}

bool isPalindrome(string s)
{
    string s_tmp=s;
    reverse(s.begin(), s.end());
    return s_tmp==s;
}
