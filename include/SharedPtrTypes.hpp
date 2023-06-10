#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<string>

class IAinFile;
class ILexer;
class ILexerLine;
class IParser;
class LexerToken;
class Scope;
class GlobalScope;
class FunScope;
class ClassScope;
class Variable;
class Constant;
class IStatement;
class IExpression;

template<typename T>
using SharedVector=std::shared_ptr<std::vector<T>>;

using SharedWString=std::shared_ptr<std::wstring>;

using SharedILexerLine=std::shared_ptr<ILexerLine>;

using SharedLexerToken=std::shared_ptr<LexerToken>;

using SharedIAinFile=std::shared_ptr<IAinFile>;

using SharedILexer=std::shared_ptr<ILexer>;

using SharedIParser=std::shared_ptr<IParser>;

using SharedScope=std::shared_ptr<Scope>;

using SharedGlobalScope=std::shared_ptr<GlobalScope>;

using SharedClassScope=std::shared_ptr<ClassScope>;

using SharedFunScope=std::shared_ptr<FunScope>;

using SharedVariable=std::shared_ptr<Variable>;

using SharedConstant=std::shared_ptr<Constant>;

using SharedIStatement=std::shared_ptr<IStatement>;

using SharedIExpression=std::shared_ptr<IExpression>;