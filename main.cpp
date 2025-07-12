// Full Name: Frank Smith
// Class: [Itcs-2530]
// GitHub Repo URL: [Paste the URL to your repo here, e.g., https://github.com/yourusername/your-repo]
// One-Sentence Summary: A menu-driven C++ program to organize, add, and save a shoe collection.
// Your posted hobby or interest: Shoes collection
// AI Tool(s) Used: ChatGPT

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Shoe {
    string brand;
    string model;
    double size;
    double price; 
};

class ShoeManager {
private:
    int count;
public:
    ShoeManager() { count = 0; }
    void setCount(int c) { count = c; }
    int getCount() { return count; }
    void increment() { count++; }
    void decrement() { if (count > 0) count--; }
};


void displayMenu();
int loadShoes(Shoe shoes[], int maxSize, string filename);
void saveShoes(Shoe shoes[], int count, string filename);
void showShoes(Shoe shoes[], int count);
void addShoe(Shoe shoes[], int& count, int maxSize);


void displayMenu() {
    cout << "\n--- Shoe Collection Menu ---\n";
    cout << "1. View Shoes Collection\n";
    cout << "2. Add New Shoe\n";
    cout << "3. Save Collection to File\n";
    cout << "4. Exit\n";
}

int loadShoes(Shoe shoes[], int maxSize, string filename) {
    ifstream inFile(filename.c_str());
    if (!inFile) {
    
        return 0;
    }
    int count = 0;
    while (count < maxSize && inFile >> ws && getline(inFile, shoes[count].brand, ',')) {
        getline(inFile, shoes[count].model, ',');
        inFile >> shoes[count].size >> shoes[count].price;
        inFile.ignore(1000, '\n');
        count++;
    }
    cout << count << " shoes loaded from file.\n";
    inFile.close();
    return count;
}

void saveShoes(Shoe shoes[], int count, string filename) {
    ofstream outFile(filename.c_str());
    for (int i = 0; i < count; i++) { 
        outFile << shoes[i].brand << ","
            << shoes[i].model << ","
            << fixed << setprecision(1) << shoes[i].size << " "
            << fixed << setprecision(2) << shoes[i].price << endl;
    }
    outFile.close();
}

void showShoes(Shoe shoes[], int count) {
    if (count == 0) {
        cout << "No shoes in collection.\n";
        return;
    }
    cout << left << setw(15) << "Brand" << setw(20) << "Model" << setw(6) << "Size" << setw(8) << "Price" << endl;
    for (int i = 0; i < count; i++) { 
        cout << left << setw(15) << shoes[i].brand
            << setw(20) << shoes[i].model
            << setw(6) << shoes[i].size
            << setw(8) << shoes[i].price << endl;
    }
}

void addShoe(Shoe shoes[], int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Collection is full. Cannot add more shoes.\n";
        return;
    }
    Shoe newShoe;
    cout << "Enter brand: ";
    cin >> ws;
    getline(cin, newShoe.brand);
    cout << "Enter model: ";
    getline(cin, newShoe.model);
    cout << "Enter size: ";
    cin >> newShoe.size;
    cout << "Enter price: ";
    cin >> newShoe.price;
    
    if (newShoe.size <= 0 || newShoe.price < 0) {
        cout << "Invalid size or price. Shoe not added.\n";
        return;
    }
    shoes[count++] = newShoe; 
    cout << "Shoe added successfully.\n";
}



int main() {
    const int MAX_SHOES = 100; 
    Shoe shoes[MAX_SHOES];
    ShoeManager manager;

   
    int shoeCount = loadShoes(shoes, MAX_SHOES, "input.txt");
    manager.setCount(shoeCount);

    int choice = 0;
    while (choice != 4) { 
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) { 
            showShoes(shoes, manager.getCount());
        }
        else if (choice == 2) { 
            addShoe(shoes, shoeCount, MAX_SHOES);
            manager.setCount(shoeCount);
        }
        else if (choice == 3) { 
            saveShoes(shoes, manager.getCount(), "output.txt");
            cout << "Shoes saved to output.txt\n";
        }
        else if (choice == 4) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
