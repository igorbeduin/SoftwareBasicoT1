#include <map>
#include <string>

class DirectTable 
{
    public:
        static std::map<std::string, std::map<std::string, int>> directTable;
        DirectTable();
};