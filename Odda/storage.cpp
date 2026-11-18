#include "storage.h"
#include <fstream>
#include <sstream>
#include <algorithm>

static vector<string> split(const string& line) {
    vector<string> fields; string field; stringstream stream(line);
    while (getline(stream, field, '|')) fields.push_back(field);
    return fields;
}
bool loadDatabase(vector<Reservation>& rentals) {
    ifstream file(DATABASE_FILE); if (!file) return false;
    string line; rentals.clear();
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto f = split(line); if (f.size() < 10) continue;
        Reservation r; r.rentalNumber = stoi(f[0]); r.name=f[1]; r.plate=f[2]; r.tier=f[3];
        r.paymentMethod=f[4]; r.paymentDetails=f[5]; r.slot=stoi(f[6]); r.hours=stoi(f[7]);
        r.total=stoi(f[8]); r.startTime=stoll(f[9]);
        r.status = f.size() >= 11 && f[10] == "COMPLETED" ? RentalStatus::COMPLETED : RentalStatus::ACTIVE;
        rentals.push_back(r);
    }
    return true;
}
void saveDatabase(const vector<Reservation>& rentals) {
    ofstream file(DATABASE_FILE); if (!file) return;
    file << "# rentalNumber|name|plate|tier|paymentMethod|paymentDetails|slot|hours|total|startTime|status\n";
    for (const auto& r : rentals)
        file << r.rentalNumber << '|' << r.name << '|' << r.plate << '|' << r.tier << '|'
             << r.paymentMethod << '|' << r.paymentDetails << '|' << r.slot << '|' << r.hours << '|'
             << r.total << '|' << static_cast<long long>(r.startTime) << '|'
             << (r.status == RentalStatus::ACTIVE ? "ACTIVE" : "COMPLETED") << '\n';
}
bool refreshExpiredRentals(vector<Reservation>& rentals) {
    bool changed = false; time_t now = time(nullptr);
    for (auto& r : rentals) if (r.status == RentalStatus::ACTIVE && r.startTime > 0 &&
        now >= r.startTime + static_cast<time_t>(r.hours) * 3600) {
        r.status = RentalStatus::COMPLETED; changed = true;
    }
    return changed;
}
int nextRentalNumber(const vector<Reservation>& rentals) {
    int highest = 1000;
    for (const auto& r : rentals) highest = max(highest, r.rentalNumber);
    return highest + 1;
}
