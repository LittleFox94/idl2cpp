#ifndef _ATTRIBUTE_HXX_INCLUDED
#define _ATTRIBUTE_HXX_INCLUDED

#include <string>
#include "type.hxx"

namespace idl2cpp {
    class Parser;

    class Attribute {
        public:
            Attribute(Parser* parser, std::string name, Type* type);

            std::string toCode();
            std::string getName() { return mName; }
            Type* getType() { return mType; }

        private:
            std::string mName;
            Type* mType;
            Parser* mParser;
    };
}

#endif
