#pragma once

#include <iterator>
#include <initializer_list>

#include "util/Macros.h"

#ifndef LINCPP_NO_EXCEPTIONS
#include <stdexcept>
#include "exceptions/InvalidOperation.h"
#include "exceptions/OutOfRange.h"
#endif

#include "base/Iterator.h" // last declared so that it knows all definitions
#include "clauses/SelectIterator.h"
#include "clauses/WhereIterator.h"

#include "base/Queriable.h" // last declared so that it knows all definitions
