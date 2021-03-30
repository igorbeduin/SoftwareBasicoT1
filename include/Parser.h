#include <vector>
#include <string>

class Parser
{
    private:
        static std::vector<std::string> outputString;
    public:
        void set_elements();
        void set_elements_lines();
        void set_elements_classes();
        void verify_syntactic_errors();
        void mount_output();
};      