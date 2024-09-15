#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"

void testHwm(const char* taskName) {
  static int stack_hwm, stack_hwm_temp;

  stack_hwm_temp = uxTaskGetStackHighWaterMark(nullptr);
  if (!stack_hwm || stack_hwm_temp < stack_hwm) {
    stack_hwm = stack_hwm_temp;
    Serial.printf("%s with hwm: %d\n", taskName, stack_hwm);
    Serial.printf("%s without hwm: %d\n", taskName, stack_hwm + 512);
  }
}

void trim(std::string* str) {
  size_t first = str->find_first_not_of(" \n\r\t");
  size_t last = str->find_last_not_of(" \n\r\t");

  if (first != std::string::npos && last != std::string::npos) {
    *str = str->substr(first, (last - first + 1));
  } else if (first != std::string::npos) {
    *str = str->substr(first);
  } else if (last != std::string::npos) {
    *str = str->substr(0, (last + 1));
  }

  *str = "";
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

#endif