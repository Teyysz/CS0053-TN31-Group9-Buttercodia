#ifndef BUTTERCODIA_PARKING_SLOTS_H
#define BUTTERCODIA_PARKING_SLOTS_H

#include <array>
#include <string>

constexpr int kParkingTierCount = 3;
constexpr int kParkingSlotsPerTier = 100;

enum class ParkingTier {
    Economy = 1,
    Business = 2,
    FirstClass = 3
};

struct ParkingState {
    // The first dimension follows ParkingTier's values: Economy, Business,
    // then FirstClass. A value of true means that the slot is occupied.
    std::array<std::array<bool, kParkingSlotsPerTier>, kParkingTierCount> occupied{};
};

bool isValidParkingTier(int choice);
ParkingTier parkingTierFromChoice(int choice);
std::string parkingTierName(ParkingTier tier);
double parkingRate(ParkingTier tier);

void showRates();
void displayParkingSlots(const ParkingState& parking, ParkingTier tier);

bool isValidSlot(int slot);
bool isSlotAvailable(const ParkingState& parking, ParkingTier tier, int slot);
bool occupySlot(ParkingState& parking, ParkingTier tier, int slot);
bool releaseSlot(ParkingState& parking, ParkingTier tier, int slot);

#endif
