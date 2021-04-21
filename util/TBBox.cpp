#include "TBBox.h"

bool TBBox::operator==(const TBBox &rhs) const
{
    return this->t == rhs.t;
}

bool TBBox::operator<(const TBBox &rhs) const
{
    return this->t < rhs.t;
}

bool TBBox::operator>(const TBBox &rhs) const
{
    return this->t > rhs.t;
}