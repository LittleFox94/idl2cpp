#ifndef _TYPE_HXX_INCLUDED
#define _TYPE_HXX_INCLUDED

#include <string>
#include <vector>

namespace idl2cpp {
    class Parser;
    
    class Type {
        public:
            Type(Parser* parser, std::string name, std::string codeName);
            Type(Parser* parser, std::string name, std::string baseType, int min, int max);
            Type(Parser* parser, std::string name, std::string baseType, std::vector<std::string>& enumeration);

            std::string getName() const { return mName; }
            std::string getCodeName() const { return mCodeName; }

        private:
            std::string mName;
            std::string mCodeName;
            Parser* mParser;

            int mMinimum;
            int mMaximum;

            std::vector<std::string> mEnumeration;
    };
}

#endif
