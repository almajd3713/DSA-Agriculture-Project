#pragma once
#ifndef INCLUDESDSA
#define INCLUDESDSA

#include <vector>
#include <type_traits>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <queue>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "util.hpp"
#include "../../lib/json.hpp"

using std::cout, std::cin, std::endl, std::stoi;
using std::ostream, std::ifstream, std::ofstream;
using std::string, std::move;
using std::filesystem::exists;
using std::unordered_map, std::vector, std::pair;
using std::setw, std::setfill;
using std::queue, std::function;
using std::is_pointer;

using json = nlohmann::json;

#endif