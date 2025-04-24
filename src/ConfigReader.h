#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct Config {
  int width = 0;
  int height = 0;
  float speed = 1.f;
  float angle = 0.f;
  std::vector<std::string> logos;
  float rColor;
  float gColor;
  float bColor;
  float scale;
};

class ConfigReader {
 public:
  static Config LoadConfig(const std::string &filename);
};

#endif  // CONFIGREADER_H
