#pragma once

namespace Lincpp
{
    namespace internal
    {
        // traits info specialization for Enumerable
        template <typename TElement, typename TIterator>
        struct traits<Enumerable<TElement, TIterator>>
        {
            typedef TElement Element;
            // typedef TIterator ITerator;
            typedef typename default_container<TElement>::size_type Size;
        };
    } // namespace internal

    template <typename TElement, typename TIterator = typename default_container<TElement>::const_iterator>
    struct Enumerable : public Queriable<Enumerable<TElement, TIterator>>
    {
    public:
        typedef typename default_container<TElement>::size_type size_type;
        // friend struct Queriable<Enumerable<TElement, TIterator>>;

    public:
        // 1: Constructs an Enumerable from a temporary initializer list, copies data
        Enumerable(std::initializer_list<TElement> &&list) : is_data_copied(true)
        {
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            this->data.reserve(std::distance(list.begin(), list.end()));
            std::move(internal::default_execution_policy, list.begin(), list.end(), std::back_inserter(this->data));
        }

        // 2: Constructs an Enumerable from a temporary source, must copy data
        template <typename TSource>
        Enumerable(const TSource &&source) requires(!internal::LincppEnumerable<TSource>) : is_data_copied(true)
        {
            CHECK_SOURCE_CONTENT(TSource, TElement);
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            this->data.reserve(std::distance(source.begin(), source.end()));
            std::move(internal::default_execution_policy, source.begin(), source.end(), std::back_inserter(this->data));
        }

        // 3: Constructs an Enumerable from a non-temporary Queriable, must copy data to force evaluation
        template <typename TEnumerable>
        Enumerable(const TEnumerable &source) requires internal::LincppEnumerable<TEnumerable> : is_data_copied(true)
        {
            CHECK_SOURCE_CONTENT(TEnumerable, TElement);
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            size_type L = source.Size();
            this->data.reserve(L);
            for (size_type i = 0; i < L; ++i)
                this->data.push_back(source.ElementAt(i));
        }

        // 5: Constructs an Enumerable from a non-temporary source, can choose to copy data or just iterators
        template <typename TSource>
        Enumerable(const TSource &source, bool forceCopy) requires(!internal::LincppEnumerable<TSource>) : is_data_copied(forceCopy)
        {
            CHECK_SOURCE_CONTENT(TSource, TElement);
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            if (forceCopy)
            {
                this->data.reserve(std::distance(source.cbegin(), source.cend()));
                std::copy(internal::default_execution_policy, source.cbegin(), source.cend(), std::back_inserter(this->data));
            }
            else
            {
                this->begin = source.cbegin();
                this->end = source.cend();
            }
        }

        // 7: Constructs an Enumerable from a non-temporary Enumerable, can choose to copy data or just iterators
        Enumerable(const Enumerable<TElement, TIterator> &source, bool forceCopy) : is_data_copied(forceCopy)
        {
            CHECK_ITERATOR_TYPE(TIterator, TElement);
            if (forceCopy)
            {
                this->data.reserve(source.Size());
                std::copy(internal::default_execution_policy, source.cbegin(), source.cend(), std::back_inserter(this->data));
            }
            else
            {
                this->begin = source.cbegin();
                this->end = source.cend();
            }
        }

    public:
        inline size_type Size() const { return this->is_data_copied ? this->data.size() : std::distance(this->begin, this->end); }

        inline const TElement &ElementAt(size_type i) const
        {
            if (!this->is_data_copied)
            {
                auto it = this->begin;
                while (i != 0)
                {
                    --i;
                    it++;
                    if (it == this->end)
                        throw std::out_of_range("index outside range");
                }
                return *it;
            }
            else
                return this->data.at(i);
        }

        inline TIterator cbegin() const { return this->is_data_copied ? this->data.cbegin() : this->begin; }
        inline TIterator cend() const { return this->is_data_copied ? this->data.cend() : this->end; }

        // TODO inline Enumerable<TElement, TIterator> Clone() const { return Enumerable<TElement, TIterator>(*this, true); }

    private:
        Enumerable() = default;
        Enumerable(const Enumerable<TElement, TIterator> &) = delete;

        TIterator begin;
        TIterator end;
        default_container<TElement> data;
        bool is_data_copied;
    }; // namespace Lincpp

    // 1: Constructs an Enumerable from a temporary initializer list, copies data
    template <typename TElement>
    static Enumerable<TElement, typename std::initializer_list<TElement>::const_iterator> From(std::initializer_list<TElement> &&list)
    {
        return Enumerable<TElement, typename std::initializer_list<TElement>::const_iterator>(std::forward<std::initializer_list<TElement>>(list));
    }

    // 2: temporary ref to whatever source, must copy data
    template <typename TSource, typename TElement = typename TSource::value_type, typename TIterator = typename TSource::const_iterator>
    static Enumerable<TElement, TIterator> From(const TSource &&source) requires(!internal::LincppEnumerable<TSource>)
    {
        return Enumerable<TElement, TIterator>(std::forward<const TSource &&>(source));
    }

    // 3-6: Constructs an Enumerable from a non-temporary Queriable, must copy data to force evaluation
    template <typename TEnumerable>
    static Enumerable<typename internal::traits<TEnumerable>::Element> From(const TEnumerable &source) requires internal::LincppEnumerable<TEnumerable>
    {
        return Enumerable<typename internal::traits<TEnumerable>::Element>(source);
    }

    // 4: Constructs an Enumerable from a non-temporary Enumerable, must copy data
    template <typename TElement, typename TIterator>
    static Enumerable<TElement, TIterator> From(const Enumerable<TElement, TIterator> &&source)
    {
        return Enumerable<TElement, TIterator>(source, true);
    }

    // 5: Constructs an Enumerable from a non-temporary source, can choose to copy data or just iterators
    template <typename TSource, typename TElement = typename TSource::value_type, typename TIterator = typename TSource::const_iterator>
    static Enumerable<TElement, TIterator> From(const TSource &source, bool copyData = true) requires(!internal::LincppEnumerable<TSource>)
    {
        return Enumerable<TElement, TIterator>(source, copyData);
    }

    // 7: Constructs an Enumerable from a non-temporary Enumerable, can choose to copy data or just iterators
    template <typename TElement, typename TIterator>
    static Enumerable<TElement, TIterator> From(const Enumerable<TElement, TIterator> &source, bool copyData = true)
    {
        return Enumerable<TElement, TIterator>(source, copyData);
    }
} // namespace Lincpp
