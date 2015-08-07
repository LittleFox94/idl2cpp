#include "../include/type.hxx"
#include "../include/parser.hxx"

namespace idl2cpp {
    Type::Type(Parser* parser, std::string name, std::string codeName)
        : mParser(parser), mName(name), mCodeName(codeName) {
    }

    Type::Type(Parser* parser, std::string name, std::string baseType, int min, int max)
        : mParser(parser), mName(name), mMinimum(min), mMaximum(max) {
        mCodeName = mParser->getType(baseType)->getCodeName();
    }

    Type::Type(Parser* parser, std::string name, std::string baseType, std::vector<std::string>& enumeration)
        : mParser(parser), mName(name), mEnumeration(enumeration) {
        mCodeName = mParser->getType(baseType)->getCodeName();
    }
}
