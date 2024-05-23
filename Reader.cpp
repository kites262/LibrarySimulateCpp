//
// Created by xuan on 2024/5/22.
//

#include "lib.h"
#include "project.h"

void Reader::borrowBook(Book* book) {
	books.push_back(book);
	book->setReader(this);
}

void Reader::returnBook(const String& bookTitle) {
	for (int i = 0; i < books.size(); ++i) {
		if (books[i]->getTitle() == bookTitle) {
			returnBookAt(i);
			return;
		}
	}
	std::cerr << "Book titled '" << bookTitle << "' not found." << std::endl;
}

void Reader::returnBookAt(int index) {
	if( index >= books.size() ){
		std::cerr << "Invalid index" << endl;
		return;
	}

	books[index]->setReader(nullptr);
	books.erase(books.begin() + index);
}

void Reader::showBooks() {
	if( books.empty() ){
		cout << "No books" << endl;
		return;
	}else {
		for( auto book : books ){
			cout << book->getTitle() << ", ";
		}
		cout << endl;
	}
}
