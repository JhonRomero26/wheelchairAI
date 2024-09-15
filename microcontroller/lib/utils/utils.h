#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"

void testHwm(const char* taskName);

void trim(std::string* str);
std::string trim(const std::string& str);

#endif