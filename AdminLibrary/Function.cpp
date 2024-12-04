#include "LibrarySystem.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <regex>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Validation for ISBN format (only digits, exactly 6 characters)
bool isValidISBN(const string& isbn) {
    regex pattern("\\d{6}"); // ISBN should be exactly 6 digits
    return regex_match(isbn, pattern);
}

// Constructor for Book
Book::Book(string t, string a, string i, bool avail, time_t date)
    : title(t), author(a), isbn(i), isAvailable(avail), dateAdded(date) {}

// Set book details
void Book::setBookDetails(string t, string a, string i, bool avail, time_t date) {
    title = t;
    author = a;
    isbn = i;
    isAvailable = avail;
    dateAdded = date;
}

// Display book details
void Book::displayBookDetails() const {
    cout << "Title: " << title << ", Author: " << author
        << ", ISBN: " << isbn << ", Availability: "
        << (isAvailable ? "Available" : "Borrowed")
        << ", Date Added: " << getDateAdded() << endl;
}
void Book::setDateAdded(time_t date) {
    dateAdded = date;
}

// Check if the ISBN of the book matches the provided ISBN
bool Book::checkISBN(const string& i) const {
    return isbn == i;
}

// Get the date the book was added in yyyy-mm-dd format
string Book::getDateAdded() const {
    char buffer[20];
    struct tm timeinfo;

    localtime_s(&timeinfo, &dateAdded); // Using localtime_s instead of localtime

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
    return string(buffer);
}

// Borrow book if available
void Book::borrowBook() {
    if (isAvailable) {
        isAvailable = false;
        cout << "Book borrowed successfully." << endl;
    }
    else {
        cout << "Error: Book is already borrowed." << endl;
    }
}

// Return book and mark as available
void Book::returnBook() {
    isAvailable = true;
    cout << "Book returned successfully." << endl;
}

// Check if the book is available for borrowing
bool Book::isAvailableForBorrow() const {
    return isAvailable;
}

// Constructor for LibrarySystem
LibrarySystem::LibrarySystem() {}

// Add a new book to the library
void LibrarySystem::addBook(const std::string& title, const std::string& author, const std::string& isbn) {
    // Validate title, author, and ISBN
    if (title.empty() || author.empty()) {
        cout << "Error: Title and author cannot be empty." << endl;
        return;
    }

    if (!isValidISBN(isbn)) {
        cout << "Error: Invalid ISBN format. ISBN must be exactly 6 digits." << endl;
        return;
    }

    // Ensure ISBN is unique
    for (const auto& book : books) {
        if (book.checkISBN(isbn)) {
            cout << "Error: A book with ISBN " << isbn << " already exists." << endl;
            return;
        }
    }

    // Add book with the current date and available status
    books.emplace_back(title, author, isbn, true, std::time(nullptr));
    cout << "Book added successfully." << endl;
}

// Display all books
void LibrarySystem::displayAllBooks() const {
    if (books.empty()) {
        cout << "No books in the library." << endl;
        return;
    }

    for (const auto& book : books) {
        book.displayBookDetails();
    }
}

// Find a book by ISBN
Book* LibrarySystem::findBookByISBN(const std::string& isbn) {
    for (auto& book : books) {
        if (book.checkISBN(isbn)) {
            return &book;
        }
    }
    return nullptr;
}

// Sorting in ascending order (by dateAdded, earliest first)
void LibrarySystem::sortBooksAscending() {
    std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getDateAdded() < b.getDateAdded(); // Compare by dateAdded
        });
    cout << "Books sorted in ascending order (earliest first)." << endl;
}

// Sorting in descending order (by dateAdded, latest first)
void LibrarySystem::sortBooksDescending() {
    std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getDateAdded() > b.getDateAdded(); // Compare by dateAdded
        });
    cout << "Books sorted in descending order (latest first)." << endl;
}

// Shuffling books for mixed order (random order)
void LibrarySystem::shuffleBooks() {
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(books.begin(), books.end(), rng);
    cout << "Books shuffled in mixed order." << endl;
}
