#ifndef _PARSER_HXX_INCLUDED
#define _PARSER_HXX_INCLUDED

#include <unordered_map>
#include <memory>
#include <string>

#include "message.hxx"
#include "type.hxx"

namespace idl2cpp {
    class Parser {
        
        public:
            Parser(std::string const & idlCode);
            std::string toCode() const;

            Message * getMessage(std::string const & name);
            Type * getType(std::string const & name);

        private:
            enum class ParseState {
                None,
                MessageDefinition,
                TypeDefinition,
            };

            std::unordered_map<std::string, std::unique_ptr<Type>> initTypes();
            
            std::unordered_map<std::string, std::unique_ptr<Message>> mMessages;
            std::unordered_map<std::string, std::unique_ptr<Type>> mTypes;
    };
}

#endif
