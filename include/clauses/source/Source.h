#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename TIterator>
        struct traits<Source<TIterator>>
        {
            // typedef TIterator Iterator;
            // typedef SourceIterator<TIterator> Iterator;
            typedef typename std::iterator_traits<TIterator>::value_type Element;
        };
    } // namespace internal

    template <typename TIterator>
    struct Source : public Queriable<Source<TIterator>>
    {
    private:
        template <typename AnyElement>
        friend Source<typename std::initializer_list<AnyElement>::const_iterator> From(std::initializer_list<AnyElement> &&);
        template <typename AnyIterator>
        friend Source<AnyIterator> From(AnyIterator, AnyIterator);
        // template <typename AnyDerived>
        // friend struct Queriable;

        typedef typename std::iterator_traits<TIterator>::value_type TElement;

    protected:
        Source(TIterator begin, TIterator end) : b(begin), e(end) {}

    public:
        // inline SourceIterator<TIterator> cbegin() const { return MakeSourceIterator<TIterator>(b, e, b); }
        // inline SourceIterator<TIterator> cend() const { return MakeSourceIterator<TIterator>(b, e, e); }

    private:
        TIterator b;
        TIterator e;

    private:
        Source() = delete;
        Source(const Source<TIterator> &) = delete;
        Source(Source<TIterator> &&) = delete;
    };

    template <typename TElement>
    static Source<typename std::initializer_list<TElement>::const_iterator> From(std::initializer_list<TElement> &&list)
    {
        return Source<typename std::initializer_list<TElement>::const_iterator>(list.begin(), list.end());
    }

    template <typename TIterator>
    static Source<TIterator> From(TIterator begin, TIterator end)
    {
        return Source<TIterator>(begin, end);
    }
} // namespace Lincpp
