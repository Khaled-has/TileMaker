#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <functional>
#include <memory>

#include <vector>
#include <string>

#include "Log/Log.h"


#define BIT(x) (1 << x)
#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

#endif