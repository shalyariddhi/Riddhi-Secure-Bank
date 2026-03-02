#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

void showMenu() {
    std::cout << "\n1. Deposit | 2. Withdraw | 3. Balance | 4. Exit" << std::endl;
    std::cout << "Selection: ";
}

double deposit(double currentBalance) {
    double amount;
    std::cout << "Enter deposit amount: $";
    if (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Error: Invalid amount." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return currentBalance;
    }
    return currentBalance + amount;
}

double withdraw(double currentBalance) {
    double amount;
    std::cout << "Enter withdrawal amount: $";
    if (!(std::cin >> amount) || amount <= 0 || amount > currentBalance) {
        std::cout << "Error: Invalid amount or Insufficient Funds." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return currentBalance;
    }
    return currentBalance - amount;
}

int main() {
    std::string name;
    double balance = 0.0;
    std::string savedPIN;
    std::string enteredPIN;
    int choice;

    std::cout << "==============================" << std::endl;
    std::cout << "      RIDDHI SECURE BANK      " << std::endl;
    std::cout << "==============================" << std::endl;

    // --- STEP 1: PIN REGISTRATION OR LOGIN ---
    std::ifstream pinFileIn("pin.txt");
    
    if (!pinFileIn.is_open()) {
        // First time running the app: Register PIN
        std::cout << "No User Found. Please register a 4-digit PIN: ";
        std::cin >> savedPIN;
        
        std::ofstream pinFileOut("pin.txt");
        pinFileOut << savedPIN;
        pinFileOut.close();
        std::cout << "PIN Registered Successfully!\n" << std::endl;
    } else {
        // Returning User: Load the PIN
        pinFileIn >> savedPIN;
        pinFileIn.close();

        int attempts = 0;
        while (attempts < 3) {
            std::cout << "Enter your PIN to Login: ";
            std::cin >> enteredPIN;
            if (enteredPIN == savedPIN) {
                std::cout << "Access Granted!\n" << std::endl;
                break;
            } else {
                attempts++;
                std::cout << "Wrong PIN. [" << (3 - attempts) << " attempts left]" << std::endl;
            }
            if (attempts == 3) {
                std::cout << "System Locked. Contact Administrator." << std::endl;
                return 0;
            }
        }
    }

    // --- STEP 2: LOAD BALANCE ---
    std::ifstream inFile("balance.txt");
    if (inFile.is_open()) {
        inFile >> balance;
        inFile.close();
    }

    // Clear buffer for name input
    std::cin.ignore(); 
    std::cout << "Enter Account Holder Name: ";
    std::getline(std::cin, name);
    std::cout << std::fixed << std::setprecision(2);

    // --- STEP 3: MAIN MENU LOOP ---
    do {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Error: Invalid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: balance = deposit(balance); break;
            case 2: balance = withdraw(balance); break;
            case 3: std::cout << "\n>>> Current Balance: $" << balance << std::endl; break;
            case 4: std::cout << "Saving and logging out..." << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    // --- STEP 4: SAVE BALANCE ---
    std::ofstream outFile("balance.txt");
    if (outFile.is_open()) {
        outFile << balance;
        outFile.close();
    }

    std::cout << "Goodbye, " << name << "!" << std::endl;
    return 0;
}