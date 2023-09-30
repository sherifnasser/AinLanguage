cmake_minimum_required(VERSION 3.26.3)

project(AinLanguage)

### start files_cmake.cpp ###

add_library(ainsrc
    src/main.cpp
    src/Interpreter.cpp
    src/lexer/LexerToken.cpp
    src/lexer/Lexer.cpp
    src/lexer/KeywordToken.cpp
    src/lexer/LexerLine.cpp
    src/lexer/LiteralToken.cpp
    src/lexer/NumberToken.cpp
    src/lexer/SymbolToken.cpp
    src/expression/OperatorFunInvokeExpression.cpp
    src/expression/value/IntValue.cpp
    src/expression/value/UnitValue.cpp
    src/expression/value/DoubleValue.cpp
    src/expression/value/CharValue.cpp
    src/expression/value/BoolValue.cpp
    src/expression/value/ObjectValue.cpp
    src/expression/value/ULongValue.cpp
    src/expression/value/StringValue.cpp
    src/expression/value/IValue.cpp
    src/expression/value/FloatValue.cpp
    src/expression/value/LongValue.cpp
    src/expression/value/UIntValue.cpp
    src/expression/FunInvokeExpression.cpp
    src/expression/NonStaticFunInvokeExpression.cpp
    src/expression/LiteralExpression.cpp
    src/expression/UnitExpression.cpp
    src/expression/VarAccessExpression.cpp
    src/expression/IExpression.cpp
    src/expression/NonStaticVarAccessExpression.cpp
    src/expression/NewObjectExpression.cpp
    src/expression/LogicalExpression.cpp
    src/scope/BaseScope.cpp
    src/scope/function/BuiltInFunScope.cpp
    src/scope/PackageScope.cpp
    src/scope/LoopScope.cpp
    src/scope/FunScope.cpp
    src/scope/ClassScope.cpp
    src/scope/StmListScope.cpp
    src/scope/StringClassScope.cpp
    src/scope/FileScope.cpp
    src/scope/Variable.cpp
    src/ain_file/AinFile.cpp
    src/semantics/SemanticsChecksVisitor.cpp
    src/semantics/ImplicitVarTypeChecker.cpp
    src/semantics/TypeChecker.cpp
    src/statement/IStatement.cpp
    src/statement/WhileStatement.cpp
    src/statement/IfStatement.cpp
    src/statement/ContinueStatement.cpp
    src/statement/ExpressionStatement.cpp
    src/statement/AssignStatement.cpp
    src/statement/ReturnStatement.cpp
    src/statement/BreakStatement.cpp
    src/statement/VarStm.cpp
    src/helpers/string_helper.cpp
    src/helpers/ainio.cpp
    src/helpers/wchar_t_helper.cpp
    src/helpers/number_helper.cpp
    src/parser/ExpressionParser.cpp
    src/parser/elements/Type.cpp
    src/parser/elements/FunDecl.cpp
    src/parser/elements/FunParam.cpp
    src/parser/elements/parser/FunParamParser.cpp
    src/parser/elements/parser/FunDeclParser.cpp
    src/parser/elements/parser/VarDeclParser.cpp
    src/parser/elements/parser/TypeParser.cpp
    src/parser/elements/VarDecl.cpp
    src/parser/PackageParser.cpp
    src/parser/FunParser.cpp
    src/parser/TokensIterator.cpp
    src/parser/StmListParser.cpp
    src/parser/ClassParser.cpp
    src/parser/VarStatementParser.cpp
    src/parser/FileParser.cpp
    src/parser/ASTVisitor.cpp
)

set(INCLUDE
    include/
    include/exceptions/
    include/exceptions/lexer/
    include/exceptions/expression/
    include/exceptions/semantics/
    include/exceptions/statement/
    include/exceptions/parser/
    include/exceptions/runtime/
    include/lexer/
    include/expression/
    include/expression/value/
    include/scope/
    include/scope/function/
    include/scope/class/
    include/ain_file/
    include/semantics/
    include/statement/
    include/helpers/
    include/parser/
    include/parser/elements/
    include/parser/elements/parser/
    include/parser/AST/
)

set(TEST
    test/lexer/LexerTest.cpp
    test/lexer/LexerLineTest.cpp
    test/ain_file/AinFileTest.cpp
    test/parser/PackageParserTest.cpp
    test/parser/elements/FunDeclTest.cpp
    test/parser/elements/VarDeclTest.cpp
    test/parser/elements/parser/VarDeclParserTest.cpp
    test/parser/elements/parser/FunDeclParserTest.cpp
    test/parser/elements/parser/TypeParserTest.cpp
    test/parser/elements/parser/FunParamParserTest.cpp
    test/parser/elements/TypeTest.cpp
    test/parser/elements/FunParamTest.cpp
    test/parser/FileParserTest.cpp
    test/parser/TokensIteratorTest.cpp
    test/parser/TokensIteratorForTests.cpp
    test/parser/FunParserTest.cpp
)

### end files_cmake.cpp ###



set(TEST_INCLUDE
    testInclude/
)


add_executable(ain src/main.cpp)

target_include_directories(ainsrc PUBLIC ${INCLUDE})

target_link_libraries(ain ainsrc)

# Add Catch2 library
find_package(Catch2 REQUIRED)

# Add test executable
add_executable(unit_tests ${TEST})

target_include_directories(unit_tests PUBLIC ${TEST_INCLUDE})

# Link Catch2 library to the test executable
target_link_libraries(unit_tests Catch2::Catch2 ainsrc)

# Add test executable
add_executable(pretty_print ExpressionPrettyPrintTest.cpp)

# Link Catch2 library to the test executable
target_link_libraries(pretty_print ainsrc)

# Make executables in build/bin
set_target_properties(ain PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin/)

set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin/)

set_target_properties(pretty_print PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin/)