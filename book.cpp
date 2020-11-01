#include <iostream>
#include <vector>
#include "book.h"
using namespace std;

book::book(int a, string b, string c, string d, int e, string f, int g, int h) {
	ISBN = a;
	title = b;
	author = c;
	category = d;
	ID = e;
	readerName = f;
	startDate = g;
	expDate = h;
}

book::book(int a, string b, string c, string d, int e) {
	ISBN = a;
	title = b;
	author = c;
	category = d;
	ID = e;
}

void book::returnBook() {
	readerName = "";
	startDate = NULL;
	expDate = NULL;
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

void book::setStartDate(int x) {
	startDate = x;
}

void book::setExpDate(int x) {
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

int book::getStartDate() {
	return startDate;
}

int book::getExpDate() {
	return expDate;
}
