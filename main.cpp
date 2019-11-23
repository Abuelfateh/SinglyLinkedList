#include "LinkedList.h"
// include the template class implementation here to avoid link errors
#include "LinkedList.cpp"


using namespace std;
using namespace Abuelfateh;

int main() {
	LinkedList<int> list;

	list.insertStart(100);
	list.insertEnd(101);
	list.insertEnd(102);
	list.insertEnd(103);
	

	int i = 0;
	for (list.toStart(); list.hasData(); list.advance(), i++) {
		//cout << list.getData() << endl;
		if (i == 1) {
			//list.remove();
			list.insertAfter(111);
			//list.goBack();
		}
		else if (i == 3) {
			list.insertBefore(222);
			//list.goBack();
		}
	}

	cout << "----------------------------------------\n";
	for (list.toStart(); list.hasData(); list.advance()) {
		cout << list.getData() << endl;
	}


	// prevent console auto close
	cout << endl;
	system("pause");
	return 0;
}