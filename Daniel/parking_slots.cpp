#include "parking_slots.h"

#include <iomanip>
#include <iostream>

namespace {

int tierIndex(ParkingTier tier) {
    return static_cast<int>(tier) - 1;
}

bool hasValidTierIndex(ParkingTier tier) {
    const int index = tierIndex(tier);
    return index >= 0 && index < kParkingTierCount;
}

} // namespace

bool isValidParkingTier(int choice) {
    return choice >= static_cast<int>(ParkingTier::Economy) &&
           choice <= static_cast<int>(ParkingTier::FirstClass);
}

ParkingTier parkingTierFromChoice(int choice) {
    if (!isValidParkingTier(choice)) {
        return ParkingTier::Economy;
    }
    return static_cast<ParkingTier>(choice);
}

std::string parkingTierName(ParkingTier tier) {
    switch (tier) {
        case ParkingTier::Economy:
            return "Economy";
        case ParkingTier::Business:
            return "Business";
        case ParkingTier::FirstClass:
            return "First Class";
    }
    return "Unknown";
}

double parkingRate(ParkingTier tier) {
    switch (tier) {
        case ParkingTier::Economy:
            return 35.0;
        case ParkingTier::Business:
            return 55.0;
        case ParkingTier::FirstClass:
            return 85.0;
    }
    return 0.0;
}

void showRates() {
    std::cout << "\nParking Rates (per hour)\n"
              << "1. Economy     - PHP " << parkingRate(ParkingTier::Economy) << "\n"
              << "2. Business    - PHP " << parkingRate(ParkingTier::Business) << "\n"
              << "3. First Class - PHP " << parkingRate(ParkingTier::FirstClass) << "\n";
}

void displayParkingSlots(const ParkingState& parking, ParkingTier tier) {
    if (!hasValidTierIndex(tier)) {
        std::cout << "Invalid parking tier.\n";
        return;
    }

    const auto& slots = parking.occupied[tierIndex(tier)];
    std::cout << "\n" << parkingTierName(tier) << " parking slots\n"
              << "O = available, X = occupied\n";

    for (int slot = 0; slot < kParkingSlotsPerTier; ++slot) {
        std::cout << std::setw(3) << slot + 1 << ":" << (slots[slot] ? 'X' : 'O') << "  ";
        if ((slot + 1) % 10 == 0) {
            std::cout << '\n';
        }
    }
}

bool isValidSlot(int slot) {
    return slot >= 1 && slot <= kParkingSlotsPerTier;
}

bool isSlotAvailable(const ParkingState& parking, ParkingTier tier, int slot) {
    return hasValidTierIndex(tier) && isValidSlot(slot) &&
           !parking.occupied[tierIndex(tier)][slot - 1];
}

bool occupySlot(ParkingState& parking, ParkingTier tier, int slot) {
    if (!isSlotAvailable(parking, tier, slot)) {
        return false;
    }
    parking.occupied[tierIndex(tier)][slot - 1] = true;
    return true;
}

bool releaseSlot(ParkingState& parking, ParkingTier tier, int slot) {
    if (!hasValidTierIndex(tier) || !isValidSlot(slot) ||
        !parking.occupied[tierIndex(tier)][slot - 1]) {
        return false;
    }
    parking.occupied[tierIndex(tier)][slot - 1] = false;
    return true;
}
