#include "../include/attribute.hxx"

namespace idl2cpp {
    Attribute::Attribute(Parser* parser, std::string name, Type* type)
        : mParser(parser), mName(name), mType(type) {
    }
}
