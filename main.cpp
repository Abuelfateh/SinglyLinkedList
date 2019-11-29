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

int main() {
	LinkedList<Student, int> list;

	Student * stArray, *student;
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

	cout << "---------------------------------------------\n"
		<< "ID\tName\n"
		<< "---------------------------------------------\n";
	for (list.toStart(); list.hasData(); list.advance()) {
		student = list.getData();
		cout << student->id << "\t" << student->name << endl;
	}


	// prevent console auto close
	cout << endl;
	system("pause");
	return 0;
}