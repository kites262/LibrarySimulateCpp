//
// Created by xuan on 2024/5/22.
//

#ifndef LIBRARY_H
#define LIBRARY_H

#include "lib.h"

class Reader;

class Library {
	private:
	vector<Book> books;
	vector<Reader> readers;

	public:
	Library() : books(), readers() {
		books.reserve(20);
		readers.reserve(10);
	};

	void copyIn(const Book& book);

	void addBook(const String& title);
	void removeBook(const String& title);
	Book* searchBook(const String& title);
	Book* getBook(const String& title);

	void addReader(const String& name);
	void removeReader(const String& name);
	Reader* searchReader(const String& name);
	Reader* getReader(const String& name);

	void showBooksTable() const;

	void saveFile(const String& filename);
	static Library loadFile(const String& filename);
};

#endif //LIBRARY_H
