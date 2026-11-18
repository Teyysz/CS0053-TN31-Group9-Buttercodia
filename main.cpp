#include "../Daniel/parking_slots.h"
#include "../Patrick/reservations.h"
#include "../Odda/storage.h"
#include <iostream>
#include <vector>

using namespace std;

static void showMenu() {
    cout << "--------------- MENU ---------------\n"
         << "1. View parking rates\n"
         << "2. Rent a parking space\n"
         << "3. View parking rentals\n"
         << "4. Search rental history\n"
         << "5. View rental summary\n"
         << "6. Exit\n"
         << "------------------------------------\n";
}

static void showRentalSummary(const vector<Reservation>& rentals) {
    const int active = countRentalsByStatus(rentals, RentalStatus::ACTIVE);
    const int completed = countRentalsByStatus(rentals, RentalStatus::COMPLETED);
    cout << "Rental Summary\n"
         << "Total rentals: " << rentals.size() << '\n'
         << "Active rentals: " << active << '\n'
         << "Completed rentals: " << completed << '\n';
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
            case 5: showRentalSummary(rentals); break;
            case 6: cout << "Thank you for using Buttercodia Parking.\n"; break;
            default: cout << "Invalid choice. Please select 1 to 6.\n";
        }

        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore(1000, '\n');
            cin.get();
            clearScreen();
        }
    } while (choice != 6);
}
