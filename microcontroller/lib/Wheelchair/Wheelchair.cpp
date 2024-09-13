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
  if (!debug) {
    st.motor(MOTOR_LEFT, 0);
    st.motor(MOTOR_RIGHT, 0);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);

    Serial.print("Right and Left move percent: ");
    Serial.println(WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT);
  }
}

void Wheelchair::loop() {
  const std::string cmd = trim(ble.getControlCharacteristic()->getValue());

  const size_t separatorIndex = cmd.find(WHEELCHAIR_VALUE_SEPARATOR_CMD);
  if (separatorIndex > 0) {
    if (cmd.rfind(WHEELCHAIR_ENGINE_CORRECTION_CMD, 0) == 0) {
      float data = std::stof(cmd.substr(separatorIndex + 1));
      this->engineCorection = data / 100; 
    }
    if (cmd.rfind(WHEELCHAIR_SPEED_CORRECTION_CMD, 0) == 0) {
      this->acceleration = std::stoi(cmd.substr(separatorIndex + 1));
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
  const unsigned long isTimeForMove = millis() - prevMoveTime > TIME_FOR_MOVE;
  const unsigned long isTimeForStop = millis() - prevMoveTime > TIME_FOR_STOP;

  if (isMovesCommand(cmd)) {
    directionCommand = *cmd;
  } else if (isLeftRightCommand(cmd)) {
    if (*cmd != directionCommand) oldCmd = directionCommand;
    directionCommand = *cmd;
  } else if (isOffLeftRightCommand(cmd)) {
    directionCommand = oldCmd;
  }


  if (
    directionCommand == WHEELCHAIR_MOVE_LEFT && isTimeForMove) {
      moveLeft();
      prevMoveTime = millis();
  } else if (
    directionCommand == WHEELCHAIR_MOVE_RIGHT && isTimeForMove) {
      moveRight();
      prevMoveTime = millis();
  } else if (directionCommand == WHEELCHAIR_ROTATE_LEFT && isTimeForMove) {
      rotateLeft();
      prevMoveTime = millis();
  } else if (directionCommand == WHEELCHAIR_ROTATE_RIGHT && isTimeForMove) {
      rotateRight();
      prevMoveTime = millis();
  } else if (directionCommand == WHEELCHAIR_MOVE_FORWARD && isTimeForMove) {
      moveForward();
      prevMoveTime = millis();
  } else if (directionCommand == WHEELCHAIR_MOVE_STOP && isTimeForStop) {
      stop();
      prevMoveTime = millis();
  } else if (directionCommand == WHEELCHAIR_MOVE_BACKWARD && isTimeForMove) {
      moveBackward();
      prevMoveTime = millis();
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
  const int8_t maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;

  adjustSpeed(leftEngineSpeed, maxSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, maxSpeed, this->acceleration);

  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::moveLeft() {
  int maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;
  int limiterSpeed = maxSpeed * WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT;;

  if (oldCmd == WHEELCHAIR_MOVE_BACKWARD) maxSpeed = - maxSpeed;

  const int8_t rightSpeed = maxSpeed + limiterSpeed;
  const int8_t leftSpeed = maxSpeed - limiterSpeed;

  adjustSpeed(leftEngineSpeed, leftSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, rightSpeed, this->acceleration);
  
  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::moveRight() {
  int maxSpeed = MAX_SPEED_MOTOR * this->speedPercent;
  int limiterSpeed = maxSpeed * WHEELCHAIR_MOVE_LEFT_RIGHT_PERCENT;

  if (oldCmd == WHEELCHAIR_MOVE_BACKWARD) {
    maxSpeed = - maxSpeed;
  }

  const int8_t rightSpeed = maxSpeed - limiterSpeed;
  const int8_t leftSpeed = maxSpeed + limiterSpeed;

  adjustSpeed(leftEngineSpeed, leftSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, rightSpeed, this->acceleration);
  
  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.8);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::rotateLeft() {
  const int8_t maxSpeed = WHEELCHAIR_ROTATE_SPEED;

  const int8_t rightSpeed = maxSpeed;
  const int8_t leftSpeed = -(maxSpeed * 2.3);

  int acc = this->acceleration + 2;
  if (acc < 4) acc = 4;

  adjustSpeed(leftEngineSpeed, leftSpeed, acc);
  adjustSpeed(rightEngineSpeed, rightSpeed, acc);
  
  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.6);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * this->engineCorection * 0.6);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::rotateRight() {
  const int8_t maxSpeed = WHEELCHAIR_ROTATE_SPEED;

  const int8_t rightSpeed = -(maxSpeed * 2.3);
  const int8_t leftSpeed = maxSpeed;

  int acc = this->acceleration + 2;
  if (acc < 4) acc = 4;

  adjustSpeed(leftEngineSpeed, leftSpeed, acc);
  adjustSpeed(rightEngineSpeed, rightSpeed, acc);
  
  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * this->engineCorection * 0.6);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed * 0.6);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::moveBackward() {
  const int8_t maxSpeed = -MAX_SPEED_MOTOR * this->speedPercent;

  adjustSpeed(leftEngineSpeed, maxSpeed, this->acceleration);
  adjustSpeed(rightEngineSpeed, maxSpeed, this->acceleration);

  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed * 0.98);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

void Wheelchair::stop() {
  if (this->leftEngineSpeed == 0 && this->rightEngineSpeed == 0) return;

  int acc = this->acceleration + 3;
  if (acc < 4) acc = 4;
  
  adjustSpeed(this->leftEngineSpeed, 0, acc);
  adjustSpeed(this->rightEngineSpeed, 0, acc);

  if (!debug) {
    st.motor(MOTOR_LEFT, this->leftEngineSpeed);
    st.motor(MOTOR_RIGHT, this->rightEngineSpeed);
  } else {
    Serial.print("Left: ");
    Serial.println(this->leftEngineSpeed);
    Serial.print("Right: ");
    Serial.println(this->rightEngineSpeed);
  }
}

std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(" \n\r\t");
  size_t last = str.find_last_not_of(" \n\r\t");

  if (first != std::string::npos && last != std::string::npos) {
    return str.substr(first, (last - first + 1));
  } else if (first != std::string::npos) {
    return str.substr(first);
  } else if (last != std::string::npos) {
    return str.substr(0, (last + 1));
  }

  return "";
}