#include "GasCar.h"

GasCar::GasCar(const std::string& make, const std::string& model,
               const std::string& color, int year,
               double fuelCapacity, double efficiency)
                : Vehicle(make, model, color, year),   // base class is built first
              fuelCapacity(fuelCapacity),
              efficiency(efficiency)
{
}

double GasCar::GetFuelCapacity() const
{
    return fuelCapacity;
}

double GasCar::GetFuelEfficiency() const
{
    return efficiency;
}

double GasCar::GetRangeMiles() const
{
    return fuelCapacity * efficiency;
}

std::string GasCar::GetPropulsionType() const
{
    return "Gas";
}

void GasCar::Print(std::ostream& os) const
{
    Vehicle::Print(os);
    os << " | " << fuelCapacity << " gal, "
       << efficiency << " MPG, "
       << GetRangeMiles() << " mi range";
}
