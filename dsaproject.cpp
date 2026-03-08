#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
struct Book {
    string id;
    string title;
    string author;
    bool available;
};

Book library[100];
int totalBooks = 0;
struct IssueRecord {
    string regNo;
    string bookId;
    IssueRecord* next;
};

IssueRecord* issuedHead = NULL;
struct Request {
    string regNo;
    string bookId;
};

queue<Request> requestQueue;

int findBook(string id) {
    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == id)
            return i;
    }
    return -1;
}
void addBook() {
    cout << "\nEnter Book ID: ";
    cin >> library[totalBooks].id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, library[totalBooks].title);
    cout << "Enter Author: ";
    getline(cin, library[totalBooks].author);
    library[totalBooks].available = true;
    totalBooks++;

    cout << "Book added successfully"<<endl;
}

void showBooks() {
    cout << "\nID\tTitle\tAuthor\tStatus\n";
    for (int i = 0; i < totalBooks; i++) {
       cout << library[i].id << "    "
     << library[i].title << "      "
     << library[i].author << "  ";
    if (library[i].available){
    cout << "Available";
}
else{
    cout << "Issued";
}
cout << endl;
}
}
 
void deleteBook() {
    string id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    int index = findBook(id);
    if (index == -1) {
        cout << "Book not found"<<endl;
        return;
    }
    for (int i = index; i < totalBooks - 1; i++) {
    library[i] = library[i + 1];
}
   totalBooks--;
   cout << "Book deleted successfully"<<endl;
}

void updateBook() {
    string id;
    cout << "Enter Book ID to update: ";
    cin >> id;
    cin.ignore();
    int index = findBook(id);
    if (index == -1) {
        cout << "Book not found"<<endl ;
        return;
    }
    cout << "Enter new Title: ";
    getline(cin, library[index].title);
    cout << "Enter new Author: ";
    getline(cin, library[index].author);
    cout << "Book updated successfully"<<endl;
}
 
void requestIssue() {
    Request r;
    cout << "Enter 8 digit Registration Number: ";
    cin >> r.regNo;
    if (r.regNo.length() != 8) {
        cout << "Invalid Registration Number"<<endl;
        return;
    }
    cout << "Enter Book ID: ";
    cin >> r.bookId;
    requestQueue.push(r);
    cout << "Request added to queue"<<endl;
}

void processIssue() {
    if (requestQueue.empty()) {
        cout << "No pending requests"<<endl;
        return;
    }
    Request r = requestQueue.front();
    requestQueue.pop();
    int index = findBook(r.bookId);
    if (index == -1 || !library[index].available) {
        cout << "Book not available"<<endl;
        return;
    }
    IssueRecord* newNode = new IssueRecord();
    newNode->regNo = r.regNo;
    newNode->bookId = r.bookId;
    newNode->next = issuedHead;
    issuedHead = newNode;
    library[index].available = false;
    cout << "Book issued successfully"<<endl;
}
 
void returnBook() {
    string reg, id;
    cout << "Enter Registration Number: ";
    cin >> reg;
    if (reg.length() != 8) {
        cout << "Invalid Registration Number"<<endl;
        return;
    }
    cout << "Enter Book ID: ";
    cin >> id;
    IssueRecord* temp = issuedHead;
    IssueRecord* prev = NULL;
    while (temp != NULL) {
        if (temp->regNo == reg && temp->bookId == id) {
            int index = findBook(id);
            if (index != -1)
                library[index].available = true;
        if (prev == NULL)
                issuedHead = temp->next;
            else
                prev->next = temp->next;
          delete temp;
      cout << "Book returned successfully"<<endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
     cout << "Record not found"<<endl;
}

void showIssued() {
   IssueRecord* temp = issuedHead;
   if (temp == NULL) {
        cout << "No issued books"<<endl;
        return;
    }
    cout << "\nIssued Records: "<<endl;
   while (temp != NULL) {
        cout << "RegNo: " << temp->regNo
             << " | BookID: " << temp->bookId << endl;
        temp = temp->next;
    }
}

int main() {

    int choice;

    do {
        cout << "\n---- LIBRARY MANAGEMENT MENU ----"<<endl;
        cout << "1 Add Book"<<endl;
        cout << "2 Show Books"<<endl;
       cout << "3 Update Book"<<endl;
        cout << "4 Delete Book"<<endl;
          cout << "5 Request Issue"<<endl;
        cout << "6 Process Issue"<<endl;
     cout << "7 Return Book"<<endl;
          cout << "8 Show Issued Records"<<endl;
        cout << "9 Exit"<<endl;
       cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: showBooks(); break;
        case 3: updateBook(); break;
        case 4: deleteBook(); break;
        case 5: requestIssue(); break;
        case 6: processIssue(); break;
        case 7: returnBook(); break;
        case 8: showIssued(); break;
         }
 } while (choice != 9);
  return 0;
}