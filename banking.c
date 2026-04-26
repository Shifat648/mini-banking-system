#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// =============================================
//  STEP 3: Array of accounts (multiple users)
//  STEP 2: PIN added to each account
//  STEP 1: deposit, withdraw, view balance
// =============================================

#define MAX_ACCOUNTS 5   // max number of accounts allowed

// --- Struct for one bank account ---
struct Account {
    char name[50];
    double balance;
    int pin;
    int active;   // 1 = account exists, 0 = empty slot
    char photo[100];
    char id[20];   // user ID like 25*-**-***
};

// --- Global account list ---
struct Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;


// =============================================
//  HELPER FUNCTIONS
// =============================================

void clearScreen() {
    printf("\n\n");
}

void printLine() {
    printf("================================\n");
}

void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}


// =============================================
// Check if ID already exists
// =============================================

int isIDUnique(char newID[]) {
    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(accounts[i].id, newID) == 0) {
            return 0;
        }
    }
    return 1;
}

// Open photo automatically
void openPhoto(const char *path) {
    char command[300];

#ifdef _WIN32
    sprintf(command, "start \"\" \"%s\"", path);
#elif __APPLE__
    sprintf(command, "open \"%s\"", path);
#else
    sprintf(command, "xdg-open \"%s\"", path);
#endif

    system(command);
}


// =============================================
//  STEP 1 — Core Banking Functions
// =============================================


void viewBalance(struct Account *acc) {
    printLine();
    printf("  Account : %s\n", acc->name);
    printf("  ID      : %s\n", acc->id);
    printf("  Balance : $%.2f\n", acc->balance);
    printf("  Photo   : %s\n", acc->photo);
    printLine();
}

void deposit(struct Account *acc) {
    double amount;
    printf("Enter deposit amount: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Must be greater than 0.\n");
        return;
    }

    acc->balance += amount;
    printf("Success! Deposited $%.2f\n", amount);
    printf("New Balance: $%.2f\n", acc->balance);
}

void withdraw(struct Account *acc) {
    double amount;
    printf("Enter withdrawal amount: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Must be greater than 0.\n");
        return;
    }

    if (amount > acc->balance) {
        printf("Not enough balance! You only have $%.2f\n", acc->balance);
        return;
    }

    acc->balance -= amount;
    printf("Success! Withdrew $%.2f\n", amount);
    printf("New Balance: $%.2f\n", acc->balance);
}

// =============================================
//  STEP 2 — PIN Validation
// =============================================

int checkPin(struct Account *acc) {
    int entered;
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter PIN: ");
        scanf("%d", &entered);

        if (entered == acc->pin) {
            return 1;   // correct PIN
        }

        attempts++;
        printf("Wrong PIN! Attempts left: %d\n", 3 - attempts);
    }

    printf("Too many wrong attempts. Locked out.\n");
    return 0;   // wrong PIN
}

// =============================================
//  STEP 3 — Create Account
// =============================================

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("Sorry, maximum %d accounts reached.\n", MAX_ACCOUNTS);
        return;
    }

    struct Account *acc = &accounts[totalAccounts];

    printf("Enter your name: ");
    scanf(" %[^\n]", acc->name);

    printf("Set a 4-digit PIN: ");
    scanf("%d", &acc->pin);

    printf("Enter starting balance: $");
    scanf("%lf", &acc->balance);

    printf("Enter photo filename/path: ");
    scanf(" %[^\n]", acc->photo);

    printf("Enter your custom ID (e.g. 123-45-678): ");
    scanf(" %[^\n]", acc->id);

    if (!isIDUnique(acc->id)) {
        printf("That ID is already taken! Please choose a different one.\n");
        return;
    }

    acc->active = 1;
    totalAccounts++;

    printf("\nAccount created! Welcome, %s!\n", acc->name);
    printf("Your ID is: %s\n", acc->id);
}


// =============================================
//  STEP 3 — Account Menu (after login)
// =============================================

void accountMenu(struct Account *acc) {
    int choice;

    while (1) {
        clearScreen();
        printLine();
        printf("  Logged in : %s\n", acc->name);
        printf("  ID        : %s\n", acc->id);
        printf("  Balance   : $%.2f\n", acc->balance);
        printf("  Photo     : %s\n", acc->photo);
        printLine();
        printf("[1] Deposit\n");
        printf("[2] Withdraw\n");
        printf("[3] View Balance\n");
        printf("[4] Open Photo Again\n");
        printf("[5] Logout\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            deposit(acc);
            pressEnter();
        } else if (choice == 2) {
            withdraw(acc);
            pressEnter();
        } else if (choice == 3) {
            viewBalance(acc);
            pressEnter();
        } else if (choice == 4) {
            printf("Opening photo...\n");
            openPhoto(acc->photo);
            pressEnter();
        } else if (choice == 5) {
            printf("Logged out. Goodbye, %s!\n", acc->name);
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

// =============================================
//  STEP 3 — Login (search by name + PIN)
// =============================================

void login() {
    if (totalAccounts == 0) {
        printf("No accounts found. Please create one first.\n");
        return;
    }

    char name[50], id[20];

    printf("Enter your name: ");
    scanf(" %[^\n]", name);

    printf("Enter your ID: ");
    scanf(" %[^\n]", id);

    int found = -1;

    for (int i = 0; i < totalAccounts; i++) {
        if (strcmp(accounts[i].name, name) == 0 &&
            strcmp(accounts[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Account not found or ID mismatch.\n");
        return;
    }

    if (checkPin(&accounts[found])) {
        printf("\nLogin successful!\n");
        printf("Opening your photo automatically...\n");
        openPhoto(accounts[found].photo);
        accountMenu(&accounts[found]);
    }
}

// =============================================
//  MAIN MENU
// =============================================

int main() {
    int choice;
    srand(time(NULL));

    while (1) {
        clearScreen();
        printLine();
        printf("    MINI BANKING SYSTEM\n");
        printLine();
        printf("[1] Create New Account\n");
        printf("[2] Login\n");
        printf("[3] Exit\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createAccount();
            pressEnter();
        } else if (choice == 2) {
            login();
            pressEnter();
        } else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}