
ll compute_hash1(string const& s) {
    const int p=31; // If including uppercase, use p=53
    const int m=1e9+7;
    ll hash_value = 0;
    ll p_pow=1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

ll compute_hash2(string const& s) {
    const int p=53;
    const int m=INT_MAX;
    ll hash_value = 0;
    ll p_pow=1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

ll compute_hash2(string const& s) {
    const int p=31;
    const int m=1e9+7;
    ll hash_value = 0;
    ll p_pow=1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// If we know max string size (i.e. max power of p), can calculate powers in advance like this:
vector<ll> p_pow(max_str_len);
p_pow[0] = 1;
for (int i = 1; i < (int)p_pow.size(); i++) {
    p_pow[i] = (p_pow[i-1] * p) % m;
}