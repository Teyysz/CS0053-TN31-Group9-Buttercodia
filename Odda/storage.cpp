#include "storage.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <algorithm>

static vector<string> split(const string& line) {
    vector<string> fields; string field; stringstream stream(line);
    while (getline(stream, field, '|')) fields.push_back(field);
    return fields;
}

static bool parseInt(const string& text, int& value) {
    istringstream stream(text);
    stream >> value;
    return stream && stream.eof();
}

static bool parseTime(const string& text, time_t& value) {
    long long parsed = 0;
    istringstream stream(text);
    stream >> parsed;
    if (!stream || !stream.eof() ||
        parsed < static_cast<long long>(numeric_limits<time_t>::min()) ||
        parsed > static_cast<long long>(numeric_limits<time_t>::max())) {
        return false;
    }
    value = static_cast<time_t>(parsed);
    return true;
}

bool loadDatabase(vector<Reservation>& rentals) {
    ifstream file(DATABASE_FILE); if (!file) return false;
    string line; rentals.clear();
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto f = split(line); if (f.size() < 10 || f.size() > 11) continue;
        Reservation r;
        if (!parseInt(f[0], r.rentalNumber) || !parseInt(f[6], r.slot) ||
            !parseInt(f[7], r.hours) || !parseInt(f[8], r.total) ||
            !parseTime(f[9], r.startTime)) {
            continue;
        }
        r.name=f[1]; r.plate=f[2]; r.tier=f[3];
        r.paymentMethod=f[4]; r.paymentDetails=f[5];
        if (f.size() == 11 && f[10] != "ACTIVE" && f[10] != "COMPLETED") continue;
        r.status = f.size() == 11 && f[10] == "COMPLETED" ? RentalStatus::COMPLETED : RentalStatus::ACTIVE;
        rentals.push_back(r);
    }
    return true;
}
bool saveDatabase(const vector<Reservation>& rentals) {
    ofstream file(DATABASE_FILE);
    if (!file) {
        cerr << "Unable to open " << DATABASE_FILE << " for saving.\n";
        return false;
    }
    file << "# rentalNumber|name|plate|tier|paymentMethod|paymentDetails|slot|hours|total|startTime|status\n";
    for (const auto& r : rentals)
        file << r.rentalNumber << '|' << r.name << '|' << r.plate << '|' << r.tier << '|'
             << r.paymentMethod << '|' << r.paymentDetails << '|' << r.slot << '|' << r.hours << '|'
             << r.total << '|' << static_cast<long long>(r.startTime) << '|'
             << (r.status == RentalStatus::ACTIVE ? "ACTIVE" : "COMPLETED") << '\n';
    if (!file) {
        cerr << "Unable to finish saving " << DATABASE_FILE << ".\n";
        return false;
    }
    return true;
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

int countRentalsByStatus(const vector<Reservation>& rentals, RentalStatus status) {
    return static_cast<int>(count_if(rentals.begin(), rentals.end(),
        [status](const Reservation& rental) { return rental.status == status; }));
}
