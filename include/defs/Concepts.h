#pragma once

namespace Lincpp
{
    namespace internal
    {
        // template <typename I>
        // concept MinimumIteratorRequirements = std::input_iterator<I> &&std::incrementable<I>;

        // template <typename T>
        // concept LincppEnumerable = std::is_base_of<Queriable<T>, T>::value;

        // template <typename Tin1, typename Tin2, typename Tout>
        // concept Addable = requires(Tin1 x, Tin2 y) { { x + y } -> std::same_as<Tout>; };

        // template <typename Tnum, typename Tden, typename Tout>
        // concept Divisible = requires(Tnum n, Tden d) { { n / d } -> std::same_as<Tout>; };

        // template <typename T>
        // concept Averageable = Addable<T, T, T> && Divisible<T, double, double>;
    } // namespace internal
} // namespace Lincpp
