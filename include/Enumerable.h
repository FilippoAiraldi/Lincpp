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
            typedef typename default_container<TElement>::size_type size_type;
        };
    } // namespace internal

    template <typename TElement>
    struct Enumerable : public Queriable<Enumerable<TElement>>
    {
    public:
        // these allow to instantiate an Enumerable from another Enumerable
        typedef TElement value_type;
        typedef typename default_container<TElement>::const_iterator const_iterator;
        typedef typename default_container<TElement>::size_type size_type;

    public:
        template <typename TSource>
        Enumerable(const TSource &source)
        {
            // static_assert(std::is_convertible_v<typename TSource::value_type, TElement>, "Input container must contain TElement as value type, or at least something convertible to it.");
            static_assert(std::is_same_v<typename TSource::value_type, TElement>, "Input container must contain TElement as value type.");

            if constexpr (std::is_base_of_v<Queriable<TSource>, TSource>)
            {
                size_type L = source.Count();
                this->data.reserve(L);
                for (size_type i = 0; i < L; ++i)
                    this->data.push_back(source.ElementAt(i));
            }
            else
            {
                // auto begin = source.cbegin();
                // auto end = source.cend();
                // this->data.reserve(std::distance(begin, end));
                this->data.reserve(source.size());
                std::copy(source.begin(), source.end(), std::back_inserter(this->data));
            }
        }

        Enumerable(std::initializer_list<TElement> &&list)
        {
            this->data.reserve(list.size());
            std::move(list.begin(), list.end(), std::back_inserter(this->data));
        }

    public:
        size_type Count() const { return this->data.size(); }
        TElement &ElementAt(size_type i) { return this->data.at(i); }
        const TElement &ElementAt(size_type i) const { return this->data.at(i); }

        const_iterator cbegin() const { return this->data.cbegin(); }
        const_iterator cend() const { return this->data.cend(); }

    private:
        default_container<TElement> data;
    };

    template <typename TSource, typename TElement = typename TSource::value_type>
    static Enumerable<TElement> From(const TSource &source)
    {
        return Enumerable<TElement>(source);
    }

    template <typename TElement>
    static Enumerable<TElement> From(std::initializer_list<TElement> &&list)
    {
        return Enumerable<TElement>(std::forward<std::initializer_list<TElement>>(list));
    }
} // namespace Lincpp
