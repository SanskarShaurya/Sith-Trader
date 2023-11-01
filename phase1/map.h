#include <iostream>
#include <vector>
#include <string>
using namespace std;

class mystring
{
public:
    std::string name;
    mystring(const std::string &stockName) : name(stockName){}
    mystring(){}

    // Overload the ">" operator to compare based on name
    bool operator>(const mystring &other) const
    {
        return name.compare(other.name) > 0;
    }
    bool operator<(const mystring& other) const {
        return name.compare(other.name) < 0;
    }
    bool operator!=(const mystring& other) const {
        return name != other.name;
    }
};

template <class T>
class Map {
private:
	Map* iterator(mystring first)
	{
		Map* temp = root;

		while (temp != nullptr &&
			temp->first != first) {

			if (first < temp->first) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return temp;
	}

	const Map* iterator(mystring first) const
	{
		Map* temp = root;
		while (temp != nullptr
			&& temp->first != first) {
			if (first < temp->first) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return temp;
	}
	const int search(mystring first) const
	{
		const Map* temp = iterator(first);
		if (temp != nullptr) {
			return temp->second;
		}
		return 0;
	}

	Map* create(mystring first)
	{
		Map* newnode = (Map*)malloc(sizeof(Map));
		newnode->first = first;
		newnode->second = T();
		newnode->left = nullptr;
		newnode->right = nullptr;
		newnode->par = nullptr;
		newnode->depth = 1;
		return newnode;
	}
	void right_rotation(Map* x)
	{
		Map* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->par = x;
		}
		if (x->par != nullptr && x->par->right == x) {
			x->par->right = y;
		}
		else if (x->par != nullptr && x->par->left == x) {
			x->par->left = y;
		}
		y->par = x->par;
		y->right = x;
		x->par = y;
	}

	void left_rotation(Map* x)
	{
		Map* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->par = x;
		}
		if (x->par != nullptr && x->par->left == x) {
			x->par->left = y;
		}
		else if (x->par != nullptr && x->par->right == x) {
			x->par->right = y;
		}
		y->par = x->par;
		y->left = x;
		x->par = y;
	}

	
	void helper(Map* node)
	{
		if (depthf(node->left)
			- depthf(node->right) > 1) {

			if (depthf(node->left->left)
				> depthf(node->left->right)) {
				node->depth
					= max(depthf(node->right) + 1,
						depthf(node->left->right) + 1);
				node->left->depth
					= max(depthf(node->left->left) + 1,
						depthf(node) + 1);
				right_rotation(node);
			}
			else {
				node->left->depth = max(
					depthf(node->left->left) + 1,
					depthf(node->left->right->left)
					+ 1);
				node->depth
					= max(depthf(node->right) + 1,
					depthf(node->left->right->right) + 1);
				node->left->right->depth
					= max(depthf(node) + 1,
						depthf(node->left) + 1);
				left_rotation(node->left);
				right_rotation(node);
			}
		}
		else if (depthf(node->left)
				- depthf(node->right) < -1) {
			if (depthf(node->right->right)
				> depthf(node->right->left)) {
				node->depth
					= max(depthf(node->left) + 1,
						depthf(node->right->left) + 1);
				node->right->depth
					= max(depthf(node->right->right) + 1,
						depthf(node) + 1);
				left_rotation(node);
			}

			else {
				node->right->depth = max(
					depthf(node->right->right) + 1,
					depthf(node->right->left->right) + 1);
				node->depth = max(
					depthf(node->left) + 1,
					depthf(node->right->left->left) + 1);
				node->right->left->depth
					= max(depthf(node) + 1,
						depthf(node->right) + 1);
				right_rotation(node->right);
				left_rotation(node);
			}
		}
	}

	void balance(Map* node)
	{
		while (node != root) {
			int d = node->depth;
			node = node->par;
			if (node->depth < d + 1) {
				node->depth = d + 1;
			}
			if (node == root
				&& depthf(node->left) 
				- depthf(node->right) > 1) {
				if (depthf(node->left->left)
					> depthf(node->left->right)) {
					root = node->left;
				}
				else {
					root = node->left->right;
				}
				helper(node);
				break;
			}
			else if (node == root
					&& depthf(node->left) 
					- depthf(node->right)
							< -1) {
				if (depthf(node->right->right)
					> depthf(node->right->left)) {
					root = node->right;
				}
				else {
					root = node->right->left;
				}
				helper(node);
				break;
			}
			helper(node);
		}
	}

	int depthf(Map* node)
	{
		if (node == nullptr)

			return 0;
		return node->depth;
	}

	Map* insert(mystring first)
	{
		cnt++;
		Map* newnode = create(first);
		if (root == nullptr) {
			root = newnode;
			return root;
		}
		Map *temp = root, *prev = nullptr;
		while (temp != nullptr) {
			prev = temp;
			if (first < temp->first) {
				temp = temp->left;
			}
			else if (first > temp->first) {
				temp = temp->right;
			}
			else {
				free(newnode);
				cnt--;
				return temp;
			}
		}
		if (first < prev->first) {
			prev->left = newnode;
		}
		else {
			prev->right = newnode;
		}
		newnode->par = prev;
		balance(newnode);
		return newnode;
	}

	
	Map* inorderPredecessor(Map* head)
	{
		if (head == nullptr)
			return head;
		while (head->right != nullptr) {
			head = head->right;
		}
		return head;
	}

	Map* inorderSuccessor(Map* head)
	{
		if (head == nullptr)
			return head;
		while (head->left != nullptr) {
			head = head->left;
		}
		return head;
	}

public:
	static class Map* root;
	static int cnt;

	// "first" is key and "second" is value
	Map *left, *right, *par;
	int depth;
	T second;
    mystring first;

    Map(){
        root = nullptr;
    }

	T& operator[](mystring key) {
		return insert(key)->second;
	}

	const int operator[](mystring key) const
	{
		return search(key);
	}

	int count(mystring first)
	{
		Map* temp = iterator(first);
		if (temp != nullptr) {
			return 1;
		}
		return 0;
	}

	int size(void) {
		return cnt;
	}

	// Removes an element given its key
	void erase(mystring first, Map* temp = root)
	{
		Map* prev = nullptr;
		cnt--;
		while (temp != nullptr &&
			temp->first != first) {
			prev = temp;
			if (first < temp->first) {
				temp = temp->left;
			}
			else if (first > temp->first) {
				temp = temp->right;
			}
		}
		if (temp == nullptr) {
			cnt++;
			return;
		}
		if (cnt == 0 && temp == root) {
			free(temp);
			root = nullptr;
			return;
		}
		Map* l
			= inorderPredecessor(temp->left);
		Map* r
			= inorderSuccessor(temp->right);
		if (l == nullptr && r == nullptr) {
			if (prev == nullptr) {
				root = nullptr;
			}
			else {
				if (prev->left == temp) {
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}
				free(temp);
				balance(prev);
			}
			return;
		}
		Map* start;
		if (l != nullptr) {
			if (l == temp->left) {
				l->right = temp->right;
				if (l->right != nullptr) {
					l->right->par = l;
				}
				start = l;
			}
			else {
				if (l->left != nullptr) {
					l->left->par = l->par;
				}
				start = l->par;
				l->par->right = l->left;
				l->right = temp->right;
				l->par = nullptr;
				if (l->right != nullptr) {
					l->right->par = l;
				}
				l->left = temp->left;
				temp->left->par = l;
			}
			if (prev == nullptr) {
				root = l;
			}
			else {
				if (prev->left == temp) {
					prev->left = l;
					l->par = prev;
				}
				else {
					prev->right = l;
					l->par = prev;
				}
				free(temp);
			}
			balance(start);
			return;
		}
		else {
			if (r == temp->right) {
				r->left = temp->left;
				if (r->left != nullptr) {
					r->left->par = r;
				}
				start = r;
			}
			else {
				if (r->right != nullptr) {
					r->right->par = r->par;
				}
				start = r->par;
				r->par->left = r->right;
				r->left = temp->left;
				r->par = nullptr;
				if (r->left != nullptr) {
					r->left->par = r;
				}
				r->right = temp->right;
				temp->right->par = r;
			}
			if (prev == nullptr) {
				root = r;
			}
			else {
				if (prev->right == temp) {
					prev->right = r;
					r->par = prev;
				}
				else {
					prev->left = r;
					r->par = prev;
				}
				free(temp);
			}
			balance(start);
			return;
		}
	}
	
	// Returns if the map is empty or not
	bool empty(void)
	{
		if (root == nullptr)
			return true;
		return false;
	}
	
	// Given the key of an element it updates
	// the value of the key
	void update(mystring first, T second)
	{
		Map* temp = iterator(first);
		if (temp != nullptr) {
			temp->second = second;
		}
	}


	void clear(void)
	{
		while (root != nullptr) {
			erase(root->first);
		}
	}

	Map* find(mystring first) {
		return iterator(first);
	}

	void insert(mystring first, T second)
	{
		Map* temp = iterator(first);
		if (temp == nullptr) {
			insert(first)->second = second;
		}
		else {
			temp->second = second;
		}
	}
};

template<class T>
Map<T>* Map<T>::root = nullptr;

template<class T>
int Map<T>::cnt = 0;


