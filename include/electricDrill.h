#ifndef ELECTRICDRILL_H
#define ELECTRICDRILL_H

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include "electricMotor.h"

class MYLIBRARY_API ElectricDrill : public ElectricMotor {
public:
    ElectricDrill();
    ElectricDrill(std::string Name, float Consumption, float Power, std::string Manufacturer);
    virtual ~ElectricDrill();
    std::string getManufacturer();
    void setManufacturer(std::string Manufacturer);

private:
    std::string manufacturer;
};

#endif