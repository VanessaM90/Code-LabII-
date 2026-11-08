
#include <iostream> 
using namespace std;

// Function to get distance travelled
double getDistance() {
    double distance;

    cout << "Enter distance travelled in miles: ";
    cin >> distance;

    return distance;
}

// Function to get fuel type
int getFuelType() {
    int fuel;

    cout << "Choose fuel type:" << endl;
    cout << "1. Petrol" << endl;
    cout << "2. Diesel" << endl;
    cout << "Enter your choice: ";
    cin >> fuel;

    return fuel;
}

// Function to calculate CO2 emissions
double calculateCO2(double distance, int fuel) {
    double litres = (distance / 100) * 9.66;
    double co2;

    if (fuel == 1) {
        co2 = litres * 2.31;
    }
    else {
        co2 = litres * 2.68;
    }

    return co2;
}

int main() {
    double distance = getDistance();
    int fuel = getFuelType();

    if (cin.fail() || distance < 0 ||
        (fuel != 1 && fuel != 2)) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    double result = calculateCO2(distance, fuel);

    cout << "CO2 emissions: " << result << " kg" << endl;

    return 0;
}
