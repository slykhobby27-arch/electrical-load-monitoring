/*
 * ELECTRICAL LOAD MONITORING SYSTEM
 * Author:AKOSA OFOSU GYEABOUR SYLVESTER
 * Index: 01242131D
 * Course: EEE 227
 * Week 1: Basic Structure and Appliance Class
 * Date: February 10, 2026
 */

#include <iostream>
#include <string>
using namespace std;

class Appliance {
private:
    string name;
    double powerRating;
    double usageHours;

public:
    // Constructors
    Appliance() : name(""), powerRating(0), usageHours(0) {}
    
    Appliance(string n, double p, double h) {
        name = n;
        powerRating = p;
        usageHours = h;
    }
    
    // Getters
    string getName() { return name; }
    double getPower() { return powerRating; }
    double getHours() { return usageHours; }
    
    // Simple display
    void display() {
        cout << "Appliance: " << name << ", " 
             << powerRating << "W, " 
             << usageHours << " hours/day" << endl;
    }
};

int main() {
    cout << "\n=========================================\n";
    cout << "   ELECTRICAL LOAD MONITORING SYSTEM\n";
    cout << "            WEEK 1 - BASIC STRUCTURE\n";
    cout << "=========================================\n";
    
    // Test the class
    Appliance testApp("Test Appliance", 100, 5);
    testApp.display();
    
    cout << "\nWeek 1 complete: Appliance class created.\n";
    cout << "Press Enter to exit...";
    cin.get();
    
    return 0;
}
