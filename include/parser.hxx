#ifndef _PARSER_HXX_INCLUDED
#define _PARSER_HXX_INCLUDED

#include <vector>
#include <string>
#include "message.hxx"
#include "type.hxx"

namespace idl2cpp {
    class Parser {
        
        public:
            Parser(const std::string idlCode);
            std::string toCode() const;

            Message* getMessage(std::string name);
            Type* getType(std::string name);

        private:
            enum class ParseState {
                None,
                MessageDefinition,
                TypeDefinition,
            };
            
            std::vector<Message*> mMessages;
            std::vector<Type*> mTypes;

            void initTypes();
    };
}

#endif
