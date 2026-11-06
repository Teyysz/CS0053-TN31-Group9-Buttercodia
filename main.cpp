#include "../Daniel/parking_slots.h"
#include "../Partick/reservations.h"
#include "../Odda/storage.h"
#include <iostream>

using namespace std;

static void showMenu() {
    cout << "--------------- MENU ---------------\n"
         << "1. View parking rates\n"
         << "2. Rent a parking space\n"
         << "3. View parking rentals\n"
         << "4. Search rental history\n"
         << "5. Exit\n"
         << "------------------------------------\n";
}

int main() {
    ParkingState parking;
    vector<Reservation> rentals;
    loadDatabase(rentals);
    refreshExpiredRentals(rentals);
    rebuildOccupancy(parking, rentals);
    saveDatabase(rentals);

    cout << "====================================\n"
         << "         BUTTERCODIA PARKING       \n"
         << "====================================\n";

    int choice;
    do {
        refreshExpiredRentals(rentals);
        rebuildOccupancy(parking, rentals);
        saveDatabase(rentals);
        showMenu();
        choice = readNumber("Choose an option: ");
        cout << '\n';

        switch (choice) {
            case 1: showRates(); break;
            case 2: makeReservation(parking, rentals); break;
            case 3: showReservations(rentals); break;
            case 4: searchRentalHistory(rentals); break;
            case 5: cout << "Thank you for using ParkClass.\n"; break;
            default: cout << "Invalid choice. Please select 1 to 5.\n";
        }

        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore(1000, '\n');
            cin.get();
            clearScreen();
        }
    } while (choice != 5);
}