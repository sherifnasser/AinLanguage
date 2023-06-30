#include <catch2/catch.hpp>
#include <string>
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "string_helper.hpp"
#include "VarDecl.hpp"

namespace Catch {
    template<>
    struct StringMaker<Type> {
        static std::string convert( Type const& value ){
            return "Type: ("+std::string(
                toCharPointer(*value.name)
            )+")";
        }
    };

    template<>
    struct StringMaker<VarDecl> {
        static std::string convert( VarDecl const& value ){
            return
                "VarDecl: ("+
                std::string(toCharPointer(*value.name+L", "))+
                StringMaker<Type>::convert(*value.type)+", "+
                std::to_string(*value.isVal)+
                ")"
            ;
        }
    };
}