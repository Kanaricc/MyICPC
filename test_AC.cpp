#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAXCHR=512;

struct Node{
    bool flag;
    Node *ch[MAXCHR];
    Node *failed;
    char chr;
    Node(char chr):chr(chr){
        for(int i=0;i<MAXCHR;i++)ch[i]=NULL;
        failed=NULL;
        flag=false;
    }
};

Node root('\0');

void build(Node *node,const string &str,int ptr){
    node->failed=&root;
    if(ptr>=str.size()){
        node->flag=1;
        return;
    }

    if(node->ch[str[ptr]]!=NULL)node->ch[str[ptr]]=new Node(str[ptr]);
    build(node->ch[str[ptr]],str,ptr+1);
}

void genAC(Node *root){
    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        Node *cur=q.front();q.pop();
        for(int i=0;i<MAXCHR;i++){
            if(cur->ch[i]==NULL)continue;
            Node *failed=cur->failed;
            for(;failed!=NULL;failed=failed->failed){
                if(failed->ch[i]->chr==cur->ch[i]->chr){
                    cur->ch[i]->failed=failed->ch[i]->failed;
                    break;
                }
            }
            if(failed==NULL){
                cur->ch[i]->failed=root;
            }
            q.push(cur->ch[i]);
        }
    }
}

int main(){
    int len;
    for(int i=0;i<len;i++){
        string inp;cin>>inp;
        build(&root,inp,0);
    }
    genAC(&root);

    return 0;
}
