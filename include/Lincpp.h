#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#include "util/Macros.h"

#include "exceptions/InvalidOperation.h"
#include "exceptions/OutOfRange.h"

#include "base/Iterator.h" // last declared so that it knows all definitions
#include "clauses/SelectIterator.h"
#include "clauses/WhereIterator.h"

#include "base/Queriable.h" // last declared so that it knows all definitions
