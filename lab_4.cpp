#include <iostream>
#include <fstream>

using namespace std;

// Функція для обчислення Y(x)
double yFunction(double x, int n) {
    double y = 0;
    if (x <= 0) {
        for (int i = 0; i <= n; i++) {
            y += (x - i) * (x - i);
        }
    } else {
        for (int i = 1; i <= n; i++) {
            int p = 1;
            for (int j = 1; j < n; j++) {
                p *= (x - i - 2 * j);
            }
            y += p;
        }
    }
    return y;
}

// Функція для обчислення одного значення Y(x)
void calculateSingleValue() {
    double x;
    int n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n (integer > 1): ";
    cin >> n;

    if (n <= 1) {
        cerr << "Error: n must be greater than 1." << endl;
        return;
    }

    double y = yFunction(x, n);
    cout << fixed << setprecision(4) << "Y(" << x << ") = " << y << endl;
}

// Функція для обчислення багатьох значень Y(x) на інтервалі
void calculateIntervalValues() {
    double a, b, h;
    int n;
    cout << "Enter the start and end of the interval (a and b): ";
    cin >> a >> b;
    cout << "Enter step size h (h > 0): ";
    cin >> h;
    cout << "Enter n (integer > 1): ";
    cin >> n;

    if (a >= b || h <= 0 || n <= 1) {
        cerr << "Error: Invalid input. Check that a < b, h > 0, and n > 1." << endl;
        return;
    }

    char saveToFile;
    string fileName;
    cout << "Do you want to save results to a file? (y/n): ";
    cin >> saveToFile;

    ofstream fout;
    if (saveToFile == 'y') {
        cout << "Enter the file path: ";
        cin >> fileName;
        fout.open(fileName);
        if (!fout) {
            cerr << "Error: Unable to open file " << fileName << endl;
            return;
        }
    }

    cout << "Results of calculations:" << endl;
    cout << fixed << setprecision(4);

    for (double x = a; x <= b; x += h) {
        double y = yFunction(x, n);
        cout << "x = " << x << ", Y(x) = " << y << endl;
        if (saveToFile == 'y') {
            fout << "x = " << x << ", Y(x) = " << y << endl;
        }
    }

    if (saveToFile == 'y') {
        fout.close();
        cout << "Results saved to " << fileName << endl;
    }
}

int main() {
    int choice;
    cout << "Choose an option:" << endl;
    cout << "1. Calculate a single value of Y(x)" << endl;
    cout << "2. Calculate Y(x) for an interval" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    switch (choice) {
        case 1:
            calculateSingleValue();
            break;
        case 2:
            calculateIntervalValues();
            break;
        default:
            cerr << "Error: Invalid choice." << endl;
            break;
    }

    return 0;
}