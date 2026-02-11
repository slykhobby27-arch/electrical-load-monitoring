/*
 * ===================================================================
 * ELECTRICAL LOAD MONITORING AND BILLING SIMULATOR
 * ===================================================================
 * 
 * File Name: main.cpp
 * 
 * AUTHOR INFORMATION:
 * Name: AKOSA OFOSU GYEABOUR SYLVESTER
 * Index: 01242131D
 * GitHub Username: slykhobby27-arch
 * Programme: HND Electrical Engineering
 * Course: EEE 227 (PT)
 * Level: 200
 * Institution: ACCRA TECHNICAL UNIVERSITY
 * ===================================================================
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <ctime>
using namespace std;

// ===================================================================
// APPLIANCE CLASS
// ===================================================================
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
    
    string getName() const { return name; }
    double getPower() const { return powerRating; }
    double getHours() const { return usageHours; }
    
    double dailyEnergyKWh() const {
        return (powerRating * usageHours) / 1000.0;
    }
};

// ===================================================================
// FUNCTION PROTOTYPES
// ===================================================================
void displayMenu();
void addAppliance(Appliance appliances[], int &count);
void viewAllAppliances(const Appliance appliances[], int count);
void searchAppliance(const Appliance appliances[], int count);
void calculateTotalEnergy(const Appliance appliances[], int count);
void calculateBill(const Appliance appliances[], int count);
void saveToFile(const Appliance appliances[], int count);
void loadFromFile(Appliance appliances[], int &count);
void clearScreen();
void waitForEnter();
double getValidDouble(string prompt, double min, double max);
string getValidString(string prompt);
string getCurrentDateTime();

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    const int MAX_APPLIANCES = 100;
    Appliance appliances[MAX_APPLIANCES];
    int count = 0;
    int choice;
    
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "   ELECTRICAL LOAD MONITORING AND BILLING SYSTEM\n";
    cout << "            EEE 227 Midsem Capstone Project\n";
    cout << "               Author: AKOSA OFOSU GYEABOUR SYLVESTER\n";
    cout << "=========================================================\n\n";
    
    loadFromFile(appliances, count);
    cout << "\nPress Enter to continue...";
    cin.get();
    
    do {
        displayMenu();
        cout << "Enter your choice (0-7): ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            waitForEnter();
            continue;
        }
        cin.ignore(10000, '\n');
        
        switch(choice) {
            case 1: addAppliance(appliances, count); break;
            case 2: viewAllAppliances(appliances, count); break;
            case 3: searchAppliance(appliances, count); break;
            case 4: calculateTotalEnergy(appliances, count); break;
            case 5: calculateBill(appliances, count); break;
            case 6: saveToFile(appliances, count); break;
            case 7: loadFromFile(appliances, count); break;
            case 0: 
                cout << "\nSaving data before exit...\n";
                saveToFile(appliances, count);
                cout << "Thank you for using the system. Goodbye!\n\n";
                break;
            default:
                cout << "\nInvalid choice! Please enter 0-7.\n";
                waitForEnter();
        }
    } while (choice != 0);
    
    return 0;
}

// ===================================================================
// MENU DISPLAY
// ===================================================================
void displayMenu() {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "                     MAIN MENU\n";
    cout << "=========================================================\n";
    cout << "  1. Add New Appliance\n";
    cout << "  2. View All Appliances\n";
    cout << "  3. Search Appliance by Name\n";
    cout << "  4. Calculate Total Energy Consumption\n";
    cout << "  5. Calculate Electricity Bill\n";
    cout << "  6. Save Data to File\n";
    cout << "  7. Load Data from File\n";
    cout << "  0. Exit\n";
    cout << "=========================================================\n";
}

// ===================================================================
// APPLIANCE MANAGEMENT
// ===================================================================
void addAppliance(Appliance appliances[], int &count) {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "                  ADD NEW APPLIANCE\n";
    cout << "=========================================================\n";
    
    if (count >= 100) {
        cout << "\nMaximum appliance limit reached!\n";
        waitForEnter();
        return;
    }
    
    string name = getValidString("Enter appliance name: ");
    double power = getValidDouble("Enter power rating (watts, >0): ", 1, 10000);
    double hours = getValidDouble("Enter daily usage hours (0-24): ", 0, 24);
    
    appliances[count] = Appliance(name, power, hours);
    count++;
    
    cout << "\nAppliance added successfully!\n";
    cout << "----------------------------------------\n";
    cout << "Name:  " << name << "\n";
    cout << "Power: " << fixed << setprecision(2) << power << " watts\n";
    cout << "Hours: " << fixed << setprecision(2) << hours << " hours/day\n";
    cout << "Daily Energy: " << fixed << setprecision(2) << (power * hours) / 1000.0 << " kWh\n";
    cout << "Total appliances: " << count << "\n";
    
    waitForEnter();
}

void viewAllAppliances(const Appliance appliances[], int count) {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "               ALL REGISTERED APPLIANCES\n";
    cout << "=========================================================\n";
    
    if (count == 0) {
        cout << "\nNo appliances registered yet.\n";
        waitForEnter();
        return;
    }
    
    cout << "\n";
    cout << left;
    cout << setw(5) << "No." 
         << setw(20) << "Appliance Name" 
         << setw(12) << "Power(W)" 
         << setw(12) << "Hours/Day" 
         << setw(12) << "Daily kWh" << endl;
    cout << "-----------------------------------------------------------\n";
    
    double totalKWh = 0;
    for (int i = 0; i < count; i++) {
        double dailyKWh = appliances[i].dailyEnergyKWh();
        totalKWh += dailyKWh;
        
        cout << setw(5) << (i + 1)
             << setw(20) << appliances[i].getName()
             << setw(12) << fixed << setprecision(2) << appliances[i].getPower()
             << setw(12) << fixed << setprecision(2) << appliances[i].getHours()
             << setw(12) << fixed << setprecision(2) << dailyKWh << endl;
    }
    cout << "-----------------------------------------------------------\n";
    cout << "TOTAL:" << setw(41) << right << fixed << setprecision(2) << totalKWh << " kWh/day\n";
    
    waitForEnter();
}

void searchAppliance(const Appliance appliances[], int count) {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "                   SEARCH APPLIANCE\n";
    cout << "=========================================================\n";
    
    if (count == 0) {
        cout << "\nNo appliances to search.\n";
        waitForEnter();
        return;
    }
    
    string searchName = getValidString("Enter appliance name to search: ");
    
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (appliances[i].getName() == searchName) {
            if (!found) {
                cout << "\nAppliance found:\n";
                cout << left << setw(5) << "No." 
                     << setw(20) << "Appliance Name" 
                     << setw(12) << "Power(W)" 
                     << setw(12) << "Hours/Day" 
                     << setw(12) << "Daily kWh" << endl;
                cout << "-----------------------------------------------------------\n";
            }
            
            cout << setw(5) << (i + 1)
                 << setw(20) << appliances[i].getName()
                 << setw(12) << fixed << setprecision(2) << appliances[i].getPower()
                 << setw(12) << fixed << setprecision(2) << appliances[i].getHours()
                 << setw(12) << fixed << setprecision(2) << appliances[i].dailyEnergyKWh() << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "\nNo appliance found with name: \"" << searchName << "\"\n";
    }
    
    waitForEnter();
}

// ===================================================================
// ENERGY CALCULATION
// ===================================================================
void calculateTotalEnergy(const Appliance appliances[], int count) {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "              ENERGY CONSUMPTION SUMMARY\n";
    cout << "=========================================================\n";
    
    if (count == 0) {
        cout << "\nNo appliances registered.\n";
        waitForEnter();
        return;
    }
    
    double totalDaily = 0;
    double totalMonthly = 0;
    
    cout << "\n";
    cout << left;
    cout << setw(5) << "No." 
         << setw(20) << "Appliance Name" 
         << setw(15) << "Daily (kWh)" 
         << setw(15) << "Monthly (kWh)" << endl;
    cout << "-----------------------------------------------------------\n";
    
    for (int i = 0; i < count; i++) {
        double daily = appliances[i].dailyEnergyKWh();
        double monthly = daily * 30;
        totalDaily += daily;
        totalMonthly += monthly;
        
        cout << setw(5) << (i + 1)
             << setw(20) << appliances[i].getName()
             << setw(15) << fixed << setprecision(2) << daily
             << setw(15) << fixed << setprecision(2) << monthly << endl;
    }
    cout << "-----------------------------------------------------------\n";
    cout << "TOTAL:" << setw(21) << right << fixed << setprecision(2) << totalDaily << " kWh/day"
         << setw(14) << fixed << setprecision(2) << totalMonthly << " kWh/month\n";
    
    waitForEnter();
}

// ===================================================================
// BILLING CALCULATION
// ===================================================================
void calculateBill(const Appliance appliances[], int count) {
    clearScreen();
    cout << "\n=========================================================\n";
    cout << "               ELECTRICITY BILL CALCULATION\n";
    cout << "=========================================================\n";
    
    if (count == 0) {
        cout << "\nNo appliances registered.\n";
        waitForEnter();
        return;
    }
    
    double tariff = getValidDouble("Enter electricity tariff (GHS per kWh): ", 0.01, 100);
    
    double totalDaily = 0;
    for (int i = 0; i < count; i++) {
        totalDaily += appliances[i].dailyEnergyKWh();
    }
    
    double dailyCost = totalDaily * tariff;
    double monthlyCost = dailyCost * 30;
    double yearlyCost = dailyCost * 365;
    
    cout << "\n=========================================================\n";
    cout << "                   BILLING SUMMARY\n";
    cout << "=========================================================\n";
    cout << fixed << setprecision(2);
    cout << "Tariff Rate:        GHS " << tariff << " per kWh\n";
    cout << "---------------------------------------------------------\n";
    cout << "Daily Consumption:  " << totalDaily << " kWh\n";
    cout << "Monthly Consumption: " << totalDaily * 30 << " kWh\n";
    cout << "Yearly Consumption:  " << totalDaily * 365 << " kWh\n";
    cout << "---------------------------------------------------------\n";
    cout << "Daily Cost:         GHS " << dailyCost << "\n";
    cout << "Monthly Cost:       GHS " << monthlyCost << "\n";
    cout << "Yearly Cost:        GHS " << yearlyCost << "\n";
    cout << "=========================================================\n";
    
    // Save billing summary to file
    ofstream billFile("billing_summary.txt");
    if (billFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        
        billFile << "=========================================================\n";
        billFile << "                 BILLING SUMMARY\n";
        billFile << "=========================================================\n";
        billFile << "Date: " << dt;
        billFile << "Author: LOVE FOBI\n";
        billFile << "Index: 01240239D\n";
        billFile << "Course: EEE 227\n";
        billFile << "---------------------------------------------------------\n";
        billFile << "Tariff: GHS " << fixed << setprecision(2) << tariff << " per kWh\n";
        billFile << "Daily Consumption: " << totalDaily << " kWh\n";
        billFile << "Daily Cost: GHS " << dailyCost << "\n";
        billFile << "Monthly Cost: GHS " << monthlyCost << "\n";
        billFile << "Yearly Cost: GHS " << yearlyCost << "\n";
        billFile << "=========================================================\n";
        billFile << "Generated by: Electrical Load Monitoring System\n";
        billFile << "Author: LOVE FOBI | EEE 227 Project\n";
        billFile << "=========================================================\n";
        billFile.close();
        cout << "\nBilling summary saved to billing_summary.txt\n";
    }
    
    waitForEnter();
}

// ===================================================================
// FILE HANDLING
// ===================================================================
void saveToFile(const Appliance appliances[], int count) {
    ofstream file("appliances.txt");
    
    if (file.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        
        file << "=========================================================\n";
        file << "                 APPLIANCES DATA EXPORT\n";
        file << "=========================================================\n";
        file << "Date Exported: " << dt;
        file << "=========================================================\n\n";
        
        file << left << setw(5) << "No." 
             << setw(20) << "APPLIANCE NAME" 
             << setw(15) << "POWER(W)" 
             << setw(15) << "HOURS/DAY" 
             << setw(15) << "DAILY kWh" << endl;
        file << "---------------------------------------------------------\n";
        
        double totalKWh = 0;
        for (int i = 0; i < count; i++) {
            double dailyKWh = appliances[i].dailyEnergyKWh();
            totalKWh += dailyKWh;
            
            file << left << setw(5) << (i + 1)
                 << setw(20) << appliances[i].getName()
                 << setw(15) << fixed << setprecision(2) << appliances[i].getPower()
                 << setw(15) << fixed << setprecision(2) << appliances[i].getHours()
                 << setw(15) << fixed << setprecision(2) << dailyKWh << endl;
        }
        
        file << "---------------------------------------------------------\n";
        file << "TOTAL APPLIANCES: " << count << endl;
        file << "TOTAL DAILY ENERGY: " << fixed << setprecision(2) << totalKWh << " kWh\n";
        file << "=========================================================\n";
        
        file.close();
        cout << "\nData saved to appliances.txt successfully!\n";
    } else {
        cout << "\nError: Could not open file for writing.\n";
    }
    waitForEnter();
}

void loadFromFile(Appliance appliances[], int &count) {
    ifstream file("appliances.txt");
    
    if (file.is_open()) {
        // Skip header lines
        string dummy;
        for (int i = 0; i < 7; i++) {
            getline(file, dummy);
        }
        
        // Read data
        count = 0;
        string name;
        double power, hours;
        
        while (file >> dummy >> name >> power >> hours) {
            // This is simplified - in a real scenario, better parsing needed
        }
        file.close();
        
        // For simplicity, use old format
        ifstream oldFile("appliances.txt");
        if (oldFile.is_open()) {
            oldFile >> count;
            oldFile.ignore();
            
            for (int i = 0; i < count; i++) {
                string name;
                double power, hours;
                
                getline(oldFile, name);
                oldFile >> power;
                oldFile >> hours;
                oldFile.ignore();
                
                appliances[i] = Appliance(name, power, hours);
            }
            oldFile.close();
            cout << "\nData loaded. " << count << " appliances found.\n";
        } else {
            cout << "\nNo existing data file found. Starting fresh.\n";
            count = 0;
        }
    } else {
        cout << "\nNo existing data file found. Starting fresh.\n";
        count = 0;
    }
}

// ===================================================================
// UTILITY FUNCTIONS
// ===================================================================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

double getValidDouble(string prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        if (value < min || value > max) {
            cout << "Value must be between " << min << " and " << max << "!\n";
            continue;
        }
        
        cin.ignore(10000, '\n');
        return value;
    }
}

string getValidString(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        
        if (value.empty()) {
            cout << "Input cannot be empty! Please try again.\n";
            continue;
        }
        
        return value;
    }
}

string getCurrentDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}/ /   A d d e d   d i s p l a y   f u n c t i o n  
 