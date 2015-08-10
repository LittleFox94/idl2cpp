#include "../include/attribute.hxx"

namespace idl2cpp {
    Attribute::Attribute(Parser* parser, std::string const & name, Type* type)
        : mParser(parser), mName(name), mType(type) {
    }
}
