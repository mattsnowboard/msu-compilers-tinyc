
#include "IfStmt.h"
#include "Block.h"

IfStmt* IfStmt::Clone()
{
    Expr *c = (_cond) ? _cond->Clone() : NULL;
    Block *b = (_block) ? _block->Clone() : NULL;
    IfStmt *ifstmt = new IfStmt(c, b, _line);
    return ifstmt;
}
