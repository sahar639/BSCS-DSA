#include <iostream>
#include <string>
using namespace std;

// Node for Expense
class ExpenseItem {
public:
    string itemName;
    float cost;
    ExpenseItem* next;

    ExpenseItem(string item, float price) {
        itemName = item;
        cost = price;
        next = NULL;
    }
};

// Node for Month
class MonthlyRecord {
public:
    string monthLabel;
    ExpenseItem* itemHead;
    MonthlyRecord* next;

    MonthlyRecord(string label) {
        monthLabel = label;
        itemHead = NULL;
        next = NULL;
    }
};

// Start of month records
MonthlyRecord* yearHead = NULL;

// Add new month
void insertMonth(string label) {
    MonthlyRecord* newMonth = new MonthlyRecord(label);
    if (!yearHead) {
        yearHead = newMonth;
    } else {
        MonthlyRecord* ptr = yearHead;
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = newMonth;
    }
    cout << "New month added successfully.\n";
}

// Find month node
MonthlyRecord* getMonth(string label) {
    MonthlyRecord* ptr = yearHead;
    while (ptr) {
        if (ptr->monthLabel == label)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

// Add expense to given month
void insertExpense(string label, string item, float price) {
    MonthlyRecord* mPtr = getMonth(label);
    if (!mPtr) {
        cout << "Month not found.\n";
        return;
    }
    ExpenseItem* newItem = new ExpenseItem(item, price);
    if (!mPtr->itemHead) {
        mPtr->itemHead = newItem;
    } else {
        ExpenseItem* temp = mPtr->itemHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newItem;
    }
    cout << "Expense added successfully.\n";
}

// Display everything
void showAllRecords() {
    MonthlyRecord* mPtr = yearHead;
    while (mPtr) {
        cout << "\nMonth: " << mPtr->monthLabel << endl;
        ExpenseItem* ePtr = mPtr->itemHead;
        if (!ePtr) {
            cout << "  No expenses recorded.\n";
        }
        while (ePtr) {
            cout << "  * " << ePtr->itemName << ": " << ePtr->cost << endl;
            ePtr = ePtr->next;
        }
        mPtr = mPtr->next;
    }
}

// Update an expense entry
void modifyExpense(string label, string oldItem, string newItem, float newCost) {
    MonthlyRecord* mPtr = getMonth(label);
    if (!mPtr) {
        cout << "Month not found.\n";
        return;
    }
    ExpenseItem* ePtr = mPtr->itemHead;
    while (ePtr) {
        if (ePtr->itemName == oldItem) {
            ePtr->itemName = newItem;
            ePtr->cost = newCost;
            cout << "Expense updated successfully.\n";
            return;
        }
        ePtr = ePtr->next;
    }
    cout << "Expense item not found.\n";
}

// Delete expense
void removeExpense(string label, string item) {
    MonthlyRecord* mPtr = getMonth(label);
    if (!mPtr) {
        cout << "Month not found.\n";
        return;
    }
    ExpenseItem* current = mPtr->itemHead;
    ExpenseItem* previous = NULL;

    while (current) {
        if (current->itemName == item) {
            if (!previous)
                mPtr->itemHead = current->next;
            else
                previous->next = current->next;
            delete current;
            cout << "Expense deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Expense item not found.\n";
}

// Show most expensive item
void showHighestExpense(string label) {
    MonthlyRecord* mPtr = getMonth(label);
    if (!mPtr || !mPtr->itemHead) {
        cout << "No expenses to analyze.\n";
        return;
    }
    ExpenseItem* temp = mPtr->itemHead;
    ExpenseItem* maxItem = temp;

    while (temp) {
        if (temp->cost > maxItem->cost)
            maxItem = temp;
        temp = temp->next;
    }
    cout << "Most expensive item in " << label << ": " << maxItem->itemName << " - " << maxItem->cost << endl;
}

// Menu-driven interaction
void startMenu() {
    int option;
    string month, itemName, newItemName;
    float price;

    while (true) {
        cout << "\n--- Expense Tracker Menu ---\n";
        cout << "1. Add Month\n2. Add Expense\n3. View All\n4. Edit Expense\n5. Delete Expense\n6. Most Expensive\n7. Exit\nSelect: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                cout << "Enter month name: ";
                getline(cin, month);
                insertMonth(month);
                break;
            case 2:
                cout << "Enter month: ";
                getline(cin, month);
                cout << "Expense name: ";
                getline(cin, itemName);
                cout << "Amount: ";
                cin >> price;
                insertExpense(month, itemName, price);
                break;
            case 3:
                showAllRecords();
                break;
            case 4:
                cout << "Month: ";
                getline(cin, month);
                cout << "Old expense name: ";
                getline(cin, itemName);
                cout << "New expense name: ";
                getline(cin, newItemName);
                cout << "New amount: ";
                cin >> price;
                modifyExpense(month, itemName, newItemName, price);
                break;
            case 5:
                cout << "Month: ";
                getline(cin, month);
                cout << "Expense to delete: ";
                getline(cin, itemName);
                removeExpense(month, itemName);
                break;
            case 6:
                cout << "Month: ";
                getline(cin, month);
                showHighestExpense(month);
                break;
            case 7:
                cout << "Exiting program"<<endl;
                return;
            default:
                cout << "Invalid selection. Try again.\n";
        }
    }
}

int main() {
    startMenu();
    return 0;
}