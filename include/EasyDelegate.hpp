#pragma once
#include "custom-types/shared/delegate.hpp"

namespace EasyDelegate{
    /**
     * @param F the lambda callback to be used with the delegate.
     * @return delegate of type T
     */
    template <typename T, class F>
    T MakeDelegate(F f){ 
        return custom_types::MakeDelegate<T>(std::function(f));
    }

    template<typename TRet, typename ...TArgs>
    using func_ptr = TRet(*)(TArgs...);

    template <typename T, typename ReturnType, typename... Args>
    T MakeDelegate(func_ptr<ReturnType, Args...> func){
        return custom_types::MakeDelegate<T>(static_cast<std::function<ReturnType(Args...)>>(func));
    }

    template<typename T, typename TRet, typename... TArgs>
    using mem_func_ptr = TRet(T::*)(TArgs...);

    template <typename T, typename TRet, typename TName, typename... TArgs, typename... Args>
    T MakeDelegate(std::__ndk1::__bind<mem_func_ptr<TName, TRet, TArgs...>, Args...> b){
        return custom_types::MakeDelegate<T>(std::function<TRet(TArgs...)>(b));
    }

    template <typename... T, std::size_t... I>
    auto subtuple(const std::tuple<T...>& t, std::index_sequence<I...>) {
        return std::make_tuple(std::get<I>(t)...);
    }

    template <typename TRet, typename TName, typename... TArgs, typename TObj>
    const auto bind(mem_func_ptr<TName, TRet, TArgs...> fp, TObj obj){
        using namespace std::placeholders;
        auto placeholders = std::make_tuple(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);
        constexpr int argc = sizeof...(TArgs);
        if constexpr (argc == 0) return std::bind(fp, obj);
        auto paramPack = std::tuple_cat(std::make_tuple(fp, obj), subtuple(placeholders, std::make_index_sequence<argc>()));
        return std::apply([](auto &&... args) { return std::bind(args...); }, paramPack);
    }

    template <typename T, typename TRet, typename TName, typename... TArgs, typename TObj>
    T MakeDelegate(mem_func_ptr<TName, TRet, TArgs...> fp, TObj obj){
        return custom_types::MakeDelegate<T>(std::function<TRet(TArgs...)>(bind(fp, obj)));
    }

    template <typename T, typename TRet, typename... TArgs, typename... TObj>
    T MakeDelegate(func_ptr<TRet, TArgs...> fp, TObj... obj){
        return custom_types::MakeDelegate<T>(std::function<TRet()>(std::bind(fp, obj...)));
    }
}