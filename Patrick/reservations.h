#pragma once

#include "../Daniel/parking_slots.h"
#include "../Odda/storage.h"

#include <string>
#include <vector>

void makeReservation(
    ParkingState& parking,
    std::vector<Reservation>& rentals
);

void showReservations(
    const std::vector<Reservation>& rentals
);

int readNumber(const std::string& message);
void clearScreen();