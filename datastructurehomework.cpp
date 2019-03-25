#include <iostream>
#include <stack>
using namespace std;

struct Node{
    Node *left,*right;
    char chr;
    Node(char chr):chr(chr){}
} *root;

void init(){
    root=new Node('A');
    root->left=new Node('B');
    root->right=new Node('C');
    root->left->left=new Node('D');
    root->left->left->right=new Node('E');

    root->right=new Node('C');
    root->right->left=new Node('F');
    root->right->left->right=new Node('G');
    root->right->right=new Node('H');
    root->right->right->left=new Node('I');
} 

void postorder(Node *node){
    stack<Node *> s;
    if(!node)return;
    s.push(node);
    while(!s.empty()){
        Node *cur=s.top();s.pop();
        if(cur->left)s.push(cur->left);
        if(cur->right)s.push(cur->right);
        cout<<cur->chr<<endl;
    }
}

int main(){
    init();
    postorder(root);
}

