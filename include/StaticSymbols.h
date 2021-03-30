#include <string>
#include <vector>

class StaticSymbols
{
    public:
        static std::string spaceSeparator;
        static std::string labelSeparator;
        static std::string argumentSeparator;
        static std::vector<char> separators;

        static std::string labelClass;
        static std::string dummyClass;
        static std::string labelSeparatorClass;
        static std::string argumentSeparatorClass;
        static std::string argumentClass;
        static std::string operationClass;
        static std::string symbolClass;

        static std::string sectionMark;
        static std::string dataSectionMark;
        static std::string textSectionMark;
        static std::string stopSectionMark;
};