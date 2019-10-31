//如果s的字典序严格小于s的所有后缀的字典序，称s是简单串，或者 Lyndon 串 。

//分解:s=w1w2w3w4..... 分解后 w1>=w2>=w3>=...,该分解唯一
// duval_algorithm
vector<string> duval(string const &s)
{
    int n = s.size(), i = 0;
    vector<string> factorization;
    while (i < n)
    {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j])
        {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
        {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

//基于以上的最小表示法
// smallest_cyclic_string
string min_cyclic_string(string s)
{
    s += s;
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n / 2)
    {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j])
        {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
            i += j - k;
    }
    return s.substr(ans, n / 2);
}