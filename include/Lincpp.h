#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

// #include <deque>
#include <forward_list>
#include <list>
// #include <map>
// #include <set>
// #include <unordered_map>
// #include <unordered_set>
#include <vector>

#include "util/ForwardDeclarations.h"
#include "util/Macros.h"

#include "exceptions/InvalidOperation.h"
#include "exceptions/OutOfRange.h"

#include "iterators/SelectIterator.h"
#include "iterators/WhereIterator.h"
#include "iterators/Iterator.h" // last declared so that it knows all definitions

#include "base/Orderable.h"
#include "base/Queriable.h"
