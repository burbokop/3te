#include "object.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

Object::Object()
{
    this->capabilities = new std::vector<Capability>();
}
