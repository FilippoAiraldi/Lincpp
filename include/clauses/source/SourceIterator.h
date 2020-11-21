// #pragma once

// namespace Lincpp
// {
//     template <typename I>
//     struct SourceIterator : public internal::BaseIterator<I>
//     {
//     public:
//         typedef std::iterator_traits<I>::iterator_category iterator_category;
//         typedef std::iterator_traits<I>::difference_type difference_type;
//         typedef std::iterator_traits<I>::value_type value_type;
//         typedef std::iterator_traits<I>::reference reference;
//         typedef std::iterator_traits<I>::pointer pointer;

//         explicit SourceIterator(I begin, I end, I it) : internal::BaseIterator<I>(begin, end, it) {}
//         SourceIterator(const internal::BaseIterator<I> &a) : internal::BaseIterator<I>(a) {}

//         SourceIterator<I> &operator++() noexcept // pre
//         {
//             return *this;
//         }
//     };

//     template <typename I>
//     static SourceIterator<I> MakeSourceIterator(I begin, I end, I it)
//     {
//         return SourceIterator<I>(begin, end, it);
//     }
// } // namespace Lincpp
