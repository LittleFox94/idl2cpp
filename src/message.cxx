#include "../include/message.hxx"
#include "../include/parser.hxx"

#include <sstream>

namespace idl2cpp {
    Message::Message(Parser* parser, MessageType type, std::string name)
        : mParser(parser), mType(type), mName(name) {
    }

    std::string Message::toCode() {
        std::stringstream code;

        code << "typedef struct {\n";

        for(auto && attribute : mAttributes) {
            code << "    ";
            code << attribute->getType()->getCodeName() << " ";
            code << attribute->getName() << ";\n";
        }

        code << "} MESSAGE_STRUCTURE_" << mName << ";\n";
        return code.str();
    }

    void Message::addAttribute(std::string name, Type* type) {
        mAttributes.push_back(std::unique_ptr<Attribute>(new Attribute(mParser, name, type)));
    }
}
