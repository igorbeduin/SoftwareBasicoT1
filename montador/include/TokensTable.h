#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "DirectTable.h"
#include "SymbTable.h"
#include "DefTable.h"
#include "UsageTable.h"
#include "ControlVariables.h"

class TokensTable
{
    private:
    public:
        static int max_length;
        static std::vector<char> letters;
        static std::vector<char> numbers;

        static std::vector<std::string> elements;
        static std::vector<int> elementsLine;
        static std::vector<std::string> elementsClass;
        static std::map<std::string, int> dataSection;
        static std::map<std::string, int> textSection;

        static SymbTable symbTable;
        static DefTable defTable;
        static UsageTable usageTable;

        static void insert_token(std::string element, int elementLine, std::string elementClass);
        static void print_elements();
        static void classify_tokens();
        static bool is_label_sep(std::string element);
        static bool is_argument_sep(std::string element);
        static bool is_operation(std::string element);
        static bool is_argument(std::string element);
        static bool is_symbol(std::string element);
        static bool is_symbol_candidate(std::string element);
        static bool is_section_mark(std::string element);
        static bool is_in_text_section(int index);
        static void search_for_sections();
        static void fill_tables();
        static bool lexical_error(int index);
        static void raise_semantic_error(int index);
        static void raise_syntactic_error(int index);
        static void find_first_pass_errors();
        static void reset_class();
        static bool found_modTags(bool isModule);
        static void remove_label_spaces();

        static bool label_is_in_text_section(std::string label);
        static bool label_is_in_data_section(std::string label);
        static void set_offset_to_labels(int offset);
        static void set_offset_to_data_labels(int offset);
        static bool label_is_space(std::string label);

        static void solve_extern_and_public_pos();
        static bool find_extern_or_public_in_data_section();

        static SymbTable get_symbTable();
        static DefTable get_defTable();
        static UsageTable get_usageTable();
};