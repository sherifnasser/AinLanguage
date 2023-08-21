#pragma once
#include "VarStm.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
#include <vector>

namespace Semantics{


    class IImplicitVarTypeChecker{
        public:
            virtual void subscribe(std::shared_ptr<VarStm> varStm)=0;
            virtual void check()=0;
    };

    class ImplicitVarTypeChecker:public IImplicitVarTypeChecker{
        private:
            std::vector<std::shared_ptr<VarStm>> checkStatements;
            static inline std::shared_ptr<ImplicitVarTypeChecker> instance;
            ImplicitVarTypeChecker();
        public:
            static std::shared_ptr<ImplicitVarTypeChecker> getInstance();
            void subscribe(std::shared_ptr<VarStm> varStm)override;
            void check()override;
    };
};
