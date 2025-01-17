# Custom Binary Search Tree (BST) and Account Manager

## 📚 **Overview**
This project showcases a **Custom Binary Search Tree (BST)** implementation in C++ and an **Account Management System** built on top of it. The project demonstrates my understanding of data structures, algorithms, and practical software engineering principles through a functional application.

## 🛠️ **Key Features**
### 1. **Custom Binary Search Tree (BST)**
   - **Implemented from Scratch**:
     - Built using `std::shared_ptr` to manage memory dynamically and avoid manual deallocation.
   - **Core Functionality**:
     - Insert, Search, Remove.
     - Traversal methods: Pre-Order, In-Order, Post-Order, Level-Order.
     - Height calculation, depth management, and node classification (e.g., leaf, internal, root).
   - **Error Handling**:
     - Custom exceptions for value duplication (`ValueExistsError`) and missing values (`ValueNotFoundError`).
   - **Use Cases**:
     - Versatile enough to serve as a foundation for any application requiring sorted data and efficient searches.

### 2. **Account Manager**
   - **Functionality**:
     - Create, Login, Delete, and Display user accounts.
     - Accounts are stored in the custom BST, using email as the unique identifier.
   - **Secure Account Management**:
     - Ensures duplicate emails cannot be created.
     - Protects against invalid login attempts with clear error messages.
   - **Interactive Console Menu**:
     - User-friendly interface to perform account operations directly in the console.
   - **Scalable Design**:
     - The modular design allows easy integration of additional account features (e.g., password encryption, email validation).
   - **Efficiency**:
     - Fast account operations leveraging the BST's logarithmic time complexity for insertions, deletions, and searches.

---

## 🔧 **How It Works**
### **Binary Search Tree (BST)**
1. **Nodes**: Each node contains data (`T`), pointers to parent, left child, and right child nodes, and its depth in the tree.
2. **Insert**:
   - Recursively finds the correct position for a new value.
   - Updates node depth dynamically.
3. **Remove**:
   - Handles all cases: leaf node, single child, and two children.
   - Balances the tree by promoting an in-order successor or predecessor when necessary.
4. **Traversal**:
   - Supports Pre-Order, In-Order, Post-Order, and Level-Order traversals for various use cases.

### **Account Manager**
- Built on top of the BST, accounts are stored as `Account` objects:
  ```cpp
  struct Account {
      std::string email;
      std::string password;
      std::string accountName;
      std::string dateCreated;
  };
  ```
- **Key Operations**:
  1. **Create Account**:
     - Prompts the user for email, password, and account name.
     - Validates uniqueness by searching the BST.
  2. **Login**:
     - Verifies email and password against existing accounts.
  3. **Delete Account**:
     - Removes the specified email from the BST.
  4. **Display Accounts**:
     - Uses an in-order traversal to display accounts alphabetically by email.

---

## 🚀 **How to Run**
### Prerequisites
- **C++17 or newer** (required for modern features like `std::shared_ptr` and `localtime_s`).

### Compilation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/custom-bst-account-manager.git
   cd custom-bst-account-manager
   ```
2. Compile the project:
   ```bash
   g++ -std=c++17 -o account_manager main.cpp BST_EVAN.cpp Accounts.cpp
   ```
3. Run the executable:
   ```bash
   ./account_manager
   ```
