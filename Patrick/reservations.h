#pragma once
#include "../Daniel/parking_slots.h"

void makeReservation(ParkingState& parking, vector<Reservation>& rentals);
void showReservations(const vector<Reservation>& rentals);
int readNumber(const string& message);
void clearScreen();
