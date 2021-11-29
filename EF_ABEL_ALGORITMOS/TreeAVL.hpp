#pragma once
#include<functional>

template<class T>
class TreeAVL;
template<class T>
class Node {
private:
	T element;
	Node* left;
	Node* right;
	long high;
	friend class TreeAVL<T>;
public:
	Node(T e) :element(e)
	{
		left = right = nullptr;
		high = 0;
	}
	~Node() { delete left, right; }
};
template<class T>
class TreeAVL {
private:
	Node<T>* foot;
	void (*criteria)(T);
	function<int(T, T)>compare;//PARA INSERTAR
	function<int(T, T)>_lambda;//PARA BUSCAR
	long _high(Node<T>* node)
	{
		if (node == nullptr) return 0;
		return node->high;
	}
	void _rotateRight(Node<T>*& node)
	{
		Node<T>* p = node->left;
		node->left = p->right;
		p->right = node;
		node = p;
	}
	void _rotateLeft(Node<T>*& node)
	{
		Node<T>* p = node->right;
		node->right = p->left;
		p->left = node;
		node = p;
	}
	void _balanced(Node<T>*& node)
	{
		long hleft = _high(node->left);
		long hright = _high(node->right);
		int diff = hright - hleft;
		if (diff > 1)
		{
			long hhleft=_high(node->right->left);
			long hhright=_high(node->right->right);
		    if (hhleft > hhright) {
		    	_rotateRight(node);
		    }
			_rotateLeft(node);
		}
		if (diff < -1) {
			long hhleft = _high(node->left->left);
				long hhright = _high(node->left->right);
			if (hhleft < hhright)
			{
				_rotateLeft(node);
			}
			_rotateRight(node);
		}
		hleft = _high(node->left);
		hright = _high(node->right);
		if (hleft > hright)
			node->high = 1 + hleft;
		else
			node->high = 1 + hright;
	}
	bool _insert(Node<T>*&node,T e)
	{
		if (node == nullptr)
		{
			node = new Node<T>(e);
		}
		else if (compare(e, node->element) == -1)
		{
			return _insert(node->left, e);
		}
		else if (compare(e, node->element) == 1)
		{
			return _insert(node->right, e);
		}
		_balanced(node);
		return true;
	}
	void _inOrder(Node<T>* node) {
		if (node == nullptr) return;
		_inOrder(node->left);
		criteria(node->element);
		_inOrder(node->right);
	}
	void _inOrderHigh(Node<T>* node) {
		if (node == nullptr) return;
		_inOrderHigh(node->left);
		criteria(node->high);
		_inOrderHigh(node->right);
	}
	bool _empty() {
		return foot == nullptr;
	}
	long _size(Node<T>* node)
	{
		if (node == nullptr)
			return 0;
		else
		{
			long sizeL, sizeR;
			sizeL = _size(node->left);
			sizeR = _size(node->right);
			return 1 + sizeL + sizeR;
		}
	}
	long _highTree(Node<T>* node) {
		long highL, highR;
		if (node == nullptr)
			return 0;
		else {
			highL = 1 + _high(node->left);
			highR = 1 + _high(node->right);
			return max(highL, highR);
		}
	}
	bool _search(Node<T>* node, T e)
	{
		if (node == nullptr)
			return false;
		else {
			int r = _lambda(node->element, e);
			if (r == 0)
				return true;
			else
			{
				if (r < 0)
					return _search(node->right, e);
				else
					return _search(node->left, e);
			}
		}
	}
	Node<T>* _minimum(Node<T>* node)
	{
		if (node->left == nullptr)
			return node->element;
		else
			return _minimum(node->left);
	}
	T _maxim(Node<T>* node)
	{
		if (node->left == nullptr)
		{
			return node->element;
		}
		else
			return _maxim(node->right);
	}
	bool _erase(Node<T>*& node, T e)
	{
		if (node == nullptr)//1+Max(If,else)
			return false;//1
		else
		{
			int result = compare(node->element, e);//1+2
			if (result < 0)//1+Max(If,else)
			{
				return _erase(node->right, e);//1+
				//verify if the tree is balanced
				_balanced(node);
			}
			else if (result > 0)//1+Max(If,else)
			{
				return _erase(node->left, e);
				_balanced(node);
			}
			{
				if (node->right == nullptr && node->left == nullptr)//
				{
					node = nullptr;
					delete node;
					return true;
				}
				else if (node->left == nullptr)
				{
					node = node->right;
					return true;
				}
				else {
					Node<T>* aux = node->right;
					while (aux->left != nullptr)
						aux = aux->left;
					node->element = aux->element;
					return _erase(node->right, aux->element);
				}
			}
		}
		_balanced(node);
	}
	function<void(T)>contador;
	void _contar(Node<T>*node) {
		if (node == nullptr) return;
		_contar(node->left);
		contador(node->element);
		_contar(node->right);
	}
	public:
		TreeAVL(void(*newFunction)(T),function<int(T,T)>compare, function<int(T, T)>f)
		{
			foot = nullptr;
			this->criteria = newFunction; 
			this->compare = compare;      
			this->_lambda = f;	           
		}
		~TreeAVL() {}
		bool insert(T e)
		{
			return _insert(foot, e);
		}
		void inOrder() {
			_inOrder(foot);
		}
		long size() {
			return _size(foot);
		}
		long highTree()
		{
			return _highTree(foot);
		}
		bool search(T e)
		{
			return _search(foot, e);
		}
		bool erase(T e) {
			return _erase(foot, e);
		}
		void setLambda(function<void(T)>cont)
		{
			contador = cont;
		}
		void contar() {
			_contar(foot);
		}
		T maxim() {
			return _maxim(foot);
		}
};