#pragma once

namespace Lincpp
{
    namespace internal
    {
        // traits info specialization for Enumerable
        template <typename TElement>
        struct traits<Enumerable<TElement>>
        {
            typedef TElement Element;
            typedef typename default_container<TElement>::size_type Size;
        };
    } // namespace internal

    template <typename TElement>
    struct Enumerable : public Queriable<Enumerable<TElement>>
    {
    public:
        typedef typename default_container<TElement>::size_type size_type;
        typedef typename default_container<TElement>::const_iterator const_iterator;
        friend struct Queriable<Enumerable<TElement>>;

    public:
        template <typename TIterator>
        Enumerable(TIterator begin, TIterator end)
        {
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            this->data.reserve(std::distance(begin, end));
            std::copy(begin, end, std::back_inserter(this->data));
        }

        Enumerable(std::initializer_list<TElement> &&list) : Enumerable(list.begin(), list.end()) {}

        template <typename TSource>
        Enumerable(const TSource &source) : Enumerable(source.begin(), source.end()) {}

        template <typename TEnumerable>
        Enumerable(const TEnumerable &source) requires(std::is_base_of_v<Queriable<TEnumerable>, TEnumerable>)
        {
            CHECK_SOURCE_CONTENT(TEnumerable, TElement);
            size_type L = source.Count();
            this->data.reserve(L);
            for (size_type i = 0; i < L; ++i)
                this->data.push_back(source.ElementAt(i));
        }

    public:
        size_type Count() const { return this->data.size(); }

        TElement &ElementAt(size_type i) { return this->data.at(i); }
        const TElement &ElementAt(size_type i) const { return this->data.at(i); }

        const_iterator cbegin() const { return this->data.cbegin(); }
        const_iterator cend() const { return this->data.cend(); }

    private:
        Enumerable() = default;
        default_container<TElement> data;
    };

    template <typename TSource, typename TElement = typename TSource::value_type>
    static Enumerable<TElement> From(const TSource &source)
    {
        return Enumerable<TElement>(source);
    }

    template <typename TElement>
    static Enumerable<TElement> From(TElement *source, std::size_t n)
    {
        return Enumerable<TElement>(source, source + n);
    }

    template <typename TIterator, typename TElement = typename std::iterator_traits<TIterator>::value_type>
    static Enumerable<TElement> From(TIterator begin, TIterator end)
    {
        return Enumerable<TElement>(begin, end);
    }

    template <typename TElement>
    static Enumerable<TElement> From(std::initializer_list<TElement> &&list)
    {
        return Enumerable<TElement>(std::forward<std::initializer_list<TElement>>(list));
    }
} // namespace Lincpp
