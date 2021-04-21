#ifndef FUNSHIT_TBBOX_H
#define FUNSHIT_TBBOX_H

#include "Triangle.h"
#include "BBox.h"

class TBBox : public BBox
{
public:
    explicit TBBox(Triangle& _t) :
            BBox(_t.get_BBox()),
            t(&_t)
    { }
    TBBox(const TBBox& other) = default;
    TBBox& operator=(const TBBox& other) {
        BBox::operator=(other);
        t = other.t;
        return *this;
    }
    ~TBBox() = default;

    bool operator==(const TBBox&) const;
    bool operator<(const TBBox&) const;
    bool operator>(const TBBox&) const;

//    Triangle& t;
    Triangle* t;
};



#endif //FUNSHIT_TBBOX_H
