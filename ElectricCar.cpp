#include "ElectricCar.h"

ElectricCar::ElectricCar(const std::string& make, const std::string& model,
                         const std::string& color, int year,
                         double energyCapacity, double efficiency)
                        : Vehicle(make, model, color, year),   // base class is built first
                          energyCapacity(energyCapacity),
                          efficiency(efficiency)
{}

double ElectricCar::GetEnergyCapacity() const
{
    return energyCapacity;
}

double ElectricCar::GetEfficiency() const
{
    return efficiency;
}

double ElectricCar::GetRangeMiles() const
{
    return energyCapacity * efficiency;
}

std::string ElectricCar::GetPropulsionType() const
{
    return "Electric";
}

void ElectricCar::Print(std::ostream& os) const
{
    Vehicle::Print(os);
    os << " | " << energyCapacity << " kWh, "
       << efficiency << " mi/kWh, "
       << GetRangeMiles() << " mi range";
}
