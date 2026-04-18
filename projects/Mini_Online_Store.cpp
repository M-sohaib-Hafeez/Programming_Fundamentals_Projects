
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Struct to represent a product
struct Product {
    string name;
    float price;
};

// Vector to store cart items
vector<Product> cart;

// Function to add items to the cart
void addToCart(const string& name, float price, int quantity) {
    ofstream cartFile("cart.txt", ios::app); // Open cart.txt in append mode
    if (!cartFile) {
        cout << "Error: Unable to open cart file!" << endl;
        return;
    }

    for (int i = 0; i < quantity; ++i) {
        cart.push_back({name, price});
        cartFile << name << "," << price << endl; // Save to file
    }

    cartFile.close();
    cout << quantity << " x " << name << " has been added to your cart.\n";
}

// Function to view cart items
void viewCart() {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "\n****** Items in Your Cart ******\n";
    float totalCartAmount = 0;
    for (const auto& item : cart) {
        cout << "- " << item.name << " => Price: " << item.price << endl;
        totalCartAmount += item.price;
    }
    cout << "Total Cart Amount: " << totalCartAmount << " Only\n";
}

// Function to save transaction history
void saveTransactionHistory(float totalAmount) {
    ofstream historyFile("transaction_history.txt", ios::app); // Open transaction_history.txt in append mode
    if (!historyFile) {
        cout << "Error: Unable to open transaction history file!" << endl;
        return;
    }

    historyFile << "Transaction: \n";
    for (const auto& item : cart) {
        historyFile << "- " << item.name << " => Price: " << item.price << endl;
    }
    historyFile << "Total Amount: " << totalAmount << "\n\n";

    historyFile.close();
    cout << "Transaction has been saved to history.\n";
}

void displayMenu() {
    cout << "****** Welcome To Mini Online Store ******" << endl;
    cout << "(1) Mobile Phones" << endl;
    cout << "(2) Laptops" << endl;
    cout << "(3) Desktops" << endl;
    cout << "(4) Speakers" << endl;
    cout << "(5) Headphones" << endl;
    cout << "(6) View Cart" << endl;
    cout << "(7) Checkout" << endl;
    cout << "Please Enter Your Choice: ";
}

void shopCategory(const string& category, Product products[], int size, float& totalAmount) {
    cout << "*** " << category << " ***" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "(" << i + 1 << ") " << products[i].name
             << " => Price: " << products[i].price << endl;
    }

    cout << "Please Enter Your Choice: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > size) {
        cout << "Invalid choice. Returning to menu." << endl;
        return;
    }

    cout << "Enter Quantity: ";
    int quantity;
    cin >> quantity;

    totalAmount += products[choice - 1].price * quantity;
    addToCart(products[choice - 1].name, products[choice - 1].price, quantity); // Add to cart
}

int main() {
    char startValue;
    float totalAmount = 0;
    char choiceAgain;

start:
    do {
        cout << "Please Press 'S' to Start Shopping" << endl;
        cin >> startValue;

        if (startValue == 's' || startValue == 'S') {
            totalAmount = 0;
            bool shopping = true;

            while (shopping) {
                displayMenu();
                char choice;
                cin >> choice;

                if (choice == '1') {
                    // Mobile Phones
                    Product mobiles[] = {
                        {"Apple", 80000}, {"Samsung", 70000}, {"Vivo", 65000},
                        {"Redmi", 55000}, {"Oppo", 50000}, {"Infinix", 45000}};
                    shopCategory("Mobile Phones", mobiles, 6, totalAmount);
                } else if (choice == '2') {
                    // Laptops
                    Product laptops[] = {
                        {"Dell", 50000}, {"HP", 55000}, {"Lenovo", 60000},
                        {"Asus", 70000}, {"Acer", 65000}};
                    shopCategory("Laptops", laptops, 5, totalAmount);
                } else if (choice == '3') {
                    // Desktops
                    Product desktops[] = {
                        {"Intel", 50000}, {"AMD", 45000}, {"Nvidia", 60000},
                        {"MSI", 65000}, {"Qualcomm", 35000}};
                    shopCategory("Desktops", desktops, 5, totalAmount);
                } else if (choice == '4') {
                    // Speakers
                    Product speakers[] = {
                        {"Audionic", 8000}, {"Beats", 7000}, {"JBL", 9000},
                        {"Xpod", 6000}, {"Space", 5500}};
                    shopCategory("Speakers", speakers, 5, totalAmount);
                } else if (choice == '5') {
                    // Headphones
                    Product headphones[] = {
                        {"Sony", 2000}, {"Audionic", 1800}, {"Beats", 2500},
                        {"Razer", 2500}, {"Logitech", 1500}};
                    shopCategory("Headphones", headphones, 5, totalAmount);
                } else if (choice == '6') {
                    // View Cart
                    viewCart();
                } else if (choice == '7') {
                    // Checkout
                    shopping = false;
                    saveTransactionHistory(totalAmount); // Save transaction history
                    cart.clear(); // Clear cart after checkout
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }

            // Displaying the total bill
            cout << "Total Bill Amount is => " << totalAmount << " Only" << endl;
        } else {
            cout << "Invalid Key!" << endl;
            goto start;
        }

        // Asking if the user wants to shop again
    choiceagain:
        cout << "If You Want To Shop Again, Press 'Y' otherwise 'N'" << endl;
        cin >> choiceAgain;

    } while (choiceAgain == 'Y' || choiceAgain == 'y');

    if (choiceAgain == 'n' || choiceAgain == 'N') {
        cout << "Thanks For Shopping" << endl;
    } else {
        cout << "Invalid Character!" << endl;
        goto choiceagain;
    }

    return 0;
}
