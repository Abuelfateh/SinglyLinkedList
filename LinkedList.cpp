#include "LinkedList.h"

using namespace Abuelfateh;
using namespace std;

template <typename T, typename K>
void LinkedList<T, K>::_init() {
	head = NULL;
	tail = NULL;
	cur = NULL;
	prev = NULL;
	length = 0;
}

template <typename T, typename K>
LinkedList<T, K>::LinkedList(LLByte defIns) {
	_init();
	defInsert = defIns;
}

template <typename T, typename K>
LinkedList<T, K>::~LinkedList() {
	clear();
}

template <typename T, typename K>
int LinkedList<T, K>::getLength() const {
	return length;
}

template <typename T, typename K>
bool LinkedList<T, K>::isEmpty() {
	return head == NULL;
}

template <typename T, typename K>
void LinkedList<T, K>::toStart() {
	cur = head;
	prev = NULL;
}

template <typename T, typename K>
void LinkedList<T, K>::toEnd() {
	for (toStart(); hasData(); advance());
}

template <typename T, typename K>
void LinkedList<T, K>::advance() {
	// check if the cursor is at the end of the list
	if (cur != NULL) {
		prev = cur;
		cur = cur->next;
	}
}

template <typename T, typename K>
void LinkedList<T, K>::toKey(K key) {
	if (key != NULL) {
		toStart();
		while (cur != NULL && cur->key != key)
			advance();
	}
}

template <typename T, typename K>
void LinkedList<T, K>::goBack() {
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

template <typename T, typename K>
bool LinkedList<T, K>::hasNext() {
	// check first for cursor at the end, to avoid calling next on a null pointer
	return (cur != NULL && cur->next != NULL);
}

template <typename T, typename K>
bool LinkedList<T, K>::hasData() {
	return cur != NULL;
}

template <typename T, typename K>
T * LinkedList<T, K>::getData() const {
	// make sure always get data, even if the cursor at the end of the list
	return cur == NULL ? &tail->data : &cur->data;
}

template <typename T, typename K>
bool LinkedList<T, K>::getData(T &buffer) {
	if (cur != NULL) {
		buffer = cur->data;
		return true;
	}
	return false;
}

template <typename T, typename K>
K LinkedList<T, K>::getKey() const {
	return cur == NULL ? tail->key : cur->key;
}

template <typename T, typename K>
void LinkedList<T, K>::clear() {
	while ((head != NULL)) {
		cur = head->next;
		delete head;
		head = cur;
	}
	_init();
}

template <typename T, typename K>
void LinkedList<T, K>::remove() {
	// make sure the cursor points to an element and not at the end of the list
	if (cur != NULL) {
		if (length == 1) {
			clear();
		}
		// special case for cursor points to the head, so we asume that (cur = head);
		else if (prev == NULL) {
			head = head->next;
			delete cur;
			cur = head;
		}
		// special case for cursor points to the tail
		else if (cur->next == NULL) {
			delete tail;
			prev->next = NULL;
			tail = prev;
			toEnd();
		}
		else {
			cur = cur->next;
			delete prev->next;
			prev->next = cur;
		}
		length--;
	}
}

template <typename T, typename K>
void LinkedList<T, K>::update(const T &data) {
	if (cur != NULL)
		cur->data = data;
	// Update the tail if the cursor points to the end of the list
	else if (head != NULL)
		tail->data = data;
}

// here we must add an extra keyword (typename) before the return type,
// and also we have to add the class name and the scope operator before the return type,
// all that to be able to use the inner struct Node in the template class as a return type,
template <typename T, typename K> typename
LinkedList<T, K>::Node * LinkedList<T, K>::_createNode(const T &data) {
	// here we use nothrow to be able to handle no enough memory error by our self
	Node *tmp = new(nothrow) Node;
	if (!tmp) {
		cout << "\nFailed to insert new Node, no enough memory to be allocated.\n";
		return NULL;
	}
	tmp->key = NULL;
	tmp->data = data;
	tmp->next = NULL;
	length++;
	return tmp;
}

template <typename T, typename K>
void LinkedList<T, K>::_insertFirstNode(Node *n) {
	head = n;
	tail = n;
	cur = n;
	prev = NULL;
}

template <typename T, typename K>
void LinkedList<T, K>::insertStart(const T &data, K key) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		tmp->key = key;
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			tmp->next = head;
			head = tmp;
			prev = NULL;
			cur = head;
		}
	}
}

template <typename T, typename K>
void LinkedList<T, K>::insertEnd(const T &data) {
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
	}
}

template <typename T, typename K>
void LinkedList<T, K>::insertAfter(const T &data) {
	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			// special case for cursor at the end of list
			if (cur == NULL) {
				tail->next = tmp;
				prev = tail;
				cur = tmp;
				tail = tmp;
			}
			else {
				prev = cur;
				tmp->next = cur->next;
				cur->next = tmp;
				cur = tmp;
				// keep track of the list tail
				if (cur->next == NULL)
					tail = cur;
			}
		}
	}
}

template <typename T, typename K>
void LinkedList<T, K>::insertBefore(const T &data, K key) {
	// special case for cursor at the start of the list
	if (prev == NULL && head != NULL) {
		insertStart(data, key);
		return;
	}

	Node *tmp = _createNode(data);
	if (tmp != NULL) {
		tmp->key = key;
		if (head == NULL) {
			_insertFirstNode(tmp);
		}
		else {
			tmp->next = cur;
			prev->next = tmp;
			cur = tmp;
		}
	}
}

template <typename T, typename K>
void LinkedList<T, K>::insertOrdered(const T &data, const K key, LLByte order) {
	// don't create a new node unless it is the first node,
	// as we will let this on insertBefore
	if (head == NULL) {
		Node *tmp = _createNode(data);
		if (tmp != NULL) {
			tmp->key = key;
			_insertFirstNode(tmp);
		}
	}
	else {
		// set the cursor on the first greater element in the list
		for (toStart(); hasData() && (order == ASC ? (cur->key < key) : (cur->key > key)); advance());

		// Another way to do the loop using while
		//toStart();
		//while ((hasData() && (cur->data < data)))
		//	advance();

		// insert before the greater element
		insertBefore(data, key);
	}
}

template <typename T, typename K>
void LinkedList<T, K>::insert(const T &data, K key, LLByte order) {
	switch (defInsert) {
		case START:
			insertStart(data);
			break;
		case END:
			insertEnd(data);
			break;
		case ORDERED:
			insertOrdered(data, key, order);
			break;
		case BEFORE:
			insertBefore(data);
			break;
		case AFTER:
		default:
			insertAfter(data);
			break;
	}
}

template <typename T, typename K>
void LinkedList<T, K>::reverse() {
	Node *tmp;
	// if we have only two nodes, then swap head and tail pointers
	if (length == 2) {
		tail = head;
		head = tail->next;
		head->next = tail;
		tail->next = NULL;
	}
	else if (length > 2) {
		// move the cursor to the start
		toStart();
		// set the cursor to the second node in the list
		advance();
		// this condition will pass if there is more than two nodes in the list
		// so, this loop will run at least twice if there is three nodes in the list
		do {
			// catch the next node after the current position
			tmp = cur->next;
			// reverse the pointer to the previous node
			cur->next = prev;
			// handle control variables to the next itteration
			prev = cur;
			cur = tmp;
		} while (cur != NULL);
		// reverse the tail pointer, and set the head to last non null pointer
		tail = head;
		head = prev;
		// make sure the tail ends with null
		tail->next = NULL;
	}
	// set the cursor position at the start of the list
	toStart();
}

template <typename T, typename K>
void LinkedList<T, K>::copy(LinkedList<T, K> &list, K key, int fn, LLByte order) {
	if (cur != NULL) {
		switch (fn) {
			case START:
				list.insertStart(cur->data, NULL);
				break;
			case END:
				list.insertEnd(cur->data);
				break;
			case AFTER:
				list.insertAfter(cur->data);
				break;
			case BEFORE:
				list.insertBefore(cur->data, NULL);
				break;
			case ORDERED:
				list.insertOrdered(cur->data, key, order);
				break;
		}
		list.toKey(key);
	}
}

template <typename T, typename K>
void LinkedList<T, K>::move(LinkedList<T, K> &list, K key, int fn, LLByte order) {
	toKey(key);
	if (cur != NULL) {
		// first we copy current node data to the new list
		copy(list, key, fn, order);
		// then, delete current node, as it was copied to the new list
		remove();
	}
}