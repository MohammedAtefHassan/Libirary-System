#include<iostream>
#include<set>
#include<map>
#include<string>
using  namespace std;
struct studentData {
	string name, ssn; int age;
	studentData()
	{
		name = ssn = ""; age = 0;
	}
	studentData(string ssn, string name, int age)
	{
		this->name = name;
		this->ssn = ssn;
		this->age = age;
	}
	bool operator <(studentData o)const
	{
		return ssn < o.ssn;
	}

};
struct bookData {
	string id, title; int numberOfCopies;
	bookData()
	{
		id = title = "";
		numberOfCopies = 0;
	}
	bookData(string id, string title, int numberOfCopies)
	{
		this->id = id;
		this->title = title;
		this->numberOfCopies = numberOfCopies;
	}
	bool operator <(bookData o)const
	{
		return id < o.id;
	}

};
int main()
{
	cout << "-----------Welcome to my project-----------" << endl;
	set<studentData>students; set<bookData>books;
	map<string, set<string>>borrowedBooks, studentBooks;
	while (true)
	{
		bool option;
		cout << "Enter 1 to continue or 0 to break:"; cin >> option;
		if (!option)break;
		cout << "Enter 1 to add student data or update it, or 0 to skip this step:"; cin >> option;
		if (option)
		{
			string studentName, studentSsn; int studentAge;
			getline(cin, studentName);
			cout << "Enter the student name:"; getline(cin, studentName);
			while (studentName.empty())
			{
				cout << "Oops! you may make a wronge.Enter the student name:"; getline(cin, studentName);
			}
			cout << "Enter the student ssn:"; cin >> studentSsn;
			cout << "Enter the student age:"; cin >> studentAge;
			auto found = students.lower_bound(studentData(studentSsn, "", 0));
			if (found == students.end() || found->ssn != studentSsn)
			{
				students.insert(studentData(studentSsn, studentName, studentAge));
			}
			else
			{
				cout << "there exist a student with this ssn enter 1 to update it or 0 to skip:"; cin >> option;
				if (option)
				{
					students.erase(found);
					students.insert(studentData(studentSsn, studentName, studentAge));
				}
			}
		}
		cout << "Enter 1 to add book data or update it, or 0 to skip this step:"; cin >> option;
		if (option)
		{
			string bookId, bookTitle; int numberOfCopies;
			getline(cin, bookId);
			cout << "Enter the book id:"; getline(cin, bookId);
			while (bookId.empty())
			{
				cout << "Oops! you may make a wronge.Enter the book id:"; getline(cin, bookId);
			}
			cout << "Enter the book title:"; cin >> bookTitle;
			cout << "Enter number of copies of this book:"; cin >> numberOfCopies;
			auto found = books.lower_bound(bookData(bookId, "", 0));
			if (found == books.end() || found->id != bookId)
			{
				books.insert(bookData(bookId, bookTitle, numberOfCopies));
			}
			else
			{
			    cout << "there exist a book with this id enter 1 to update it or 0 to skip:"; cin >> option;
			    if (option)
			    {
				    books.erase(found);
				    books.insert(bookData(bookId, bookTitle, numberOfCopies));
			    }
			}
		}
		cout << "Enter 1 to print all student's data or 0 to skip:"; cin >> option;
		if (option)
		{
			int studentNumber = 1;
			for (auto st : students)
			{
				cout << "Student number #" << studentNumber++ << ":" << endl;
				cout << "       studentSsn: " << st.ssn << endl;
				cout << "       studentName: " << st.name << endl;
				cout << "       studentAge: " << st.age << endl;
			}
		}
		cout << "Enter 1 to print all books's data or 0 to skip:"; cin >> option;
		if (option)
		{
			int bookNumber = 1;
			for (auto bk : books)
			{
				cout << "book number #" << bookNumber++ << ":" << endl;
				cout << "       bookId: " << bk.id << endl;
				cout << "       bookTitle: " << bk.title << endl;
				cout << "       numberOfCopies: " << bk.numberOfCopies << endl;
			}
		}
		cout << "Enter 1 to borrow books or 0 to skip:"; cin >> option;
		if (option)
		{
			string studentSsn = "", bookId = "";
			cout << "Enter student ssn:"; cin >> studentSsn;
			auto foundStudent = students.lower_bound(studentData(studentSsn, "", 0));
			while (foundStudent == students.end() || foundStudent->ssn != studentSsn)
			{
				cout << "this student not found! Enter the book id again:"; cin >> studentSsn;
				foundStudent = students.lower_bound(studentData(studentSsn, "", 0));
			}
			cout << "Enter book id:"; cin >> bookId;
			auto foundBook = books.lower_bound(bookData(bookId, "", 0));
			while (foundBook == books.end() || foundBook->id != bookId)
			{
				cout << "book id not found! Enter the book id again:"; cin >> bookId;
				foundBook = books.lower_bound(bookData(bookId, "", 0));
			}
			if (foundBook->numberOfCopies == 0)
			{
				cout << "sorry this book is an available!" << endl;
			}
			else
			{
				auto st = borrowedBooks[bookId].find(studentSsn);
				if (st != borrowedBooks[bookId].end())
				{
					cout << "Sorry this student can not borrow this book again!" << endl;
				}
				else
				{
					borrowedBooks[bookId].insert(studentSsn);
					studentBooks[studentSsn].insert(bookId);
					bookData updateBook = *foundBook;
					books.erase(foundBook);
					updateBook.numberOfCopies--;
					books.insert(updateBook);
				}
			}
		}
		cout << "Enter 1 to return books or 0 to skip:"; cin >> option;
		if (option)
		{
			string studentSsn = "", bookId = "";
			cout << "Enter student ssn:"; cin >> studentSsn;
			auto foundStudent = students.lower_bound(studentData(studentSsn, "", 0));
			while (foundStudent == students.end() || foundStudent->ssn != studentSsn)
			{
				cout << "this student not found! Enter the book id again:"; cin >> studentSsn;
				foundStudent = students.lower_bound(studentData(studentSsn, "", 0));
			}
			cout << "Enter book id:"; cin >> bookId;
			auto foundBook = books.lower_bound(bookData(bookId, "", 0));
			while (foundBook == books.end() || foundBook->id != bookId)
			{
				cout << "book id not found! Enter the book id again:"; cin >> bookId;
				foundBook = books.lower_bound(bookData(bookId, "", 0));
			}
			auto foundBorrowedBook = borrowedBooks.find(bookId);
			if (foundBorrowedBook == borrowedBooks.end())
			{
				cout << "sorry this book is not borrowed yet!" << endl;
			}
			else
			{
				auto foundStudentBorrowedBook = borrowedBooks[bookId].find(studentSsn);
				if (foundStudentBorrowedBook == borrowedBooks[bookId].end())
				{
					cout << "this student didn't borrow this book!" << endl;
				}
				else
				{
					borrowedBooks[bookId].erase(foundStudentBorrowedBook);
					if (borrowedBooks[bookId].empty())
						borrowedBooks.erase(foundBorrowedBook);
					studentBooks[studentSsn].erase(studentBooks[studentSsn].find(bookId));
					if (studentBooks[studentSsn].empty())
						studentBooks.erase(studentBooks.find(studentSsn));
					auto updateBook = *foundBook;
					books.erase(foundBook);
					updateBook.numberOfCopies++;
					books.insert(updateBook);
				}
			}
		}
	}
}