#include<iostream>
#include <vector>

using namespace std;

// BM23 二叉树的前序遍历
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> ret;
    stack<TreeNode*> st;
    if (!root) return ret;
    st.push(root);
    while (!st.empty())
    {
        auto cur = st.top(); st.pop();
        ret.push_back(cur->val);
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
    return ret;
}


//BM24 二叉树的中序遍历
vector<int> inorderTraversal(TreeNode* root)
{
    vector<int> ret;
    stack<TreeNode*> st;
    if (!root) return ret;
    st.push(root);
    if (root->left)
    {
        st.push(root->left);
        root->left = nullptr;
    }
    while (!st.empty())
    {
        auto cur = st.top();
        if (cur->left)
        {
            st.push(cur->left);
            cur->left = nullptr;
        }
        else {
            st.pop();
            ret.push_back(cur->val);
            if (cur->right) st.push(cur->right);
        }
    }
    return ret;
}

//BM25 二叉树的后序遍历

vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> ret;
    stack<TreeNode*> st;
    if (!root) return ret;

    st.push(root);
    if (root->right)
    {
        st.push(root->right);
        root->right = nullptr;
    }
    if (root->left)
    {
        st.push(root->left);
        root->left = nullptr;
    }
    while (!st.empty())
    {
        auto cur = st.top();
        int flag = 0;
        if (cur->right)
        {
            st.push(cur->right);
            cur->right = nullptr;
            flag = 1;
        }
        if (cur->left)
        {
            st.push(cur->left);
            cur->left = nullptr;
            flag = 1;
        }
        if (!flag)
        {
            ret.push_back(cur->val);
            st.pop();
        }
    }
    return ret;
}


//BM26 求二叉树的层序遍历
class Solution {
public:
    vector<vector<int> > _levelOrder(int depth, TreeNode* root)
    {
        if (!root) return ret;
        if (ret.size() < depth)
            ret.emplace_back(vector<int>());

        ret[depth - 1].push_back(root->val);
        _levelOrder(depth + 1, root->left);
        _levelOrder(depth + 1, root->right);
        return ret;
    }

    vector<vector<int> > levelOrder(TreeNode* root)
    {
        return _levelOrder(1, root);
    }
private:
    vector<vector<int>> ret;
};

//BM27 按之字形顺序打印二叉树

vector<vector<int> > Print(TreeNode* pRoot)
{
    vector<vector<int>> ret;
    int depth = 0;
    vector<TreeNode*> cur, next;
    if (!pRoot) return ret;
    cur.push_back(pRoot);

    while (cur.size())
    {
        if (ret.size() <= depth) ret.emplace_back(vector<int>());
        auto it = cur.back();
        ret[depth].push_back(it->val);
        if (depth % 2 == 0)
        {
            if (it->left) next.push_back(it->left);
            if (it->right) next.push_back(it->right);
        }
        else {
            if (it->right) next.push_back(it->right);
            if (it->left) next.push_back(it->left);
        }
        cur.pop_back();
        if (cur.empty())
        {
            cur.swap(next);
            next.clear();
            // for(auto a : cur) cout<< a->val<< " ";
            // cout<< endl;
            ++depth;
        }
    }
    return ret;
}

//BM28 二叉树的最大深度
int maxDepth(TreeNode* root)
{
    int ret = 0;
    if (!root) return ret;
    stack<pair<int, TreeNode*>> st;
    st.emplace(1, root);
    while (!st.empty())
    {
        auto it = st.top(); st.pop();
        ret = max(ret, it.first);
        if (it.second->left) st.emplace(it.first + 1, it.second->left);
        if (it.second->right) st.emplace(it.first + 1, it.second->right);
    }
    return ret;
}