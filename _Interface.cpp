#include "project.h"
#include <conio.h>

class Interface {
	public:
	Library* lib;
	String username;
	const String prefix = "!INFO> ";

	Interface(Library* lib, const String& username) : lib(lib), username(username) {}

	void change_user() {
		cout << prefix << "Please enter your username: ";
		str(username);
	}

	static void newline() {
		cout << endl;
	}

	static int key() {
		return _getch();
	}

	static void str(String& s) {
		std::getline(std::cin, s);
	}

	void search_book() const {
		String title;
		cout << prefix << "Please enter the book title: ";
		str(title);

		if( lib->searchBook(title) == nullptr ) {
			cout << prefix << "Book " << title << " not found!" << endl;
		}else {
			cout << prefix << "Book " << title << " found available." << endl;
		}
	}

	void borrow_book() const {
		String title;

		cout << prefix << "Please enter the book title: ";
		str(title);

		Book* book = lib->searchBook(title);

		if(book == nullptr) {
			cout << prefix << "Book " << title << " not found!" << endl;
		}else if(book->isAvailable()) {
			lib->getReader(username)->borrowBook(book);
			cout << prefix << "Book " << title << " borrowed successfully by user: " << username<< endl;
		}else {
			cout << prefix << "Book " << title << " is not available!" << endl;
		}
	}

	void return_book() const {
		String title;

		cout << prefix << "Please enter the book title to return: ";
		str(title);

		if(!lib->getBook(title)->isAvailable()) {
			lib->getReader(username)->returnBook(title);
			cout << prefix << "Book " << title << " returned successfully by user: " << username << endl;
		}else {
			cout << prefix << "Book " << title << " is not borrowed by user: " << username << endl;
		}
	}

	void admin_add_book() const  {
		String title;

		cout << prefix << "Please enter the book title to add: ";
		str(title);

		if(lib->searchBook(title) == nullptr) {
			lib->addBook(title);
			cout << prefix << "Book " << title << " added by admin." << endl;
		}else {
			cout << prefix << "Book " << title << " already exists!" << endl;
		}
	}

	void admin_remove_book() const {
		String title;

		cout << prefix << "Please enter the book title to remove: ";
		str(title);

		if (lib->searchBook(title) == nullptr) {
			cout << prefix << "Book " << title << " not found!" << endl;
		}else {
			lib->removeBook(title);
			cout << prefix << "Book " << title << " removed by admin." << endl;
		}
	}

	void list_user_book() const {
		cout << prefix << "User: " << username << " have borrowed: " << endl;
		lib->getReader(username)->showBooks();
	}

	void list_lib_book() const {
		cout << prefix << "The Library has: " << endl;
		lib->showBooksTable();
	}

	static void menu_user_info() {
		cout << "1. Search book" << endl;
		cout << "2. Borrow book" << endl;
		cout << "3. Return book" << endl;
		cout << "4. User books" << endl;
		cout << "5. Library books" << endl;
		cout << "q. Quit" << endl;
		cout << "--------" << endl;
	}

	static void menu_admin_info() {
		cout << "1. Search book" << endl;
		cout << "2. Borrow book" << endl;
		cout << "3. Return book" << endl;
		cout << "4. User books" << endl;
		cout << "5. Library books" << endl;
		cout << "--------" << endl;
		cout << "a. Add book" << endl;
		cout << "b. Remove book" << endl;
		cout << "o. Quit only" << endl;
		cout << "q. Save&Quit" << endl;
		cout << "--------" << endl;
	}

	void menu_user() const {
		cout << username << "$> ";
		int c = key();
		switch (c) {
			case '1':
				cout << "1->Search" << endl;
				search_book();
				break;
			case '2':
				cout << "2->Borrow" << endl;
				borrow_book();
				break;
			case '3':
				cout << "3->Return" << endl;
				return_book();
				break;
			case '4':
				cout << "4->User" << endl;
				list_user_book();
				break;
			case '5':
				cout << "5->Libray" << endl;
				list_lib_book();
				break;
			case 'q':
				cout << "q->Exit" << endl;
				exit(0);
			default:
				cout << "Invalid choice!" << endl;
		}
		newline();
	}

	void menu_admin() const {
		cout << "Admin$> ";
		int c = key();
		switch (c) {
			case '1':
				cout << "1->Search" << endl;
				search_book();
				break;
			case '2':
				cout << "2->Borrow" << endl;
				borrow_book();
				break;
			case '3':
				cout << "3->Return" << endl;
				return_book();
				break;
			case '4':
				cout << "4->User" << endl;
				list_user_book();
				break;
			case '5':
				cout << "5->Libray" << endl;
				list_lib_book();
				break;
			case 'a':
				cout << "a->Add" << endl;
				admin_add_book();
				break;
			case 'b':
				cout << "b->Remove" << endl;
				admin_remove_book();
				break;
			case 'o':
				cout << "o->Quit Only" << endl;
				exit(0);
				break;
			case 'q':
				cout << "q->Save&Exit" << endl;
				lib->saveFile("lib.ini");
				exit(0);
			default:
				cout << "Invalid choice!" << endl;
		}
		newline();
	}

};

void test_saveFile(const String& fileName) {
	Library lib;
	lib.addBook("Hello");
	lib.addBook("1998");
	lib.addBook("xixuanus");

	lib.addReader("xx");

	Reader* r = lib.getReader("xx");

	r->borrowBook(lib.getBook("xixuanus"));

	lib.saveFile(fileName);
}

void test_loadFile(const String& fileName) {
	Library lib = Library::loadFile(fileName);

	cout << "User " << lib.getReader("xx")->getName() << " have borrowed:" << endl;
	lib.getReader("xx")->showBooks();
}

void test_loadAndSave() {
	cout << "!> LOAD START" << endl;

	Library lib = Library::loadFile("lib_src.ini");
	cout << "User " << lib.getReader("xx")->getName() << " have borrowed:" << endl;
	lib.getReader("xx")->showBooks();

	cout << "!> LOAD COMPLETE" << endl << "!> SAVE START" << endl;

	lib.saveFile("lib_dst.ini");

	cout << "!> SAVE COMPLETE" << endl;
}

void test() {
	Library lib;
	Book* a = lib.getBook("Book1");
	Book* b = lib.getBook("Hello");

	Reader* u1 = lib.getReader("xx");
	Reader* u2 = lib.getReader("xx");

	u1->borrowBook(a);
	u2->borrowBook(b);

	u1->showBooks();
	u2->showBooks();

	lib.searchReader("xx")->showBooks();
}

void run(const String& username) {
	Library lib = Library::loadFile("lib.ini");
	Interface ui(&lib, username);
	bool isRunning = true;

	if(username == "admin") {
		cout << "Login as " << username << endl;
		ui.menu_admin_info();
		while(isRunning) {
			ui.menu_admin();
		}
	}else {
		cout << "Login as user " << username << endl;
		ui.menu_user_info();
		while (isRunning) {
			ui.menu_user();
		}
	}


}

void usage() {
	cout << "Usage: <exe> -<a|u> [username]" << endl;
}

int main(int argc, char* argv[]) {

	#define DEBUG_CODE 0

	if(DEBUG_CODE == 0) {
		if(argc == 1) {
			cout << "Choose your role: " << endl;
			cout << "1. Admin" << endl;
			cout << "2. User" << endl;
			int c = Interface::key();
			if(c == '1') {
				run("admin");
			}else if(c == '2') {
				cout << "Please enter your username: ";
				String username;
				Interface::str(username);
				if(username.empty() || username == "admin") {
					cout << "Invalid username!" << endl;
					exit(0);
				}
				run(username);
			}else {
				cout << "Invalid choice!" << endl;
			}
		}else if (argc <= 3){
			if(argv[1][0] == '-') {
				if(argv[1][1] == 'a') {
					run("admin");
				}else if(argv[1][1] == 'u') {
					if(argc == 3) {
						run(argv[2]);
					}else {
						usage();
					}
				}else {
					usage();
				}
			}else {
				usage();
			}
		}else {
			usage();
		}
	}

	if( DEBUG_CODE == 1) {
		test_saveFile("save.ini");
	}

	if( DEBUG_CODE == 2) {
		test_loadFile("load.ini");
	}

	if( DEBUG_CODE == 3) {
		test_loadAndSave();
	}

	if( DEBUG_CODE == 4) {
		test();
	}

	return 0;
}

