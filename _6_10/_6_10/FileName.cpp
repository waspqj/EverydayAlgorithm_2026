//BM30 二叉搜索树与双向链表
// 按顺序搜索一个二叉搜索树
TreeNode* Convert(TreeNode* pRootOfTree)
{
	// shared_ptr<TreeNode> head = make_shared<TreeNode>(0);
	TreeNode* head = nullptr;
	TreeNode* cur = head;
	stack<TreeNode*> st;
	if (!pRootOfTree) return nullptr;
	st.push(pRootOfTree);
	while (!st.empty())
	{
		auto it = st.top();
		if (it->left == nullptr)
		{
			st.pop();
			if (cur) {
				cur->right = it;
				it->left = cur;
				cur = it;
			}
			else {
				head = it;
				cur = head;
			}
			if (it->right)
			{
				st.push(it->right);
				it->right = nullptr;
			}
		}
		else {
			st.push(it->left);
			it->left = nullptr;
		}
	}
	return head;
}

//BM31 对称的二叉树
bool _isSymmetrical(TreeNode* L, TreeNode* R)
{
	if (!L && !R) return true;
	else if (!L || !R) return false;

	if (L->val != R->val)
		return false;
	if (L->left && R->right && _isSymmetrical(L->left, R->right))
		;
	else if (L->left || R->right)
		return false;
	if (L->right && R->left)
		return _isSymmetrical(L->right, R->left);
	else if (L->right || R->left)
		return false;

	return true;
}
bool isSymmetrical(TreeNode* pRoot)
{
	if (!pRoot) return true;
	return _isSymmetrical(pRoot->left, pRoot->right);
}