#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_PRODUCTS = 100;
//Team Names
//Rinad Alanazi
//Shomokh Alshehri
//Lama Alzahrani
//Nada Abuabdullah
//Riman Aidrous

// Struct for product
struct Product {
    string name;
    int quantity;
    float price;
};

// Function prototypes
void displayMenu();
void addProduct(Product products[], int& numProducts);
void displayProducts(Product products[], int numProducts);
void saveToFile(Product products[], int numProducts);
void loadFromFile(Product products[], int& numProducts);
bool login();
void displayNoProducts();
void displayProductDetails(const Product& product);
void openFile(const string& filePath);
void closeFile(ofstream& file);

int main() {
    if (!login()) {
        cout << "Login failed. Exiting program.\n";
        return 0;
    }

    // Array of structs for products
    Product products[MAX_PRODUCTS];
    int numProducts = 0;

    // Add three products
    products[numProducts++] = {"Laptop", 5, 799.99};
    products[numProducts++] = {"Headphones", 10, 49.99};
    products[numProducts++] = {"Book", 20, 12.99};

    // Save products to file
    saveToFile(products, numProducts);

    // Display user input
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(products, numProducts);
                break;
            case 2:
                displayProducts(products, numProducts);
                break;
            case 3:
                saveToFile(products, numProducts);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        // Pause the program until a key is pressed
        system("pause");
    } while (choice != 4);

    return 0;
}

// Function to display menu
void displayMenu() {
    cout << "\n------ Menu ------\n";
    cout << "1. Add Product\n";
    cout << "2. Display Products\n";
    cout << "3. Save Products to File\n";
    cout << "4. Exit\n";
}

// Function to add a product
void addProduct(Product products[], int& numProducts) {
    if (numProducts < MAX_PRODUCTS) {
        cout << "Enter product name: ";
        cin >> products[numProducts].name;
        cout << "Enter product quantity: ";
        cin >> products[numProducts].quantity;
        cout << "Enter product price: ";
        cin >> products[numProducts].price;
        numProducts++;
        cout << "Product added successfully.\n";
    } else {
        cout << "Maximum number of products reached.\n";
    }
}

// Function to display all products
void displayProducts(Product products[], int numProducts) {
    if (numProducts == 0) {
        displayNoProducts();
    } else {
        cout << "\n------ Products ------\n";
        for (int i = 0; i < numProducts; ++i) {
            displayProductDetails(products[i]);
        }
    }
}

// Function to save products to a file
void saveToFile(Product products[], int numProducts) {
    string userDir = getenv("USERPROFILE");
    string filePath = userDir + "\\products.txt";

    ofstream outFile;
    openFile(filePath);
    if (outFile.is_open()) {
        for (int i = 0; i < numProducts; ++i) {
            outFile << products[i].name << " " << products[i].quantity << " " << products[i].price << endl;
        }
        closeFile(outFile);
        cout << "Products saved to file successfully.\n";
    } else {
        cout << "Unable to open file.\n";
    }
}

// Function to display a message when no products are available
void displayNoProducts() {
    cout << "No products available.\n";
}

// Function to display details of a product
void displayProductDetails(const Product& product) {
    cout << "Name: " << product.name << ", Quantity: " << product.quantity << ", Price: $" << product.price << endl;
}

// Function to open a file
void openFile(const string& filePath) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cout << "Unable to open file.\n";
    }
}

// Function to close a file
void closeFile(ofstream& file) {
    file.close();
}

// Function to load products from a file
void loadFromFile(Product products[], int& numProducts) {
    ifstream inFile("C:\\products.txt");
    if (inFile.is_open()) {
        numProducts = 0;
        while (!inFile.eof()) {
            inFile >> products[numProducts].name >> products[numProducts].quantity >> products[numProducts].price;
            numProducts++;
        }
        inFile.close();
        cout << "Products loaded from file successfully.\n";
    } else {
        cout << "File not found. Starting with an empty product list.\n";
    }
}

// Function for login
bool login() {
    string username;
    string password;

    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

    // Check if username and password are correct
    if (username == "admin" && password == "1234") {
        cout << "Login successful.\n";
        return true;
    } else {
        cout << "Incorrect username or password.\n";
        return false;
    }
}
