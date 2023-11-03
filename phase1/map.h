
using namespace std;
#include<string>
#include<iostream>
#include "mystring.h"

template <class T>
class RedBlackTree {
private:
	// Node creating subclass
	struct Node {
		mystring data;
		Node* left;
		Node* right;
		char colour;
		Node* parent;
        T value;


		Node(mystring data, T value) : data(data),value(value), left(nullptr), right(nullptr), colour('R'), parent(nullptr) {}
	};

	Node* root;
	bool ll; // Left-Left Rotation flag
	bool rr; // Right-Right Rotation flag
	bool lr; // Left-Right Rotation flag
	bool rl; // Right-Left Rotation flag

	// Function to perform Left Rotation
	Node* rotateLeft(Node* node) {
		Node* x = node->right;
		Node* y = x->left;
		x->left = node;
		node->right = y;
		node->parent = x;
		if (y != nullptr)
			y->parent = node;
		return x;
	}

	// Function to perform Right Rotation
	Node* rotateRight(Node* node) {
		Node* x = node->left;
		Node* y = x->right;
		x->right = node;
		node->left = y;
		node->parent = x;
		if (y != nullptr)
			y->parent = node;
		return x;
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
			root->right->parent = root;
			root = rotateLeft(root);
			root->colour = 'B';
			root->left->colour = 'R';
			rl = false;
		} else if (lr) {
			root->left = rotateLeft(root->left);
			root->left->parent = root;
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
	RedBlackTree() : root(nullptr), ll(false), rr(false), lr(false), rl(false) {}

	// Function to insert data into the tree
	void insert(mystring data, T value) {
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


