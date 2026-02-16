/*
 * ELECTRICAL LOAD MONITORING SYSTEM
 * Author: AKOSA OFOSU GYEABOUR SYLVESTER
 * Index: 01242131D
 * Course: EEE 227
 * Week 3: Billing Calculation Added
 * Date: February 15, 2026
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

// NEW in Week 3: Billing function
void calculateBill(Appliance apps[], int count, double tariff) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += apps[i].dailyEnergyKWh();
    }
    
    double dailyCost = total * tariff;
    double monthlyCost = dailyCost * 30;
    
    cout << "\n--- Billing Summary ---\n";
    cout << "Tariff: GHS " << fixed << setprecision(2) << tariff << " per kWh\n";
    cout << "Daily Consumption: " << total << " kWh\n";
    cout << "Daily Cost: GHS " << dailyCost << "\n";
    cout << "Monthly Cost: GHS " << monthlyCost << "\n";
}

int main() {
    cout << "\n=========================================\n";
    cout << "   ELECTRICAL LOAD MONITORING SYSTEM\n";
    cout << "         WEEK 3 - BILLING CALCULATION\n";
    cout << "=========================================\n";
    
    // Test with sample appliances
    Appliance appliances[3];
    appliances[0] = Appliance("Refrigerator", 150, 24);
    appliances[1] = Appliance("Air Conditioner", 2000, 8);
    appliances[2] = Appliance("LED TV", 120, 5);
    
    cout << "\nAppliances:\n";
    cout << left << setw(15) << "Name" << setw(10) << "Power" << setw(12) << "Hours" << setw(12) << "kWh" << endl;
    cout << "----------------------------------------\n";
    
    for (int i = 0; i < 3; i++) {
        appliances[i].display();
    }
    cout << "----------------------------------------\n";
    
    // Test billing with tariff 0.15
    calculateBill(appliances, 3, 0.15);
    
    cout << "\nWeek 3 complete: Billing calculation working.\n";
    cout << "Press Enter to exit...";
    cin.get();
    
    return 0;
}