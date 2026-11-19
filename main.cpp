#include "Daniel/parking_slots.h"
#include "Odda/storage.h"
#include "Patrick/reservations.h"
#include <iostream>
#include <vector>

using namespace std;

static void showMenu() {
    cout << "--------------- MENU ---------------\n"
         << "1. View parking rates\n"
         << "2. Rent a parking space\n"
         << "3. View parking rentals\n"
         << "4. Exit\n"
         << "------------------------------------\n";
}

int main() {
    ParkingState parking;
    vector<Reservation> rentals;

    loadDatabase(rentals);
    refreshExpiredRentals(rentals);
    saveDatabase(rentals);

    cout << "====================================\n"
         << "         BUTTERCODIA PARKING        \n"
         << "====================================\n";

    int choice;

    do {
        refreshExpiredRentals(rentals);
        saveDatabase(rentals);

        showMenu();
        choice = readNumber("Choose an option: ");
        cout << '\n';

        switch (choice) {
            case 1:
                showRates();
                break;

            case 2:
                makeReservation(parking, rentals);
                break;

            case 3:
                showReservations(rentals);
                break;

            case 4:
                cout << "Thank you for using Buttercodia Parking.\n";
                break;

            default:
                cout << "Invalid choice. Please select 1 to 4.\n";
                break;
        }

        if (choice != 4) {
            cout << "\nPress Enter to continue...";
            cin.ignore(1000, '\n');
            cin.get();
            clearScreen();
        }

    } while (choice != 4);

    saveDatabase(rentals);
    return 0;
}