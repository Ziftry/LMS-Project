#include <iostream>
#include <vector>
#include "book.h"
using namespace std;

book::book(int a, string b, string c, string d, int e) {
	ISBN = a;
	title = b;
	author = c;
	category = d;
	ID = e;
}


void book::setISBN(int x) {
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

void book::setStartDate(string x) {
	startDate = x;
}

void book::setExpDate(string x) {
	expDate = x;
}

int book::getISBN() {
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

string book::getStartDate() {
	return startDate;
}

string book::getExpDate() {
	return expDate;
}