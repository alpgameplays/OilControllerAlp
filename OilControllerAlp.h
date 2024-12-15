/**
 * @file OilControllerAlp.h
 * @brief Declaration of the OilControllerAlp class for managing oil behavior.
 */
#ifndef FUEL_CONTROLLER_H
#define FUEL_CONTROLLER_H

#include <Arduino.h>
#include "OilObject.h"
#include "JsonDeserializeAlp.h"

/**
 * @class OilControllerAlp
 * @brief Manages the oil behavior based on input JSON data.
 *
 * The OilControllerAlp class interprets JSON inputs to update the oil state
 * and adjust PWM outputs accordingly.
 */
class OilControllerAlp
{
public:
    /**
     * @brief Constructor to initialize the OilControllerAlp.
     * @param oil The OilObject to control.
     */
    OilControllerAlp(OilObject oilTemp, JsonDeserializeAlp jsonDeserialize = JsonDeserializeAlp());

    /**
     * @brief Updates the oil state, validating certain conditions (e.g., "electricOn" or "engineOn").
     * @param json The input JSON string with oil-related data.
     */
    void update(const String &json);

    /**
     * @brief Directly updates the oil state without additional validation.
     * @param json The input JSON string with oil-related data.
     */
    void updateFuelState(const String &json); // Nome atualizado

    void resetPinState();

    bool canSendSignalToPin(const String &json);

private:
    OilObject _oilValue;
    JsonDeserializeAlp _jsonDeserialize;
};

#endif
