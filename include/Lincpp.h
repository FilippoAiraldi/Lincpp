#pragma once

#include <stdexcept>
#include <type_traits>
#include <vector>
#include <list>
#include <memory>
#include <iterator>
#include <algorithm>
#include <execution>

#include "util/ForwardDeclarations.h"
#include "util/Constants.h"
#include "util/Macros.h"
#include "util/Concepts.h"

#include "util/ParallelFor.h"

#include "Enumerable.h"

#include "clauses/CastClause.h"
#include "clauses/SelectClause.h"

#include "Queriable.h" // last declared so that it knows all definitions
