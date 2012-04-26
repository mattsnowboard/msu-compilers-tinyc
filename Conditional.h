#ifndef _CONDITIONAL_H
#define _CONDITIONAL_H

#include "Statement.h"
#include <list>

class Block;
class Expr;

class Conditional : public Statement
{
public:
    Conditional(Expr *cond, Block *block, int lineNum) :
        _cond(cond), _block(block), _value(lineNum)
    {}
    virtual ~Conditional();
    
    virtual int Get() const { return _value; }

    Expr const* GetCondition() const {
        return _cond;
    }

    Block const* GetBlock() const {
        return _block;
    }

protected:
    Expr *_cond;
    Block *_block;
    int _value;
};

#endif
