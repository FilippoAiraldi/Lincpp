#pragma once

//#include <stdexcept>
//#include <type_traits>
//#include <memory>
//#include <iterator>
//#include <algorithm>
// #include <execution>

#include <iterator>
#include <initializer_list>

#include "defs/ForwardDeclarations.h"
#include "defs/Constants.h"
#include "defs/Macros.h"
#include "defs/Concepts.h"

// #ifndef LINCPP_PARALLEL_DISABLE
// #include "util/ParallelFor.h"
// #endif

// #include "Enumerable.h"

#include "clauses/source/SourceIterator.h"
#include "base/QueriableIterator.h" // last declared so that it knows all definitions

#include "clauses/source/Source.h"

#include "base/Queriable.h" // last declared so that it knows all definitions
