//
//  main.cpp
//  Reservation
//
//  Created by Kapilkumar Muruganantham on 10/23/26.
//


// The program reads Inventory.txt which has information on the Make, Model, Year, Type, Capacity and Efficiency of each car
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
 
#include "Database.h"
#include "ElectricCar.h"
#include "GasCar.h"
 
using namespace std;
 
// Reads the inventory file and adds each car to the database. Returns false if the file can't be opened
bool LoadInventory(const string& path, Database& db)
{
    ifstream in(path);
    if (!in)
        return false;
 
    string make, model, type, color;
    int year;
    double capacity, efficiency;
 
    // Reads one car at a time. Stops at the end of the file
    while (in >> make >> model >> color >> year >> type >> capacity >> efficiency)
    {
        // Underscores in the file become spaces, so Model_3 is stored as Model 3
        replace(make.begin(), make.end(), '_', ' ');
        replace(model.begin(), model.end(), '_', ' ');
        replace(color.begin(), color.end(), '_', ' ');
 
        // Gas Vehicle, Unknown is the color because it isn't included in the file
        if (type == "Gas")
            db.AddVehicle(make_unique<GasCar>(make, model, color, year, capacity, efficiency));
        // Electric Vehicle
        else if (type == "Electric")
            db.AddVehicle(make_unique<ElectricCar>(make, model, color, year, capacity, efficiency));
        else
            cout << "Skipping " << make << " " << model << ": unknown type " << type << '\n';
    }
    return true;
}
 
// Prompts the user on what to search by and what to search for, then prints every matching result
void Search(const Database& db)
{
    cout << "Search by: 1 Make, 2 Model, 3 Propulsion (Gas/Electric), 4 Color, 5 Year: ";
    int choice;
    cin >> choice;
 
    // Models w/ spaces will still work
    cout << "Value: ";
    string value;
    cin >> ws;
    getline(cin, value);
 
    // Menu choice 1 to 5 picks the matching field from this list
    Database::SearchField fields[] = {
        Database::SearchField::Make, Database::SearchField::Model,
        Database::SearchField::Propulsion, Database::SearchField::Color,
        Database::SearchField::Year };
 
    if (choice < 1 || choice > 5)
    {
        cout << "Invalid choice.\n";
        return;
    }
 
    // Prints the matches
    auto matches = db.Search(fields[choice - 1], value);
    if (matches.empty())
        cout << "No matches.\n";
    for (size_t index : matches)
        db.PrintVehicle(cout, index);
}
 
// Shows the cars, asks which one and for what day, then confirms if the reservation worked
void Reserve(Database& db)
{
    db.PrintAll(cout);
 
    size_t index;
    int day;
    cout << "Vehicle number: ";
    cin >> index;
    cout << "Day (after " << db.GetCurrentDate() << "): ";
    cin >> day;
 
    // The database checks all the reservation rules and returns the result
    switch (db.Reserve(index, day))
    {
        case Database::ReserveResult::Ok:              cout << "Reserved.\n"; break;
        case Database::ReserveResult::BadIndex:        cout << "No such vehicle.\n"; break;
        case Database::ReserveResult::NotFuture:       cout << "Day must be in the future.\n"; break;
        case Database::ReserveResult::AlreadyReserved: cout << "Already reserved that day.\n"; break;
        case Database::ReserveResult::LimitReached:    cout << "Vehicle already has 3 reservations.\n"; break;
    }
}
 
int main(int argc, char* argv[])
{
    // Uses the file given on the command line, otherwise Inventory.txt
    string path = (argc > 1) ? argv[1] : "Inventory.txt";
 
    // Checks if the file can be opened, if it can't then it will return an error message
    Database db;
    if (!LoadInventory(path, db))
    {
        cout << "Cannot open " << path << '\n';
        return 1;
    }
 
    // Constantly shows the menu and prompts the user for a choice until they choose to quit
    int choice = -1;
    while (choice != 0)
    {
        cout << "\nCurrent date: " << db.GetCurrentDate() << "\n"
             << "1 Search\n2 Reserve\n3 Print all\n4 Print reserved\n"
             << "5 Print available\n6 Advance date\n0 Quit\nChoice: ";
 
        // Stops the program if the input ends or is not a number
        if (!(cin >> choice))
            break;
 
        switch (choice)
        {
            case 1: Search(db);                break; // Search by Make, Model, Propulsion, Color or Year
            case 2: Reserve(db);               break; // Reserve a car for one day
            case 3: db.PrintAll(cout);         break; // Every car
            case 4: db.PrintReserved(cout);    break; // Cars with reservations
            case 5: db.PrintAvailable(cout);   break; // Cars with no reservations
            case 6: db.AdvanceDate();          break; // Moves to the next day
            case 0:                            break; // Exit the program
            default: cout << "Invalid choice.\n";
        }
    }
    return 0;
}
 
