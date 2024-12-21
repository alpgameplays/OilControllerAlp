#include <FuelController.h>
#include <OilControllerAlp.h>


int FUEL_PIN = 5;  // Pin 5
/** 
  PWM de 0 a 30
*/
int FUEL_PWM_MAX = 210;
int FUEL_PWM_MIN = 0;
// INITIAL VALUE TO FUEL THAT ONE IS EMPTY. 100 EMPTY AND 0 FULL
int FUEL_INITIAL_STATE = 500;

FuelObject fuel(FUEL_PIN, FUEL_PWM_MIN, FUEL_PWM_MAX, FUEL_INITIAL_STATE);
FuelController fuelControl(fuel);


int PRESSURE_OIL_PIN = 3;  // Pin 3
int PRESSURE_OIL_PWM_MAX = 255;
int PRESSURE_OIL_PWM_MIN = 125;
// int PRESSURE_OIL_PWM_MIN = 100;
int PRESSURE_OIL_INITIAL_STATE = 255;
int PRESSURE_OIL_CAPACITY = 100;
int PRESSURE_OIL_MIN_CAPACITY = 0;
char* PRESSURE_OIL_KEY = "oilPressure";

OilObject oilPressure(PRESSURE_OIL_PIN, PRESSURE_OIL_PWM_MIN, PRESSURE_OIL_PWM_MAX, PRESSURE_OIL_INITIAL_STATE, PRESSURE_OIL_CAPACITY, PRESSURE_OIL_MIN_CAPACITY, PRESSURE_OIL_KEY);
OilControllerAlp oilPressureControl(oilPressure);

int TEMP_OIL_PIN = 6;
int TEMP_OIL_PWM_MAX = 75;
int TEMP_OIL_PWM_MIN = 210;
int TEMP_OIL_INITIAL_STATE = 0;
int TEMP_OIL_CAPACITY = 150;
int TEMP_OIL_MIN_CAPACITY = 50;

char* TEMP_OIL_KEY = "oilTemperature";


OilObject oilTemp(TEMP_OIL_PIN, TEMP_OIL_PWM_MIN, TEMP_OIL_PWM_MAX, TEMP_OIL_INITIAL_STATE, TEMP_OIL_CAPACITY, TEMP_OIL_MIN_CAPACITY, TEMP_OIL_KEY);
OilControllerAlp oilTempControl(oilTemp);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("DEVICE TO TELEMETRY FUEL, OIL/PSI AND OIL/TMP");

  // Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String json = Serial.readStringUntil('\n');
    // Serial.println(json);
    const bool canUpdate = fuelControl.canSendSignalToPin(json);
    // Serial.println(canUpdate);
    if (canUpdate) {
      fuelControl.updateFuelState(json);
      // fuelControl.update(json);
      oilPressureControl.updateOilState(json);
      // oilPressureControl.update(json);
      // oilTempControl.update(json);
      oilTempControl.updateOilState(json);
    }else{
      fuelControl.resetPinState();
      oilPressureControl.resetPinState();
      oilTempControl.resetPinState();
      
    }
  }
}
