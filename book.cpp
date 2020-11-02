#include <iostream>
#include <vector>
#include "book.h"
using namespace std;

book::book(long long a, string b, string c, string d, int e, string f, int g, int h) {
	// This is the construcor for a book which has been borrowed
	ISBN = a;
	title = b;
	author = c;
	category = d;
	ID = e;
	readerName = f;
	startDate = g;
	expDate = h;
}

book::book(long long a, string b, string c, string d, int e) {
	// This is the constructor for a book that is not being borrowed
	ISBN = a;
	title = b;
	author = c;
	category = d;
	ID = e;
}

void book::returnBook() {
	// Return Book function is used when the user returns a book. It resets the reader name and dates preparing it
	// for the next user
	readerName = "";
	startDate = NULL;
	expDate = NULL;
}

//set functions set a variable to the inputted value
void book::setISBN(long long x) {
	ISBN = x;
}

void book::setTitle(string x) {
	title = x;
}

void book::setAuthor(string x) {
	author = x;
}

void book::setCategory(string x) {
	category = x;
}

void book::setID(int x) {
	ID = x;
}

void book::setName(string x) {
	readerName = x;
}

void book::setStartDate(int x) {
	startDate = x;
}

void book::setExpDate(int x) {
	expDate = x;
}

//get functions return a variable
long long book::getISBN() {
	return ISBN;
}

string book::getTitle() {
	return title;
}

string book::getAuthor() {
	return author;
}

string book::getCategory() {
	return category;
}

int book::getID() {
	return ID;
}

string book::getName() {
	return readerName;
}

int book::getStartDate() {
	return startDate;
}

int book::getExpDate() {
	return expDate;
}
