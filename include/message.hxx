#ifndef _MESSAGE_HXX_INCLUDED
#define _MESSAGE_HXX_INCLUDED

#include <string>
#include "attribute.hxx"

namespace idl2cpp {
    class Parser;

    enum class MessageType {
        Message,
        BaseOnly,
    };

    class Message {
        public:
            Message(Parser* parser, MessageType type, std::string name);
            std::string toCode();

            MessageType getType() { return mType; }
            std::string getName() { return mName; }
            std::string getBaseName() { return mBaseName; }
            void setBaseName(std::string baseName) { mBaseName = baseName; }
            std::vector<Attribute*> getAttributes() { return mAttributes; }
            void addAttribute(std::string name, Type* type);

        private:
            MessageType mType;
            std::string mName;
            std::string mBaseName;
            std::vector<Attribute*> mAttributes;
            Parser* mParser;
    };
}

#endif
