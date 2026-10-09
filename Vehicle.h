#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ostream>

/* Abstract base class.
 * Every vehicle has a make, model, and year.
 * Derived classes must say how they are powered.
 */
class Vehicle
{
    public:
        Vehicle(const std::string& make, const std::string& model, 
                const std::string& color, int year);
        virtual ~Vehicle() = default;


        // Accessors
        std::string GetMake() const;
        std::string GetModel() const;
        std::string GetColor() const;
        int GetYear() const;

        /* Pure virtual returns the propulsion type, Gas or Electric. */
        virtual std::string GetPropulsionType() const = 0;

        /* Prints the fields common to all vehicles: year, make, model, color and propulsion type.
         * Derived classes override this method to append their own fields.
         * Example:
         *          Vehicle:Print(os)
         */
        virtual void Print(std::ostream& os) const;
        
    private:
        std::string make;
        std::string model;
        std::string color;
        int year;
};

#endif
