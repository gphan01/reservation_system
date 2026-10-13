#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H

#include <ostream>
#include <string>
#include "Vehicle.h"

/* A battery electric vehicle.
 * Adds range and efficiency on top of the common Vehicle fields.
 *
 * Example:
 *      ElectricCar car("Tesla", "Model 3", "White", 2020, 310, 
 *      4.1);
 *      car.GetPropulsionType(); //Electric
 *      car.GetRangeMiles();  // 310
 */

class ElectricCar : public Vehicle
{
public:
    ElectricCar(const std::string& make, const std::string& model, const std::string& color,
                int year, int energyCapacity, double efficiency);

    /* Battery energy capacity in kWh */
    int GetEnergyCapacity() const;

    /* Efficiency in miles per kWh */
    double GetEfficiency() const;

    /* Range on a full charge, in miles: energy capacity * efficiency */
    double GetRangeMiles() const override;

    /* Returns "Electric"*/
    std::string GetPropulsionType() const override;

    /* Prints the vehicle fields, then capacity, effiency, and range */
    void Print(std::ostream& os) const override;

private:
    double energyCapacity;
    double efficiency;
};

#endif
