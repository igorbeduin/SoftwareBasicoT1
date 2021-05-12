#include "../include/StaticSymbols.h"

std::string StaticSymbols::labelSeparator = ":";
std::string StaticSymbols::argumentSeparator = ",";
std::string StaticSymbols::spaceSeparator = " ";
std::vector<char> StaticSymbols::separators = {',', ' ', ':'};

std::string StaticSymbols::labelSeparatorClass = "label_sep";
std::string StaticSymbols::argumentSeparatorClass = "arg_sep";

std::string StaticSymbols::dummyClass = "";
std::string StaticSymbols::argumentClass = "argument";
std::string StaticSymbols::labelClass = "label";
std::string StaticSymbols::operationClass = "operation";
std::string StaticSymbols::symbolClass = "symbol";
std::string StaticSymbols::symbolCandidateClass = "cand_symbol";
std::string StaticSymbols::ignoreClass = "ignore";

std::string StaticSymbols::sectionMark = "SECTION";
std::string StaticSymbols::dataSectionMark = "DATA";
std::string StaticSymbols::textSectionMark = "TEXT";
std::string StaticSymbols::stopSectionMark = "STOP";

std::string StaticSymbols::beginMark = "BEGIN";
std::string StaticSymbols::endMark = "END";
std::string StaticSymbols::publicMark = "PUBLIC";
std::string StaticSymbols::externMark = "EXTERN";
