#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include <memory>
#include <string>
#include "electrodevice.h"  
#include "heatingElement.h" 
#include "electricMotor.h"  
#include "electricDrill.h"  

class Electrodevice;
class HeatingElement;
class ElectricMotor;
class ElectricDrill;

class IDeviceFactory {
public:
    virtual ~IDeviceFactory() {}
    virtual std::shared_ptr<Electrodevice> createElectrodevice(const std::string& name, float consumption) = 0;
    virtual std::shared_ptr<HeatingElement> createHeatingElement(const std::string& name, float consumption, float heatGeneration) = 0;
    virtual std::shared_ptr<ElectricMotor> createElectricMotor(const std::string& name, float consumption, float power) = 0;
    virtual std::shared_ptr<ElectricDrill> createElectricDrill(const std::string& name, float consumption, float power, const std::string& manufacturer) = 0;
};

extern "C" MYLIBRARY_API IDeviceFactory* createDeviceFactory();

#endif