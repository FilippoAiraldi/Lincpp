#pragma once

namespace Lincpp
{
    namespace internal
    {
        // specialization used by base Iterator struct to get traits of derived
        template <typename It, typename TFunc, typename TReturn>
        struct traits<SelectIterator<It, TFunc, TReturn>>
        {
            typedef It iterator_type;
            typedef typename std::iterator_traits<It>::iterator_category iterator_category;
            typedef typename std::iterator_traits<It>::difference_type difference_type;
            typedef TReturn value_type;
            typedef TReturn &reference;
            typedef TReturn *pointer;
        };
    } // namespace internal

    template <typename It, typename TFunc, typename TReturn>
    struct SelectIterator : public Iterator<SelectIterator<It, TFunc, TReturn>>
    {
    public:
        typedef typename std::iterator_traits<It>::iterator_category iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef TReturn value_type;
        typedef TReturn &reference;
        typedef TReturn *pointer;

        explicit SelectIterator(It iterator, TFunc selector) noexcept : Iterator<SelectIterator<It, TFunc, TReturn>>(iterator), _func(selector)
        {
            typedef typename std::iterator_traits<It>::value_type TInput;
            CHECK_FUNC_WITH_ALLOWED_CONVERSION(TFunc, TInput, TReturn);
        }

        // necessary to provide this method for base Iterator struct
        SelectIterator<It, TFunc, TReturn> Clone() const { return SelectIterator<It, TFunc, TReturn>(this->_current, this->_func); }

        // necessary to provide this operator for base Iterator struct
        SelectIterator<It, TFunc, TReturn> &operator=(const SelectIterator<It, TFunc, TReturn> &other)
        {
            this->_current = other._current;
            // this->_func = other._func; // cannot copy lambda, but should be equal anyway
            return *this;
        };

        // Forward iterator requirements
        value_type operator*() { return this->_func(*(this->_current)); }

        // Bidirectional iterator requirements
        // Random access iterator requirements

    private:
        const TFunc _func;
    };
} // namespace Lincpp
