//树状数组
//需要知道输入信息的范围
/*
using ll=long long;
const int MAXN=10;
*/

const int MAXFT=500000;
int ft[MAXFT];
inline int lowbit(int x) {
    return x&-x;
}
inline void ftadd(int pos, int x) {
    while (pos <= MAXN) {
        ft[pos] += x;
        pos += lowbit(pos);
    }
}
inline ll ftget(int pos) {
    ll res = 0;
    while (pos != 0) {
        res += ft[pos];
        pos -= lowbit(pos);
    }
    return res;
}