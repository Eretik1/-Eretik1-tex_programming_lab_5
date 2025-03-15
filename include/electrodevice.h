#ifndef ELECTRODEVICE_H
#define ELECTRODEVICE_H

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include <string>

class MYLIBRARY_API Electrodevice {
public:
    Electrodevice();
    Electrodevice(std::string Name, float Consumption);
    virtual ~Electrodevice();
    std::string getName();
    void setName(std::string Name);
    float getConsumption();
    void setConsumption(float Consumption);
    void activate();
    bool getStatus();

private:
    std::string name;
    bool status = 0;
    float consumption;
};

#endif