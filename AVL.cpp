#include <iostream>
#include <algorithm>
using namespace std;
struct Node{
    int data;
    Node *ch[2];
    Node *fa;
    int height;
    Node(){
        height=1;
        data=0;
        ch[0]=ch[1]=NULL;
    }
    Node(int data):data(data){
        height=1;
        ch[0]=ch[1]=NULL;
    }
    int update(){
        int a=0,b=0;
        if(ch[0])a=ch[0]->height;
        if(ch[1])b=ch[1]->height;
        height=max(a,b)+1;
        return height;
    }
    bool isbalance(){
        int a=0,b=0;
        if(ch[0])a=ch[0]->height;
        if(ch[1])b=ch[1]->height;
        return abs(a-b)<=1;
    }
    int initheight(){
        if(ch[0]==NULL && ch[1]==NULL)return 0;
        if(height)return height;
        int a=0,b=0;
        if(ch[0])a=ch[0]->initheight();
        if(ch[1])b=ch[1]->initheight();
        height=max(a,b)+1;
        return height;
    }
    bool pos(Node *node){
        return ch[1]==node;
    }
};
Node *root;
void rotate(Node *node){
    Node *fa=node->fa;
    if(fa==NULL)return;
    int wai=fa->pos(node);
    fa->ch[wai]=node->ch[!wai];
    if(fa->ch[wai]!=NULL)fa->ch[wai]->fa=fa;
    node->ch[!wai]=fa;

    node->fa=fa->fa;
    if(node->fa!=NULL)node->fa->ch[node->fa->pos(fa)]=node;
    else root=node;
    fa->fa=node;
}
bool autorotate(Node *fafa,Node *fa,Node *node){
    if(fafa==NULL)return true;
    node->update();
    fa->update();
    fafa->update();
    if(!fafa->isbalance()){
        int fapos=fafa->pos(fa);
        int pos=fa->pos(node);
        if((fapos^pos)==0){
            rotate(fa);
            fafa->update();
            fa->update();
            if(fa->fa!=NULL)
                return autorotate(fa->fa->fa,fa->fa,fa);
        }else{
            rotate(node);
            fa->update();
            node->update();
            rotate(node);
            fafa->update();
            node->update();
            if(node->fa!=NULL)
                return autorotate(node->fa->fa,node->fa,node);
        }
    }else return autorotate(fafa->fa,fafa,fa);

    return true;
}
void insert(int x,Node *fafa,Node *fa,Node **node){
    if(*node==NULL){
        *node=new Node(x);
        (*node)->fa=fa;
        if(fa==NULL)return;
        fa->update();

        if(fafa==NULL)return;
        autorotate(fafa,fa,*node);
        /*
        if(!fafa->isbalance()){
            int fapos=fafa->pos(fa);
            int pos=fa->pos(*node);
            if((fapos^pos)==0){
                rotate(fa);
                fafa->update();
                fa->update();
            }else{
                rotate(nn);
                fa->update();
                nn->update();
                rotate(nn);
                fafa->update();
                nn->update();
            }
        }
        */
        return;
    }

    if(x<=(*node)->data){
        insert(x,fa,*node,&((*node)->ch[0]));
    }else{
        insert(x,fa,*node,&((*node)->ch[1]));
    }
    if(fa==NULL)return;
    fa->update();
    if(fafa==NULL)return;
    fafa->update();
}
void INSERT(int x){
    if(root==NULL)insert(x,NULL,NULL,&root);
    else{
        if(x<=root->data){
            insert(x,NULL,root,&(root->ch[0]));
        }else{
            insert(x,NULL,root,&(root->ch[1]));
        }
    }
}
void travel(Node *node){
    if(node->ch[0]){
        cout<<node->data<<"->"<<node->ch[0]->data<<endl;
        travel(node->ch[0]);
    }
    if(node->ch[1]){
        cout<<node->data<<"->"<<node->ch[1]->data<<endl;
        travel(node->ch[1]);
    }
}

int main(){
    int len;cin>>len;
    for(int i=0;i<len;i++){
        int x;cin>>x;
        INSERT(x);
    }
    cout<<root->data<<endl;

    return 0;
}

