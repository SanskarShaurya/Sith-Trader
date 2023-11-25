
using namespace std;
#include<string>
#include<iostream>
#include "mystring.h"

template <class T>
class RedBlackTree {
public:
	int nodeCount = 0;

	// Node creating subclass
	struct Node {
		mystring data;
		Node* left;
		Node* right;
		char colour;
		Node* parent;
        T value;

		Node () {nodeCount = 0;};
		Node(mystring data, T value) : data(data),value(value), left(nullptr), right(nullptr), colour('R'), parent(nullptr) {}
	};


	Node* root;
	bool ll; // Left-Left Rotation flag
	bool rr; // Right-Right Rotation flag
	bool lr; // Left-Right Rotation flag
	bool rl; // Right-Left Rotation flag

	// Function to perform Left Rotation
	Node* rotateLeft(Node* loc) {
		// if(!loc->right) return;
		if(!loc) return loc;
		Node* q = loc->right;
		if(!q) return loc;
		Node* b = q->left;
		q->left = loc;
		if(loc->parent) if(loc->parent->left == loc) loc->parent->left = q;
		else loc->parent->right = q;
		q->parent = loc->parent;
		loc->parent = q;
		loc->right = b;
		if(b)b->parent = loc;
		if (loc==root) root = q;
		return q;
	}

	// Function to perform Right Rotation
	Node* rotateRight(Node* loc) {
		// if (!loc->left) return;
		if(!loc) return loc;
		Node* p = loc->left;
		if(!p) return loc;
		Node* b = p->right;
		p->right = loc;
		if(loc->parent) if(loc->parent->left == loc) loc->parent->left = p;
		else loc->parent->right = p;
		p->parent = loc->parent;
		loc->parent = p;
		if(b)b->parent = loc;
		loc->left = b;
		if(loc==root) root = p;
		return p;
	}

	// Helper function for insertion
	Node* insertHelp(Node* root, mystring data, T value) {
		bool f = false; // Flag to check RED-RED conflict

		if (root == nullptr)
			return new Node(data, value);
		else if (data < root->data) {
			root->left = insertHelp(root->left, data, value);
			root->left->parent = root;
			if (root != this->root) {
				if (root->colour == 'R' && root->left->colour == 'R')
					f = true;
			}
		} else {
			root->right = insertHelp(root->right, data, value);
			root->right->parent = root;
			if (root != this->root) {
				if (root->colour == 'R' && root->right->colour == 'R')
					f = true;
			}
		}

		// Perform rotations
		if (ll) {
			root = rotateLeft(root);
			root->colour = 'B';
			root->left->colour = 'R';
			ll = false;
		} else if (rr) {
			root = rotateRight(root);
			root->colour = 'B';
			root->right->colour = 'R';
			rr = false;
		} else if (rl) {
			root->right = rotateRight(root->right);
			if(root->right) root->right->parent = root;
			root = rotateLeft(root);
			root->colour = 'B';
			root->left->colour = 'R';
			rl = false;
		} else if (lr) {
			root->left = rotateLeft(root->left);
			if(root->left) root->left->parent = root;
			root = rotateRight(root);
			root->colour = 'B';
			root->right->colour = 'R';
			lr = false;
		}

		// Handle RED-RED conflicts
		if (f) {
			if (root->parent->right == root) {
				if (root->parent->left == nullptr || root->parent->left->colour == 'B') {
					if (root->left != nullptr && root->left->colour == 'R')
						rl = true;
					else if (root->right != nullptr && root->right->colour == 'R')
						ll = true;
				} else {
					root->parent->left->colour = 'B';
					root->colour = 'B';
					if (root->parent != this->root)
						root->parent->colour = 'R';
				}
			} else {
				if (root->parent->right == nullptr || root->parent->right->colour == 'B') {
					if (root->left != nullptr && root->left->colour == 'R')
						rr = true;
					else if (root->right != nullptr && root->right->colour == 'R')
						lr = true;
				} else {
					root->parent->right->colour = 'B';
					root->colour = 'B';
					if (root->parent != this->root)
						root->parent->colour = 'R';
				}
			}
			f = false;
		}
		return root;
	}

	

public:

	Node* successor(Node* current) {
		if (current->right != nullptr){
			current = current->right;
			while(current->left != nullptr){
				current = current->left;
			}
			return current;
		}
		Node* temp = new Node;
		temp = current->parent;
		if(temp == nullptr) return nullptr;
		while(temp != nullptr && current == temp->right){
			current = temp;
			temp = temp->parent;
		}
		return temp;
	}

	bool operator==(RedBlackTree<T>& rhs){
		for(auto i : rhs){
			if(this->search(i.first) != i.second) return false;
		}
		for(auto i : *this){
			if(rhs.search(i.first) != i.second) return false;
		}
		return true;
	}

	// Copy constructor
	RedBlackTree(const RedBlackTree& other) {
		root = copyHelper(other.root);
	}

	// Helper function to copy a node and its children
	Node* copyHelper(Node* node) {
		if (node == nullptr) {
			return nullptr;
		} else {
			Node* newNode = new Node(node->data, node->value);
			newNode->colour = node->colour;
			newNode->left = copyHelper(node->left);
			newNode->right = copyHelper(node->right);
			if (newNode->left != nullptr) {
				newNode->left->parent = newNode;
			}
			if (newNode->right != nullptr) {
				newNode->right->parent = newNode;
			}
			return newNode;
		}
	}
	class iterator
	{
		Node *current;

	public:
		iterator(Node *node) : current(node) {}

		const std::pair<mystring,T> operator*() const { return {current->data,current->value}; }
		iterator &operator++()
		{
			if (current->right != nullptr)
			{
				current = current->right;
				while (current->left != nullptr)
				{
					current = current->left;
				}
			}
			else
			{
				Node *temp = current->parent;
				while (temp != nullptr && current == temp->right)
				{
					current = temp;
					temp = temp->parent;
				}
				current = temp;
			}
			return *this;
		}
		bool operator!=(const iterator &other) { return current != other.current; }
		bool operator!=(const iterator &other) const { return current != other.current; }
   		bool operator==(const iterator &other) const { return current == other.current; }

	};

	iterator begin() const
	{
		Node *node = root;
		if(node) while (node->left != nullptr)
		{
			node = node->left;
		}
		return iterator(node);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}


	RedBlackTree() : root(nullptr), ll(false), rr(false), lr(false), rl(false) {nodeCount=0;}

	// Function to insert data into the tree
	void insert(mystring data, T value) {
		nodeCount++;
		if (root == nullptr) {
			root = new Node(data, value);
			root->colour = 'B';
		} else
			root = insertHelp(root, data, value);
	}

    T& search(mystring data){
        Node* temp = root;
        while(temp != nullptr){
            if(temp->data == data) return temp->value;
            else if(temp->data > data) temp = temp->left;
            else temp = temp->right;
        }
		insert(data,T(0));
		return search(data);
        // return -1;
    }
    bool find(mystring data){
        Node* temp = root;
        while(temp != nullptr){
            if(temp->data == data) return true;
            else if(temp->data > data) temp = temp->left;
            else temp = temp->right;
        }
        return false;
    }

};


