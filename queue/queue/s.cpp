#include <iostream>
using namespace std;

class Node {
private:
	int e;
	Node* prev;
	Node* next;
public:
	Node() {
		this->e = e;
		this->prev = prev;
		this->next = next;
	}

	friend class LinkedList;
};
class LinkedList {
private:
	int n;
	Node* header;
	Node* trailer;
public:
	LinkedList();
	int size();
	bool empty();
	void enqueue(const int& e);
	void dequeue();
	void print();
};
LinkedList::LinkedList() {
	n = 0;
	this->header = trailer;
	this->trailer = header;
}
int LinkedList::size() {
	return n;
}
bool LinkedList::empty() {
	return n == 0;
}
void LinkedList::enqueue(const int& e) {
	Node* v = trailer;
	Node* u = v->prev;
	Node* w = new Node;
	w->e = e;
	v->prev = w; w->next = v;
	u->next = w; w->prev = u;
	this->n++;
}
void LinkedList::dequeue() {
	if (empty()) cout << "Empty" << endl;
	cout << header->next->e << endl;
}
int main() {
	int T;
	cin >> T;

	LinkedList list;
	for (int i = 0; i < T; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "size") {
			cout << list.size() << endl;
		}
		else if (cmd == "empty") {
			cout << boolalpha << list.empty() << endl;
		}
		else if (cmd == "enqueue") {
			int e;
			cin >> e;
			list.enqueue(e);
		}
		else if (cmd == "dequeue") {
			list.dequeue();
		}
	}
	return 0;
}