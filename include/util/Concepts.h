#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename T>
        concept Averageable = requires(T anElement, double aDouble)
        {
            {
                anElement + anElement
            }
            ->std::same_as<T>;
            {
                anElement / aDouble
            }
            ->std::convertible_to<double>;
        };
    } // namespace internal
} // namespace Lincpp
