#pragma once

template<typename Func>
struct FuncArgTraitsHelper;

template <typename R, typename T1, typename ... OtherArgs>
struct FuncArgTraitsHelper<R (*) (T1, OtherArgs ... )>
{
    typedef T1 arg1;
};

template <typename Func>
struct FuncArgTraits : public FuncArgTraitsHelper<Func> 
{};