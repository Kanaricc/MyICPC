#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
typedef long long ll;

struct Node{
    Node *ch[2];
    int key;
    ll val;
    ll isum=0;
    Node *fa;
    int data;//this is just a example.in this, we count the size of subtree.
    bool sign;
    //return the position of node in self's children, left or right child.
    int pos(Node *node){
        return ch[1]==node;
    }
    Node(int key):key(key){
        ch[0]=ch[1]=NULL;
        fa=NULL;
    }
    //Node(){}
    Node(int key,Node *fa):Node(key){
        this->fa=fa;
    }

    void setval(ll val){
        this->val=val;
    }
    static ll getval(Node *node){
        return node?node->val:0;
    }
    static ll getsum(Node *node){
        return node?node->isum:0;
    }

    static int size(Node *node){
        return node?node->data:0;
    }
    static void update(Node *node){
        node->data=Node::size(node->ch[0])+Node::size(node->ch[1])+1;
        node->isum=Node::getsum(node->ch[0])+Node::getsum(node->ch[1])+Node::getval(node->ch[0])+Node::getval(node->ch[1]);
        //cout<<"node "<<node->key<<":"<<node->data<<endl;
        //cout<<"node.s "<<node->key<<":"<<node->isum<<endl;
    }
    static bool tag(Node *node){
        return node?node->sign:0;
    }
    static bool tag(Node *node,bool val){
        if(node)node->sign=val;
        return tag(node);
    }

};

struct Splay{
    Node *root;
    Splay(){
        root=NULL;
    }
    void rotate(Node *node){
        Node *fa=node->fa;
        if(fa==NULL)return;

        //tag should be pushed down before rotating.
        pushdown(fa);
        pushdown(node);

        int wai=fa->pos(node);
        fa->ch[wai]=node->ch[!wai];
        if(fa->ch[wai]!=NULL) fa->ch[wai]->fa=fa;

        node->ch[!wai]=fa;

        node->fa=fa->fa;
        if(node->fa!=NULL)node->fa->ch[node->fa->pos(fa)]=node;
        else root=node;
        fa->fa=node;

        //update the data.
        Node::update(fa);Node::update(node);
    }
    //splay will rotate node until it becomes target's children.
    void splay(Node *node,Node *target){
        //if node and node'father are all at same position,we rotate p and x in order.
        //if node and node'father are at different position, we rotate x twice.
        while(node->fa!=target){
            Node *fa=node->fa;
            Node *gr=fa->fa;
            if(gr==target)rotate(node);
            else{
                if(gr->pos(fa) ^ fa->pos(node)){
                    rotate(node);rotate(node); //zig-zig
                }else{
                    rotate(fa);rotate(node); //zig-zag
                }
            }
        }
        node->update(node);
    }
    void pushdown(Node *node){
        if(!Node::tag(node))return;
        Node::tag(node->ch[0],Node::tag(node));
        Node::tag(node->ch[1],Node::tag(node));
    }

   //insert a new value at a empty leaf, then splay it. 
    void insert(int key,ll val){
        if(root==NULL){
            root=new Node(key);
            root->setval(val);
            splay(root,NULL);return;
        }
        //to make sure left child is smaller strictly than its father
        for(Node *node=root;node;node=node->ch[key>=node->key]){
            if(node->key==key){
                //TODO: keys in this tree are unique. maybe it should be improved.
                if(node->ch[1]==NULL){
                    node->ch[1]=new Node(key,node);
                    node=node->ch[1];
                    node->setval(val);
                }else{
                    node=node->ch[1];
                    while(node->ch[0]!=NULL){
                        node=node->ch[0];
                    }
                    node->ch[0]=new Node(key,node);
                    node=node->ch[0];
                    node->setval(val);
                }
                splay(node,NULL);return;
            }
            if(node->ch[key>=node->key]==NULL){
                node->ch[key>=node->key]=new Node(key,node);
                node->ch[key>=node->key]->setval(val);
                splay(node,NULL);return;
            }
        }
    }
    Node* findbyrank(int rank){
        Node *t=root;
        while(t!=NULL){
            if(Node::size(t->ch[0])+1==rank){
                splay(t,NULL);
                return t;
            }
            else if(Node::size(t->ch[0])>=rank)t=t->ch[0];
            else{
                rank-=Node::size(t->ch[0])+1;
                t=t->ch[1];
            }
        }
        return NULL;
    }
    void print(Node *node){
        if(node==NULL)return;
        cout<<node->key<<":";
        if(node->ch[0]!=NULL)cout<<node->ch[0]->key;
        cout<<",";
        if(node->ch[1]!=NULL)cout<<node->ch[1]->key;
        cout<<endl;
        print(node->ch[0]);print(node->ch[1]);
    }
};
int main(){
    Splay splay;
    
    int nlen,mlen;cin>>nlen>>mlen;
    splay.insert(0,0);
    for(int i=1;i<=nlen;i++){
        int t;cin>>t;
        splay.insert(i,t);
    }
    for(int i=0;i<mlen;i++){
        int op;cin>>op;
        if(op==0){
            nlen++;
            int r;
            ll t;cin>>r>>t;
            Node *res=splay.findbyrank(r+1);
            int n;
            if(res)n=res->key;
            else n=nlen;
            splay.insert(n,t);
        }else if(op==1){
            int r;cin>>r;
            Node *l=splay.findbyrank(r+1)->ch[0];

            cout<<Node::getsum(l)+Node::getval(l)<<endl;
        }else if(op==3){
            splay.print(splay.root);
        }
    }
    return 0;
}
