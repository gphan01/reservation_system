#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "Vehicle.h"

/* Owns the fleet of cars, the current date, and all reservations.
 * All reservation rules are enforced here, no other code modifies the reservations
 * directly
 */
class Database
{
public:
    static constexpr std::size_t MAX_VEHICLES = 50;
    static constexpr std::size_t MAX_RESERVATIONS = 3;

    enum class SearchField { Make, Model, Propulsion, Color, Year};

    enum class ReserveResult
    {
        Ok,
        BadIndex, /* No vehicle at the index */
        NotFuture, /* day <= current data */
        AlreadyReserved,  /* Vehicle already reserved that day */
        LimitReached, /* Vehicle has reached the MAX_RESERVATIONS allowable */
    };

    /* Takes ownership of the vehicle.
     * Returns false if the fleet is full
     */
    bool AddVehicle(std::unique_ptr<Vehicle> vehicle);

    /* Reserves the vehicle at the index for the day.
     * Returns Ok on success. otherwise the reason it failed.
    */
    ReserveResult Reserve(std::size_t index, int day);

    /* Advances the date by one and drops the reservations that have passed. */
    void AdvanceDate();

    /* Returns the indices of vehicles whose field matches the value. */
    std::vector<std::size_t> Search(SearchField field, const std::string& value) const;

    int GetCurrentDate() const;
    std::size_t GetVehicleCount() const;

    void PrintAll(std::ostream& os) const;
    void PrintReserved(std::ostream& os) const;
    void PrintAvailable(std::ostream& os) const;
    void PrintVehicle(std::ostream& os, std::size_t index) const;

private:
    struct Entry {
        std::unique_ptr<Vehicle> vehicle;
        std::vector<int> reservedDays;
    };

    std::vector<Entry> fleet;
    int currentDate = 1;
};

#endif
