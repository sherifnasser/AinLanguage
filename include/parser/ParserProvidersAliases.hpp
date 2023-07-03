#pragma once
#include "SharedPtrTypes.hpp"
#include <functional>
#include <string>

using TypeParserProvider=std::function<SharedBaseParser<SharedType>(
    SharedTokensIterator iterator,
    SharedBaseScope scope
)>;

using FunParamParserProvider=std::function<SharedBaseParser<SharedFunParam>(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    TypeParserProvider typeParserProvider
)>;

using FunDeclParserProvider=std::function<SharedBaseParser<SharedFunDecl>(
    SharedTokensIterator iterator,
    SharedBaseScope scope
)>;

using StmListParserProvider=std::function<SharedBaseParser<SharedStmList>(
    SharedTokensIterator iterator,
    SharedStmListScope scope
)>;