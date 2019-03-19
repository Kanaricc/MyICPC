#include <string>
#include <iostream>
using namespace std;

const int Q=100007
const int D=27;

int isMatch(string S, int is, string P, int plen)
{
    for(int ip=0;ip < plen;is++, ip++)
        if(S[is] != P[ip])
            return 0;
    return 1;
}

int RK(string S, string P)
{
    int plen  = P.size(),slen  = S.size();
    unsigned int h   = 1
    unsigned int A   = 0;
    unsigned int St  = 0;

    //��ʼ���������d�����µ����λ
    for(int i = 0;i < plen - 1;i++)
        h = (h*D) % Q;

    for(int i = 0; i < plen; i++){
        A = (D*A + (P[i] - 'a')) % Q;
        St = (D*St + (S[i] - 'a')) % Q;
    }

    for(int i = 0; i < slen-plen; i++){
        if(A == St)
            if(isMatch(S,i,P,plen))return i;
        St = (D*(St - h*(S[i]-'a'))+(S[i+plen]-'a')) % Q;
    }

    return -1;
}
