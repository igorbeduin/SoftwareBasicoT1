#include "../include/DirectTable.h"

std::map<std::string, std::map<std::string, int>> DirectTable::directTable;

DirectTable directTable;

DirectTable::DirectTable() 
{
    std::map<std::string, int> dummyMap;

    dummyMap["OP_CODE"] = 1;
    dummyMap["WORDS"] = 2;
    directTable["ADD"] = dummyMap;

    dummyMap["OP_CODE"] = 2;
    dummyMap["WORDS"] = 2;
    directTable["SUB"] = dummyMap;

    dummyMap["OP_CODE"] = 3;
    dummyMap["WORDS"] = 2;
    directTable["MUL"] = dummyMap;

    dummyMap["OP_CODE"] = 4;
    dummyMap["WORDS"] = 2;
    directTable["DIV"] = dummyMap;

    dummyMap["OP_CODE"] = 5;
    dummyMap["WORDS"] = 2;
    directTable["JMP"] = dummyMap;

    dummyMap["OP_CODE"] = 6;
    dummyMap["WORDS"] = 2;
    directTable["JMPN"] = dummyMap;

    dummyMap["OP_CODE"] = 7;
    dummyMap["WORDS"] = 2;
    directTable["JMPP"] = dummyMap;

    dummyMap["OP_CODE"] = 8;
    dummyMap["WORDS"] = 2;
    directTable["JMPZ"] = dummyMap;

    dummyMap["OP_CODE"] = 9;
    dummyMap["WORDS"] = 3;
    directTable["COPY"] = dummyMap;

    dummyMap["OP_CODE"] = 10;
    dummyMap["WORDS"] = 2;
    directTable["LOAD"] = dummyMap;

    dummyMap["OP_CODE"] = 11;
    dummyMap["WORDS"] = 2;
    directTable["STORE"] = dummyMap;

    dummyMap["OP_CODE"] = 12;
    dummyMap["WORDS"] = 2;
    directTable["INPUT"] = dummyMap;

    dummyMap["OP_CODE"] = 13;
    dummyMap["WORDS"] = 2;
    directTable["OUTPUT"] = dummyMap;

    dummyMap["OP_CODE"] = 14;
    dummyMap["WORDS"] = 1;
    directTable["STOP"] = dummyMap;

    dummyMap["OP_CODE"] = 0;
    dummyMap["WORDS"] = 1;
    directTable["SPACE"] = dummyMap;

    dummyMap["OP_CODE"] = 0;
    dummyMap["WORDS"] = 1;
    directTable["CONST"] = dummyMap;
}