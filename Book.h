//
// Created by xuan on 2024/5/22.
//

#ifndef BOOK_H
#define BOOK_H

#include "lib.h"

class Reader;
class Library;

class Book {
    private:
    String title;
    Reader *reader;

    public:
    explicit Book(const String& title) : title(title), reader(nullptr) {};
    Book() : title(""), reader(nullptr) {};

    String getTitle() const { return title; };
    void setReader(Reader* reader) { this->reader = reader; };
    bool isAvailable() const { return reader == nullptr; };

    Reader* getReader() const;

    void lendTo(Reader* reader);
    void returnBack();

    String serialize() const;
    static void cast(const String& data, Library* targetLib);
};

#endif //BOOK_H
