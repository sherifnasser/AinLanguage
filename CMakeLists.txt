cmake_minimum_required(VERSION 3.26.3)

project(AinLanguage)


### start files_cmake.cpp ###

add_library(ainsrc
    src/main.cpp
    src/lexer/lexer.cpp
    src/lexer/keywordtoken.cpp
    src/lexer/lexerline.cpp
    src/lexer/symboltoken.cpp
    src/lexer/lexertoken.cpp
    src/ain_file/ain_file.cpp
    src/statement/statement.cpp
    src/helpers/string_helper.cpp
    src/helpers/ainio.cpp
    src/helpers/wchar_t_helper.cpp
    src/helpers/number_helper.cpp
    src/parser/scope/scope.cpp
    src/parser/scope/globalscope.cpp
    src/parser/expression.cpp
    src/parser/parser.cpp
)

set(INCLUDE
    include/
    include/lexer/
    include/ain_file/
    include/statement/
    include/helpers/
    include/parser/
    include/parser/scope/
)

set(TEST
    test/lexer/lexertest.cpp
)

### end files_cmake.cpp ###


add_executable(ain src/main.cpp)

target_include_directories(ainsrc PUBLIC ${INCLUDE})

target_link_libraries(ain ainsrc)

# Add Catch2 library
find_package(Catch2 REQUIRED)

# Add test executable
add_executable(unit_tests ${TEST})

# Link Catch2 library to the test executable
target_link_libraries(unit_tests Catch2::Catch2 ainsrc)
