#include "LinkedList.h"
// include the template class implementation here to avoid link errors
#include "LinkedList.cpp"
#include <string>


using namespace std;
using namespace Abuelfateh;

struct Student {
	int id;
	string name;
};

void printStudentList(LinkedList<Student, int> &list) {
	Student *student;
	cout << "---------------------------------------------\n"
		<< "ID\tName\n"
		<< "---------------------------------------------\n";
	for (list.toStart(); list.hasData(); list.advance()) {
		student = list.getData();
		cout << student->id << "\t" << student->name << endl;
	}
}

void reOrderList_EvenOdd(LinkedList<int, int> &list) {
	int
		// to hold the data
		buffer, tmpBuffer,
		// to loop on the list until it all sorted in the required order
		i, len = list.getLength(),
		// to keep the order of the list
		oddPos = 0, tmpPos;
	// to stop the outer loop when the list is sorted in the required order
	bool listHasChanged = true;
	// loop until the list is not sorted
	for (i = 0; listHasChanged && i < len; i++) {
		listHasChanged = false;

		for (list.toStart(); list.hasData(); list.advance()) {
			list.getData(buffer);
			// chack for odd number, same as (buffer % 2 != 0) but faster
			if (buffer & 1) {
				// remove the current node from the list
				list.remove();
				// find the next odd number
				for (list.toStart(), tmpPos = 0; list.hasData(); list.advance()) {
					list.getData(tmpBuffer);
					if (tmpBuffer & 1) {
						// if the next odd is in position after the removed node
						if (tmpPos == oddPos) {
							listHasChanged = true;
							break;
						}
						// keep track of the tmp position
						tmpPos++;
					}
				}
				// set the position to the next odd node
				oddPos++;

				// using insertEnd will keep the order of the odd numbers
				list.insertEnd(buffer);
			}
		}
	}
}

int main() {
	// testing Even-Odd order function
	LinkedList<int, int> ev_od_list;
	int d;

	ev_od_list.insertEnd(4);
	ev_od_list.insertEnd(3);
	ev_od_list.insertEnd(13);
	ev_od_list.insertEnd(2);
	ev_od_list.insertEnd(8);
	ev_od_list.insertEnd(18);
	ev_od_list.insertEnd(1);
	ev_od_list.insertEnd(6);
	ev_od_list.insertEnd(5);
	ev_od_list.insertEnd(9);


	cout << "Original List:" << endl;
	for (ev_od_list.toStart(); ev_od_list.hasData(); ev_od_list.advance()) {
		ev_od_list.getData(d);
		cout << d << " ";
	}
	cout << endl << endl << "Oredered Even-Odd list:" << endl;
	reOrderList_EvenOdd(ev_od_list);
	for (ev_od_list.toStart(); ev_od_list.hasData(); ev_od_list.advance()) {
		ev_od_list.getData(d);
		cout << d << " ";
	}
	system("pause");
	system("cls");


	LinkedList<Student, int> list, cmList;

	Student * stArray;
	int i, size;

	cout << "Please enter the number of students to be added to the list: ";
	cin >> size;

	stArray = new Student[size];

	for (i = 0; i < size; i++) {
		cout << "Enter student id: ";
		cin >> stArray[i].id;
		cout << "Enter student name: ";
		cin >> stArray[i].name;

		cout << endl;
		// consider student id as the key
		list.insertOrdered(stArray[i], stArray[i].id, ASC);
	}

	// Clean the student array, as it now saved in the list
	delete[] stArray;

	printStudentList(list);

	cout << endl << endl << "Reversed order:" << endl;
	list.reverse();
	printStudentList(list);

	// testing copy
	cout << endl;
	system("pause");
	system("cls");
	// copy the first element
	list.toStart();
	list.copy(cmList, NULL, ORDERED, ASC);
	cout << "Original List\n";
	printStudentList(list);
	cout << endl << "Second List\n";
	printStudentList(cmList);

	// testing move
	system("pause");
	system("cls");
	// move the second element
	list.toStart();
	list.advance();
	list.move(cmList, NULL, ORDERED, ASC);
	cout << "Original List\n";
	printStudentList(list);
	cout << endl << "Second List\n";
	printStudentList(cmList);

	// prevent console auto close
	cout << endl;
	system("pause");
	return 0;
}