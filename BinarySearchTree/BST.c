#include <stdio.h>
#include <stdlib.h>

struct BST{
    int val;
    //struct BST * parent;
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

BST * findMin_BST(BST * node){
    BST * current = node;
    while(current->leftchild)
        current = current->leftchild;
    return current;
}

BST * delete_BST(BST * node, int key){
    //BST * deleted_node = search_BST(node, key);
    if(node==NULL) return node;

    if(node->val > key)
        node->leftchild = delete_BST(node->leftchild,key);
    else if(node->val < key)
        node->rightchild = delete_BST(node->rightchild,key);
    //case for node->val == key (the node exact what we need to delete it)
    else{
        //no child -> directly delete the node
        if(node->leftchild == NULL && node->rightchild == NULL){
            free(node);
            return NULL;
        }

        // only one child and is right child which should be returned to higher level recursive
        else if(node->leftchild == NULL){
            BST * temp = node->rightchild;
            free(node);
            return temp;
        }

        //only one child and is left child
        else if(node->rightchild == NULL){
            BST * temp = node->leftchild;
            free(node);
            return temp;
        }

        //both two children are existed. -> use the minimum of right subtree to replace the node
        else {
            BST * temp = findMin_BST(node->rightchild);
            node->val = temp->val;
            delete_BST(node->rightchild,temp->val);
            return node;
        }
    }
}

int main(int argc, char const *argv[])
{
    BST * root = NULL;
    root = insert_BST(root,15);
    root = insert_BST(root,5);
    root = insert_BST(root,3);
    root = insert_BST(root,12);
    root = insert_BST(root,10);
    root = insert_BST(root,13);
    root = insert_BST(root,6);
    root = insert_BST(root,7);
    root = insert_BST(root,16);
    root = insert_BST(root,20);
    root = insert_BST(root,18);
    root = insert_BST(root,23);
    tree_traveral_preorder(root);
    //BST * find = search_BST(root,5);
    //printf("%d",find->val);
    printf("\n");
    root = delete_BST(root,5);
    tree_traveral_preorder(root);
    printf("\n");
    return 0;
}


//https://www.geeksforgeeks.org/deletion-binary-tree/
//https://www.geeksforgeeks.org/bfs-vs-dfs-binary-tree/