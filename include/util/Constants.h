#pragma once

#ifndef LINCPP_PARALLEL_THRESHOLD
#define LINCPP_PARALLEL_THRESHOLD 27000;
#endif

namespace Lincpp
{
    namespace internal
    {
        constexpr auto default_execution_policy = std::execution::par;

        constexpr unsigned long int parallel_threshold_size = LINCPP_PARALLEL_THRESHOLD;
    } // namespace internal
} // namespace Lincpp
