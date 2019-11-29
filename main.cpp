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

int main() {
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
		list.insertOrdered(stArray[i], stArray[i].id);
	}

	// Clean the student array, as it now saved in the list
	delete[] stArray;

	printStudentList(list);

	// testing copy
	cout << endl;
	system("pause");
	system("cls");
	// copy the first element
	list.toStart();
	list.copy(cmList, LL_ORDERED, NULL);
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
	list.move(cmList, LL_ORDERED, NULL);
	cout << "Original List\n";
	printStudentList(list);
	cout << endl << "Second List\n";
	printStudentList(cmList);

	// prevent console auto close
	cout << endl;
	system("pause");
	return 0;
}