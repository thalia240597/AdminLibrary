#include <iostream>
#include <string>
#include "LibrarySystem.h"
#include <ctime>

using namespace std;

// Function to display the menu options
void displayMenu() {
    cout << "\nLibrary Menu:" << endl;
    cout << "1. Add a Book" << endl;
    cout << "2. Display All Books" << endl;
    cout << "3. Sort Books in Ascending Order (Earliest First)" << endl;
    cout << "4. Sort Books in Descending Order (Latest First)" << endl;
    cout << "5. Shuffle Books in Mixed Order" << endl;
    cout << "6. Exit" << endl;
    cout << "Select an option: ";
}

// Helper function to create a time_t from a date string (yyyy-mm-dd)
time_t createTimeFromDate(int year, int month, int day) {
    struct tm timeinfo = { 0 };
    timeinfo.tm_year = year - 1900;  // tm_year is years since 1900
    timeinfo.tm_mon = month - 1;     // tm_mon is months since January (0-11)
    timeinfo.tm_mday = day;

    // Convert to time_t
    return mktime(&timeinfo);
}

int main() {
    LibrarySystem library;

    // Adding predefined books to the library
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "111111");
    library.addBook("1984", "George Orwell", "222222");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "333333");
    library.addBook("Pride and Prejudice", "Jane Austen", "444444");
    library.addBook("The Catcher in the Rye", "J.D. Salinger", "555555");
    library.addBook("", "", "abc123");
    library.addBook("1984", "", "222222");
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "abc123");




    // Set fake dates for testing sort functionality (no user input)
    library.findBookByISBN("111111")->setDateAdded(createTimeFromDate(2020, 5, 1)); // 'The Great Gatsby' date: 2020-05-01
    library.findBookByISBN("222222")->setDateAdded(createTimeFromDate(2018, 10, 15)); // '1984' date: 2018-10-15
    library.findBookByISBN("333333")->setDateAdded(createTimeFromDate(2021, 2, 20)); // 'To Kill a Mockingbird' date: 2021-02-20
    library.findBookByISBN("444444")->setDateAdded(createTimeFromDate(2019, 7, 30)); // 'Pride and Prejudice' date: 2019-07-30
    library.findBookByISBN("555555")->setDateAdded(createTimeFromDate(2022, 11, 5)); // 'The Catcher in the Rye' date: 2022-11-05

    int option;
    string title, author, isbnInput;

    while (true) {
        displayMenu();
        cin >> option;
        cin.ignore();  // to ignore any newline character left in the buffer

        switch (option) {
        case 1: {  // Add a Book
            cout << "\nEnter Book Title: ";
            getline(cin, title);

            cout << "Enter Book Author: ";
            getline(cin, author);

            cout << "Enter ISBN (6 digits): ";
            getline(cin, isbnInput);

            // Add the book to the library
            library.addBook(title, author, isbnInput);
            break;
        }
        case 2:  // Display All Books
            cout << "\nDisplaying All Books:" << endl;
            library.displayAllBooks();
            break;

        case 3:  // Sort books in ascending order
            library.sortBooksAscending();
            break;

        case 4:  // Sort books in descending order
            library.sortBooksDescending();
            break;

        case 5:  // Shuffle books for mixed order
            library.shuffleBooks();
            break;

        case 6:  // Exit
            cout << "Exiting the program." << endl;
            return 0;

        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}
