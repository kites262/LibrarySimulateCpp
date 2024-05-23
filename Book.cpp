//
// Created by xuan on 2024/5/22.
//

#include "project.h"

Reader* Book::getReader() const {
	if( isAvailable() ){
		std::cerr << "Book is available" << endl;
		return nullptr;
	}

	return reader;
}

void Book::lendTo(Reader* reader) {
	if( isAvailable() ){
		reader->borrowBook(this);
		return;
	}

	std::cerr << "Book is not available" << endl;
}

void Book::returnBack() {
	if( isAvailable() ){
		std::cerr << "Book is already available" << endl;
	}

	reader->returnBook(getTitle());
}

String Book::serialize() const {
	std::stringstream ss;
	ss << "[" << title << ", " << (reader == nullptr ? "null" : reader->getName()) << "]";
	return ss.str();
}

void Book::cast(const String& data, Library* targetLib) {
	std::stringstream ss(data);
	String title, readerName;
	ss.ignore(1);
	std::getline(ss, title, ',');
	ss.ignore(1);
	std::getline(ss, readerName, ']');

	Book* book = targetLib->getBook(title);
	if (readerName != "null" && !readerName.empty()) {
		Reader* reader = targetLib->getReader(readerName);
		if (reader && book) {
			book->lendTo(reader);
		}
	}
}
