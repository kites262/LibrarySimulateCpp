//
// Created by xuan on 2024/5/22.
//

#include "project.h"

void Library::copyIn(const Book &book) {
    books.push_back(book);
}

void Library::addBook(const String &title) {
    books.emplace_back(title);
}

void Library::removeBook(const String& title) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            books.erase(it);
            return;
        }
    }

    std::cerr << "Book not found" << endl;
}

Book* Library::searchBook(const String &title) {
    for (auto& book : books) {
        if (book.getTitle() == title) {
            return &book;
        }
    }

    return nullptr;
}

Book* Library::getBook(const String &title) {
    Book* book = searchBook(title);
    if( book == nullptr ){
        addBook(title);
        return &books.back();
    }

    return book;
}

void Library::addReader(const String &name) {
    readers.emplace_back(name);
}

void Library::removeReader(const String &name) {
    for (auto it = readers.begin(); it != readers.end(); ++it) {
        if (it->getName() == name) {
            readers.erase(it);
            return;
        }
    }

    std::cerr << "Reader not found" << endl;
}

Reader* Library::searchReader(const String &name) {
    for (auto& reader : readers) {
        if (reader.getName() == name) {
            return &reader;
        }
    }

    return nullptr;
}

Reader* Library::getReader(const String &name) {
    Reader* reader = searchReader(name);
    if( reader == nullptr ){
        addReader(name);
        return &readers.back();
    }

    return reader;
}

void Library::showBooksTable() const {
    for(auto& book : books) {

        cout << "- " << book.getTitle();
        if( book.getTitle().length() <= 6) {
            cout << "\t\t";
        }else if(book.getTitle().length() <= 12) {
            cout << "\t";
        }
        cout << "# " << (book.isAvailable() ? "Available" : "Not Available") << endl;
    }
}

void Library::saveFile(const String &filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    for (auto& book : books) {
        outFile << book.serialize() << std::endl;
    }

    outFile.close();
    std::cout << "Data saved to " << filename << std::endl;
}

Library Library::loadFile(const String &filename) {
    Library newLibrary;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return newLibrary;
    }

    String line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            Book::cast(line, &newLibrary);
        }
    }

    inFile.close();
    std::cout << "Data loaded from " << filename << std::endl;
    return newLibrary;
}
