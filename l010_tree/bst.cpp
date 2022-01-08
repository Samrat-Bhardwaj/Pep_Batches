#include<iostream>
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  }

TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr) return new TreeNode(val);

        if(root->val<val){
            root->right=insertIntoBST(root->right,val);
        } else {
            root->left=insertIntoBST(root->left,val);
        }

        return root;
    }


Node* leftMost(Node* root){
        if(root->left==nullptr){
            return root;
        }
        
        return leftMost(root->left);
    }
    
    Node * inOrderSuccessor(Node *root, Node *x)
    {
        if(root==nullptr) return NULL;
        
        if(root->data==x->data){
            if(root->right!=nullptr) return leftMost(root->right);
            
            return nullptr;
        }
        
        if(root->data<x->data){
            return inOrderSuccessor(root->right,x);
        } else {
            Node* val=inOrderSuccessor(root->left,x);
            
            if(val==nullptr){
                return root;
            }
            
            return val;
        }
    }


// leet 1038 ========================================= 
void helper(TreeNode* root, int& sum){
    if(!root) return;

    helper(root->right,sum);
    
    sum+=root->val;

    root->val=sum;
    
    helper(root->left,sum);
}

TreeNode* bstToGst(TreeNode* root) {
    int sum=0;
    helper(root,sum);
    return root;
}


// leet 1305 ========================== 
void getInorder(TreeNode* root,vector<int>& arr){
    if(!root) return;

    getInorder(root->left,arr);

    arr.push_back(root->val);

    getInorder(root->right,arr);
}

vector<int> mergeTwoSortedArrays(vector<int>& arr1, vector<int>& arr2){
    int i=0;
    int j=0;

    int n=arr1.size();
    int m=arr2.size();

    vector<int> ans(n+m,0);
    int k=0;

    while(i<n && j<m){
        if(arr1[i]<=arr2[j]){
            ans[k++]=arr1[i++];
        } else {
            ans[k++]=arr2[j++];
        }
    }

    while(i<n){
        ans[k++]=arr1[i++];
    }

    while(j<m){
        ans[k++]=arr2[j++];
    }

    return ans;
}

vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    vector<int> arr1;
    vector<int> arr2;

    getInorder(root1,arr1);
    getInorder(root2,arr2);

    // merge two sorted arrays
    return mergeTwoSortedArrays(arr1,arr2);
}

// leet 669 =============================== 

TreeNode* trimBST(TreeNode* root, int low, int high) {
    if(!root) return nullptr;


    if(root->val<low){
        return trimBST(root->right,low,high);
    }

    if(root->val>high){
        return trimBST(root->left,low,high);
    }

    root->left=trimBST(root->left,low,high);
    root->right=trimBST(root->right,low,high);

    return root;
}

// leet 230 ================================================= 
void pushAllLeft(stack<TreeNode*>& st, TreeNode* root){
    while(root){
        st.push(root);
        root=root->left;
    }
}

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st;

    pushAllLeft(st,root);

    while(st.size()!=0){
        TreeNode* t=st.top(); st.pop();
        k--;
        if(k==0) return t->val;

        if(t->right){
            pushAllLeft(st,t->right);
        }
    }

    return -1;
}

// recursively 
void dfs(TreeNode* root, int& k, int& ans){
    if(!root) return;

    dfs(root->left,k,ans);

    k--;
    if(k==0){
        ans=root->val;
    }

    dfs(root->right,k,ans);
}

int kthSmallest(TreeNode* root, int k) {
    int ans=-1;
    void dfs(root,k,ans);
    return ans;
}

// leet 1382 ========================================= 
vector<int> height;
void updateHeight(TreeNode* root){
    int lh=root->left==nullptr ? -1 : height[root->left->val];
    int rh=root->right==nullptr ? -1 : height[root->right->val];

    height[root->val]=max(lh,rh)+1;
}

int getBal(TreeNode* root){
    int lh=root->left==nullptr ? -1 : height[root->left->val];
    int rh=root->right==nullptr ? -1 : height[root->right->val];

    return lh-rh;
}

TreeNode* rightRotation(TreeNode* A){
    TreeNode* B=A->left;
    TreeNode* RightofB=B->right;

    B->right=A;
    A->left=RightofB;

    B->right=rotate(A);

    return rotate(B);
}

TreeNode* leftRotation(TreeNode* A){
    TreeNode* B=A->right;
    TreeNode* leftOfB=B->left;

    B->left=A;
    A->right=leftOfB;

    B->left=rotate(A);
    return rotate(B);
}

TreeNode* rotate(TreeNode* root){ // it will balance the root
    updateHeight(root);

    if(getBal(root)>=2){
        if(getBal(root->left)>=1){
            // right rotation
            return rightRotation(root);
        } else {
            // left rotation
            root->left=leftRotation(root->left);
            // right rotation
            return rightRotation(root);
        }
    } else if(getBal(root)<=-2){
        if(getBal(root->right)<=-1){
            //left rotation
            return leftRotation(root);
        } else {
            root->right=rightRotation(root->right);

            return leftRotation(root);
        }
    }
}

TreeNode* constructTree(TreeNode* root){
    if(!root) return nullptr;

    root->left=constructTree(root->left);
    root->right=constructTree(root->right);

    return rotate(root);
}


TreeNode* balanceBST(TreeNode* root) {
    height.resize((int)(1e5+1),-1);

    return constructTree(root);
}