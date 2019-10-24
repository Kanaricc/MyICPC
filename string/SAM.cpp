//
/*
查询子串是否出现：这显然跑一次，能在自动机上跑完就是出现过。
统计不同子串的数量：自动机上每条不同的路径对应一个不同的子串。定义 \(d(x)\) 为以 x 为起点的路径数目，递推即可。
计算所有不同子串的长度总和：得到上面的 \(d\)。以 x 为起点，每条路径都会让子串总长度增加路径个。依然是递推。
字典序第 k 小子串：当你有路径数了，只需要按照字典序对节点排序，然后像编码一样找。
最小循环移位：指将原字符串首尾相接移位，找到字典序最小的一个。将字符串 \(S\) 断环成链 \(SS\)，然后建立 SAM，贪心找最小直到长度达到 \(|S|\) 即可。
多组子串出现次数：dfs 预处理每个节点的终点集合大小。在自动机上查找串 \(P\) 对应的节点，存在则答案为该节点的终点集合大小；不存在答案为 \(0\).
所有出现位置：遍历树，一旦发现终点直接输出。
*/
#include <map>

struct state
{
    int len, link;
    std::map<char, int> next;
};

const int MAXLEN = 100000;
state st[MAXLEN * 2];
int sz, last;

void sam_init()
{
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
void sam_extend(char c)
{
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c))
    {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1)
    {
        st[cur].link = 0;
    }
    else
    {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
        {
            st[cur].link = q;
        }
        else
        {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q)
            {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}