#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "book.h"
#include "student.h"


void loadBooks();
void loadStudents();
vector <book> books;
vector <student> students;

int main() {
	
	cout << "Loading files from databases..." << endl << endl;
	loadBooks();
	loadStudents();
	for (int i = 0; i < students.size(); i++) {
		cout << "Student " << i << ":" << endl;
		students[i].printStudent();
		cout << endl;
	}
	cout << endl << "ALL DONE AND GOOD" << endl;
}

void loadBooks() {    //Reads the data from book.txt
	int ISBN, ID;
	string title, author, category;

	ifstream data_in;
	data_in.open("book.txt");
	if (data_in.fail()) {
		cerr << "Error: Failed to open 'book.txt'." ;
	}
	cout << "Book Data found." << endl;

	while (!data_in.eof()) {
		data_in >> ISBN >> title >> author >> category >> ID;
		books.push_back(book(ISBN, title, author, category, ID));
	}
	cout << "Successfully loaded book data" << endl << endl;
}

void loadStudents() { //reads the data from students.txt
	string username, password, title;
	int maxAllowed, maxTime, listSize;

	ifstream data_in;
	data_in.open("student.txt");
	if (data_in.fail()) {
		cerr << "Error: Failed to open 'student.txt'.";
	}
	cout << "Student Data found." << endl;


	while (!data_in.eof()) {
		vector <string> borrowed;
		data_in >> username >> password >> maxAllowed >> maxTime >> listSize;
		for (listSize; listSize > 0; listSize--) {
			data_in >> title;
			borrowed.push_back(title);
		}
		students.push_back(student(username, password, maxAllowed, maxTime, borrowed));
	}
	cout << "Successfully loaded student data" << endl << endl;
}