// enum class CastType : unsigned char
// {
//     Explicit,
//     Implicit,
//     Static,
//     Dynamic,
//     Reinterpreted
// };

// namespace internal
// {
//     template <typename From, typename To, CastType Type>
//     struct caster;

//     template <typename From, typename To>
//     struct caster<From, To, CastType::Implicit>
//     {
//         inline To operator()(From p) { return p; }
//     };

//     template <typename From, typename To>
//     struct caster<From, To, CastType::Explicit>
//     {
//         inline To operator()(From p) { return To(p); }
//     };

//     template <typename From, typename To>
//     struct caster<From, To, CastType::Static>
//     {
//         inline To operator()(From p) { return static_cast<To>(p); }
//     };

//     template <typename From, typename To>
//     struct caster<From, To, CastType::Dynamic>
//     {
//         inline To operator()(From p) { return dynamic_cast<To>(p); }
//     };

//     template <typename From, typename To>
//     struct caster<From, To, CastType::Reinterpreted>
//     {
//         inline To operator()(From p) { return reinterpret_cast<To>(p); }
//     };
// } // namespace internal

// template <typename TOtherElement, CastType Type = CastType::Explicit>
// Enumerable<TOtherElement> Cast()
// {
//     std::list<TElement> source = this->ToList();
//     std::list<TOtherElement> dst;
//     std::transform(source.cbegin(), source.cend(), )

//     // Enumerable<TOtherElement> res;
//     // TSize L = this->Count();
//     // res.data.reserve(L);

//     // for (TSize i = 0; i < L; ++i)
//     //     res.data.push_back(internal::caster<TElement, TOtherElement, Type>::perform(this->ElementAt(i)));
//     // return res;
// }
