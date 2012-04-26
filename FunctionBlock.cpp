#include "FunctionBlock.h"

#include "Block.h"

FunctionBlock::FunctionBlock(const std::string name, ParamDefList *params, int lineNum) :
    _line(lineNum),
    _totalLocalSpace(0),
    _paramCnt(8),
    _name(name),
    _params(params),
    _block(NULL)
{
}

FunctionBlock::~FunctionBlock()
{
    if (_params) {
        delete _params;
    }
    if (_block) {
        delete _block;
    }
}

void FunctionBlock::SetBlock(Block *b)
{
    if (_block != NULL) {
        throw std::runtime_error("Function block already set!");
    }
    _block = b;

    // look for declarations
    _block->ParseLocals();
    _totalLocalSpace = _block->GetLocalTotal();

    ParamDefList::ListT plist = _params->GetParams();
    for (ParamDefList::ListT::reverse_iterator it = plist.rbegin();
         it != plist.rend();
         ++it) {
        _block->GetSymbolTable()->AddVar(*it, _paramCnt);
        _paramCnt += 4;
    }
}
