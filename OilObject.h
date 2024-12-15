/**
 * @file OilObject.h
 * @brief Declaration of the OilObject class, representing basic oil system attributes.
 */
#ifndef OIL_OBJECT_H
#define OIL_OBJECT_H

#include <Arduino.h>

/**
 * @class OilObject
 * @brief Represents a oil control object with essential attributes.
 *
 * The OilObject class encapsulates data related to a PWM output pin,
 * minimum and maximum PWM values, and the current oil state.
 */
class OilObject
{
public:
    /**
     * @brief Constructor to initialize the OilObject.
     * @param pin The output pin number for PWM.
     * @param minPWM The minimum PWM value.
     * @param maxPWM The maximum PWM value.
     * @param currentStateOil The initial oil state.
     */
    OilObject(int pin, int minPWM, int maxPWM, int currentStateOil, float oilCapacity, char* jsonKey)
        : _pin(pin), _minPWM(minPWM), _maxPWM(maxPWM), _currentStateOil(currentStateOil), _defaultInitalValue(currentStateOil), _oilCapacity(oilCapacity), _jsonKey(jsonKey) {}

    int getPin() const { return _pin; }
    int getMinPWM() const { return _minPWM; }
    int getMaxPWM() const { return _maxPWM; }
    int getCurrentStateOil() const { return _currentStateOil; }
    int getOilCapacity() const { return _oilCapacity; }
    char* getJsonKey() const { return _jsonKey; }
    int getDefaultInitialValue() const { return _defaultInitalValue; }
    void setCurrentStateOil(int value) { _currentStateOil = value; }

private:
    int _pin;
    int _minPWM;
    int _maxPWM;
    int _currentStateOil;
    int _defaultInitalValue;
    float _oilCapacity;
    char* _jsonKey;
};

#endif
