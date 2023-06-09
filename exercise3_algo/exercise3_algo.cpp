#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};

class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST = NULL;
	}
	void addNode();
	bool search(int rollno, Node** ridho, Node** alvien);
	bool listEmpty();
	bool delNode();
	void traverse();
};

void CircularLinkedList::addNode() { //Untuk menambahkan node baru pada list
	Node* newnode = new Node();
	cout << "Enter roll number: ";
	cin >> newnode->rollNumber;
	cout << "Enter name: ";
	cin >> newnode->name;

	if (LAST == NULL) {
		LAST = newnode;
		newnode->next = LAST;
	}
	else {
		newnode->next = LAST->next;
		LAST->next = newnode;
	}

	if (LAST == NULL) {
		
		newnode->next = newnode;
		LAST = newnode;
	}
	else {
		Node* alvien = LAST->next;
		Node* ridho = NULL;

		while (alvien->rollNumber < newnode->rollNumber && alvien != LAST) {
			ridho = alvien;
			alvien = alvien->next;
		}

		if (ridho == NULL) {
			newnode->next = LAST->next;
			LAST->next = newnode;
		}
		else if (alvien == LAST && alvien->rollNumber < newnode->rollNumber) {
			newnode->next = LAST->next;
			LAST->next = newnode;
			LAST = newnode;
		}
		else {
			ridho->next = newnode;
			newnode->next = alvien;
		}
	}
}
}

bool CircularLinkedList::search(int rollno, Node** ridho, Node** alvien) {
	*ridho = LAST->next;
	*alvien = LAST->next;
	while (*alvien != LAST) {
		if (rollno == (*alvien)->rollNumber) {
			return true;
		}
		*ridho = *alvien;
		*alvien = (*alvien)->next;
	}
	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() { //Untuk menghapus node yang ada pada list
	int rollno;
	cout << "Enter the roll number to delete: ";
	cin >> rollno;

	if (listEmpty()) {
		cout << "List is empty. Deletion failed." << endl;
		return false;
	}

	Node* ridho;
	Node* alvien;

	if (search(rollno, &ridho, &alvien)) {
		// Posisi pertama list
		if (alvien == LAST->next) {
			if (LAST->next == LAST) { // Jika last pointnya menunjukkan list itu sendiri
				LAST = NULL;
			}
			else {
				LAST->next = alvien->next;
			}
			delete alvien;
		}
		else if (alvien == LAST) { // Posisi diujung list
			ridho->next = LAST->next;
			LAST = ridho;
			delete alvien;
		}
		else { // Posisi diantara dua node pada list
			Node* temp = alvien->next;
			ridho->next = temp;
			delete alvien;
		}
		cout << "Record deleted successfully." << endl;
		return true;
	}
	else {
		cout << "Record not found. Deletion failed." << endl;
		return false;
	}
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* alvienNode = LAST->next;
		while (alvienNode != LAST) {
			cout << alvienNode->rollNumber << " " << alvienNode->name << endl;
			alvienNode = alvienNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}

int main() {
	CircularLinkedList obj;

	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-4): ";

			char ch;
			cin >> ch;

			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}