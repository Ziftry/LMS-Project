#include <iostream>
#include <vector>
#include "student.h"
using namespace std;

student::student(string a, string b, int c, int d, vector <string> e) {
	
	username = a;
	password = b;
	maxAllowed = c;
	maxTime = d;
	borrowedList = e;
}


void student::printStudent() {
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
void student::setBorrowedList(vector <string> x) {
	borrowedList = x;
}

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