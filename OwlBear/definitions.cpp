#include "stdafx.h"
#include "definitions.h"

Move::Move(unsigned short fromIn, unsigned short toIn, SquareState capturesIn)
{
    from = fromIn;
    to = toIn;
    captures = capturesIn;
}
