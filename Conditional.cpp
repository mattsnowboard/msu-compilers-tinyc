
#include "Conditional.h"
#include "Block.h"
#include "Expr.h"

Conditional::~Conditional()
{
    if (_cond) {
        delete _cond;
        _cond = NULL;
    }
    if (_block) {
        delete _block;
        _block = NULL;
    }
}
