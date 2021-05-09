#include <vector>
#include <string>
#include <limits>
#include "ObjectCode.h"

class Parser
{
    private:
    public:
        static std::vector<bool> relAdresses;
        static std::vector<int> relativeIdxData;
        static std::vector<std::string> outputStringVector;
        void set_elements();
        void set_elements_lines();
        void set_elements_classes();
        void verify_syntactic_errors();
        void mount_output();
        void reset_class();
        ObjectCode get_objectCode();
};      