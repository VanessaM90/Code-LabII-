
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
using namespace std;

// Book class
class Book {
public:
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    void display() {
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "ID: " << id << endl;
        cout << "Status: "
             << (borrowed ? "Borrowed" : "Available") << endl;
    }
};

// Save updated book information
void saveBooks(vector<Book>& books) {
    fstream file("bookData.txt", ios::out);

    if (!file.is_open()) {
        cout << "Error saving file!" << endl;
        return;
    }

    for (Book& book : books) {
        file << book.title << ","
             << book.author << ","
             << book.pages << ","
             << book.id << ","
             << (book.borrowed ? "true" : "false")
             << endl;
    }

    file.close();
}

int main() {
    vector<Book> books;
    fstream file("bookData.txt", ios::in);
    string line;

    if (!file.is_open()) {
        cout << "Error opening bookData.txt!" << endl;
        return 1;
    }

    // Read books from file
    while (getline(file, line)) {
        string title, author, pages, id, status;
        stringstream ss(line);

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, status, ',');

        try {
            books.push_back(Book(title, author,
                stoi(pages), id, status == "true"));
        }
        catch (...) {
            cout << "Invalid book record!" << endl;
        }
    }

    file.close();

    int choice = 0;

    do {
        cout << "\n===== BOOK MANAGER =====" << endl;
        cout << "1. View all books" << endl;
        cout << "2. View individual book" << endl;
        cout << "3. Borrow book" << endl;
        cout << "4. Return book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice!" << endl;
            continue;
        }

        if (choice == 1) {
            for (Book& book : books) {
                book.display();
            }
        }
        else if (choice >= 2 && choice <= 4) {
            string searchID;
            cout << "Enter book ID (e.g. 001): ";
            cin >> searchID;

            bool found = false;

            for (Book& book : books) {
                if (book.id == searchID) {
                    found = true;

                    if (choice == 2) {
                        book.display();
                    }
                    else if (choice == 3) {
                        if (!book.borrowed) {
                            book.borrowed = true;
                            saveBooks(books);
                            cout << "Book borrowed!" << endl;
                        }
                        else {
                            cout << "Already borrowed!" << endl;
                        }
                    }
                    else if (choice == 4) {
                        if (book.borrowed) {
                            book.borrowed = false;
                            saveBooks(books);
                            cout << "Book returned!" << endl;
                        }
                        else {
                            cout << "Book already available!" << endl;
                        }
                    }
                    break;
                }
            }

            if (!found) {
                cout << "Book not found!" << endl;
            }
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
