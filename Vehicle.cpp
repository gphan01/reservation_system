#include "Vehicle.h"

Vehicle::Vehicle(const std::string& make, const std::string& model,  const std::string& color, int year)
                        : make(make), model(model), color(color), year(year)
{}


std::string Vehicle::GetMake() const
{
    return make;
}

std::string Vehicle::GetModel() const
{
    return model;
}

std::string Vehicle::GetColor() const
{
    return color;
}

int Vehicle::GetYear() const
{
    return year;
}

void Vehicle::Print(std::ostream& os) const
{
  os << year << ' ' << make << ' ' << model << " (" << color << ", " << GetPropulsionType() << ')';
}

