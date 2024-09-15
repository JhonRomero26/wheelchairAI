#ifndef WHEELCHAIR_H
#define WHEELCHAIR_H

#include "Arduino.h"
#include "BLEWheelchair.h"
#include "SabertoothSimplified.h"
#include "utils.h"


#define MAX_SPEED_MOTOR 127  // max speed motor

#ifndef TIME_FOR_MOVE
  #define TIME_FOR_MOVE  180   // time for move in ms
#endif

#ifndef TIME_FOR_STOP
  #define TIME_FOR_STOP  50   // time for stop in ms
#endif

// MOVEMENT_COMMAND
#define WHEELCHAIR_MOVE_FORWARD "mf"
#define WHEELCHAIR_MOVE_LEFT "ml"
#define WHEELCHAIR_MOVE_BACKWARD "mb"
#define WHEELCHAIR_MOVE_RIGHT_OFF "r0"
#define WHEELCHAIR_MOVE_LEFT_OFF "l0"
#define WHEELCHAIR_MOVE_RIGHT "mr"
#define WHEELCHAIR_MOVE_STOP "ms"
#define WHEELCHAIR_ROTATE_LEFT "rl"
#define WHEELCHAIR_ROTATE_RIGHT "rr"
#define WHEELCHAIR_ROTATE_LEFT_VOICE "rlv"
#define WHEELCHAIR_ROTATE_RIGHT_VOICE "rrv"

// SPEED_COMMAND
#define WHEELCHAIR_SPEED_SLOW "sv"
#define WHEELCHAIR_SPEED_MEDIUM "nv"
#define WHEELCHAIR_SPEED_FAST "fv"

#define WHEELCHAIR_ROTATE_SPEED 13

#define WHEELCHAIR_SPEED_SLOW_VAlUE 0.14
#define WHEELCHAIR_SPEED_MEDIUM_VAlUE 0.20
#define WHEELCHAIR_SPEED_FAST_VAlUE 0.25

#define WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT 0.75

// CORRECTIONS COMMANDS
#define WHEELCHAIR_ENGINE_CORRECTION_PERCENT 0.85
#define WHEELCHAIR_MAX_SPEED_CORRECTION 0.78
#define WHEELCHAIR_ENGINE_CORRECTION_CMD "ec"
#define WHEELCHAIR_SPEED_CORRECTION_CMD "ac"
#define WHEELCHAIR_VALUE_SEPARATOR_CMD "="

enum MOTORS {
  MOTOR_LEFT = 1,
  MOTOR_RIGHT = 2
};

class Wheelchair {
  private:
    BLEWheelchair ble = BLEWheelchair();
    SabertoothSimplified st = SabertoothSimplified();
    int leftEngineSpeed = 0;
    int rightEngineSpeed = 0;
    int acceleration = 2;
    float speedPercent = WHEELCHAIR_SPEED_SLOW_VAlUE;
    float engineCorection = WHEELCHAIR_ENGINE_CORRECTION_PERCENT;
    double maxSpeedCorection = WHEELCHAIR_MAX_SPEED_CORRECTION;
    
    std::string directionCommand = WHEELCHAIR_MOVE_STOP;
    std::string oldCmd = "";

    unsigned long prevMoveTime = 0;

  private:
    void moveForward();
    void stop();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void rotateLeft();
    void rotateRight();
    void movements(const std::string *cmd);
    void adjustSpeed(int& speed, int targetSpeed);
    void adjustSpeed(int& speed, int targetSpeed, int acceleration);

  public:
    void begin(int bauds);
    void loop();
};

#endif
