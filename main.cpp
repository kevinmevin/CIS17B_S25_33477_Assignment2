#include <iostream>
#include <map>
#include <string>
#include <limits> // Helps with clearing input buffer

using namespace std;

// Book class to store book details
class Book {
public:
    string title;
    string author;
    string ISBN;
    bool available;

    // Default map
    Book() : title(""), author(""), ISBN(""), available(true) {}

    // Constructor with parameters
    Book(const string& title, const string& author, const string& ISBN, bool available = true)
        : title(title), author(author), ISBN(ISBN), available(available) {}
};

// User class to store user details
class User {
public:
    string username;
    string name;

    // Default
    User() : username(""), name("") {}

    //parameters
    User(const string& u, const string& n) : username(u), name(n) {}
};

// Library class to manage everything
class Library {
private:
    map<string, Book> books;  // ISBN → Book object
    map<string, User> users;  // username → User object
    map<string, string> borrowedBooks; // ISBN → username

public:
    // Adds a book to the library
    void addBook(const string& title, const string& author, const string& ISBN) {
        if (books.find(ISBN) == books.end()) {
            books.emplace(ISBN, Book(title, author, ISBN));
            cout << "\nBook added successfully!\n";
        } else {
            cout << "\nA book with this ISBN already exists.\n";
        }
    }

    // Registers a new user
    void registerUser(const string& username, const string& name) {
        if (users.find(username) == users.end()) {
            users.emplace(username, User(username, name));
            cout << "\nUser registered successfully!\n";
        } else {
            cout << "\nThat username is already taken. Try another.\n";
        }
    }

    // Searches for a book by title
    void searchBook(const string& title) {
        bool found = false;
        for (const auto& entry : books) {
            if (entry.second.title == title) {
                found = true;
                cout << "\nFound: " << entry.second.title << " by " << entry.second.author << endl;
                cout << "ISBN: " << entry.second.ISBN << " | Status: "
                     << (entry.second.available ? "Available" : "Checked Out") << endl;
                return;
            }
        }
        cout << "\nNo book found with that title.\n";
    }

    // Borrow a book
    void borrowBook(const string& ISBN, const string& username) {
        auto bookIter = books.find(ISBN);
        auto userIter = users.find(username);

        if (bookIter == books.end()) {
            cout << "\nNo book found with this ISBN.\n";
            return;
        }

        if (userIter == users.end()) {
            cout << "\nYou're not registered.\n";
            return;
        }

        if (!bookIter->second.available) {
            cout << "\nThis book is already checked out.\n";
            return;
        }

        bookIter->second.available = false;
        borrowedBooks[ISBN] = username;
        cout << "\nYou've successfully borrowed the book.\n";
    }

    // Return a book
    void returnBook(const string& ISBN, const string& username) {
        auto borrowIter = borrowedBooks.find(ISBN);

        if (borrowIter != borrowedBooks.end() && borrowIter->second == username) {
            books[ISBN].available = true;
            borrowedBooks.erase(ISBN);
            cout << "\nBook returned. Thanks!\n";
        } else {
            cout << "\nThis book wasn't checked out by you.\n";
        }
    }
};

// Main loop
int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Manage Books\n";
        cout << "2. Manage Users\n";
        cout << "3. Borrow/Return Books\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input

        switch (choice) {
            case 1: {
                int bookChoice;
                cout << "\nBook Management:\n";
                cout << "1. Add a Book\n";
                cout << "2. Search for a Book\n";
                cout << "Enter your choice: ";
                cin >> bookChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (bookChoice == 1) {
                    string title, author, ISBN;
                    cout << "Enter book title: ";
                    getline(cin, title);
                    cout << "Enter author name: ";
                    getline(cin, author);
                    cout << "Enter ISBN: ";
                    getline(cin, ISBN);
                    library.addBook(title, author, ISBN);
                } else if (bookChoice == 2) {
                    string title;
                    cout << "Enter the title of the book: ";
                    getline(cin, title);
                    library.searchBook(title);
                } else {
                    cout << "\nInvalid option.\n";
                }
                break;
            }
            case 2: {
                string username, name;
                cout << "\nUser Management:\n";
                cout << "Enter a username: ";
                cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter full name: ";
                getline(cin, name);
                library.registerUser(username, name);
                break;
            }
            case 3: {
                int transactionChoice;
                cout << "\nTransaction Management:\n";
                cout << "1. Borrow a Book\n";
                cout << "2. Return a Book\n";
                cout << "Enter your choice: ";
                cin >> transactionChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (transactionChoice == 1) {
                    string ISBN, username;
                    cout << "Enter book ISBN: ";
                    getline(cin, ISBN);
                    cout << "Enter your username: ";
                    getline(cin, username);
                    library.borrowBook(ISBN, username);
                } else if (transactionChoice == 2) {
                    string ISBN, username;
                    cout << "Enter book ISBN: ";
                    getline(cin, ISBN);
                    cout << "Enter your username: ";
                    getline(cin, username);
                    library.returnBook(ISBN, username);
                } else {
                    cout << "\nInvalid option.\n";
                }
                break;
            }
            case 4:
                cout << "\nThanks for using the Library System!\n";
                break;
            default:
                cout << "\nInvalid. Try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
