#include<iostream>
#include <chrono>
#include <iomanip>
// i = 2, j = 3

using namespace std;

const string red = "\033[1;31m";
const string green = "\033[1;32m";
const string resetColor = "\033[0m";
const string underline = "\033[4m";

class LozanicTriangle{
private:
    long **triangle;
    int n;

public:
     LozanicTriangle(int n) : n(n) {
        triangle = new long*[n];
        for (int i = 0; i < n; ++i) {
            triangle[i] = new long[i+1];
        }
        createTriangle();
    }

    //<editor-fold desc="Functions for creating and printing the Lozanic triangle">

    void createTriangle() {
        // Creating Pascal's triangle
        int **pascalTriangle = new int*[n];
        for(int i = 0; i < n; i++) {
            pascalTriangle[i] = new int[i+1];
            for(int j = 0; j <= i; j++) {
                if(j == 0 || j == i) {
                    pascalTriangle[i][j] = 1;
                } else {
                    pascalTriangle[i][j] = pascalTriangle[i-1][j-1] + pascalTriangle[i-1][j];
                }
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0 || j == i) {
                    triangle[i][j] = 1;
                } else {
                    triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
                    // Application of Lozanic's rule
                    if(i % 2 == 0 && j % 2 == 1) {
                        triangle[i][j] -= pascalTriangle[i/2-1][(j-1)/2];
                    }
                }
            }
        }

        // Freeing memory occupied by Pascal's triangle
        for(int i = 0; i < n; i++) {
            delete[] pascalTriangle[i];
        }
        delete[] pascalTriangle;
    }

    void printTriangle() const {
        for(int i = 0; i < n; i++) {
            for(int space = 0; space < n - i - 1; space++) {
                cout << " ";
            }
            for(int j = 0; j <= i; j++) {
                cout << triangle[i][j] << " ";
                if(j < i) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    void freeTriangle() {
        for (int i = 0; i < n; ++i) {
            delete[] triangle[i];
        }
        delete[] triangle;
    }

//</editor-fold>

    //<editor-fold> desc = "Getters"

    int getNumberOfRows() const {
        return this->n;
    }

    long* getRow(int row) const {
        if(row >= n || row < 0) {
            cout << "The given row does not exist." << endl;
            return nullptr;
        }

        long* resultRow = new long[row + 1];
        for(int i = 0; i <= row; ++i) {
            resultRow[i] = triangle[row][i];
        }

        return resultRow;
    }

//</editor-fold>

};

//<editor-fold desc = "Searches">

bool binarySearch(int key, const long *row, int n, int &numberOfBinaryAccesses) {
    n = (n+1)/2; // The length is up to half a line
    int low = 0, high = n-1;
    cout << "\t\t" << underline <<"BINARY SEARCH\n" << resetColor << endl;
    while(low <= high) {
        numberOfBinaryAccesses++; // Adding the number of entries to the search
        int mid = low + (high - low) / 2;
        cout << "Step " << numberOfBinaryAccesses << ": Comparing with the key " << row[mid] << " on index " << mid << " ( high is " << high << ", low is " << low << " ) " << endl;
        if(key == row[mid]) return true;
        else if(key < row[mid]) high = mid-1;
        else low = mid+1;
    }

    return false;
}

bool ternarySearch(int key, const long *row, int n, int &numberOfTernaryAccesses) {
    n = (n+1)/2; // The length is up to half a line
    int low = 0, high = n - 1;
    cout << "\t\t" << underline <<"TERNARY SEARCH\n" << resetColor << endl;
    while (low <= high) {
        numberOfTernaryAccesses++; // Adding the number of entries to the search

        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        cout << "Step " << numberOfTernaryAccesses << ": Comparing with keys " << row[mid1] << " and " << row[mid2] << " on the indexes " << mid1 << " and " << mid2 << endl;

        if (key == row[mid1]) return true;
        if (key == row[mid2]) return true;

        if (key < row[mid1]) high = mid1 - 1;
        else if (key > row[mid2]) low = mid2 + 1;
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return false;
}

//</editor-fold>

//<editor-fold desc = "Menu Outputs">

void finish() {
    printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printf("\xB3         Exiting the program...       \xB3\n");
    printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    printf("----------------------------------------");
    printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printf("\xB3    Program successfully completed!   \xB3\n");
    printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    exit(0);
}

void displayDuration(chrono::microseconds duration) {
    double microseconds = static_cast<double>(duration.count());
    double milliseconds = microseconds / 1000;
    double seconds = milliseconds / 1000;

    if (seconds > 1) {
        cout << "\xB3Time needed to perform the search: " << seconds << " seconds" << endl;
    }
    else if (milliseconds > 1) {
        cout << "\xB3Time needed to perform the search: " << milliseconds << " milliseconds" << endl;
    }
    else {
        cout << "\xB3Time needed to perform the search: " << microseconds << " microseconds" << endl;
    }
}

void displayComparisonTable(int binaryAccesses, int ternaryAccesses, chrono::microseconds binaryDuration, chrono::microseconds ternaryDuration) {
    printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printf("\xB3  Search   \xB3  NoAcc  \xB3      Time      \xB3\n");
    printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
    cout << "\xB3  Binary   \xB3    " << binaryAccesses << "    \xB3     " << std::fixed << std::setprecision(3) << binaryDuration.count()/1000.0 << "ms    \xB3"  << endl;
    printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
    cout << "\xB3  Ternary  \xB3    " << ternaryAccesses << "    \xB3     " << std::fixed << std::setprecision(3) << ternaryDuration.count()/1000.0 << "ms    \xB3" << endl;
    printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    cout << "*NoAcc - number of accesses" << endl;
}


//</editor-fold>

int main() {

    int choice;
    do {
        printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
        printf("\xB3                 MENU                 \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  1. START THE SIMULATION             \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  0. EXIT                             \xB3\n");
        printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        cout << "\xB3" << "Enter the number to select the desired option: " << endl << "\xC4>";
        cin >> choice;

        switch (choice) {
            case 1: {

                cout << "You have selected the option \"ENTER ROW AND SEARCH KEY\"" << endl;
                int n, key;
                cout << "\xB3" << "Enter the row number: " << endl << "\xC4>";
                cin >> n;
                if(n <= 0) {
                    cout << "\nThe row number cannot be 0 or a negative number." << endl;
                    break;
                }
                cout << "\xB3" << "Enter the key you are looking for: " << endl << "\xC4>";
                cin >> key;

                LozanicTriangle *lozanicTriangle = new LozanicTriangle(n+1); // Counting is from 0, so it must be n+1
                cout << "\xB3Print of triangle up to the requested row: \n" << endl;
                lozanicTriangle->printTriangle();

                long *row = lozanicTriangle->getRow(n); // We select the required row and place it in the array

                cout << "\n\xB3The row in which the key is being searched for: " << endl;
                for (int i = 0; i < (n+2)/2; ++i) {
                    cout << row[i] << " ";
                }
                cout << endl << endl;

                int numberOfBinaryAccesses = 0;
                int numberOfTernaryAccesses = 0;

                //<editor-fold desc = "Binary search"
                auto startBinary = chrono::high_resolution_clock::now(); // Start of timing

                bool binary = binarySearch(key, row, n+1, numberOfBinaryAccesses);

                auto stopBinary = chrono::high_resolution_clock::now(); // End of timing
                auto durationBinary = chrono::duration_cast<chrono::microseconds>(stopBinary - startBinary); // Calculating duration

                //<editor-fold desc = "Printing binary search results in color">
                if(binary) {
                    cout << "\n\xB3" << "Binary search result: " << green <<  "The key has been found." << resetColor << endl;
                }
                else {
                    cout << "\n\xB3" << "Binary search result: " << red <<  "The key has not been found." << resetColor << endl;
                }
                //</editor-fold> (

            //    cout << "\n\xB3" << "Binary search result: " << (binary ? "The key has been found." : "The key has not been found") << endl;
                cout << "\xB3" << "Number of search operations: " << numberOfBinaryAccesses << endl;
            //  cout << "\n\xB3Time needed to perform the search: " << duration.count() << " microseconds" << endl;
               displayDuration(durationBinary);

               putchar('\n');

                // </editor-fold>

                //<editor-fold desc = "Ternary search">

                auto startTernary = chrono::high_resolution_clock ::now(); // Start of timing

                bool ternary = ternarySearch(key, row, n+1, numberOfTernaryAccesses);

                auto stopTernary = chrono::high_resolution_clock ::now(); // End of timing
                auto durationTernary = chrono::duration_cast<chrono::microseconds>(stopTernary - startTernary);

                //<editor-fold desc = "Printing ternary search results in color">
                if(ternary) {
                    cout << "\n\xB3Ternary search result: " << green <<  "The key has been found." << resetColor << endl;
                }
                else {
                    cout << "\n\xB3Ternary search result: " << red <<  "The key has not been found." << resetColor << endl;
                }
                //</editor-fold>

//                cout << "\n\xB3Ternary search result: " << (ternary ? "The key has been found." : "The key has not been found") << endl;
                cout << "\xB3" << "Number of search operations: " << numberOfTernaryAccesses << endl;
                //  cout << "\n\xB3Time needed to perform the search: " << duration.count() << " microseconds" << endl;
                displayDuration(durationTernary);

                //</editor-fold>

                displayComparisonTable(numberOfBinaryAccesses, numberOfTernaryAccesses, durationBinary, durationTernary);

                lozanicTriangle->freeTriangle();
                break;
            }
            case 0:
                finish();
                break;
            default:
                cout << "Invalid entry. Please enter 1 or 0 to exit the program." << endl;
        }

    } while (choice != 0);


    return 0;
}