#include <iostream>
#include <fstream>
#include <sstream>
#include <Validator.h>

using namespace json11;

bool parseJsonFile(const char *fileName, Json &json) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    return false;
  }
  std::stringstream stream;
  stream << file.rdbuf();
  std::string error;
  std::string string = stream.str();
  json = Json::parse(string, error);
  return error.length() == 0;
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " json_file schema_file" << std::endl;
    return -1;
  }

  Json json, schema;
  if (!parseJsonFile(argv[1], json)) {
    std::cerr << "Can't parse json file " << argv[1] << std::endl;
    return -1;
  }
  if (!parseJsonFile(argv[2], schema)) {
    std::cerr << "Can't parse schema file " << argv[2] << std::endl;
    return -1;
  }

  Validator validator(schema);
  if (validator.validate(json)) {
    std::cout << "JSON is valid" << std::endl;
    return 0;
  }

  std::cerr << "JSON is invalid" << std::endl;
  return -1;
}
