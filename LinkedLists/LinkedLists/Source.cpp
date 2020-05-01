#include <iostream>

using namespace std;
class Node{
	int value;
	Node* next;
public:
	Node(){
		value = 0;
		next = NULL;
	}
	Node(int v){
		value = v;
		next = NULL;
	}
	void setVal(int v){ value = v; }
	void setNext(Node* n){ next = n; }
	int getValue(){ return value; }
	Node* getNext(){ return next; }
};
class SSL{
private:
	int val;
	Node* head;
public:
	SSL(){
		val = 0; head = NULL;
	}

	void insert(int v){
		
		Node* n = new Node(v);
		if (head == NULL) { head = n; return; }
		Node* it;
		for (it = head; it != NULL && it->getNext() != NULL; it = it->getNext()){}
		it->setNext(n);
	}
	void insert(int* arr, int ln){
		for (int i = 0; i < ln; ++i) this->insert(arr[i]);
	}
	void print(){
		Node* it;
		for (it = head; it != NULL; it = it->getNext()){ cout << it->getValue() << ' '; }
		cout << endl;
	}
};

int main(){
	SSL list;
	list.insert(10);
	list.insert(12);
	list.print();
	int arr[] = { 1, 2, 3, 4, 5 };
	list.insert(arr, 5);
	list.print();
}