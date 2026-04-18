
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to represent product information
struct Product {
    int id;
    string name;
    string category;
    int quantity;
    double price;
};

// Function
void addProduct(Product* inventory, int& count, int maxSize);
void updateProduct(Product* inventory, int count);
void searchProduct(Product* inventory, int count);
void displayInventory(Product* inventory, int count);
void saveInventoryToFile(Product* inventory, int count, const string& filename);
void loadInventoryFromFile(Product* inventory, int& count, int maxSize, const string& filename);

int main() {
    const int maxSize = 100; // Maximum inventory size
    Product* inventory = new Product[maxSize]; // Dynamically allocate memory for inventory
    int count = 0; // Current number of products
    string filename = "inventory_data.txt";
    int choice;

    // Load inventory from file(Function call)
    loadInventoryFromFile(inventory, count, maxSize, filename);

    do {
        cout << "\n*** Inventory Management System ***\n";
        cout << "Made by M.Taha Siddiqui 24F-BSCS-057,\n";
        cout << "M.Haseeb 24F-BSCS-097,\n";
        cout << "Hamza Khalid 24F-BSCS-092,\n";
        cout << "Kazim Jafri 24F-BSCS-061 and\n";
        cout << "Irfan Faiz 24F-BSCS-0\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Search Product\n";
        cout << "4. Display Inventory\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(inventory, count, maxSize);
                break;
            case 2:
                updateProduct(inventory, count);
                break;
            case 3:
                searchProduct(inventory, count);
                break;
            case 4:
                displayInventory(inventory, count);
                break;
            case 5:
                saveInventoryToFile(inventory, count, filename);
                cout << "Inventory saved. Thank you have a nice day\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                return 0;
        }
    } while (choice != 5);

    delete[] inventory; // Free allocated memory
    return 0;
 }


// Functions Perform
void addProduct(Product* inventory, int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Inventory is full. Cannot add more products.\n";
        return;
    }

    cout << "\n*** Add Product ***\n";
    cout << "Enter product ID(Only Integer): ";
    cin >> inventory[count].id;
    cin.ignore(); // Clear input buffer
    cout << "Enter product name: ";
    getline(cin, inventory[count].name);
    cout << "Enter product category: ";
    getline(cin, inventory[count].category);
    cout << "Enter product quantity (Only Integer): ";
    cin >> inventory[count].quantity;
    cout << "Enter product price (Only Integer): ";
    cin >> inventory[count].price;

    count++;
    cout << "Product added successfully!\n";
}

void updateProduct(Product* inventory, int count) {
    int id;
    cout << "\n*** Update Product ***\n";
    cout << "Enter the product ID to update: ";
    cin >> id;

    for (int i = 0; i < count; ++i) {
        if (inventory[i].id == id) {
            cout << "Enter new product name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, inventory[i].name);
            cout << "Enter new product category: ";
            getline(cin, inventory[i].category);
            cout << "Enter new product quantity: ";
            cin >> inventory[i].quantity;
            cout << "Enter new product price: ";
            cin >> inventory[i].price;
            cout << "Product updated successfully!\n";
            return;
        }
    }

    cout << "Product with ID " << id << " not found.\n";
}

void searchProduct(Product* inventory, int count) {
    int id;
    cout << "\n*** Search Product ***\n";
    cout << "Enter the product ID to search: ";
    cin >> id;

    for (int i = 0; i < count; ++i) {
        if (inventory[i].id == id) {
            cout << "\nProduct Details:\n";
            cout << "ID: " << inventory[i].id << "\n";
            cout << "Name: " << inventory[i].name << "\n";
            cout << "Category: " << inventory[i].category << "\n";
            cout << "Quantity: " << inventory[i].quantity << "\n";
            cout << "Price: $" << inventory[i].price << "\n";
            return;
        }
    }

    cout << "Product with ID " << id << " not found.\n";
}

void displayInventory(Product* inventory, int count) {
    if (count == 0) {
        cout << "\nInventory is empty.\n";
        return;
    }

    cout << "\n*** Current Inventory ***\n";
    for (int i = 0; i < count; ++i) {
        cout << "ID: " << inventory[i].id << ", Name: " << inventory[i].name
             << ", Category: " << inventory[i].category
             << ", Quantity: " << inventory[i].quantity
             << ", Price: $" << inventory[i].price << "\n";
    }
}

void saveInventoryToFile(Product* inventory, int count, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        file << inventory[i].id << "\n" << inventory[i].name << "\n" << inventory[i].category
             << "\n" << inventory[i].quantity << "\n" << inventory[i].price << "\n";
    }

    file.close();}

void loadInventoryFromFile(Product* inventory, int& count, int maxSize, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No previous inventory data found.\n";
        return;
    }

    while (count < maxSize && file >> inventory[count].id) {
        file.ignore();
        getline(file, inventory[count].name);
        getline(file, inventory[count].category);
        file >> inventory[count].quantity >> inventory[count].price;
        file.ignore();
        count++;
    }

    file.close();}
