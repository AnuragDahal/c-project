/*
Project Name: Expense Tracker: Manage Your Finances with Ease
Project Members Name:
1. Nabin Khair
2. Anurag Dahal
3. Mukesh Kumar Sah
4. Niraj Kumar Pal

Submitted to : Department of Electronics & Computer Engineering, IOE Purwanchal Campus Dharan

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_EXPENSES 100

// User structure
typedef struct
{
    char username[50];
    char password[50];
} User;

// Expense structure
typedef struct
{
    float amount;
    char date[20];
    char category[50];
} Expense;

// Function prototypes
void registerUser();
int loginUser();
void recordExpense();
void viewExpenses();
void saveUserData();
void loadUserData();
void saveExpenseData();
void loadExpenseData();

// Global variables
User users[MAX_USERS];
int numUsers = 0;
Expense expenses[MAX_EXPENSES];
int numExpenses = 0;

int main()
{
    // Load data from files at the beginning
    loadUserData();
    loadExpenseData();

    int choice;

    while (1)
    {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Record Expense\n");
        printf("4. View Expenses\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser())
            {
                printf("Login successful!\n");
            }
            else
            {
                printf("Invalid credentials. Please try again.\n");
            }
            break;
        case 3:
            if (numUsers == 0)
            {
                printf("You need to login first.\n");
            }
            else
            {
                recordExpense();
            }
            break;
        case 4:
            if (numUsers == 0)
            {
                printf("You need to login first.\n");
            }
            else
            {
                viewExpenses();
            }
            break;
        case 5:
            // Save data to files before exiting
            saveUserData();
            saveExpenseData();
            printf("Exiting Expense Tracker. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void registerUser()
{
    if (numUsers >= MAX_USERS)
    {
        printf("Maximum user limit reached. Cannot register new users.\n");
        return;
    }

    printf("Enter a unique username: ");
    scanf("%s", users[numUsers].username);
    for (int i = 0; i < strlen(users[numUsers].username); i++)
    {
        users[numUsers].username[i] = tolower(users[numUsers].username[i]);
    }

    printf("Enter your password: ");
    scanf("%s", users[numUsers].password);

    numUsers++;
}

int loginUser()
{
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    for (int i = 0; i < strlen(username); i++)
    {
        username[i] = tolower(username[i]);
    }

    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void recordExpense()
{
    if (numExpenses >= MAX_EXPENSES)
    {
        printf("Maximum expense limit reached. Cannot add new expenses.\n");
        return;
    }

    Expense newExpense;

    printf("Enter the amount spent: ");
    scanf("%f", &newExpense.amount);

    printf("Enter the date (DD/MM/YYYY): ");
    scanf("%s", newExpense.date);

    printf("Enter the expense category: ");
    scanf("%s", newExpense.category);

    expenses[numExpenses] = newExpense;
    numExpenses++;

    printf("Expense recorded successfully!\n");
}

void viewExpenses()
{
    printf("\n----- Your Expenses -----\n");
    printf("Date\t\tAmount\t\tCategory\n");
    printf("------------------------------------\n");

    for (int i = 0; i < numExpenses; i++)
    {
        printf("%-10s\t%.2f\t%s\n", expenses[i].date, expenses[i].amount, expenses[i].category);
    }
}

void saveUserData()
{
    FILE *file = fopen("users.txt", "w");
    if (file == NULL)
    {
        printf("Error opening users file for writing.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++)
    {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

void loadUserData()
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening users file for reading. Creating new file...\n");
        // Create the file if it doesn't exist
        file = fopen("users.txt", "w");
        if (file == NULL)
        {
            printf("Error creating users file.\n");
            return;
        }
        fclose(file);
        return;
    }

    // Reset the numUsers to zero before loading data
    numUsers = 0;

    while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2)
    {
        numUsers++;
    }

    fclose(file);
}

void saveExpenseData()
{
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL)
    {
        printf("Error opening expenses file for writing.\n");
        return;
    }

    for (int i = 0; i < numExpenses; i++)
    {
        fprintf(file, "%.2f %s %s\n", expenses[i].amount, expenses[i].date, expenses[i].category);
    }

    fclose(file);
}

void loadExpenseData()
{
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL)
    {
        printf("Error opening expenses file for reading. Creating new file...\n");
        // Create the file if it doesn't exist
        file = fopen("expenses.txt", "w");
        if (file == NULL)
        {
            printf("Error creating expenses file.\n");
            return;
        }
        fclose(file);
        return;
    }

    // Reset the numExpenses to zero before loading data
    numExpenses = 0;

    while (fscanf(file, "%f %s %s", &expenses[numExpenses].amount, expenses[numExpenses].date, expenses[numExpenses].category) == 3)
    {
        numExpenses++;
    }

    fclose(file);
}
