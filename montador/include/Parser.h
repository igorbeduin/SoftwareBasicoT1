#include <vector>
#include <string>
#include <limits>

class Parser
{
    private:
    public:
        static std::vector<std::string> outputStringVector;
        void set_elements();
        void set_elements_lines();
        void set_elements_classes();
        void verify_syntactic_errors();
        void mount_output();
};      