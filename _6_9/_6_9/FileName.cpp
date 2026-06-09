//BM29 二叉树中和为某一值的路径(一)

bool hasPathSum(TreeNode* root, int sum)
{
    if (!root) return false;
    if (root->left == nullptr && root->right == nullptr)
    {
        if (sum == root->val) return true;
        return false;
    }
    // 这里节点可能为负无法剪枝
    if (root->left && hasPathSum(root->left, sum - root->val))
    {
        return true;
    }
    if (root->right && hasPathSum(root->right, sum - root->val))
    {
        return true;
    }
    return false;
}