#pragma once

namespace Lincpp
{
    namespace internal
    {
        // traits info specialization for Enumerable
        template <typename TSource, typename TElement, typename TIterator>
        struct traits<Enumerable<TSource, TElement, TIterator>>
        {
            typedef TSource Source;
            typedef TElement Element;
            typedef TIterator Iterator;
        };
    } // namespace internal

    // Enumerable class
    template <typename TSource, typename TElement = typename TSource::value_type, typename TIterator = typename TSource::const_iterator>
    struct Enumerable : public internal::Query<Enumerable<TSource, TElement, TIterator>>
    {
    public:
        Enumerable(const TSource &source) : begin(source.cbegin()), end(source.cend()), data_copied(false) {}

    public:
        typename TSource::size_type Count() const { return std::distance(begin, end); }

        const TElement &ElementAt(typename TSource::size_type i)
        {
            if (this->data_copied)
                return this->data.at(i);

            if (i >= this->Count())
                throw std::out_of_range("index out of range");

            TIterator it = this->begin;
            while (i > 0)
            {
                ++it;
                i--;
            }
            return *it;
        }

    private:
        TIterator begin;
        TIterator end;
        typename internal::container<TElement> data;
        bool data_copied;

        // void copyData()
        // {
        //     for (auto it = source.cbegin(); it != source.cend(); it++)
        //         this->data.push_back(*it);
        // }

    public:
        // these allow to write instantiate an Enumerable from another one
        typedef TElement value_type;
        typedef typename internal::container<TElement>::const_iterator const_iterator;
        typedef typename internal::container<TElement>::size_type size_type;

        const_iterator cbegin() const { return this->data_copied ? this->data.cbegin() : this->begin; }
        const_iterator cend() const { return this->data_copied ? this->data.cend() : this->end; }
    };

    template <typename T>
    static Enumerable<T> From(const T &source)
    {
        return Enumerable<T>(source);
    }
} // namespace Lincpp
