#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string>

namespace Muvt { namespace Utils {

namespace Color {
const std::string kBold = "\e[1m";
const std::string kEndBold= "\e[0m";
const std::string kRed = "\033[0;31m";
const std::string kBoldRed = "\033[1;31m";
const std::string kGreen = "\033[0;32m";
const std::string kBoldGreen = "\033[1;32m";
const std::string kYellow = "\033[0;33m";
const std::string kBoldYellow = "\033[1;33m";
const std::string kBlue = "\033[0;34m";
const std::string kBoldBlue = "\033[1;34m";
const std::string kMagenta = "\033[0;35m";
const std::string kBoldMagenta = "\033[1;35m";
const std::string kCyan = "\033[0;36m";
const std::string kBoldCyan = "\033[1;36m";
const std::string kEndl = "\033[0m";
}; // namespace color

} }

#endif
