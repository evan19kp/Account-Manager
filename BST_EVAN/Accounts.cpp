#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include "BST_EVAN.hpp"

struct Account {
    std::string email;
    std::string password;
    std::string accountName;
    std::string dateCreated;

    bool operator<(const Account& other) const {
        return email < other.email;
    }
    bool operator==(const Account& other) const {
        return email == other.email;
    }
};

class AccountManager {
private:
    BST<Account> accounts;

    std::string getCurrentDate() {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &ltm);
        return std::string(buffer);
    }

public:
    void createAccount() {
        Account newAccount;
        std::cout << "Enter email: ";
        std::cin >> newAccount.email;

        if (accounts.exists(newAccount)) {
            std::cout << "Error: Account with this email already exists!" << std::endl;
            return;
        }

        std::cout << "Enter account name: ";
        std::cin >> newAccount.accountName;

        std::cout << "Enter password: ";
        std::cin >> newAccount.password;

        newAccount.dateCreated = getCurrentDate();

        accounts.insert(newAccount);
        std::cout << "Account successfully created!" << std::endl;
    }

    void login() {
        std::string email, password;
        std::cout << "Enter email: ";
        std::cin >> email;

        try {
            Account account = accounts.find({ email, "", "", "" });
            std::cout << "Enter password: ";
            std::cin >> password;

            if (password == account.password) {
                std::cout << "Login successful! Welcome, " << account.accountName << "." << std::endl;
            }
            else {
                std::cout << "Error: Incorrect password!" << std::endl;
            }
        }
        catch (const ValueNotFoundError&) {
            std::cout << "Error: Account not found!" << std::endl;
        }
    }

    void deleteAccount() {
        std::string email;
        std::cout << "Enter email of the account to delete: ";
        std::cin >> email;

        try {
            accounts.remove({ email, "", "", "" });
            std::cout << "Account successfully deleted." << std::endl;
        }
        catch (const ValueNotFoundError&) {
            std::cout << "Error: Account not found!" << std::endl;
        }
    }

    void displayAccounts() {
        if (accounts.empty()) {
            std::cout << "No accounts to display." << std::endl;
            return;
        }

        std::cout << "List of accounts:" << std::endl;
        accounts.traverseInOrder([](const BST<Account>&, std::shared_ptr<BST<Account>::Node> node) {
            const Account& acc = node->getData();
            std::cout << "Email: " << acc.email
                << ", Account Name: " << acc.accountName
                << ", Date Created: " << acc.dateCreated << std::endl;
            return true;
            });
    }

    void menu() {
        while (true) {
            std::cout << "\nAccount Management System" << std::endl;
            std::cout << "1. Create Account" << std::endl;
            std::cout << "2. Login" << std::endl;
            std::cout << "3. Delete Account" << std::endl;
            std::cout << "4. Display Accounts" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "Choose an option: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                displayAccounts();
                break;
            case 5:
                std::cout << "Exiting the application." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    AccountManager manager;
    manager.menu();
    return 0;
}
