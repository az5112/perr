#ifdef PERR
#include "perr.h"
#else
static struct Perr {template <typename T> constexpr Perr& operator<<(T const &any) {return *this;}} perr;
#endif
