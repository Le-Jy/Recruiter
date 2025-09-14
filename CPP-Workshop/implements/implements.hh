#pragma once

template <typename T, typename T2 = T>
concept impl_basic_op = requires(T& a, T2& b)
{
    +a;
    -a;
    +b;
    -b;
    a + b;
    a - b;
    a* b;
    a / b;
    b + a;
    b - a;
    b* a;
    b / a;
};

template <typename T, typename T2 = T>
concept impl_modulo = requires(T& a, T2& b)
{
    a % b;
    b % a;
};

template <typename T, typename T2 = T>
concept impl_bitwise_op = requires(T& a, T2& b)
{
    ~a;
    ~b;
    a& b;
    a | b;
    a ^ b;
    a << b;
    a >> b;
    b& a;
    b | a;
    b ^ a;
    b << a;
    b >> a;
};

template <typename T, typename T2 = T>
concept impl_arith_op =
    impl_basic_op<T, T2> && impl_modulo<T, T2> && impl_bitwise_op<T, T2>;
