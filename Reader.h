//
// Created by xuan on 2024/5/22.
//

#ifndef READER_H
#define READER_H

#include "lib.h"

class Book;
class Library;

class Reader {
	private:
	String name;
	vector<Book*> books;

	public:
	Reader(const String& name) : name(name), books() {};
	String getName() const { return name; };

	void showBooks();

	void borrowBook(Book* book);
	void returnBook(const String& bookTitle);
	void returnBookAt(int index);

};

#endif //READER_H
