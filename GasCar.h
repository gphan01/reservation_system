#ifndef GASCAR_H
#define GASCAR_H

#include <ostream>
#include <string>
#include "Vehicle.h"

/* A gas powered vehicle.
 * Adds fuel efficiency on top of the common Vehicle fields.
 *
 * Example:
 *      GasCar car("Honda", "Civic", "White", 2020, 35.0);
 *      car.GetPropulsionType(); // Gas
 *      car.Print(std::cout); // 2020 Honda Civic (White, Gas)
 *
 */
class GasCar : public Vehicle
{
public:
    GasCar(const std::string& make, const std::string& model,
               const std::string& color, int year, double fuelCapacity, double effieciency);

    /* Fuel tank capacity in gallons." */
    double GetFuelCapacity() const;

    /* Fuel efficiency in miles per gallon */
    double GetFuelEfficiency() const;

    /* Range on a full tank, in miles: fuel capacity * effiency */
    double GetRangeMiles() const override;

    /* Returns "Gas" */
    std::string GetPropulsionType() const override;

    /* Prints the common vehicle fields, then the the MPG */
    void Print(std::ostream& os) const override;

private:
    double fuelCapacity;
    double efficiency;
};

#endif
