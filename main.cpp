/* 
MAIN 
   Written by Henri Wood
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "SmartPhone.h"
#include "BST.h"
#include "HashList.h"
#include "DeleteStack.h"

using namespace std;

void run(HashList&, BinarySearchTree<string>&, DeleteStack&);
void menu();
void addPhone(HashList&, BinarySearchTree<string>&);
void deletePhone(HashList&, BinarySearchTree<string>&, DeleteStack&);
void undoDelete(HashList&, BinarySearchTree<string>&, DeleteStack&);
void readFromFile(HashList&, BinarySearchTree<string>&);
void displayManager(BinarySearchTree<string>&, int, HashList&);
void display(string &, HashList&);
void displayIndented(string&, int);
void searchManager(HashList&);
void viewStatistics(HashList&);
int findNextPrime(int n);
bool isPrime(int n);

int main() {

	HashList phoneList;
	BinarySearchTree<string> bst;
	DeleteStack deleted;

	run(phoneList, bst, deleted);

	return 0;

}

void run(HashList& hash, BinarySearchTree<string>& bst, DeleteStack& deleted) {
	char userChoice = ' ';

	cout << "Welcome to De Anza Smart Repair!" << endl;
	menu();

	while (userChoice != 'Q') {
		cout << "\nPlease select an option (or enter \'M\' to view menu): ";
		cin >> userChoice;

		userChoice = toupper(userChoice);

		switch (userChoice) {
		case 'M':
			menu();
			break;
		case 'D':
			displayManager(bst, 0, hash); //Print inorder
			break;
		case 'S':
			searchManager(hash);
			break;
		case 'A':
			addPhone(hash, bst);
			break;
		case 'F':
			readFromFile(hash, bst);
			break;
		case 'X':
			deletePhone(hash, bst, deleted);
			break;
		case 'Z':
			undoDelete(hash, bst, deleted);
			break;
		case 'I':
			//saveToFile(hash, bst, deleted);
			break;
		case 'V':
			viewStatistics(hash);
			break;
		case 'Q':
			break;
		case 'N': //Hidden option
			cout << "\nCreated by: Teresa Bui, Kimberly Duong, Prasham Sheth, and Henri Wood" << endl;
			break;
		case 'T': //Hidden option
			displayManager(bst, 1, hash); //Print indented
			break;
		default:
			cout << "\nSorry, your input was not recognized. Please try again.\n" << endl;

		}
	}

	cout << "\nGoodbye." << endl;

}

void menu() {
	cout << "\n\tD - Display inventory"
		<< "\n\tS - Search for smartphone by serial number"
		<< "\n\tA - Add a new smartphone for repairs"
		<< "\n\tF - Insert smartphones from file"
		<< "\n\tX - Delete a smartphone from inventory"
		<< "\n\tZ - Undo delete"
		<< "\n\tI - Save inventory to file"
		<< "\n\tV - View statistics"
		<< "\n\tQ - Quit" << endl;
}

void readFromFile(HashList& hash, BinarySearchTree<string>& bst) {
	string filename;
	ifstream inFS;
	string line;

	string serial;
	string name;
	string model;
	string date;
	string issue;
	string cost;
	string status;

	cout << "\nPlease enter the name of the file: ";
	cin >> filename;

	inFS.open(filename);

	if (!inFS.is_open()) {
		cout << "Sorry, file " << filename << " could not be opened.\n" << endl;
	}
	else {
		
		while (getline(inFS, line)) {
			stringstream phone(line);

			getline(phone, serial, ';');
			getline(phone, name, ';');
			getline(phone, model, ';');
			getline(phone, date, ';');
			getline(phone, issue, ';');
			getline(phone, cost, ';');
			getline(phone, status);

			SmartPhone newPhone(serial, name, model, date, issue, cost, status);

			hash.insert(newPhone);
			bst.insert(serial);
            
            if (hash.getLoadFactor() > 75) {
                            int newSize = findNextPrime(hash.getSize() * 2);
                            //cout << endl << newSize << endl;
                            //cout << hash.getCount() << endl;
                            hash = *hash.rehash(newSize);
                            //cout << hash.getSize() << endl;
                        }

		}

		cout << "File read successfully.\n" << endl;

		inFS.close();

	}
}

void display(string& serial, HashList& hash) {
	SmartPhone displayPhone;
	SmartPhone searchPhone;
	bool searched;

	searchPhone.setSerial(serial);

	searched = hash.search(displayPhone, searchPhone);

	if (searched) {
		cout << displayPhone << endl;
	}
	else {
		cout << "Error printing object" << endl;
	}
}

void displayIndented(string& serial, int level) {

	for (int i = 1; i < level; i++)
		cout << "..";
	cout << level << "). " << serial << endl;

}

void displayManager(BinarySearchTree<string>& bst, int style, HashList& hash) {
	switch (style) {
	case 0:
		cout << "\nCurrent inventory:\n" << endl;
		bst.inOrder(display, hash);
		break;
	case 1:
		cout << "\n";
		bst.printTree(displayIndented);
		cout << endl;
		break;
	}
}

void searchManager(HashList& phoneList) {

	SmartPhone searchPhone;
	SmartPhone resultPhone;
	string serial;

	cout << "\nEnter the serial number: ";

	cin >> serial;

	searchPhone.setSerial(serial);

	bool found = phoneList.search(resultPhone, searchPhone);

	if (found) {
		cout << "\nDevice found:" << endl;
		cout << resultPhone << endl;
	}
	else {
		cout << "\nSorry, we couldn't find that device in the inventory.\n" << endl;
	}

}

void addPhone(HashList& hash, BinarySearchTree<string>& bst) {
	
	string input;
	SmartPhone newPhone;
	SmartPhone testPhone;
	
	cin.ignore();
	cout << "\nEnter the serial number: ";
	getline(cin, input);

	newPhone.setSerial(input);

	if (hash.search(testPhone, newPhone)) {
		cout << "This device is already in the inventory:" << endl;
		cout << testPhone << endl;
	}
	else {
		cout << "Enter the owner's name: ";
		getline(cin, input);
		newPhone.setName(input);

		cout << "Enter the device model: ";
		getline(cin, input);
		newPhone.setModel(input);

		cout << "Enter the date: ";
		getline(cin, input);
		newPhone.setDate(input);

		cout << "Enter brief description of issue: ";
		getline(cin, input);
		newPhone.setIssue(input);

		cout << "Enter estimated cost of repair: ";
		getline(cin, input);
		newPhone.setCost(input);

		cout << "Enter status of repair: ";
		getline(cin, input);
		newPhone.setStatus(input);

		hash.insert(newPhone);
		bst.insert(newPhone.getSerial());
        
        if (hash.getLoadFactor() > 75) {
                        int newSize = findNextPrime(hash.getSize() * 2);
                        //cout << endl << newSize << endl;
                        //cout << hash.getCount() << endl;
                        hash = *hash.rehash(newSize);
                        //cout << hash.getSize() << endl;
                }

		cout << "\nPhone successfully added to inventory:\n" << newPhone << endl;

	}
}

void deletePhone(HashList& hash, BinarySearchTree<string>& bst, DeleteStack& deleted) {
	
	string serial;
	SmartPhone searchPhone;
	SmartPhone deletePhone;

	cout << "\nEnter the serial number of the device to delete: ";
	cin >> serial;

	searchPhone.setSerial(serial);

	if (hash.remove(deletePhone, searchPhone)) {
		bst.remove(serial);
		deleted.push(deletePhone);

		cout << "\nThis device has been removed from inventory:\n" 
			<< deletePhone << endl;
	}
	else {
		cout << "\nThat device is not in the inventory." << endl;
	}
}

void undoDelete(HashList& hash, BinarySearchTree<string>& bst, DeleteStack& deleted) {
	
	SmartPhone restorePhone;

	if (deleted.isEmpty()) {
		cout << "\nThere are no deleted devices to restore." << endl;
	}
	else {
		restorePhone = deleted.pop();
		hash.insert(restorePhone);
		bst.insert(restorePhone.getSerial());

		cout << "\nThis device has been restored to the inventory:\n" 
			<< restorePhone << endl;
	}
}

void viewStatistics(HashList& hash) {

	cout << "\nHashlist Statistics:" << endl;

	cout << "\tNumber of collisions: " << hash.getTotalCollisions() << endl;
	cout << "\tLongest collision path: " << hash.getLongestCollision() << endl;
	cout << "\tLoad factor: " << hash.getLoadFactor() << "%" << endl;

}

// Given a number n, find the next closest prime number above n
int findNextPrime(int n)
{
    int nextPrime = n;
    bool found = false;

    //loop continuously until isPrime returns true for a number above n
    while (!found) {
        nextPrime++;
        if (isPrime(nextPrime)) found = true;
    }

    return nextPrime;
}

// Given a number n, determine if it is prime
bool isPrime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false; //found a factor that isn't 1 or n, therefore not prime
    
    return true;
}

