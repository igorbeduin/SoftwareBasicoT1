#include "../include/CodeTable.h"

std::map<int, std::string> CodeTable::codeTable;

CodeTable codeTable;

CodeTable::CodeTable()
{

    codeTable[1] = "ADD";
    codeTable[2] = "SUB";
    codeTable[3] = "MUL";
    codeTable[4] = "DIV";
    codeTable[5] = "JMP";
    codeTable[6] = "JMPN";
    codeTable[7] = "JMPP";
    codeTable[8] = "JMPZ";
    codeTable[9] = "COPY";
    codeTable[10] = "LOAD";
    codeTable[11] = "STORE";
    codeTable[12] = "INPUT";
    codeTable[13] = "OUTPUT";
    codeTable[14] = "STOP";
    codeTable[0] = "SPACE";
    codeTable[-1] = "CONST";
}