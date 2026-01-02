#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <chrono>

class Log {
public:
template<typename T>
 static void printError(T t) {
  std::cout << "Error: " << t << std::endl;
  }
template<typename T>
  static void printWarning(T t) {
  std::cout << "Warning: " << t << std::endl;
  }
template<typename T>
  static void printInfo(T t){ ;
  std::cout << "INFO: " << t << std::endl;
  }
};
#endif
