#include <iostream>
using namespace std;

const int MAXN=10;

struct Node{
    Node *ch[2];
    int key;
    Node *fa;
    //return the position of node, left or right child.
    int pos(Node *node){
        return ch[1]==node;
    }
    Node(int val):key(val){}
    Node(){}
    Node(int val,Node *fa):key(val),fa(fa){}
}nodes[MAXN];
struct Splay{
    Node *root;
    Splay(){
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
    }
   //insert a new value at a empty leaf, then splay it. 
    void insert(int val){
        if(root==NULL)root=new Node(val);
        //to make sure left child is smaller strictly than its father
        for(Node *node=root;node;node=node->ch[val>=node->key]){
            if(node->key==val){
                //TODO: keys in this tree are unique. maybe it should be improved.
                splay(node,NULL);return;
            }
            if(node->ch[val>=node->key]==NULL)
                node->ch[val>=node->key]=new Node(val,node);
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
    int op,inp;
    while(cin>>op>>inp){
        if(op==1)splay.insert(inp);
        else if(op==2)splay.erase(inp);
        else if(op==3)splay.print(splay.root);
        cout<<"============="<<endl;
    }
    return 0;
}
