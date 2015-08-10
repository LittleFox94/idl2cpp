#include "../include/strutil.hxx"
#include <string>

namespace idl2cpp {
    std::string trim(std::string const & str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');

        if(last == first && last == -1)
            return "";

        return str.substr(first, (last-first+1));
    }
}
