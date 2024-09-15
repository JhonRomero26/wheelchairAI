#include "Wheelchair.h"


bool debug = true;
unsigned long testTime = 0;


bool isLeftRightCommand(const std::string* cmd) {
  return *cmd == WHEELCHAIR_MOVE_LEFT ||
          *cmd == WHEELCHAIR_MOVE_RIGHT ||
          *cmd == WHEELCHAIR_ROTATE_RIGHT ||
          *cmd == WHEELCHAIR_ROTATE_LEFT;
}

bool isMovesCommand(const std::string* cmd) {
  return *cmd == WHEELCHAIR_MOVE_FORWARD ||
          *cmd == WHEELCHAIR_MOVE_BACKWARD ||
          *cmd == WHEELCHAIR_MOVE_STOP;
}

bool isOffLeftRightCommand(const std::string* cmd) {
  return *cmd == WHEELCHAIR_MOVE_LEFT_OFF ||
          *cmd == WHEELCHAIR_MOVE_RIGHT_OFF;
}


void Wheelchair::begin(int bauds) {
  SabertoothTXPinSerial.begin(bauds);
  ble.begin("Hanalab Wheelchair");

  if (debug) {
    st.motor(MOTOR_LEFT, 0);
    st.motor(MOTOR_RIGHT, 0);
  } else {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
    Serial.printf(">Engine correction: %f\n", this->engineCorection);
    Serial.printf(">Acceleration: %d\n", this->acceleration);
  }
}

void Wheelchair::loop() {
  ble.checkToReconnect();

  if (
    !ble.isConnected() &&
    leftEngineSpeed != 0 &&
    rightEngineSpeed != 0
  ) {
    ble.getControlCharacteristic()->setValue("ms");
    stop();
    return;
  };

  const std::string cmd = trim(ble.getControlCharacteristic()->getValue());

  const size_t separatorIndex = cmd.find(WHEELCHAIR_VALUE_SEPARATOR_CMD);
  if (separatorIndex > 0) {
    if (cmd.rfind(WHEELCHAIR_ENGINE_CORRECTION_CMD, 0) == 0) {
      float data = std::stof(cmd.substr(separatorIndex + 1));
      this->engineCorection = data / 100; 
      if (debug) Serial.printf(">Engine correction: %f\n", this->engineCorection);
    }
    if (cmd.rfind(WHEELCHAIR_SPEED_CORRECTION_CMD, 0) == 0) {
      this->acceleration = std::stoi(cmd.substr(separatorIndex + 1));
      if (debug) Serial.printf(">Acceleration: %d\n", this->acceleration);
    }
  }

  if (cmd == WHEELCHAIR_SPEED_SLOW) {
    this->speedPercent = WHEELCHAIR_SPEED_SLOW_VAlUE;
  } else if (cmd == WHEELCHAIR_SPEED_MEDIUM) {
    this->speedPercent = WHEELCHAIR_SPEED_MEDIUM_VAlUE;
  } else if (cmd == WHEELCHAIR_SPEED_FAST) {
    this->speedPercent = WHEELCHAIR_SPEED_FAST_VAlUE;
  }

  movements(&cmd);
}

void Wheelchair::movements(const std::string* cmd) {
  if (isMovesCommand(cmd)) {
    directionCommand = *cmd;
  } else if (isLeftRightCommand(cmd)) {
    if (*cmd != directionCommand) oldCmd = directionCommand;
    directionCommand = *cmd;
  } else if (isOffLeftRightCommand(cmd)) {
    directionCommand = oldCmd;
  }


  if (
    directionCommand == WHEELCHAIR_MOVE_LEFT) {
      moveLeft();
  } else if (directionCommand == WHEELCHAIR_MOVE_RIGHT) {
      moveRight();
  } else if (directionCommand == WHEELCHAIR_ROTATE_LEFT) {
      rotateLeft();
  } else if (directionCommand == WHEELCHAIR_ROTATE_RIGHT) {
      rotateRight();
  } else if (directionCommand == WHEELCHAIR_MOVE_FORWARD) {
      moveForward();
  } else if (directionCommand == WHEELCHAIR_MOVE_STOP) {
      stop();
  } else if (directionCommand == WHEELCHAIR_MOVE_BACKWARD) {
      moveBackward();
  }
}

void Wheelchair::adjustSpeed(int& speed, int targetSpeed, int acceleration) {
  if (speed < targetSpeed) {
    speed += acceleration;
    if (speed > targetSpeed) speed = targetSpeed;
  } else if (speed > targetSpeed) {
    speed -= acceleration;
    if (speed < targetSpeed) speed = targetSpeed;
  }
}

void Wheelchair::moveForward() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  const int8_t maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;

  adjustSpeed(leftEngineSpeed, maxSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, maxSpeed, this->acceleration);

  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  }
  prevMoveTime = millis();
}

void Wheelchair::moveLeft() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  int maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;
  int limiterSpeed = maxSpeed * WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT;;

  if (oldCmd == WHEELCHAIR_MOVE_BACKWARD) maxSpeed = - maxSpeed;

  const int8_t rightSpeed = maxSpeed + limiterSpeed;
  const int8_t leftSpeed = maxSpeed - limiterSpeed;

  adjustSpeed(leftEngineSpeed, leftSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, rightSpeed, this->acceleration);
  
  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  }
  prevMoveTime = millis();
}

void Wheelchair::moveRight() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  int maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;
  int limiterSpeed = maxSpeed * WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT;

  if (oldCmd == WHEELCHAIR_MOVE_BACKWARD) {
    maxSpeed = - maxSpeed;
  }

  const int8_t rightSpeed = maxSpeed - limiterSpeed;
  const int8_t leftSpeed = maxSpeed + limiterSpeed;

  adjustSpeed(leftEngineSpeed, leftSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, rightSpeed, this->acceleration);
  
  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.8);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  }
  prevMoveTime = millis();
}

void Wheelchair::rotateLeft() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  const int8_t maxSpeed = WHEELCHAIR_ROTATE_SPEED;

  const int8_t rightSpeed = maxSpeed;
  const int8_t leftSpeed = -(maxSpeed * 2.3);

  int acc = this->acceleration + 2;
  if (acc < 4) acc = 4;

  adjustSpeed(leftEngineSpeed, leftSpeed, acc);
  adjustSpeed(rightEngineSpeed, rightSpeed, acc);
  
  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.6);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection * 0.6);
  }
  prevMoveTime = millis();
}

void Wheelchair::rotateRight() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  const int8_t maxSpeed = WHEELCHAIR_ROTATE_SPEED;

  const int8_t rightSpeed = -(maxSpeed * 2.3);
  const int8_t leftSpeed = maxSpeed;

  int acc = this->acceleration + 2;
  if (acc < 4) acc = 4;

  adjustSpeed(leftEngineSpeed, leftSpeed, acc);
  adjustSpeed(rightEngineSpeed, rightSpeed, acc);
  
  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * this->engineCorection * 0.6);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * 0.6);
  }
  prevMoveTime = millis();
}

void Wheelchair::moveBackward() {
  if (millis() - prevMoveTime < TIME_FOR_MOVE) return;
  const int8_t maxSpeed = -MAX_SPEED_MOTOR * this->speedPercent;

  adjustSpeed(leftEngineSpeed, maxSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, maxSpeed, this->acceleration);

  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.98);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed);
  }
  prevMoveTime = millis();
}

void Wheelchair::stop() {
  if (millis() - prevMoveTime < TIME_FOR_STOP) return;
  if (this->leftEngineSpeed == 0 && this->rightEngineSpeed == 0) return;

  int acc = this->acceleration + 3;
  if (acc < 4) acc = 4;
  
  adjustSpeed(this->leftEngineSpeed, 0, acc);
  adjustSpeed(this->rightEngineSpeed, 0, acc);

  if (debug) {
    Serial.printf(">Motor Left: %d\n", this->leftEngineSpeed);
    Serial.printf(">Motor Right: %d\n", this->rightEngineSpeed);
  } else {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed);
  }

  prevMoveTime = millis();
}
