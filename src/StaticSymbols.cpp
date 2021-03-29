#include "../include/StaticSymbols.h"

std::string StaticSymbols::labelSeparator = ":";
std::string StaticSymbols::argumentSeparator = ",";
std::string StaticSymbols::spaceSeparator = " ";
std::vector<char> StaticSymbols::separators = {',', ' ', ':'};

std::string StaticSymbols::dummyClass = "";
std::string StaticSymbols::labelSeparatorClass = "label_sep";
std::string StaticSymbols::argumentSeparatorClass = "arg_sep";
std::string StaticSymbols::labelClass = "label";

std::string StaticSymbols::sectionMark = "SECTION";
std::string StaticSymbols::dataSectionMark = "DATA";
std::string StaticSymbols::textSectionMark = "TEXT";
std::string StaticSymbols::stopSectionMark = "STOP";
