#include <string>

#include "../include/DefTable.h"
#include "../include/ObjectCode.h"
#include "../include/UseTable.h"

class FileToMount
{
    private:
        std::string moduleName;
        //SymbTable symbTable;
        DefTable defTable;
        ObjectCode objCode;
        UseTable useTable;
        int correctionFactor;
    public:
        std::string assemblyExt = ".asm";
        FileToMount();
        FileToMount(std::string programName);
        void parseModuleName(std::string programName);
};