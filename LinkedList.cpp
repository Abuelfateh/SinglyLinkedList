#include "LinkedList.h"

using namespace Abuelfateh;
using namespace std;

template <typename T>
void LinkedList<T>::_init() {
	head = NULL;
	tail = NULL;
	cur = NULL;
	prev = NULL;
	length = 0;
}

template <typename T>
LinkedList<T>::LinkedList() {
	_init();
}

template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

template <typename T>
int LinkedList<T>::getLength() const {
	return length;
}

template <typename T>
bool LinkedList<T>::isEmpty() {
	return head == NULL;
}

template <typename T>
void LinkedList<T>::toStart() {
	cur = head;
	prev = NULL;
}

template <typename T>
void LinkedList<T>::advance() {
	// check if the cursor is at the end of the list
	if (cur != NULL) {
		prev = cur;
		cur = cur->next;
	}
}

template <typename T>
void LinkedList<T>::goBack() {
	cur = head;
	// special case for 1 element in the list, so we set the cursor to the head
	if (prev == NULL)
		return;

	// another special case for cursor points to the second element in the list
	if (prev == head) {
		prev = NULL;
		return;
	}

	while (cur != NULL) {
		if (cur->next == prev) {
			prev = cur;
			cur = prev->next;
			break;
		}
		cur = cur->next;
	}
}

template <typename T>
bool LinkedList<T>::hasNext() {
	// check first for cursor at the end, to avoid calling next on a null pointer
	return (cur != NULL && cur->next != NULL);
}

template <typename T>
bool LinkedList<T>::hasData() {
	return cur != NULL;
}

template <typename T>
T LinkedList<T>::getData() {
	// make sure not to call data member on a null pointer
	return cur != NULL ? cur->data : NULL;
}

template <typename T>
void LinkedList<T>::clear() {
	while ((head != NULL)) {
		cur = head->next;
		delete head;
		head = cur;
	}
	_init();
}

template <typename T>
void LinkedList<T>::remove() {
	// make sure the cursor points to an element and not at the end of the list
	if (cur != NULL) {
		// special case for cursor points to the head, so we asume that (cur = head);
		if (prev == NULL) {
			head = head->next;
			delete cur;
			cur = head;
		}
		else {
			cur = cur->next;
			delete prev->next;
			prev->next = cur;
		}
	}
}

// here we must add an extra keyword (typename) before the return type,
// and also we have to add the class name and the scope operator before the return type,
// all that to be able to use the inner struct Node in the template class as a return type,
template <typename T> typename
LinkedList<T>::Node * LinkedList<T>::_createNode(const T &data) {
	// here we use nothrow to be able to handle no enough memory error by our self
	Node *tmp = new(nothrow) Node;
	if (!tmp) {
		cout << "\nFailed to insert new Node, no enough memory to be allocated.\n";
		return NULL;
	}
	tmp->data = data;
	tmp->next = NULL;

	return tmp;
}

template <typename T>
void LinkedList<T>::_insertFirstNode(Node *n) {
	head = n;
	tail = n;
	cur = n;
	prev = NULL;
}

template <typename T>
void LinkedList<T>::insertStart(const T &data) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			tmp->next = head;
			head = tmp;
			prev = NULL;
			cur = tmp;
		}

		length++;
	}
}

template <typename T>
void LinkedList<T>::insertEnd(const T &data) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			tail->next = tmp;
			prev = tail;
			tail = tmp;
			cur = tmp;
		}

		length++;
	}
}

template <typename T>
void LinkedList<T>::insertAfter(const T &data) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			// special case for cursor at the end of list
			if (cur == NULL)
				cur = tail;

			tmp->next = cur->next;
			cur->next = tmp;
			prev = cur;
			cur = tmp;
		}

		length++;
	}
}

template <typename T>
void LinkedList<T>::insertBefore(const T &data) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			// special case for cursor at the start of the list
			if (prev == NULL)
				prev = head;
			
			tmp->next = cur;
			prev->next = tmp;
			cur = tmp;
		}

		length++;
	}
}

