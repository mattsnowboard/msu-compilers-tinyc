

#include "WhileStmt.h"
#include "Block.h"

WhileStmt* WhileStmt::Clone()
{
    Expr *c = (_cond) ? _cond->Clone() : NULL;
    Block *b = (_block) ? _block->Clone() : NULL;
    WhileStmt *wstmt = new WhileStmt(c, b, _line);
    return wstmt;
}
