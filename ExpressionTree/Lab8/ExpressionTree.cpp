
#include "ExpressionTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr ){
	this->dataItem = elem;
	this->left = leftPtr;
	this->right = rightPtr;
}

template <typename DataType>
ExprTree<DataType>::ExprTree (){
	this->root = NULL;
}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source){
	this->root = source.root;
	copyHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode *&p) {
	if(p != NULL) {
		p = new ExprTreeNode(p->dataItem, p->left, p->right);
		copyHelper(p->left);
		copyHelper(p->right);
	}
}

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source){
	clear();
	this->root = source.root;
	copyHelper(root);
	if (p != NULL) {
		p = new ExprTreeNode(p->dataItem, p->left, p->right);
		copyHelper(p->left);
		copyHelper(p->right);
	}
}

template <typename DataType>
ExprTree<DataType>::~ExprTree (){
	clear();

}

template <typename DataType>
void ExprTree<DataType>::build (){
	clear();
	buildHelper(root);
}

template <>
inline void ExprTree<float>::buildHelper(ExprTreeNode*& p){
	char ch;
	cin >> ch;
	ExprTreeNode* tempNode = new ExprTreeNode(ch, NULL, NULL);
	if(isdigit(ch)) {
		p = tempNode;
	}else {
		p = tempNode;
		buildHelper(tempNode->left);
		buildHelper(tempNode->right);
	}
}

template<>
inline void ExprTree<bool>::buildHelper(ExprTreeNode*& p) {
	char ch;
	cin >> ch;
	ExprTreeNode* tempNode = new ExprTreeNode(ch, NULL, NULL);
	if(isdigit(ch)) {
		p = tempNode;
	}
	else if(ch == '-') {
		p = tempNode;
		buildHelper(tempNode->left);
	}
	else {
		p = tempNode;
		buildHelper(tempNode->left);
		buildHelper(tempNode->right);
	}
}

template <typename DataType>
void ExprTree<DataType>::expression () const{
	exprHelper(root);
}

template <typename dataType>
void ExprTree<dataType>::exprHelper(ExprTreeNode* p) const{
	if(p != NULL) {
		if (!isdigit(p->dataItem)) {
			cout << "(";
		}
		exprHelper(p->left);
		cout << p->dataItem;
		exprHelper(p->right);
		if(!isdigit(p->dataItem)) {
			cout << ")";
		}
	}
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error){
	return evalHelper(root);
}

template<>
inline float ExprTree<float>::evalHelper(ExprTreeNode* p) const {
	float result = 0.0;
	if(isdigit(p->dataItem)) {
		result = p->dataItem - '0';
	}else {
		switch (p->dataItem) {
		case '*':
			result = evalHelper(p->left) * evalHelper(p->right);
			break;
		case '+':
			result = evalHelper(p->left) + evalHelper(p->right);
			break;
		case '-':
			result = evalHelper(p->left) - evalHelper(p->right);
			break;
		}
	}
	return result;
}

template <>
inline float ExprTree<bool>::evalHelper(ExprTreeNode* p) const {
	float result = 0.0;
	if (isdigit(p->dataItem)) {
		result = p->dataItem - '0';
	} else {
		switch (p->dataItem) {
		case '*':
			if (int(evalHelper(p->left)) == 1 || int(evalHelper(p->right)) == 1) {
				return 1;
			}
			return 0;
		case '+':
			if (int(evalHelper(p->left)) == 1 && int(evalHelper(p->right)) == 1) {
				return 1;
			}
			return 0;
		case '-':
			if (p->left != NULL) {
				if (int(evalHelper(p->left)) == 1) {
					return 0;
				}
			} else {
				if (int(evalHelper(p->right)) == 1) {
					return 0;
				}
			}
			return 1;
		}
	}
}

template <typename DataType>
void ExprTree<DataType>::clear (){
	clearHelper(root);
	this->root = NULL;
}

template<typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode* p) {
	if(p != NULL) {
		clearHelper(p->left);
		clearHelper(p->right);
	}
	delete p;
}

template <typename DataType>
void ExprTree<DataType>::commute(){
	commuteHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p) {
	if(p != NULL) {
		ExprTreeNode* tempNode1 = p->left;
		ExprTreeNode* tempNode2 = p->right;
		commuteHelper(p->left);
		commuteHelper(p->right);
		p->left = tempNode2;
		p->right = tempNode1;
	}
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const{
	return isEquivalentHelper(root, source.root);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x, const ExprTreeNode* y) const {
	if(x == NULL && y == NULL) {
		return true;
	}
	if(x == NULL  || y == NULL) {
		return false;
	}
	if(x->dataItem != y->dataItem) {
		return false;
	}
	if(isEquivalentHelper(y->right, x->right) && isEquivalent(y->left, x->left)) {
		return true;
	}
	return false;
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const{
	if(this->root == NULL) {
		return true;
	}
	return false;
}

#include "show8.cpp"