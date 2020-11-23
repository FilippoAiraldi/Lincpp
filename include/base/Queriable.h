#pragma once

namespace Lincpp
{
    template <typename TIterator>
    struct Queriable
    {
    private:
        using category = typename std::iterator_traits<TIterator>::iterator_category;
        template <typename AnyIterator>
        friend struct Queriable;

    public:
        Queriable() = delete;
        Queriable(const Queriable<TIterator> &) = default;
        Queriable(Queriable<TIterator> &&) = default;
        Queriable(TIterator begin, TIterator end) : _begin(begin), _end(end) {}

    public:
        typedef typename std::iterator_traits<TIterator>::value_type TElement;

        const TIterator cbegin() const { return this->_begin; }
        const TIterator cend() const { return this->_end; }

        template <typename TPredicate>
        bool All(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            return std::all_of(_begin, _end, predicate);
        }

        template <typename TPredicate>
        bool Any(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            return std::any_of(_begin, _end, predicate);
        }

        inline bool Any() const { return _begin != _end; }

        double Average() const
        {
            CHECK_INTEGRAL_OR_FLOATING(TElement);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            TIterator it = _begin;
            double avg = *it;
            ++it;
            for (double k = 1.0; it != _end; ++it, k += 1.0)
                avg = (avg * k + *it) / (k + 1.0);
            return avg;
        }

        template <typename TFunc>
        double Average(TFunc evaluator) const
        {
            CHECK_FUNC_WITH_ALLOWED_CONVERSION(TFunc, TElement, double);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            TIterator it = _begin;
            double avg = evaluator(*it);
            ++it;
            for (double k = 1.0; it != _end; ++it, k += 1.0)
                avg = (avg * k + evaluator(*it)) / (k + 1.0);
            return avg;
        }

        template <typename TPredicate>
        std::size_t Count(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            return (std::size_t)std::count_if(_begin, _end, predicate);
        }
        constexpr std::size_t Count() const { return (std::size_t)std::distance(this->cbegin(), this->cend()); }

        bool Contains(const TElement &value) const { return std::find(_begin, _end, value) != _end; }

        template <typename TPredicate>
        bool Contains(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            return std::find_if(_begin, _end, predicate) != _end;
        }

        TElement ElementAt(std::size_t i) const
        {
            if constexpr (std::is_same_v<category, std::random_access_iterator_tag>)
            {
                if (i >= this->Count())
                    throw OutOfRange("index outside range");
                return *(_begin + i);
            }
            else
            {
                TIterator it = _begin;
                while (i--)
                {
                    it++;
                    if (it == _end)
                        throw OutOfRange("index outside range");
                }
                return *it;
            }
        }

        TElement ElementAtOrDefault(std::size_t i, const TElement &defaultValue) const
        {
            using category = typename std::iterator_traits<TIterator>::iterator_category;
            if constexpr (std::is_same_v<category, std::random_access_iterator_tag>)
            {
                if (i >= this->Count())
                    return defaultValue;
                return *(_begin + i);
            }
            else
            {
                TIterator it = _begin;
                while (i--)
                {
                    it++;
                    if (it == _end)
                        return defaultValue;
                }
                return *it;
            }
        }

        template <typename TPredicate>
        bool Empty(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            return std::none_of(_begin, _end, predicate);
        }

        inline bool Empty() const { return !this->Any(); }

        TElement First() const
        {
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            return *_begin;
        }

        template <typename TPredicate>
        TElement First(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            for (TIterator it = _begin; it != _end; ++it)
                if (predicate(*it))
                    return *it;
            throw InvalidOperation("no element satisfies the predicate");
        }

        TElement FirstOrDefault(const TElement &defaultValue) const
        {
            if (!this->Any())
                return defaultValue;
            return *_begin;
        }

        template <typename TPredicate>
        TElement FirstOrDefault(TPredicate predicate, const TElement &defaultValue) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            for (TIterator it = _begin; it != _end; ++it)
                if (predicate(*it))
                    return *it;
            return defaultValue;
        }

        TElement Max() const
        {
            // TComparer: comparison which returns ​true if the first argument is less than the second.
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            return *std::max_element(_begin, _end);
        }

        template <typename TComparer>
        TElement Max(TComparer comparer) const
        {
            // TComparer: comparison which returns ​true if the first argument is less than the second.
            CHECK_COMPARER(TComparer, TElement);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            return *std::max_element(_begin, _end, comparer);
        }

        TElement Min() const
        {
            // TComparer: comparison which returns ​true if the first argument is less than the second.
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            return *std::min_element(_begin, _end);
        }

        template <typename TComparer>
        TElement Min(TComparer comparer) const
        {
            // TComparer: comparison which returns ​true if the first argument is less than the second.
            CHECK_COMPARER(TComparer, TElement);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            return *std::min_element(_begin, _end, comparer);
        }

        TElement Last() const
        {
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
            {
                TIterator it = _end;
                return *(--it);
            }
            else
            {
                TIterator prev = _begin;
                TIterator curr = _begin;
                while (curr != _end)
                    prev = curr++;
                return *prev;
            }
        }

        template <typename TPredicate>
        TElement Last(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            if (!this->Any())
                throw InvalidOperation("sequence contains no element");
            if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
            {
                TIterator it = _end;
                do
                {
                    if (it == _begin)
                        throw InvalidOperation("no element satisfies the predicate");
                    --it;
                } while (!predicate(*it));
                return *it;
            }
            else
            {
                bool found = false;
                TIterator last = _begin;
                TIterator it = _begin;
                while (it != _end)
                {
                    if (predicate(*it))
                    {
                        last = it;
                        found = true;
                    }
                    ++it;
                }
                if (found)
                    return *last;
                else
                    throw InvalidOperation("no element satisfies the predicate");
            }
        }

        TElement LastOrDefault(const TElement &defaultValue) const
        {
            if (!this->Any())
                return defaultValue;
            if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
            {
                TIterator it = _end;
                return *(--it);
            }
            else
            {
                TIterator prev = _begin;
                TIterator curr = _begin;
                while (curr != _end)
                    prev = curr++;
                return *prev;
            }
        }

        template <typename TPredicate>
        TElement LastOrDefault(TPredicate predicate, const TElement &defaultValue) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            if (!this->Any())
                return defaultValue;
            if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
            {
                TIterator it = _end;
                do
                {
                    if (it == _begin)
                        return defaultValue;
                    --it;
                } while (!predicate(*it));
                return *it;
            }
            else
            {
                TElement res = defaultValue;
                TIterator it = _begin;
                while (it != _end)
                {
                    if (predicate(*it))
                        res = *it;
                    ++it;
                }
                return res;
            }
        }

        template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(TElement)>>
        Queriable<SelectIterator<TIterator, TFunc, TReturn>> Select(TFunc selector) const
        {
            return Queriable<SelectIterator<TIterator, TFunc, TReturn>>(
                SelectIterator<TIterator, TFunc, TReturn>(_begin, selector),
                SelectIterator<TIterator, TFunc, TReturn>(_end, selector));
        }

        template <typename TPred>
        Queriable<WhereIterator<TIterator, TPred>> Where(TPred predicate) const
        {
            return Queriable<WhereIterator<TIterator, TPred>>(
                WhereIterator<TIterator, TPred>(_begin, _end, predicate),
                WhereIterator<TIterator, TPred>(_end, _end, predicate));
        }

    private:
        const TIterator _begin;
        const TIterator _end;

        template <typename AnyElement>
        friend Queriable<typename std::initializer_list<AnyElement>::const_iterator> From(std::initializer_list<AnyElement> &&);
        template <typename AnyIterator>
        friend Queriable<AnyIterator> From(AnyIterator, AnyIterator);
    };

    template <typename TElement>
    static Queriable<typename std::initializer_list<TElement>::const_iterator> From(std::initializer_list<TElement> &&list)
    {
        return Queriable<typename std::initializer_list<TElement>::const_iterator>(list.begin(), list.end());
    }

    template <typename TIterator>
    static Queriable<TIterator> From(TIterator begin, TIterator end)
    {
        return Queriable<TIterator>(begin, end);
    }
} // namespace Lincpp

// namespace Lincpp
// {
//     template <typename Derived>
//     struct Queriable
//     {
//     private:
//         typedef typename internal::traits<Derived>::Element TElement;
//         typedef typename internal::traits<Derived>::Size TSize;

//     protected:
//         inline Derived &derived() { return *static_cast<Derived *>(this); }
//         inline const Derived &derived() const { return *static_cast<const Derived *>(this); }

//     public:
//         // TODO: make this a clause
//         // Enumerable<TElement> Append(const TElement &element) const
//         // {
//         //     std::list<TElement> tmp = this->ToList();
//         //     tmp.push_back(element);
//         //     return Enumerable<TElement>(tmp);
//         // }
//         // TODO: Cast
//
//         // TODO: make this a clause
//         // Enumerable<TElement> Concat(const Enumerable<TElement> &other) const
//         // {
//         //     TSize L1 = this->Size();
//         //     TSize L2 = other.Size();
//         //     Enumerable<TElement> res;
//         //     res.data.reserve(L1 + L2);
//         //     for (TSize i = 0; i < L1; ++i)
//         //         res.data.push_back(this->ElementAt(i));
//         //     for (TSize i = 0; i < L2; ++i)
//         //         res.data.push_back(other.ElementAt(i));
//         //     return res;
//         // }

//         // TODO: make this a clause
//         // Enumerable<TElement> DefaultIfEmpty(TElement defaultValue) const
//         // {
//         //     Enumerable<TElement> res;
//         //     TSize L = this->Count();
//         //     if (L != 0)
//         //     {
//         //         res.data.reserve(L);
//         //         for (TSize i = 0; i < L; ++i)
//         //             res.data.push_back(this->ElementAt(i));
//         //     }
//         //     else
//         //         res.data.push_back(defaultValue);

//         //     return res;
//         // }

//         template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(const TElement &)>>
//         SelectClause<TElement, Derived, TFunc, TReturn> Select(TFunc selector)
//         {
//             return SelectClause<TElement, Derived, TFunc, TReturn>(this->derived(), selector);
//         }

//         std::unique_ptr<TElement[]> ToArray() const
//         {
//             this->RequestCopyOriginalData();
//             TSize L = this->Size();
//             auto p = std::make_unique<TElement[]>(L);
//             for (TSize i = 0; i < L; ++i)
//                 p[i] = this->ElementAt(i);
//             return p;
//         }

//         std::list<TElement> ToList() const
//         {
//             this->RequestCopyOriginalData();
//             std::list<TElement> l;
//             TSize L = this->Size();
//             for (TSize i = 0; i < L; ++i)
//                 l.push_back(this->ElementAt(i));
//             return l;
//         }

//         std::vector<TElement> ToVector() const
//         {
//             this->RequestCopyOriginalData();
//             TSize L = this->Size();
//             std::vector<TElement> v(L);
//             for (TSize i = 0; i < L; ++i)
//                 v[i] = this->ElementAt(i);
//             return v;
//         }

//     public:
//         // methods that all derived structs must implement
//         inline TSize Size() const { return this->derived().Size(); }
//         inline TElement ElementAt(TSize i) const { return this->derived().ElementAt(i); }

//         inline void RequestCopyOriginalData() const { return this->derived().RequestCopyOriginalData(); }
//     };
// } // namespace Lincpp
