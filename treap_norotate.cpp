#include <iostream>
using namespace std;
const int MAXN=1000;

struct Node{
    Node *ch[2];
    int key,val,sz;
    Node(int v){
        sz=1;
        val=v;
        key=rand();
        ch[0]=ch[1]=NULL;
    }
    static int size(Node *node){
        return node?node->sz:0;
    }
    inline void tain(){
        sz=1+(ch[0]?ch[0]->sz:0)+(ch[1]?ch[1]->sz:0);
    }

};
Node *root;
typedef pair<Node*,Node*> D;
//merge b into a
Node* merge(Node *a,Node *b){
    if(!a)return b;
    if(!b)return a;
    if(a->key<b->key){
        a->ch[1]=merge(a->ch[1],b);
        a->tain();
        return a;
    }else{
        b->ch[0]=merge(a,b->ch[0]);
        b->tain();
        return b;
    }
}
//split front k.
//D(splited one,rest one)
D split(Node *node,int k){
    if(!node)return D(NULL,NULL);
    D res;
    if(Node::size(node->ch[0])>=k){
        res=split(node->ch[0],k);
        node->ch[0]=res.second;
        node->tain();
        res.second=node;
    }else{
        res=split(node->ch[1],k-Node::size(node->ch[0])-1);
        node->ch[1]=res.first;
        node->tain();
        res.first=node;
    }
    return res;
}
int getrank(Node *node,int v){
    if(node==NULL)return 0;
    return (node->val>=v)?getrank(node->ch[0],v):Node::size(node->ch[0])+1+getrank(node->ch[1],v);
}
inline int getbyrank(int k){
    D x=split(root,k-1);
    D y=split(x.second,1);
    Node *ans=y.first;
    root=merge(merge(x.first,ans),y.second);
    return ans?ans->val:0;
}
inline void insert(int v){
    int k=getrank(root,v);
    D x=split(root,k);
    Node *o=new Node(v);
    root=merge(merge(x.first,o),x.second);
}
void remove(int v){
    int k=getrank(root,v);
    D x=split(root,k);
    D y=split(x.second,1);
    root=merge(x.first,y.second);
}
int main(){
    int op,x;
    while(cin>>op>>x){
        switch(op){
            case 1:insert(x);break;
            case 2:remove(x);break;
            case 3:cout<<getrank(root,x)+1<<endl;break;
            case 4:cout<<getbyrank(x)<<endl;break;
            case 5:cout<<getbyrank(getrank(root,x))<<endl;break;
            case 6:cout<<getbyrank(getrank(root,x+1)+1)<<endl;break;
        }
    }
    return 0;
}
