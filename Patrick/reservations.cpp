#include "reservations.h"
#include <cctype>
#include <iostream>

using namespace std;

static int rateFor(const string& tier) {
    return tier == "Economy" ? 35 : (tier == "Business" ? 55 : 85);
}
static string chooseTier() {
    int choice = readNumber("Choose a tier (0 to cancel): ");
    if (choice == 1) return "Economy";
    if (choice == 2) return "Business";
    if (choice == 3) return "First Class";
    return {};
}
static bool validCard(const string& digits) {
    if (digits.size() != 4) return false;
    for (unsigned char c : digits) if (!isdigit(c)) return false;
    return true;
}
static void collectPayment(Reservation& r) {
    cout << "1. Cash\n2. Card\n3. E-wallet\n";
    int method = readNumber("Choose a payment method: ");
    if (method == 1) { r.paymentMethod = "Cash"; r.paymentDetails = "Pay at the parking counter"; }
    else if (method == 2) {
        r.paymentMethod = "Card"; cin.ignore(1000, '\n');
        do { cout << "Enter exactly the last 4 digits of the card: "; getline(cin, r.paymentDetails); }
        while (!validCard(r.paymentDetails));
    } else if (method == 3) {
        r.paymentMethod = "E-wallet"; cin.ignore(1000, '\n');
        cout << "Enter the e-wallet reference: "; getline(cin, r.paymentDetails);
    }
}

void makeReservation(ParkingState& parking, vector<Reservation>& rentals) {
    Reservation r;
    r.rentalNumber = nextRentalNumber(rentals);
    cout << "\nParking tiers:\n1. Economy - P35\n2. Business - P55\n3. First Class - P85\n";
    r.tier = chooseTier();
    if (r.tier.empty()) { cout << "Rental cancelled.\n"; return; }
    while (true) {
        showSlots(parking, r.tier);
        r.slot = readNumber("\nEnter an available slot (0 to cancel): ");
        if (r.slot == 0) { cout << "Rental cancelled.\n"; return; }
        if (r.slot >= 1 && r.slot <= SLOT_COUNT && !parking.occupied[tierIndex(r.tier)][r.slot - 1]) break;
        cout << "That slot is not available.\n";
    }
    cin.ignore(1000, '\n');
    cout << "Customer name: "; getline(cin, r.name);
    cout << "Plate number: "; getline(cin, r.plate);
    r.hours = readNumber("Number of hours: ");
    while (r.hours <= 0) r.hours = readNumber("Hours must be greater than zero: ");
    collectPayment(r);
    r.total = rateFor(r.tier) * r.hours;
    cout << "\nRental R" << r.rentalNumber << " | " << r.name << " | " << r.tier
         << " | Slot " << r.slot << " | Total P" << r.total << ".00\n";
    if (readNumber("1. Confirm rental  2. Cancel: ") != 1) { cout << "Rental cancelled.\n"; return; }
    r.startTime = time(nullptr); r.status = RentalStatus::ACTIVE;
    rentals.push_back(r); rebuildOccupancy(parking, rentals); saveDatabase(rentals);
    cout << "Parking space rental created successfully! Rental number: R" << r.rentalNumber << '\n';
}

void showReservations(const vector<Reservation>& rentals) {
    if (rentals.empty()) { cout << "No parking rentals yet.\n"; return; }
    for (const auto& r : rentals)
        cout << "\nR" << r.rentalNumber << " | " << (r.status == RentalStatus::ACTIVE ? "ACTIVE" : "COMPLETED")
             << " | " << r.name << " | " << r.plate << " | " << r.tier << " | Slot " << r.slot
             << " | " << r.hours << " hours | " << r.paymentMethod << " | P" << r.total << ".00\n";
}

int readNumber(const string& message) {
    int value;
    while (true) { cout << message; cin >> value; if (!cin.fail()) return value;
        cout << "Please enter a whole number.\n"; cin.clear(); cin.ignore(1000, '\n'); }
}
void clearScreen() { cout << string(35, '\n'); }
