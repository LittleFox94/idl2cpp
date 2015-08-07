#include "../include/parser.hxx"
#include "../include/strutil.hxx"
#include "../include/message.hxx"
#include <sstream>
#include <iostream>

namespace idl2cpp {
    Parser::Parser(std::string idlCode) {
        initTypes();

        std::stringstream stream(idlCode);

        Parser::ParseState state = Parser::ParseState::None;
        int linenumber = 0;

        while(!stream.eof()) {
            linenumber++;

            char buffer[1024];
            stream.getline(buffer, 1024);
            std::string line(buffer);
            line = trim(line);

            Message* newMessage;
            Type* newType;

            if(line == "") {
                switch(state) {
                    case Parser::ParseState::MessageDefinition:
                        {
                            mMessages.push_back(newMessage);
                        }
                        break;
                    case Parser::ParseState::TypeDefinition:
                        {
                            mTypes.push_back(newType);
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
                            newMessage = new Message(this, keyword == "base" ? MessageType::BaseOnly : MessageType::Message, name);
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

                            if(type == 0) {
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
    }

    std::string Parser::toCode() const {
        std::stringstream code;

        code << "#ifndef __CPP_NETWORK_USER_HEADER_INCLUDED" << std::endl
             << "#define __CPP_NETWORK_USER_HEADER_INCLUDED" << std::endl
             << std::endl;

        for (auto && message : mMessages) {
            if(message->getType() == MessageType::Message) {
                code << message->toCode() << std::endl;
            }
        }

        code << "#endif" << std::endl;

        return code.str();
    }

    void Parser::initTypes() {
        mTypes.push_back(new Type(this, "int8_t",   "int8_t"));
        mTypes.push_back(new Type(this, "int16_t",  "int16_t"));
        mTypes.push_back(new Type(this, "int32_t",  "int32_t"));
        mTypes.push_back(new Type(this, "int64_t",  "int64_t"));
        mTypes.push_back(new Type(this, "uint8_t",  "uint8_t"));
        mTypes.push_back(new Type(this, "uint16_t", "uint16_t"));
        mTypes.push_back(new Type(this, "uint32_t", "uint32_t"));
        mTypes.push_back(new Type(this, "uint64_t", "uint64_t"));
        mTypes.push_back(new Type(this, "cstring",  "std::string"));
        mTypes.push_back(new Type(this, "string",   "std::string"));
        mTypes.push_back(new Type(this, "boolean",  "bool"));
    }

    Type* Parser::getType(std::string name) {
        for(auto && type : mTypes) {
            if(type->getName() == name) {
                return type;
            }
        }

        return 0;
    }

    Message* Parser::getMessage(std::string name) {
        for(auto && message : mMessages) {
            if(message->getName() == name) {
                return message;
            }
        }

        return 0;
    }
}
