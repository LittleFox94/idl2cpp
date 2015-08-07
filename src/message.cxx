#include "../include/message.hxx"
#include "../include/parser.hxx"

#include <sstream>

namespace idl2cpp {
    Message::Message(Parser* parser, MessageType type, std::string name)
        : mParser(parser), mType(type), mName(name) {
    }

    std::string Message::toCode() {
        std::stringstream code;

        code << "typedef struct {" << std::endl;

        for(auto && attribute : mAttributes) {
            code << "    ";
            code << attribute->getType()->getCodeName() << " ";
            code << attribute->getName() << ";" << std::endl;
        }

        code << "} MESSAGE_STRUCTURE_" << mName << ";" << std::endl;
        return code.str();
    }

    void Message::addAttribute(std::string name, Type* type) {
        mAttributes.push_back(new Attribute(mParser, name, type));
    }
}
