#include "../include/parser.hxx"

#include <iostream>

int main()
{
    idl2cpp::Parser const & parser(std::string{
        "message: Login\n"
        "    string: username\n"
        "    string: password\n"
        "\n"
        "base: AuthorizedMessage\n"
        "    string: authorizationKey\n"
        "\n"
        "base: Position\n"
        "extends: AuthorizedMessage\n"
        "    int64_t: xpos\n"
        "    int64_t: ypos\n"
        "    int64_t: zpos\n"
    });

    std::cout << parser.toCode() << std::endl;
    
    return 0;
}
