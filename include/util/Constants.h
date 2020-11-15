#pragma once

namespace Lincpp
{
    namespace internal
    {
        constexpr auto default_execution_policy = std::execution::par;

#ifdef LINCPP_PARALLEL_THRESHOLD
        constexpr unsigned long int parallel_threshold_size = LINCPP_PARALLEL_THRESHOLD;
#else
        constexpr unsigned long int parallel_threshold_size = 27000;
#endif
    } // namespace internal
} // namespace Lincpp
