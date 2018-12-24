#include <iostream>

class BinaryTreeNode{
    char data;
    BinaryTreeNode * leftchild;
    BinaryTreeNode * rightchild;
public:
    BinaryTreeNode() : data('x'), leftchild(0), rightchild(0) {};
    BinaryTreeNode(char x) : data(x), leftchild(0), rightchild(0) {};
    BinaryTreeNode * get_left(){return this->leftchild;};
    BinaryTreeNode * get_right(){return this->rightchild;};
    void PrintNode();
    void InsertLeft(char);
    void InsertRight(char);
    void InorderTraverse(BinaryTreeNode*);  //LVR
    //void PreorderTraverse(BinaryTreeNode*); //VLR
    //void PostorderTraverse(BinaryTreeNode*);//LRV
};

void BinaryTreeNode::PrintNode(){
    std::cout << data << "\n";
}

void BinaryTreeNode::InsertLeft(char key){
    BinaryTreeNode * lchild;
    lchild = new BinaryTreeNode;
    lchild->data = key;
    lchild->leftchild = NULL;
    lchild->rightchild = NULL;
    this->leftchild = lchild;
}

void BinaryTreeNode::InsertRight(char key){
    BinaryTreeNode * rchild;
    rchild = new BinaryTreeNode;
    rchild->data = key;
    rchild->leftchild = NULL;
    rchild->rightchild = NULL;
    this->rightchild = rchild;
}

void BinaryTreeNode::InorderTraverse(BinaryTreeNode*){
    if(this){
        this->InorderTraverse(this->leftchild);//l
        std::cout << this->data << "\t";//v
        this->InorderTraverse(this->rightchild);//r
    }
}

int main(){

    //construct the binary tree
    BinaryTreeNode * root;
    BinaryTreeNode temp('+');
    root = &temp;
    root->InsertRight('E');
    root->InsertLeft('*');
    root->get_left()->InsertLeft('*');
    root->get_left()->InsertRight('D');
    root->get_left()->get_left()->InsertLeft('/');
    root->get_left()->get_left()->InsertRight('C');
    root->get_left()->get_left()->get_left()->InsertLeft('A');
    root->get_left()->get_left()->get_left()->InsertRight('B');

    root->InorderTraverse(root);
}