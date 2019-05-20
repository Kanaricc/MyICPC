#include <iostream>
#include <queue>
using namespace std;

const int MAXN=100;

struct Node{
    Node *ch[2];
    int key;
    int val;
    int isum=0;
    Node *fa;
    int data;//this is just a example.in this, we count the size of subtree.
    bool sign;
    int cnt;
    //return the position of node in self's children, left or right child.
    int pos(Node *node){
        return ch[1]==node;
    }
    Node(int key):key(key){
        ch[0]=ch[1]=NULL;
        fa=NULL;
        cnt=0;
    }
    //Node(){}
    Node(int key,Node *fa):Node(key){
        this->fa=fa;
    }

    void setval(int val){
        this->val=val;
    }
    static int getval(Node *node){
        return node?node->val:0;
    }
    static int getsum(Node *node){
        return node?node->isum:0;
    }

    static int size(Node *node){
        return node?node->data:0;
    }
    static void update(Node *node){
        node->data=Node::size(node->ch[0])+Node::size(node->ch[1])+node->cnt;
        node->isum=Node::getsum(node->ch[0])+Node::getsum(node->ch[1])+Node::getval(node->ch[0])+Node::getval(node->ch[1]);
        cout<<"node "<<node->key<<":"<<node->data<<endl;
        cout<<"node.s "<<node->key<<":"<<node->isum<<endl;
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
    //[l,r]
    void buildseq(int l,int r){
        Node *nl=findpre(l);
        Node *rl=findsuf(r);
        splay(nl,NULL);
        splay(rl,nl);
    }



   //insert a new value at a empty leaf, then splay it. 
    void insert(double key,int val){
        if(root==NULL){
            root=new Node(key);
            root->setval(val);
        }
        //to make sure left child is smaller strictly than its father
        for(Node *node=root;node;node=node->ch[key>=node->key]){
            if(node->key==key){
                //TODO: keys in this tree are unique. maybe it should be improved.
                node->cnt++;
                splay(node,NULL);return;
            }
            if(node->ch[key>=node->key]==NULL){
                node->ch[key>=node->key]=new Node(key,node);
                node->ch[key>=node->key]->setval(val);
            }
        }
    }
    //take the one to root.
    //if it has no left child, just delete it and push its right child.
    //if not, find and splay the biggest child in its left subtree to root's. at this time, this node has no right child absolutely(just calculate it). attach root's right tree to it. well done.
    void erase(int key){
        Node *node=root;
        //find node with this key.
        while(node){
            if(node->key==key)break;
            node=node->ch[key>node->key];
        }
        if(node!=NULL){
            //splay it to root.
            splay(node,NULL);
            if(node->cnt>=2){
                node->cnt--;
                return;
            }
            if(node->ch[0]==NULL){
                //if it has no left child, take it right one to root.
                root=node->ch[1];
                if(root!=NULL)root->fa=NULL;
            }else{

                Node *lc=node->ch[0];
                while(lc->ch[1]!=NULL)lc=lc->ch[1];
                splay(lc,node);root=lc;
                root->fa=NULL;
                lc->ch[1]=node->ch[1];
                if(lc->ch[1]!=NULL)lc->ch[1]->fa=lc;
            }
        }
    }
    int getdata(int key){
        Node *t=root;
        while(t){
            if(t->key==key)break;
            t=t->ch[key>t->key];
        }
        int res=-1;
        if(t!=NULL){
            res=t->isum+t->val;
            splay(t,NULL);
        }
        return res;
    }
    Node* find(int key){
        Node *t=root;
        while(t){
            if(t->key==key)break;
            t=t->ch[key>t->key];
        }
        if(t!=NULL){
            splay(t,NULL);
            return t;
        }
        return NULL;
    }
    Node* findpre(int key){
        Node *t=find(key);
        if(t==NULL)return NULL;
        Node *p=t->ch[0];
        if(p==NULL)return NULL;
        while(p->ch[1]!=NULL)p=p->ch[1];
        splay(p,NULL);
        return p;
    }
    Node* findsuf(int key){
        Node *t=find(key);
        if(t==NULL)return NULL;
        Node *p=t->ch[1];
        if(p==NULL)return NULL;
        while(p->ch[0]!=NULL)p=p->ch[0];
        splay(p,NULL);
        return p;
    }
    Node* findbyrank(int rank){
        Node *t=root;
        while(t!=NULL){
            if(Node::size(t->ch[0])<=rank && rank<=Node::size(t->ch[0])+t->cnt){
                splay(t,NULL);
                return t;
            }
            else if(Node::size(t->ch[0])>=rank)t=t->ch[0];
            else{
                rank-=Node::size(t->ch[0])+t->cnt;
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
int tick=1;
int main(){
    Splay splay;
    /*
    int nlen,mlen;cin>>nlen>>mlen;
    splay.insert(tick,0);
    for(int i=0;i<nlen;i++){
        int t;cin>>t;
        splay.insert(tick*100000,t);
        t++;
    */
    string op;
    int inp;
    //splay.insert(0,0);
    //splay.insert(0x3f3f3f3f,0);
    while(cin>>op>>inp){
        if(op=="i"){
            int val;
            splay.insert(inp,0);
        }
        else if(op=="e")splay.erase(inp);
        else if(op=="frk"){
            Node *res=splay.findbyrank(inp);
            if(res)cout<<res->key<<endl;
            else cout<<"NO"<<endl;
        }
        else if(op=="rk"){
            //to find the bucunzai
            splay.insert(inp,0);
            Node *res=splay.find(inp);
            if(res)cout<<Node::size(res->ch[0])+1<<endl;
            else cout<<"NO"<<endl;
            splay.erase(inp);
        }
        else if(op=="d")splay.print(splay.root);
        else if(op=="fp"){
            //to find the bucunzai
            splay.insert(inp,0);
            cout<<splay.findpre(inp)->key<<endl;
            splay.erase(inp);
        }
        else if(op=="fs"){
            splay.insert(inp,0);
            cout<<splay.findsuf(inp)->key<<endl;
            splay.erase(inp);
        }
        else if(op=="size")cout<<splay.getdata(inp)<<endl;
        else if(op=="ms"){
            int r;cin>>r;
            splay.buildseq(inp,r);
        }
        cout<<"============="<<endl;
    }
    return 0;
}
