#ifndef HEATINGELEMENT_H
#define HEATINGELEMENT_H

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include "electrodevice.h"

class MYLIBRARY_API HeatingElement : public Electrodevice {
public:
    HeatingElement();
    HeatingElement(std::string Name, float Consumption, float HeatGeneration);
    virtual ~HeatingElement();
    float getHeatGeneration();
    void setHeatGeneration(float HeatGeneration);

private:
    float heatGeneration;
};

#endif