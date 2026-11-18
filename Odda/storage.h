#pragma once
#include <ctime>
#include <string>
#include <vector>

using namespace std;
const int SLOT_COUNT = 100;
const char DATABASE_FILE[] = "buttercodia_database.txt";

enum class RentalStatus { ACTIVE, COMPLETED };
struct Reservation {
    int rentalNumber = 0, slot = 0, hours = 0, total = 0;
    string name, plate, tier, paymentMethod, paymentDetails;
    time_t startTime = 0;
    RentalStatus status = RentalStatus::ACTIVE;
};

bool loadDatabase(vector<Reservation>& rentals);
void saveDatabase(const vector<Reservation>& rentals);
bool refreshExpiredRentals(vector<Reservation>& rentals);
int nextRentalNumber(const vector<Reservation>& rentals);
