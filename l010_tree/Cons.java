class Cons {
    public class TreeNode {
      int val;
      TreeNode left;
      TreeNode right;
      TreeNode() {}
      TreeNode(int val) { this.val = val; }
      TreeNode(int val, TreeNode left, TreeNode right) {
          this.val = val;
          this.left = left;
          this.right = right;
      }
 }


    // leet 105 ======================================================= 

    public TreeNode construct(int[] pre, int psi, int pei, int[] in, int isi, int iei){
        if(psi==pei){
            return new TreeNode(pre[psi]);
        }

        if(psi>pei){
            return null;
        }

        TreeNode root=new TreeNode(pre[psi]);


        int find_ele=pre[psi];

        int idx=isi;

        while(in[idx]!=find_ele){
            idx++;
        }

        int left_ele=idx-isi;

        root.left=construct(pre,psi+1,psi+left_ele,in,isi,idx-1);
        root.right=construct(pre,psi+left_ele+1,pei,in,idx+1,iei);

        return root;
    }


    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return construct(preorder,0,preorder.length-1,inorder,0,inorder.length-1);
    }


    // leet 106 ============================================== 

    public TreeNode construct2(int[] post, int psi, int pei, int[] in, int isi, int iei){
        if(psi>pei) return null;

        TreeNode root=new TreeNode(post[pei]);


        int idx=isi;
        int find_ele=post[pei];

        while(in[idx]!=find_ele){
            idx++;
        }        

        int left_ele=idx-isi;

        root.left=construct2(post,psi,psi+left_ele-1,in,isi,idx-1);
        root.right=construct2(post,psi+left_ele,pei-1,in,idx+1,iei);

        return root;
    }

    public TreeNode buildTree(int[] inorder, int[] postorder) {
        return construct2(postorder,0,postorder.length-1,inorder,0,inorder.length-1);
    }


    // leet 108

    public TreeNode construct3(int[] nums, int si, int ei){
        if(si>ei) return null;        

        int mid=(si+ei)/2;

        TreeNode root=new TreeNode(nums[mid]);

        root.left=construct3(nums,si,mid-1);
        root.right=construct3(nums,mid+1,ei);

        return root;
    }
    public TreeNode sortedArrayToBST(int[] nums) {
        return construct3(nums,0,nums.length-1);
    }


    // leet 1008

    public TreeNode construct4(int[] pre, int si, int ei){
        if(si>ei) return null;
        
        TreeNode root=new TreeNode(pre[si]);

        int idx=si+1;
        while(idx<pre.length && pre[idx]<pre[si]){
            idx++;
        }

        root.left=construct4(pre,si+1,idx-1);
        root.right=construct4(pre,idx,ei);
        
        return root;
    }

    public TreeNode bstFromPreorder(int[] preorder) {
        return construct4(preorder,0,preorder.length-1);    
    }


    // optimized version ==========
    public TreeNode construct5(int[] pre, int lower_limit, int upper_limit, int[] idx){
        int i=idx[0];
        if(i>=pre.length || pre[i]<lower_limit || pre[i]>upper_limit) return null;

        TreeNode root=new TreeNode(pre[i]);
        idx[0]++;

        root.left=construct5(pre,lower_limit,pre[i],idx);
        root.right=construct5(pre,pre[i],upper_limit,idx);

        return root;
    }

    public TreeNode bstFromPreorder(int[] preorder) {
        int[] idx=new int[1];
        return construct5(preorder,Integer.MIN_VALUE, Integer.MAX_VALUE,idx);    
    }


    // leet 449 ===================================================== 

    public class Codec {
    public void getPre(TreeNode root, StringBuilder sb){
        if(root==null) return;

        sb.append(root.val);
        sb.append(" ");

        getPre(root.left);
        getPre(root.right);

    }
    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        StringBuilder sb=new StringBuilder();

        getPre(root,sb);

        return sb.toString();
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if(data.equals("")) return null;

        String[] arr=data.split(" ");

        int[] preorder=new int[arr.length];

        for(int i=0; i<arr.length; i++){
            preorder[i]=Integer.parseInt(arr[i]);
        }

        return bstFromPreorder(preorder);        
    }
}

// leet 297 ========================================

public class Codec {

    public void getPre(TreeNode root, StringBuilder sb){
        if(root==null){
            sb.append("% ");
            return;
        }

        sb.append(root.val+" ");

        getPre(root.left,sb);
        getPre(root.right,sb);
    }

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        StringBuilder sb=new StringBuilder();

        getPre(root,sb);

        return sb.toString();
    }

    // Decodes your encoded data to tree.
    public TreeNode makeTree(String[] arr, int[] idx){
        int i=idx[0];
        if(arr[i]=="%"){
            idx[0]++;
            return null;
        }

        int rv=Integer.parseInt(arr[i]);
        TreeNode root=new TreeNode(rv);
        idx[0]++;

        root.left=makeTree(arr,idx);
        root.right=makeTree(arr,idx);

        return root;
    }
    public TreeNode deserialize(String data) {
        if(data.equals("")) return null;

        String[] arr=data.split(" ");

        return makeTree(arr,new int[1]);
    }
}

}