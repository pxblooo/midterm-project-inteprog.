# include <iostream>
# include <cstring>
# include <cctype>
# include <iomanip>

using namespace std;

const int MAX_BOOKS = 100;
const char* VALID_CATEGORIES[2] = {"Fiction", "Non-fiction"};

class Book {
private:
    char id[20], isbn[20], title[50], author[50], edition[10], publication[50], category[20];

public:
    void setData(const char* newId, const char* newIsbn, const char* newTitle, const char* newAuthor, const char* newEdition, const char* newPublication, const char* newCategory) {
        strncpy(id, newId, 19); id[19] = '\0';
        strncpy(isbn, newIsbn, 19); isbn[19] = '\0';
        strncpy(title, newTitle, 49); title[49] = '\0';
        strncpy(author, newAuthor, 49); author[49] = '\0';
        strncpy(edition, newEdition, 9); edition[9] = '\0';
        strncpy(publication, newPublication, 49); publication[49] = '\0';
        strncpy(category, newCategory, 19); category[19] = '\0';
    }

    const char* getID() { return id; }
    const char* getCategory() { return category; }

    void displayBook() {
        cout << "| " << left
             << setw(8) << id << " | "
             << setw(13) << isbn << " | "
             << setw(23) << title << " | "
             << setw(18) << author << " | "
             << setw(13) << edition << " | "
             << setw(18) << publication << " | "
             << category << " |" << endl;
    }

    void editBook(const char* newIsbn, const char* newTitle, const char* newAuthor, const char* newEdition, const char* newPublication, const char* newCategory) {
        setData(id, newIsbn, newTitle, newAuthor, newEdition, newPublication, newCategory);
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Library() : bookCount(0) {}

    bool isValidCategory(const char* category) {
        for (int i = 0; i < 2; i++) {
            if (strcasecmp(category, VALID_CATEGORIES[i]) == 0) return true;
        }
        return false;
    }

    bool isValidString(const char* str) { return (strlen(str) > 0); }
    bool isValidID(const char* id) {
        if (strlen(id) == 0) return false;
        for (int i = 0; id[i] != '\0'; i++) {
            if (!isalnum(id[i])) return false; 
        }
        return true;
    }

    int findBookByID(const char* id) {
        for (int i = 0; i < bookCount; i++) {
            if (strcasecmp(books[i].getID(), id) == 0) return i;
        }
        return -1;
    }

    void addBook() {
        if (bookCount >= MAX_BOOKS) {
            cout << "Library is full! Cannot add more books." << endl;
            return;
        }

        char id[20], isbn[20], title[50], author[50], edition[10], publication[50], category[20];
        
        while (true) {
            cout << "Enter Book ID: "; cin >> id;
            cin.ignore();
            if (!isValidID(id) || findBookByID(id) != -1) {
                cout << "Invalid or duplicate Book ID! Try again." << endl;
            } else break;
        }

        cout << "Enter ISBN: "; cin.getline(isbn, 20);
        cout << "Enter Title: "; cin.getline(title, 50);
        cout << "Enter Author: "; cin.getline(author, 50);
        cout << "Enter Edition: "; cin.getline(edition, 10);
        cout << "Enter Publication: "; cin.getline(publication, 50);
        
        while (true) {
            cout << "Enter Category (Fiction/Non-fiction): "; cin.getline(category, 20);
            if (!isValidCategory(category)) {
                cout << "Invalid category! Try again." << endl;
            } else break;
        }

        books[bookCount].setData(id, isbn, title, author, edition, publication, category);
        bookCount++;
        cout << "Book added successfully! Press any key to continue...";
        cin.get();
    }

    void searchBook() {
        char id[20];
        cout << "Enter Book ID to search: "; cin >> id;
        cin.ignore();
        int index = findBookByID(id);
        if (index != -1) {
            books[index].displayBook();
        } else {
            cout << "Book not found!" << endl;
        }
        cout << "Press any key to continue...";
        cin.get();
    }

    void viewAllBooks() {
        if (bookCount == 0) {
            cout << "No books available." << endl;
        } else {
            cout << "All Books:\n";
            for (int i = 0; i < bookCount; i++) {
                books[i].displayBook();
            }
        }
        cout << "Press any key to continue...";
        cin.get();
    }
};

int main() {
    Library library;
    string input;
    int choice;
    
    do {
        cout << "\nLibrary Management System\n";
        cout << "1 - Add Book\n";
        cout << "2 - Edit Book\n";
        cout << "3 - Search Book\n";
        cout << "4 - Delete Book\n";
        cout << "5 - View Books by Category\n";
        cout << "6 - View All Books\n";
        cout << "7 - Exit\n";
        cout << "Enter choice: ";
        
        cin >> input;
        if (input.length() == 1 && isdigit(input[0])) {
            choice = input[0] - '0';
        } else {
            cout << "Invalid choice! Try again." << endl;
            continue;
        }

        cin.ignore();
        
        switch (choice) {
            case 1: library.addBook(); break;
            case 2: cout << "Feature not implemented yet!\n"; break;
            case 3: library.searchBook(); break;
            case 4: cout << "Feature not implemented yet!\n"; break;
            case 5: cout << "Feature not implemented yet!\n"; break;
            case 6: library.viewAllBooks(); break;
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 7);
    
    return 0;
}
