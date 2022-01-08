#include<iostream>
using namespace std;

class TreeNode{
    TreeNode* left;
    TreeNode* right;

    int val;
    int height;
    int bal;

    public TreeNode(int val){
        this->val=val;
    }
};

void updateHeightBal(TreeNode* root){
    int lh=root->left==nullptr ? -1: root->left->height;
    int rh=root->right==nullptr? -1 : root->right->height;


    root->height=max(lh,rh)+1;

    root->bal=lh-rh;
}

TreeNode* rightRotation(TreeNode* A){
    TreeNode* B=A->left;
    TreeNode* RightofB=B->right;

    B->right=A;
    A->left=RightofB;

    updateHeightBal(A);
    updateHeightBal(B);

    return B;
}

TreeNode* leftRotation(TreeNode* A){
    TreeNode* B=A->right;
    TreeNode* leftOfB=B->left;

    B->left=A;
    A->right=leftOfB;

    updateHeightBal(A);
    updateHeightBal(B);

    return B;
}

TreeNode* rotate(TreeNode* root){ // it will balance the root
    updateHeightBal(root);

    if(root->bal==2){
        if(root->left->bal==1){
            // right rotation
            return rightRotation(root);
        } else {
            // left rotation
            root->left=leftRotation(root->left);
            // right rotation
            return rightRotation(root);
        }
    } else if(root->bal==-2){
        if(root->right->bal==-1){
            //left rotation
            return leftRotation(root);
        } else {
            root->right=rightRotation(root->right);

            return leftRotation(root);
        }
    }
}


TreeNode* insert(TreeNode* root, int val){
    if(root==nullptr){
        return new TreeNode(val);
    }

    if(root->val < val){
        root->right=insert(root->right,val);
    } else {
        root->left = insert(root->left,val);
    }

    return rotate(root);
}


TreeNode* delete_key(TreeNode* root, int val){
    if(root==nullptr){
        return nullptr;
    }

    if(root->val==val){
        if(root->right==nullptr){
            return root->left;
        }

        if(root->left==nullptr){
            return root->right;
        }

        TreeNode* rightMax=rightMost(root->right);

        root->val=rightMax->val;

        root->right=delete_key(root->right,rightMax->val);
    }

    if(root->val<val){
        root->right=delete_key(root->right,val);
    } else {
        root->left=delete_key(root->left,val);
    }

    return rotate(root);
}

TreeNode* rightMost(TreeNode* root){
    while(root->right){
        root=root->right;
    }

    return root;
}

int main(){
    // addition
    // removal
    TreeNode* root=nullptr;
    for(int i=0; i<=100; i++){
        root=insert(i);
    }

    display(root);
}