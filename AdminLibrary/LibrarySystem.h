#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>
#include <vector>
#include <ctime>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    time_t dateAdded;

public:
    // Constructor
    Book(std::string t = "", std::string a = "", std::string i = "", bool avail = true, time_t date = std::time(nullptr));

    // Set book details
    void setBookDetails(std::string t, std::string a, std::string i, bool avail, time_t date);

    // Display book details
    void displayBookDetails() const;

    // Check ISBN match
    bool checkISBN(const std::string& i) const;

    // Get Date Added in string format (yyyy-mm-dd)
    std::string getDateAdded() const;

    // Borrow book if available
    void borrowBook();

    // Return book and mark as available
    void returnBook();

    // Check if the book is available for borrowing
    bool isAvailableForBorrow() const;
    void setDateAdded(time_t date);

};

class LibrarySystem {
private:
    std::vector<Book> books;

public:
    LibrarySystem();

    // Add a new book to the library
    void addBook(const std::string& title, const std::string& author, const std::string& isbn);

    // Display all books
    void displayAllBooks() const;

    // Find a book by ISBN
    Book* findBookByISBN(const std::string& isbn);

    // Sort books in ascending order (oldest first)
    void sortBooksAscending();

    // Sort books in descending order (latest first)
    void sortBooksDescending();

    // Shuffle books for mixed order (random order)
    void shuffleBooks();
   
};



#endif // LIBRARYSYSTEM_H