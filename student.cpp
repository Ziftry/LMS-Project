#include <iostream>
#include <vector>
#include "student.h"
using namespace std;

student::student(string a, string b, int c, int d, vector <int> e) {
					//Constructor
	username = a;
	password = b;
	maxAllowed = c;
	maxTime = d;
	borrowedList = e;
}


void student::printStudent() {						// This function is for testing
													// It prints all the information on the logged in student
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
	cout << "maxAllowed: " << maxAllowed << endl;
	cout << "maxTime: " << maxTime << endl;
	cout << "Borrowed List:" << endl;
	for (int i = 0; i < borrowedList.size(); i++) {
		cout << borrowedList[i] << endl;
	}
	cout << endl;
}


void student::printList() {							//This prints the ID's of all the student's borrowed books
	for (int i = 0; i < borrowedList.size(); i++) {
		cout << borrowedList[i] << endl;
	}
	cout << endl;
}


bool student::hasBook(int x) { // int x is a book ID

	for (int i = 0; i < borrowedList.size(); i++) {	// Loops through all the ID's in the student's list
		if (borrowedList[i] == x)					// returns true if the student is boring that book
			return true;
	}
	return false;
}

void student::returnBook(int x) {					//takes 'x' which is a book ID
	for (int i = 0; i < borrowedList.size(); i++) {	//  <----loops through the student's list of borrowed books
		if (borrowedList[i] == x) {
			borrowedList.erase(borrowedList.begin()+i);    //  Erases it from the list since the student returned it
		}
	}

	// This can be much more efficient if the book is updated individually here instead of rewriting the files

}
void student::borrowBook(int x) {     // The student borrowed a book of ID 'x'
	borrowedList.push_back(x);		// adds that ID to the students borrowed list
}


//   Set functions below
void student::setUsername(string x){
	username = x;
}
void student::setPassword(string x) {
	password = x;
}
void student::setMaxAllowed(int x) {
	maxAllowed = x;
}			
void student::setMaxTime(int x) {
	maxTime = x;
}
void student::setBorrowedList(vector <int> x) {
	borrowedList = x;
}

//    Get functions below
string student::getUsername() {
	return username;
}
string student::getPassword() {
	return password;
}
int student::getMaxAllowed() {
	return maxAllowed;
}
int student::getMaxTime() {
	return maxTime;
}
int student::getListValue(int x) {
	return borrowedList[x];
}
int student::getListSize() {
	return borrowedList.size();
}
