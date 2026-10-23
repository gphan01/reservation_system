#include "Database.h"

#include <algorithm>
#include <cctype>

/* Helper function */
namespace
{

/* Returns a lowercase copy of s, for case-insensitive compares. */
std::string ToLower(const std::string& s)
{
    std::string out = s;
    for (char& c : out)
    {
        // Cast to unsigned char first: tolower on a negative char is UB.
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return out;
}

}

bool Database::AddVehicle(std::unique_ptr<Vehicle> vehicle)
{
    if (!vehicle || fleet.size() >= MAX_VEHICLES)
    {
        return false;
    }

    // unique_ptr can only moved, ownership is now to the fleet.
    fleet.push_back(Entry{std::move(vehicle), {}});
    return true;
}

std::vector<std::size_t> Database::Search(SearchField field, const std::string& value) const
{
    std::vector<std::size_t> matches;
    const std::string target = ToLower(value);

    for (std::size_t i = 0; i < fleet.size(); ++i)
    {
        const Vehicle& v = *fleet[i].vehicle;
        std::string candidate;

        switch (field)
        {
            case SearchField::Make:       candidate = v.GetMake();                 break;
            case SearchField::Model:      candidate = v.GetModel();                break;
            case SearchField::Color:      candidate = v.GetColor();                break;
            case SearchField::Propulsion: candidate = v.GetPropulsionType();       break;
            case SearchField::Year:       candidate = std::to_string(v.GetYear()); break;
        }

        if (ToLower(candidate) == target)
        {
            // Add the element
            matches.push_back(i);
        }
    }

    return matches;
}

Database::ReserveResult Database::Reserve(std::size_t index, int day)
{
    if (index >= fleet.size())
    {
        return ReserveResult::BadIndex;
    }

    if (day <= currentDate)
    {
        return ReserveResult::NotFuture;
    }

    std::vector<int>& days = fleet[index].reservedDays;

    if (std::find(days.begin(), days.end(), day) != days.end())
    {
        return ReserveResult::AlreadyReserved;
    }

    if (days.size() >= MAX_RESERVATIONS)
    {
        return ReserveResult::LimitReached;
    }

    days.push_back(day);
    std::sort(days.begin(), days.end());   // keeps printouts in date order
    return ReserveResult::Ok;
}

void Database::AdvanceDate()
{
    ++currentDate;

    // Drop reservations whose day has passed.
    for (Entry& entry : fleet)
    {
        std::vector<int>& days = entry.reservedDays;
        days.erase(std::remove_if(days.begin(), days.end(),
                                  [this](int day) { return day < currentDate; }),
                   days.end());
    }
}

int Database::GetCurrentDate() const
{
    return currentDate;
}

std::size_t Database::GetVehicleCount() const
{
    return fleet.size();
}

void Database::PrintVehicle(std::ostream& os, std::size_t index) const
{
    if (index >= fleet.size())
    {
        return;
    }

    const Entry& entry = fleet[index];

    os << '[' << index << "] ";
    entry.vehicle->Print(os);

    if (!entry.reservedDays.empty())
    {
        os << " | reserved: ";
        for (std::size_t i = 0; i < entry.reservedDays.size(); ++i)
        {
            if (i > 0)
            {
                os << ", ";
            }
            os << entry.reservedDays[i];
        }
    }

    os << '\n';
}

void Database::PrintAll(std::ostream& os) const
{
    for (std::size_t i = 0; i < fleet.size(); ++i)
    {
        PrintVehicle(os, i);
    }
}

void Database::PrintReserved(std::ostream& os) const
{
    for (std::size_t i = 0; i < fleet.size(); ++i)
    {
        if (!fleet[i].reservedDays.empty())
        {
            PrintVehicle(os, i);
        }
    }
}

void Database::PrintAvailable(std::ostream& os) const
{
    for (std::size_t i = 0; i < fleet.size(); ++i)
    {
        if (fleet[i].reservedDays.empty())
        {
            PrintVehicle(os, i);
        }
    }
}
