#include <string>

#include "SymbTable.h"
#include "DefTable.h"
#include "ObjectCode.h"
#include "UsageTable.h"

class FileToMount
{
    private:
        std::string moduleName;
        SymbTable symbTable;
        DefTable defTable;
        ObjectCode objCode;
        UsageTable usageTable;
        int correctionFactor;
    public:
        std::string assemblyExt = ".asm";
        FileToMount();
        FileToMount(std::string programName);
        void parseModuleName(std::string programName);
};