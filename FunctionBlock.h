#ifndef _FUNCTION_BLOCK_H
#define _FUNCTION_BLOCK_H

#include "ParamDefList.h"
#include <string>

class Block;

class FunctionBlock
{
public:
    FunctionBlock(const std::string name, ParamDefList *params, int lineNum);

    virtual ~FunctionBlock();

    void SetBlock(Block *b);

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
