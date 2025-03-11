#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// This Assignment calls for a few things. Using Classes to build a library managment system.
// We will create our classes below

//Book class - this will hold all the information about an individual book
class Book {
    public:
    string title;
    string author;
    int ISBN;
    int availability; // lets make this simple 1=avail and 0= not avail to check out
};


//User class - This will handle everything about the person borrowing a book
class User {
    public:
    string username; // Will make this autogenerate
    string name;

};

//Library Class - Manages books, users, transactions
// now we need to let the user do a few things for this assignment
// Add new Books
// Register New User or Patron
//Search for a book in library
//Borrow or Return Books
class Library {
    public:
}

int main() {
int pick;

    do {
   cout << "Welcome to the Library Management System ";
        cout << "1. Manage Books ";
        cout << "2. Manage Users ";
        cout << "3. Manage Transactions";
        cout << "4. Exit";
        cout << "Enter your choice: ";
while (cin >> pick) {
    switch (pick) {
        case 1:
            cout <<"1. Add a Book"
    }
}
    }
}


