cmake_minimum_required(VERSION 3.26.3)

project(AinLanguage)

### start files_cmake.cpp ###

add_library(ainsrc
    src/main.cpp
    src/lexer/LexerToken.cpp
    src/lexer/Lexer.cpp
    src/lexer/KeywordToken.cpp
    src/lexer/LexerLine.cpp
    src/lexer/LiteralToken.cpp
    src/lexer/NumberToken.cpp
    src/lexer/SymbolToken.cpp
    src/expression/BinaryExpression.cpp
    src/expression/BoolExpression.cpp
    src/expression/StringExpression.cpp
    src/expression/FunCallExpression.cpp
    src/expression/VariableAccessExpression.cpp
    src/expression/NumberExpression.cpp
    src/scope/FunScope.cpp
    src/scope/Scope.cpp
    src/scope/Constant.cpp
    src/scope/Variable.cpp
    src/scope/GlobalScope.cpp
    src/ain_file/AinFile.cpp
    src/statement/IStatement.cpp
    src/statement/WhileStatement.cpp
    src/statement/IfStatement.cpp
    src/statement/VarDeclarationStatement.cpp
    src/statement/DoWhileStatement.cpp
    src/statement/ExpressionStatement.cpp
    src/statement/VarReassignStatement.cpp
    src/statement/ReturnStatement.cpp
    src/helpers/string_helper.cpp
    src/helpers/ainio.cpp
    src/helpers/wchar_t_helper.cpp
    src/helpers/number_helper.cpp
    src/parser/Parser.cpp
)

set(INCLUDE
    include/
    include/exceptions/
    include/lexer/
    include/expression/
    include/scope/
    include/ain_file/
    include/statement/
    include/helpers/
    include/parser/
)

set(TEST
    test/lexer/LexerTest.cpp
    test/lexer/LexerLineTest.cpp
    test/ain_file/AinFileTest.cpp
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
