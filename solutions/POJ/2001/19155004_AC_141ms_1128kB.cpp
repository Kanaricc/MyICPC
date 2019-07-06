#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=1010;
struct Node{
    Node *ch[30];
    int flag;
    int rc;
    Node(){
        for(int i=0;i<30;i++)ch[i]=NULL;
        flag=rc=0;
    }
} *root;

vector<string> inps;
string ans[MAXN];
void build(Node *node,string str,int ptr,int idx){
    node->rc++;
    if(ptr>=str.size()){
        node->flag=idx;
        return;
    }

    if(node->ch[str[ptr]-'a']==NULL)node->ch[str[ptr]-'a']=new Node();
    build(node->ch[str[ptr]-'a'],str,ptr+1,idx);
}

void travel(Node *node,string t){
    //cout<<node->rc<<endl;
    if(node->flag){
        //cout<<inps[node->flag]<<" "<<t<<endl;
        ans[node->flag]=t;
    }
    for(int i=0;i<26;i++){
        if(node->ch[i]!=NULL){
            //cout<<"->"<<char('a'+i)<<"->"<<endl;
            if(node->ch[i]->rc>1 || node->rc>1)travel(node->ch[i],t+char('a'+i));
            else travel(node->ch[i],t);
        }
    }
}
int main(){
    root=new Node();
    string inp;
    inps.push_back("#");
    while(cin>>inp){
        inps.push_back(inp);
        build(root,inp,0,inps.size()-1);
    }
    travel(root,"");
    for(int i=1;i<inps.size();i++){
        cout<<inps[i]<<" "<<ans[i]<<endl;
    }


    return 0;
}
