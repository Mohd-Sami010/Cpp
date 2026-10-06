#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

// Features
//     Add/remove books
//     Register members
//     Issue book
//     Return book
//     Search books
//     Different types of members
//     Fine calculation
//     Book availability
//     Library statistics
class Book{
    public:
        string name;
        int price;
        int amount;

        Book(string bookName, int bookPrice, int amountOfBooks){
            name = bookName;
            price = bookPrice;
            amount = amountOfBooks;
        }
};

void PrintTitle(string pageName)
{
    std::system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "|\t\t\t\t\t|" << endl;
    cout << "|\t\tSAMI LIBRARY\t\t|" << endl;
    cout << "|\t\t\t\t\t|" << endl;

    int whiteSpaces = 35 - pageName.length();
    cout << "| >> " << pageName;
    for (int i = 0; i < whiteSpaces; i++) cout << " ";
    cout << "|" << endl;

    cout << "-----------------------------------------" << endl;
}

list<Book> booksList;
void AddBooks(){
    PrintTitle("Add Books");

    string bookName;
    int bookPrice;
    int amountOfBooks;

    cout << "Enter book name: ";
    cin.ignore();
    getline(cin, bookName);

    cout << "Enter book price: ";
    cin >> bookPrice;

    cout << "Enter number books to add: ";
    cin >> amountOfBooks;

    Book newBook(bookName, bookPrice, amountOfBooks);
    booksList.push_back(newBook);
    cout << amountOfBooks << " \"" << bookName << "\" Added to Library";
}
void RemoveBooks(){
    PrintTitle("Remove Books");

    cout << "Books in Library:" << endl;
    PrintBooksInLibrary();
}
void PrintBooksInLibrary(){
    for (Book book : booksList){
        cout << book.amount + " " + book.name << endl;
    }
}
void LibraryInventory(){
    PrintTitle("Inventory");

    PrintBooksInLibrary();
}

int main()
{
    while (true)
    {
        PrintTitle("Menu");
        cout << "\n1. Add books" << endl;
        cout << "2. Remove books" << endl;
        cout << "3. Register members" << endl;
        cout << "4. Issue book" << endl;
        cout << "5. Return book" << endl;
        cout << "6. Search book" << endl;
        cout << "7. Book availability" << endl;
        cout << "8. Library Inventory" << endl;

        int option;
        cout << "Enter option: ";
        cin >> option;

        switch (option){
            case 1:
                AddBooks();
                break;
            case 2:
                PrintTitle("Remove Books");
                break;
            case 3:
                PrintTitle("Register Members");
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                LibraryInventory();
                break;
        }

        cout << "\nExit? (y/n): ";
        char exitChoice;
        cin >> exitChoice;
        if (exitChoice == 'y') break;
    }

    return 0;
}
