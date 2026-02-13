/*
 * ELECTRICAL LOAD MONITORING SYSTEM
 * Author: AKOSA OFOSU GYEABOUR SYLVESTER
 * Index: 01242131D
 * Course: EEE 227
 * Week 2: Energy Calculation Added
 * Date: February 13, 2026
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Appliance {
private:
    string name;
    double powerRating;
    double usageHours;

public:
    Appliance() : name(""), powerRating(0), usageHours(0) {}
    
    Appliance(string n, double p, double h) {
        name = n;
        powerRating = p;
        usageHours = h;
    }
    
    string getName() { return name; }
    double getPower() { return powerRating; }
    double getHours() { return usageHours; }
    
    // NEW in Week 2: Energy calculation
    double dailyEnergyKWh() {
        return (powerRating * usageHours) / 1000.0;
    }
    
    void display() {
        cout << left << setw(15) << name 
             << setw(10) << powerRating 
             << setw(12) << usageHours 
             << setw(12) << fixed << setprecision(2) << dailyEnergyKWh() << endl;
    }
};

int main() {
    cout << "\n=========================================\n";
    cout << "   ELECTRICAL LOAD MONITORING SYSTEM\n";
    cout << "         WEEK 2 - ENERGY CALCULATION\n";
    cout << "=========================================\n";
    
    // Test with sample appliances
    Appliance appliances[3];
    appliances[0] = Appliance("Refrigerator", 150, 24);
    appliances[1] = Appliance("Air Conditioner", 2000, 8);
    appliances[2] = Appliance("LED TV", 120, 5);
    
    cout << "\nAppliances:\n";
    cout << left << setw(15) << "Name" << setw(10) << "Power" << setw(12) << "Hours" << setw(12) << "kWh" << endl;
    cout << "----------------------------------------\n";
    
    double total = 0;
    for (int i = 0; i < 3; i++) {
        appliances[i].display();
        total += appliances[i].dailyEnergyKWh();
    }
    cout << "----------------------------------------\n";
    cout << "TOTAL: " << fixed << setprecision(2) << total << " kWh/day\n";
    
    cout << "\nWeek 2 complete: Energy calculation working.\n";
    cout << "Press Enter to exit...";
    cin.get();
    
    return 0;
}