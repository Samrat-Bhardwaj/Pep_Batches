class BST {
    

    // height
    public int height(TreeNode root){
        return root==null ? -1 : Math.max(height(root.left),height(root.right))+1;
    }

    // min
    public int min(TreeNode root){
        if(root.left==null) return root.val;

        return min(root.left);
    }

    // max
    public int max(TreeNode root){
        if(root.right==null) return root.val;

        return max(root.right);
    }

    // size 
    public int size(TreeNode root){
        return root==null ? 0 : size(root.left) + size(root.right)+1;
    }

    // create
    public TreeNode create(int[] arr){

    }

    // insert 

    public TreeNode insertIntoBST(TreeNode root, int val) {
        if(root==null) return new TreeNode(val);

        if(root.val<val){
            root.right=insertIntoBST(root.right,val);
        } else {
            root.left=insertIntoBST(root.left,val);
        }

        return root;
    }

    public int rightMost(TreeNode root){
        if(root.right==null) return root.val;

        return rightMost(root.right);
    }

    public int leftMost(TreeNode root){
        if(root.left==null) return root.val;

        return leftMost(root.left);
    }

    public TreeNode deleteNode(TreeNode root, int key) {
        if(root==null) return null;

        if(root.val==key){
            if(root.left==null && root.right==null){
                return null;
            }
            if(root.left!=null){
                // find just larger
                int justSmaller=rightMost(root.left);

                root.val=justSmaller;
                // delete justSmaller 
                root.left=deleteNode(root.left,justSmaller);
            } else {
                // find just smaller 
                int justLarger=leftMost(root.right);
                root.val=justLarger;

                // delete justLarger
                root.right=deleteNode(root.right,justLarger);
            }
        }

        if(root.val<key){
            root.right=deleteNode(root.right,key);
        } else {
            root.left=deleteNode(root.left,key);
        }

        return root;
    }

    public Node inorderSuccessor(Node root,Node x){
        if(root==null) return null;

        if(root.data<=x.data){
            return inorderSuccessor(root.right,x);
        } else {
            Node val=inorderSuccessor(root.left,x);

            if(val==null) return root;
            return val;
        }         
    }

    public Node inorderPredeccessor(Node root, int x){
        if(root==null) return null;

        if(root.data>=x.data){
            return inorderPredeccessor(root.left,x);
        } else {
            Node val=inorderPredeccessor(root.right,x);

            if(val==null) return root;
            return val;
        }
    }

    // pre and succ using Morris traversal ================

    public TreeNode[] inorderPreSucc(TreeNode root, int x){
        TreeNode[] ans=new TreeNode[2]; // index 0-> pre, index 1-> succ;

        TreeNode pred=null;
        TreeNode succ=null;
        TreeNode previous=null;

        TreeNode curr=root;
        

        while(curr!=null){
            if(curr.left!=null){
                int rightMost_node=rightMost(curr.left);

                if(rightMost_node.right==null){ // create thread
                    rightMost_node.right=curr;
                    curr=curr.left;
                } else { // delete thread
                    System.out.println(curr.val);



                    rightMost_node.right=null;
                    

                    if(curr==x){
                        pred=pre;
                    }
                    if(previous==x){
                        succ=curr;
                    }
                    previous=curr;
                    curr=curr.right;
                }
            } else { // through thread;
                System.out.println(curr.val);

                if(curr==x){
                        pred=pre;
                    }
                    if(pre==x){
                        succ=curr;
                    }

                previous=curr;
                curr=curr.right;
            }
        }

        ans[0]=pred;
        ans[1]=succ;

        return ans;
    }

    // O(logn);

    public TreeNode[] inorderPreSucc(TreeNode root, int x){
        TreeNode[] ans=new TreeNode[2]; // index 0-> pre, index 1-> succ;

        TreeNode pred=null;
        TreeNode succ=null;
        TreeNode previous=null;

        TreeNode curr=root;
        
        while(curr!=null){
            if(curr.val<x){
                pred=curr;
                curr=curr.right;
            } else if(curr.val>x){
                succ=curr;
                curr=curr.left;
            } else {
                TreeNode leftMost_node=leftMost(curr.right);

                if(leftMost_node!=null) succ=leftMost_node;

                TreeNode rightMost_node=rightMost(curr.left);

                if(rightMost_node!=null) pred=rightMost_node;
            }
        }

        ans[0]=pred;
        ans[1]=succ;

        return ans;
    }
}