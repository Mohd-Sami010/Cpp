#include <iostream>
#include <cstdlib>
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

        Book() = default;

        Book(string bookName, int bookPrice, int amountOfBooks){
            name = bookName;
            price = bookPrice;
            amount = amountOfBooks;
        }
        bool operator== (Book bookToCompare){
            return name == bookToCompare.name && price == bookToCompare.price;
        }
};

class LibraryStorage{
    private:
        int currentIndex = 0;
        Book booksInLibrary[15];
    
    public:
        void AddBook(Book book){
            booksInLibrary[currentIndex++] = book;
        }
        void RemoveBook(string bookName, int amount){
            for (int i = 0; i < currentIndex; i++){
                if (bookName == booksInLibrary[i].name){
                    if (booksInLibrary[i].amount <= amount){
                        for (int j = i; j < currentIndex; j++){
                            booksInLibrary[j] = booksInLibrary[j+1];
                        }
                        currentIndex--;
                    }
                    else{
                        booksInLibrary[i].amount -= amount;
                    }
                    cout << amount << " " << bookName << " Deleted succesfully" << endl;
                    return;
                }
            }
            cout << "Book with name \"" << bookName << "\" Not found" << endl;
        }
        void PrintBooksInStorage(){
            for (int i = 0; i<currentIndex; i++){
                cout << booksInLibrary[i].amount << " " << booksInLibrary[i].name << endl;
            }
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

LibraryStorage libraryStorage;

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
    libraryStorage.AddBook(newBook);
    cout << amountOfBooks << " \"" << bookName << "\" Added to Library";
}
void RemoveBooks(){
    PrintTitle("Remove Books");

    cout << "Books in Library:" << endl;
    libraryStorage.PrintBooksInStorage();

    string bookName;
    int numOfBooksToDelete;

    cout << "Enter book name to delete: ";
    cin.ignore();
    getline(cin, bookName);
    
    cout << "Enter number of books to Delete: ";
    cin >> numOfBooksToDelete;

    libraryStorage.RemoveBook(bookName, numOfBooksToDelete);
}
void LibraryInventory(){
    PrintTitle("Inventory");

    libraryStorage.PrintBooksInStorage();
}

int main()
{
    while (true)
    {
        PrintTitle("Menu");
        cout << "\n1. Add books" << endl;
        cout << "2. Remove books" << endl;
        cout << "3. Issue book" << endl;
        cout << "4. Return book" << endl;
        cout << "5. Search book" << endl;
        cout << "6. Book availability" << endl;
        cout << "7. Library Inventory" << endl;

        int option;
        cout << "Enter option: ";
        cin >> option;

        switch (option){
            case 1:
                AddBooks();
                break;
            case 2:
                RemoveBooks();
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
