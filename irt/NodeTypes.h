#pragma once

#include <irt/expressions/Binop.h>
#include <irt/expressions/Call.h>
#include <irt/expressions/Const.h>
#include <irt/expressions/ESeq.h>
#include <irt/expressions/Mem.h>
#include <irt/expressions/Name.h>
#include <irt/expressions/Temp.h>
#include <irt/expressions/Unop.h>

#include <irt/statements/CJump.h>
#include <irt/statements/Exp.h>
#include <irt/statements/Jump.h>
#include <irt/statements/Label.h>
#include <irt/statements/Move.h>
#include <irt/statements/Seq.h>

#include <irt/translator/ExprWrapper.h>
#include <irt/translator/StmWrapper.h>

#include <vector>
#include <unordered_map>

namespace NIRTree {
    using IRForest = std::unordered_map<const Symbol*, std::unique_ptr<ISubtreeWrapper>>;
    using LinearTree = std::vector<std::unique_ptr<IStm>>;
    using IRLinearForest = std::unordered_map<const Symbol*, LinearTree>;
}