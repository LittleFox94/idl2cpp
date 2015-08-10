cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)
project(idl2cpp)

add_executable(idl2cpp
    src/main.cxx
    src/strutil.cxx     include/strutil.hxx
    src/parser.cxx      include/parser.hxx
    src/type.cxx        include/type.hxx
    src/message.cxx     include/message.hxx
    src/attribute.cxx   include/attribute.hxx
)
target_include_directories(idl2cpp PRIVATE include)
target_compile_features(idl2cpp
    PRIVATE
        cxx_auto_type
        cxx_range_for
        cxx_nullptr
        cxx_strong_enums
)
