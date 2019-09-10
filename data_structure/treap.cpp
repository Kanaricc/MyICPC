#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node{
    int key,rk;
    int data;
    int cnt;
    Node *ch[2];
    Node *fa;
    Node(int key,Node *fa){
        this->key=key;
        this->fa=fa;
        cnt=data=0;
        ch[0]=ch[1]=NULL;
        rk=rand();
    }
    int pos(Node *node){
        return ch[1]==node;
    }
    int getsize(){
        return cnt+data;
    }
    void update(){
        data=0;
        if(ch[0])data+=ch[0]->getsize();
        if(ch[1])data+=ch[1]->getsize();
    }
};

struct Treap{
    Node *root;
    Treap(){
        root=NULL;
    }

    void rotate(Node *node){
        Node *fa=node->fa;
        if(fa==NULL)return;

        int wai=fa->pos(node);
        fa->ch[wai]=node->ch[!wai];
        if(fa->ch[wai]!=NULL) fa->ch[wai]->fa=fa;

        node->ch[!wai]=fa;

        node->fa=fa->fa;
        if(node->fa!=NULL)node->fa->ch[node->fa->pos(fa)]=node;
        else root=node;
        fa->fa=node;

        if(fa)fa->update();
        node->update();
    }

    //this node must be in tree
    void treap(Node *node){
        if(node==NULL)return;
        while(node->fa!=NULL && node->fa->rk<node->rk){
            rotate(node);
        }
    }
    Node* find(int key){
        Node *ptr=root;
        while(ptr!=NULL){
            if(ptr->key==key)return ptr;
            if(ptr->key>key)ptr=ptr->ch[0];
            else ptr=ptr->ch[1];
        }
        return NULL;
    }
    void INSERT(int key){
        if(root==NULL)root=new Node(key,NULL);
        insert(root,key);
        
        Treap::dprint(root);
    }
    void insert(Node *ptr,int key){
        if(ptr->key==key){
            ptr->cnt++;
            treap(ptr);
        }else if(ptr->key>key){
            if(ptr->ch[0]==NULL)ptr->ch[0]=new Node(key,ptr);
            insert(ptr->ch[0],key);
        }else{
            if(ptr->ch[1]==NULL)ptr->ch[1]=new Node(key,ptr);
            insert(ptr->ch[1],key);
        }
        ptr->update();
    }
    Node* findn(int key,bool pre){
        Node *node=find(key);
        Node *fa=node->fa;
        cout<<node->key<<endl;
        Node *left=node->ch[pre^1];
        while(left!=NULL && left->ch[pre]!=NULL)left=left->ch[pre];

        if(fa!=NULL && fa->pos(node)==pre){
            if(left==NULL)return fa;
            else return (left->key>fa->key)==pre?left:fa;
        } else return left;
    }
    static void dprint(Node *node){
        if(!node)return;
        cout<<node->key<<"("<<node->getsize()<<"):";
        if(node->ch[0]){
            cout<<node->ch[0]->key;
        }
        if(node->ch[1]){
            cout<<","<<node->ch[1]->key;
        }
        cout<<endl;
        if(node->ch[0])dprint(node->ch[0]);
        if(node->ch[1])dprint(node->ch[1]);
    }
    int getrank(int key){
        Node *ptr=root;
        //res is the number of node that less than key.
        int res=0;
        while(ptr!=NULL){
            if(ptr->key==key)return res;
            if(ptr->key>key)ptr=ptr->ch[0];
            else{
                if(ptr->ch[1])res+=ptr->ch[1]->getsize();
                res+=ptr->cnt;
                ptr=ptr->ch[1];
            }
        }
        return res+1;
    }
    Node* getbyorder(int order){
        Node *ptr=root;
        while(ptr!=NULL && order>0){
            int temp=0;
            if(ptr->ch[0])temp+=ptr->getsize();
            if(temp+1<=order && order<=temp+ptr->cnt)return ptr;
            if(temp>order){
                order-=temp+ptr->cnt;
                ptr=ptr->ch[1];
            }else{
                ptr=ptr->ch[0];
            }
        }
        return ptr;
    }

};


Treap t;
int main(){
    int kase;cin>>kase;
    while(kase--){
        int op,n;
        cin>>op>>n;
        if(op==1)t.INSERT(n);
        else if(op==2);
        else if(op==3)cout<<t.getrank(n);
        else if(op==4)cout<<t.getbyorder(n)->key<<endl;
        else if(op==5)cout<<t.findn(n,1)->key<<endl;
        else if(op==6)cout<<t.findn(n,0)->key<<endl;
        else if(op==7)Treap::dprint(t.root);
        cout<<"="<<endl;
    }
    return 0;
}

