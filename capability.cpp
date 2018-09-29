#include "capability.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

Capability::Capability(void *parent)
{
    this->parent = parent;
}
