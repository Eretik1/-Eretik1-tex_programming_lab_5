#ifndef ELECTRICMOTOR_H
#define ELECTRICMOTOR_H

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include "electrodevice.h"

class MYLIBRARY_API ElectricMotor : public Electrodevice {
public:
    ElectricMotor();
    ElectricMotor(std::string Name, float Consumption, float Power);
    virtual ~ElectricMotor();
    float getPower();
    void setPower(float Power);

private:
    float power;
};

#endif