#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BST{
	struct node{
		int key;
		int height;
		string data;
		node* left;
		node* right;
		node* parent;
	};
	node* root;

	void clear(node* t){
		if (t == NULL)
			return;
		clear(t->left);
		clear(t->right);
		delete t;
		t = NULL;
	}

	node* find(node* t, int k){
		if (t == NULL)
			return NULL;
		if (k == t->key)
			return t;

		if (k < t->key)
			return find(t->left, k);
		return find(t->right, k);
	}

	node* insert(node* t, node* p, int k, string& s){
		if (t == NULL){
			t = new node;
			t->key = k, t->data = s;
			t->left = t->right = NULL;
			t->parent = p;
		}

		else if (k < t->key)
			t->left = insert(t->left, t, k, s);
		else if (k > t->key)
			t->right = insert(t->right, t, k, s);
		return t;
	}

	node* findMin(node* t){
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	node* findMax(node* t){
		if (t == NULL)
			return NULL;
		if (t->right == NULL)
			return t;
		return findMax(t->right);
	}

	node* successor(node* t){
		if (t == NULL || t->right == NULL)
			return NULL;
		return findMin(t->right);
	}

	node* predecessor(node* t){
		if (t == NULL || t->left == NULL)
			return NULL;
		return findMax(t->left);
	}

	node* remove(node* t, int k){
		if (t == NULL)
			return NULL;
		if (k == t->key){
			if (t->left == NULL && t->right == NULL){
				delete t;
				t = NULL;
			}
			else if (t->left == NULL){
				t->right->parent = t->parent;
				node* tmp = t;
				t = t->right;
				delete tmp;
			}
			else if (t->right == NULL){
				t->left->parent = t->parent;
				node* tmp = t;
				t = t->left;
				delete tmp;
			}
			else {
				node* s = successor(t);
				t->key = s->key, t->data = s->data;
				t->right = remove(t->right, t->key);
			}
		}

		else if (k < t->key)
			t->left = remove(t->left, k);
		else if (k > t->key)
			t->right = remove(t->right, k);
		
		return t;
	}

	void inorder(node* t) {
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->key << ":" << t->data << " - ";
		inorder(t->right);
	}

public:
	BST(){
		root = NULL;
	}
	void clear(){
		clear(root);
	}
	node* find(int k){
		return find(root, k);
	}
	void insert(int k, string s){
		root = insert(root, NULL, k, s);
	}
	node* findMin(){
		return findMin(root);
	}
	node* findMax(){
		return findMax(root);
	}
	void remove(int k){
		root = remove(root, k);
	}
	void display() {
		inorder(root);
		cout << endl;
	}
	~BST(){
		clear(root);
	}
};

class AVL{
	
private:
	struct node{
		int key;
		int height;
		string data;
		node* left;
		node* right;
		node* parent;
	};
	node* root;

	void clear(node* t){
		if (t == NULL)
			return;
		clear(t->left);
		clear(t->right);
		delete t;
		t = NULL;
	}

	node* find(node* t, int k){
		if (t == NULL)
			return NULL;
		if (k == t->key)
			return t;

		if (k < t->key)
			return find(t->left, k);
		return find(t->right, k);
	}

	node* rotateRight(node* t){
		node* A = t->left;
		node* B = t;
		node* y = t->left->right;
		node* p = t->parent;
		B->left = y;
		if (y != NULL) y->parent = B;
		A->right = B;
		B->parent = A;

		A->parent = p;
		if (p != NULL && p->right == B) p->right = A;
		else if (p != NULL) p->left = A;

		updateHeight(B);
		updateHeight(A);
		return A;
	}

	node* rotateLeft(node* t){
		node* B = t->right;
		node* A = t;
		node* y = t->right->left;
		node* p = t->parent;
		B->left = A;
		A->parent = B;
		A->right = y;
		if (y != NULL) y->parent = A;

		B->parent = p;
		if (p != NULL && p->right == A) p->right = B;
		else if (p != NULL) p->left = B;

		updateHeight(A);
		updateHeight(B);
		return B;
	}

	int getHeight(node* t){
		return (t == NULL ? -1 : t->height);
	}

	void updateHeight(node* t){
		t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	}

	node* rebalance(node* t){
		if (t == NULL) return NULL;
		updateHeight(t);
		if (getHeight(t->left) >= 2 + getHeight(t->right)){
			if (getHeight(t->left->left) >= getHeight(t->left->right))
				t = rotateRight(t);
			else{
				t->left = rotateLeft(t->left);
				t = rotateRight(t);
			}
		}
		else{
			if (getHeight(t->right) >= 2 + getHeight(t->left)){
				if (getHeight(t->right->right) >= getHeight(t->right->left))
					t = rotateLeft(t);
				else{
					t->right = rotateRight(t->right);
					t = rotateLeft(t);
				}
			}
		}
		return t;
	}

	node* insert(node* t, node* p, int k, string& s){
		if (t == NULL){
			t = new node;
			t->key = k, t->data = s;
			t->left = t->right = NULL;
			t->parent = p;
		}

		else if (k < t->key)
			t->left = insert(t->left, t, k, s);
		else if (k > t->key)
			t->right = insert(t->right, t, k, s);
		t = rebalance(t);
		return t;
	}

	node* remove(node* t, int k){
		if (t == NULL)
			return NULL;
		if (k == t->key){
			if (t->left == NULL && t->right == NULL){
				delete t;
				t = NULL;
			}
			else if (t->left == NULL){
				t->right->parent = t->parent;
				node* tmp = t;
				t = t->right;
				delete tmp;
			}
			else if (t->right == NULL){
				t->left->parent = t->parent;
				node* tmp = t;
				t = t->left;
				delete tmp;
			}
			else {
				node* s = successor(t);
				t->key = s->key, t->data = s->data;
				t->right = remove(t->right, t->key);
			}
		}

		else if (k < t->key)
			t->left = remove(t->left, k);
		else if (k > t->key)
			t->right = remove(t->right, k);
		t = rebalance(t);
		return t;
	}

	node* findMin(node* t){
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	node* findMax(node* t){
		if (t == NULL)
			return NULL;
		if (t->right == NULL)
			return t;
		return findMax(t->right);
	}

	node* successor(node* t){
		if (t == NULL || t->right == NULL)
			return NULL;
		return findMin(t->right);
	}

	node* predecessor(node* t){
		if (t == NULL || t->left == NULL)
			return NULL;
		return findMax(t->left);
	}

	void inorder(node* t) {
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->key << ":" << t->data << " - ";
		inorder(t->right);
	}

public:
	AVL(){
		root = NULL;
	}
	void clear(){
		clear(root);
	}
	node* find(int k){
		return find(root, k);
	}
	void insert(int k, string s){
		root = insert(root, NULL, k, s);
	}
	node* findMin(){
		return findMin(root);
	}
	node* findMax(){
		return findMax(root);
	}
	void remove(int k){
		root = remove(root, k);
	}
	void display() {
		inorder(root);
		cout << endl;
	}
	~AVL(){
		clear(root);
	}
};

int main(){
	AVL t;
	t.insert(20, "hello");
	t.insert(25, "friends");
	t.insert(15, "how");
	t.insert(10, "are");
	t.insert(30, "you");
	t.display();
	t.remove(20);
	t.display();
	t.remove(25);
	t.display();
	t.remove(30);
	t.display();

	return 0;
}