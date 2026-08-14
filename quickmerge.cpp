#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

struct MobileUser {
    long long mobileNo;
    float balance;
    string name;
    int UserID;
};

// Global temporary array for Merge Sort
MobileUser b[100];

class Sort {
public:
    int comparisons = 0;
    int passes = 0;

    void resetStats() {
        comparisons = 0;
        passes = 0;
    }

    // --- MERGE SORT LOGIC ---
    void Merge(MobileUser arr[], int low, int mid, int high) {
        int i = low;
        int j = mid + 1;
        int k = low;

        while (i <= mid && j <= high) {
            comparisons++;
            // For Descending Order: Compare >=
            if (arr[i].UserID >= arr[j].UserID) {
                b[k++] = arr[i++];
            } else {
                b[k++] = arr[j++];
            }
        }
        while (i <= mid) b[k++] = arr[i++];
        while (j <= high) b[k++] = arr[j++];

        for (int z = low; z <= high; z++) {
            arr[z] = b[z];
        }
    }

    void mergesort(MobileUser arr[], int low, int high) {
        if (low < high) {
            passes++;
            int mid = low + (high - low) / 2;
            mergesort(arr, low, mid);
            mergesort(arr, mid + 1, high);
            Merge(arr, low, mid, high);
        }
    }

    // --- QUICK SORT LOGIC ---
    int q_partition(MobileUser arr[], int low, int high) {
        int pivot = arr[high].UserID;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comparisons++;
            // For Descending Order: Compare > pivot
            if (arr[j].UserID > pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quick_sort(MobileUser arr[], int low, int high) {
        if (low < high) {
            passes++;
            int pi = q_partition(arr, low, high);
            quick_sort(arr, low, pi - 1);
            quick_sort(arr, pi + 1, high);
        }
    }

    void display(MobileUser arr[], int n) {
        cout << "\n--- SORTED USER DATA (DESCENDING) ---";
        cout << "\nUserID\tName\t\tMobile\t\tBill";
        for (int i = 0; i < n; i++) {
            cout << "\n" << arr[i].UserID << "\t" << arr[i].name 
                 << "\t" << arr[i].mobileNo << "\t" << arr[i].balance;
        }
        cout << "\n\nTotal Comparisons: " << comparisons;
        cout << "\nTotal Passes (Recursive Splits): " << passes << endl;
    }
};

int main() {
    Sort company;
    int n, choice;
    MobileUser users[100];

    cout << "Enter number of users (max 100): ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nUser " << i + 1 << " Details:";
        cout << "\nUserID: "; cin >> users[i].UserID;
        cout << "Name: "; cin >> users[i].name;
        cout << "Mobile: "; cin >> users[i].mobileNo;
        cout << "Bill Amount: "; cin >> users[i].balance;
    }

    do {
        cout << "\n--- MENU ---\n1. Merge Sort\n2. Quick Sort\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            company.resetStats();
            company.mergesort(users, 0, n - 1);
            company.display(users, n);
        } else if (choice == 2) {
            company.resetStats();
            company.quick_sort(users, 0, n - 1);
            company.display(users, n);
        }
    } while (choice != 3);

    return 0;
}