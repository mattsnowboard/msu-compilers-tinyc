#ifndef _FUNCTION_BLOCK_H
#define _FUNCTION_BLOCK_H

#include "ParamDefList.h"
#include "Block.h"
#include <string>

class FunctionBlock
{
public:
    FunctionBlock(const std::string name, ParamDefList *params, int lineNum) :
        _line(lineNum),
        _name(name),
        _totalLocalSpace(0),
        _params(params),
        _block(NULL),
    {
        _paramCnt = 8;
        ParamDefList::ListT plist = _params->GetParams();
        for (ParamDefList::ListT::reverse_iterator it = plist.rbegin();
             it != plist.rend();
             ++it) {
            _table.AddVar(*it, _paramCnt);
            _paramCnt += 4;
        }
    }

    virtual ~FunctionBlock()
    {
        if (_params) {
            delete _params;
        }
        if (_block) {
            delete _block;
        }
    }

    void SetBlock(Block *b)
    {
        if (_block != NULL) {
            throw std::runtime_error("Function block already set!");
        }
        _block = b;

        // look for declarations
        _block->ParseLocals();
        _totalLocalSpace = _block->GetLocalTotal();
    }

    const std::string& GetName() const 
    {
        return _name;
    }

    ParamDefList const * GetParameters() const
    {
        return _params;
    }

    /**
     * Helper to just get the number of input parameters
     */
    unsigned GetParamCount() const
    {
        return _params->GetParams().size();
    }

    Block const* GetBlock() const
    {
        return _block;
    }

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    int GetLine() const
    {
        return _line;
    }

    int GetVariableSpace() const
    {
        return _totalLocalSpace;
    }
    
    int GetParamSpace() const
    {
        return _paramCnt - 8;
    }

private:
    FunctionBlock(const FunctionBlock &s);
    FunctionBlock& operator=(const FunctionBlock &s);

    int _line;
    int _totalLocalSpace;
    int _paramCnt;
    std::string _name;
    ParamDefList *_params;
    Block *_block;
};

#endif
