#ifndef A_LINKEDLIST_H
#define A_LINKEDLIST_H
#include <iostream>

// constants to select the required function in copy|move
#define LL_START    0x01
#define LL_END	    0x02
#define LL_AFTER	  0x04
#define LL_BEFORE	  0x08
#define LL_ORDERED  0x10
// to be used with insertOrdered
#define LL_ASC			0x11
#define LL_DESC			0x12

namespace Abuelfateh {

	template <typename T, typename K>
	class LinkedList {
	public:
		LinkedList();
		~LinkedList();

		// insert new node at the start of the list,
		// key argument is defined to be used internaly by insertOrdered
		void insertStart(const T &data, K key = NULL);
		// insert new node at the end of the list
		void insertEnd(const T &data);
		// insert new node after the current cursor
		void insertAfter(const T &data);
		// insert new node before the current cursor
		// key argument is defined to be used internaly by insertOrdered
		void insertBefore(const T &data, K key = NULL);
		// insert new node in ordered form
		// generally in ascending order, or LL_DESC to insert in descending order (useful for Stack implementation)
		void insertOrdered(const T &data, const K key, int order = LL_ASC);
		// Short hand to insert after the current position, as it will be the most used case
		void insert(const T &data);
		// check if the list is empty return true
		bool isEmpty();
		// clear the list, make it empty
		void clear();
		// remove the node in current position
		void remove();
		// set the cursor to the first element
		void toStart();
		// advance the cursor forward by one element
		void advance();
		// advance the cursor backward by one element
		void goBack();
		// check if there is next element, to be used in a loop
		bool hasNext();
		// check if there is data in the current element
		bool hasData();
		// move the cursor to specific key
		void toKey(K key);
		// get the data in the current cursor position
		T * getData() const;
		// return current key value
		K getKey() const;
		// get the length of the list
		int getLength() const;
		// Update current data
		void update(const T &data);
		// Copy current data in another LinkedList
		void copy(LinkedList<T, K> &list, K key, int fn = LL_ORDERED, int order = LL_ASC);
		// Move current data in another LinkedList
		void move(LinkedList<T, K> &list, K key, int fn = LL_ORDERED, int order = LL_ASC);
	private:
		struct Node {
			K key;
			T data;
			Node *next;
		} *head, *tail, *cur, *prev;
		int length;

		// private method to reset all control variables
		void _init();
		// create new node, here we separate the creation of the new node to be able to
		// handle memory allocation error once in all insert* functions
		Node *_createNode(const T &data);
		// separate first node creation as it repeated in most insert* functions
		void _insertFirstNode(Node *n);
	};//EOC

}//EONs

#endif // !A_LINKEDLIST_H
