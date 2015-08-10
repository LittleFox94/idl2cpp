#include "../include/parser.hxx"
#include "../include/strutil.hxx"
#include "../include/message.hxx"

#include <algorithm>
#include <sstream>
#include <iostream>

namespace idl2cpp {
    Parser::Parser(std::string const & idlCode)
        : mTypes(initTypes())
    {
        std::stringstream stream(idlCode);

        Parser::ParseState state = Parser::ParseState::None;
        int linenumber = 0;

        std::string line;

        std::unique_ptr<Message> newMessage;
        std::unique_ptr<Type> newType;

        while(std::getline(stream, line)) {
            ++linenumber;
            line = trim(line);

            if(line == "") {
                switch(state) {
                    case Parser::ParseState::MessageDefinition:
                        {
                            mMessages[newMessage->getName()] = std::move(newMessage);
                        }
                        break;
                    case Parser::ParseState::TypeDefinition:
                        {
                            mTypes[newType->getName()] = std::move(newType);
                        }
                        break;
                }

                state = Parser::ParseState::None;
                continue;
            }

            switch(state) {
                case Parser::ParseState::None:
                    {
                        std::string keyword = trim(line.substr(0, line.find(":")));
                        std::string name    = trim(line.substr(line.find(":") + 1));

                        if(keyword == "message" || keyword == "base") {
                            state = Parser::ParseState::MessageDefinition;
                            newMessage.reset(new Message(this, keyword == "base" ? MessageType::BaseOnly : MessageType::Message, name));
                        }
                    }
                    break;
                case Parser::ParseState::MessageDefinition:
                    {
                        std::string keyword = trim(line.substr(0, line.find(":")));
                        std::string name    = trim(line.substr(line.find(":") + 1));

                        if(keyword == "extends") {
                            newMessage->setBaseName(name);
                        }
                        else {
                            Type* type = getType(keyword);

                            if(!type) {
                                std::cerr << "Unknown type \"" << keyword << "\" on line " << linenumber << "!" << std::endl;
                                exit(-1);
                            }

                            newMessage->addAttribute(name, type);
                        }
                    }
                    break;
                case Parser::ParseState::TypeDefinition:
                    {

                    }
                    break;
            }
        }

        switch(state) {
            case Parser::ParseState::MessageDefinition:
                {
                    mMessages[newMessage->getName()] = std::move(newMessage);
                }
                break;
            case Parser::ParseState::TypeDefinition:
                {
                    mTypes[newType->getName()] = std::move(newType);
                }
                break;
        }
    }

    std::string Parser::toCode() const {
        std::stringstream code;

        code << "#ifndef __CPP_NETWORK_USER_HEADER_INCLUDED\n"
                "#define __CPP_NETWORK_USER_HEADER_INCLUDED\n\n";

        for (auto && message : mMessages) {
            if (message.second->getType() == MessageType::Message) {
                code << message.second->toCode() << "\n";
            }
        }

        code << "#endif\n";

        return code.str();
    }

    Type* Parser::getType(std::string const & name)
    {
        auto it = mTypes.find(name);
        if (it != mTypes.end())
            return it->second.get();

        return nullptr;
    }

    std::unordered_map<std::string, std::unique_ptr<Type>> Parser::initTypes()
    {
        std::unordered_map<std::string, std::unique_ptr<Type>> types;
#define TYPE(t,a) types[t] = std::unique_ptr<Type> { new Type { this, t, a } }
        TYPE("int8_t", "int8_t");
        TYPE("int16_t", "int16_t");
        TYPE("int32_t", "int32_t");
        TYPE("int64_t", "int64_t");
        TYPE("uint8_t", "uint8_t");
        TYPE("uint16_t", "uint16_t");
        TYPE("uint32_t", "uint32_t");
        TYPE("uint64_t", "uint64_t");
        TYPE("cstring", "std::string");
        TYPE("string", "std::string");
        TYPE("boolean", "bool");
#undef TYPE
        return types;
    }

    Message* Parser::getMessage(std::string const & name) {
        auto it = mMessages.find(name);
        if (it != mMessages.end())
            return it->second.get();

        return nullptr;
    }
}
