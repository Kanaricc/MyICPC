template<class T>
inline void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = 1; if (ch == EOF) return; ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + (ch - '0'); ch = getchar(); } if (f) x = -x;
}