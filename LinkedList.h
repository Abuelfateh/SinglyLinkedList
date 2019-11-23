#ifndef A_LINKEDLIST_H
#define A_LINKEDLIST_H
#include <iostream>

namespace Abuelfateh {

	template <typename T>
	class LinkedList {
	public:
		LinkedList();
		~LinkedList();

		// insert new node at the start of the list
		void insertStart(const T &data);
		// insert new node at the end of the list
		void insertEnd(const T &data);
		// insert new node after the current cursor
		void insertAfter(const T &data);
		// insert new node before the current cursor
		void insertBefore(const T &data);
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
		// get the data in the current cursor position
		T getData();
		// get the length of the list
		int getLength() const;
	private:
		struct Node {
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
