#include <vector>
#include <string>

#include "TokensTable.h"

class Parser
{
    private:
        TokensTable classifiedTokensTable;

    public:
        void configure(TokensTable tokensTable);
        void set_elements();
        void set_elements_lines();
        void set_elements_classes();
};      