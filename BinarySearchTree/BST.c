#include <stdio.h>
#include <stdlib.h>

struct BST{
    int val;
    struct BST * leftchild;
    struct BST * rightchild;
};
typedef struct BST BST;

void tree_traveral_preorder(BST * node){
    if(node){
        printf("%d\t",node->val);//v
        tree_traveral_preorder(node->leftchild);//L
        tree_traveral_preorder(node->rightchild);//R
    }
}

BST * insert_BST(BST * node, int k){
    if(!node){
        //create the leaf of BST till there is no element
        node = malloc(sizeof(BST));
        node->val = k;
        node->leftchild = NULL;
        node->rightchild = NULL;
    }
    else{
        // continue to explore the child of BST
        if(node->val > k)
            node->leftchild = insert_BST(node->leftchild,k);
        else
            node->rightchild = insert_BST(node->rightchild,k);
    }
    return node;
}

BST * search_BST(BST * node, int key){
    BST * current = node;
    while(current){
        if(current->val == key)
            return current;
        else if(current->val > key)
            current = current->leftchild;
        else
            current = current->rightchild;
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    BST * root = NULL;
    root = insert_BST(root,30);
    root = insert_BST(root,40);
    root = insert_BST(root,5);
    root = insert_BST(root,2);
    tree_traveral_preorder(root);
    BST * find = search_BST(root,5);
    printf("%d",find->val);
    return 0;
}
