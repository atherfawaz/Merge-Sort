//Merge Sort with Doubly Linked List

#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

/*Forward Declaration*/
template<class T>
class dlist;

template<class T>
class dnode {
	T data;
	dnode<T> * next;
	dnode<T> * prev;
public:
	dnode() { next = prev = nullptr; }
	dnode(T d, dnode* n = nullptr, dnode* p = nullptr) : data(d), next(n), prev(p) {}
	friend class dlist<T>;
};

template <class T>
class dlist {
	dnode<T> head;
	class dlistiterator {
		dnode<T> * curr;
	public:
		friend class dlist;
		dlistiterator(dnode<T>* n = nullptr) {
			curr = n;
		}
		dlistiterator& operator++() {
			if (curr != nullptr)
				curr = curr->next;
			return *this;
		}
		dlistiterator operator++(int) {
			dlistiterator temp = *this;
			curr = curr->next;
			return temp;
		}
		dlistiterator & operator--() {
			if (curr != nullptr)
				curr = curr->prev;
			return *this;
		}
		bool operator!=(const dlistiterator &it) const {
			return (curr != it.curr);
		}
		T& operator*() {
			return curr->data;
		}
	};
public:
	typedef dlistiterator diterator;
	dlist() { 
		head.next = nullptr;
	}
	~dlist() {
		;
		/*
		diterator it(head.next);
		diterator temp = it;
		it++;
		while (it != end())
		{
			delete temp.curr;
			temp = it;
			++it;
		}
		delete temp.curr;
		*/
	}
	void insertatstart(T d) {
		if (head.next == nullptr) {
			dnode<T> * temp = new dnode<T>(d);
			head.next = temp;
		}
		else {
			dnode<T> * temp = new dnode<T>(d);
			temp->prev = nullptr;
			temp->next = head.next;
			head.next = temp;
		}
	}
	void insertafter(dlistiterator it, T d) {
		dnode<T> *newnode = new dnode<T>(d);
		newnode->prev = it.curr;
		newnode->next = it.curr->next;
		it.curr->next->prev = newnode;
		it.curr->next = newnode;
	}
	dlistiterator remove(dlistiterator& it) {
		if (it.curr->prev == nullptr && it.curr->next != nullptr) {
			dnode<T> *toDelete = it.curr;
			it.curr = it.curr->next;
			it.curr->prev = nullptr;
			head.next = it.curr;
			delete toDelete;
			return it;
		}
		else if(it.curr->next == nullptr) {
			delete it.curr;
			it.curr = nullptr;
			return it;
		}
	}
	void insertSorted(T d) {
		dnode <T> *curr, *prev = nullptr;
		curr = head.next;
		while (curr != nullptr && curr->data < d) {
			prev = curr;
			curr = curr->next;
		}
		dnode <T> * t = new dnode<T>(d);
		t->next = curr;
		if (curr == head.next)
			head.next = t;
		else
			prev->next = t;
	}
	bool isEmpty() {
		return (head.next == nullptr);
	}
	void remove(T d) {
		dnode <T> *curr, *prev;
		curr = head;
		while (curr != nullptr && curr->data < d) {
			prev = curr;
			curr = curr->next;
		}
		if (curr != nullptr && curr->data < d) {
			if (curr == head)
				head = head->next;
			else {
				prev->next = curr->next;
				delete curr;
			}
		}
	}
	dlistiterator begin() {
		return dlistiterator(head.next);
	}
	dlistiterator end() {
		return dlistiterator(nullptr);
	}
};
template <typename T>
void mergeLists(dlist<T> L1, dlist<T> L2) {
	dlist<int>::diterator iterator;
	for (iterator = L2.begin(); iterator != L2.end();) {
		L1.insertSorted(*iterator);
		L2.remove(iterator);
	}
	cout << endl << "After merging: ";
	for (iterator = L1.begin(); iterator != L1.end(); ++iterator)
		cout << *iterator << " ";
}

int main() {
	srand(time(NULL));
	dlist <int> L1;
	for (int i = 1; i <= 10; i++) {
		L1.insertSorted(rand() % 10 + 1);
	}
	dlist <int> L2;
	for (int i = 1; i <= 10; i++) {
		L2.insertSorted(rand() % 10 + 1);
	}
	dlist<int>::diterator iterator;
	cout << "L1: ";
	for (iterator = L1.begin(); iterator != L1.end(); ++iterator)
		cout << *iterator << " ";
	cout << endl << "L2: ";
	for (iterator = L2.begin(); iterator != L2.end(); ++iterator)
		cout << *iterator << " ";
	mergeLists(L1, L2);
	_getch();
	return 0;
}
