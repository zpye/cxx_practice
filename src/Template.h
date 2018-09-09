#ifndef CXX_PRACTICE_TEMPLATE_H
#define CXX_PRACTICE_TEMPLATE_H

#include <iostream>

template< typename T >
void TempFunc()
{
    static T value = static_cast< T >(70.5);
    std::cout << "TempFunc() static value: " << value << std::endl;
    value += static_cast< T >(1);
}

template< typename T1, typename T2 >
class TempClass
{
public:
    TempClass()
    {
        cnt = count++;
        std::cout << "TempClass() < T1, T2 > " << cnt << std::endl;
    }

    ~TempClass()
    {
        std::cout << "~TempClass() < T1, T2 > " << cnt << std::endl;
    }

private:
    static size_t count;
    size_t cnt;
};

template< typename T1, typename T2 >
size_t TempClass< T1, T2 >::count = 0;

template< typename T1 >
class TempClass< T1, int >
{
public:
    TempClass()
    {
        cnt = count++;
        std::cout << "TempClass() < T1, int > " << cnt << std::endl;
    }

    ~TempClass()
    {
        std::cout << "~TempClass() < T1, int > " << cnt << std::endl;
    }

private:
    static size_t count;
    size_t cnt;
};

template< typename T1 >
size_t TempClass< T1, int >::count = 0;

template<>
class TempClass< float, int >
{
public:
    TempClass()
    {
        cnt = count++;
        std::cout << "TempClass() < float, int > " << cnt << std::endl;
    }

    ~TempClass()
    {
        std::cout << "~TempClass() < T1, int > " << cnt << std::endl;
    }

private:
    static size_t count;
    size_t cnt;
};

size_t TempClass< float, int >::count = 0;

template< typename T = int, T N = 0, typename std::enable_if< (N >= 5) >::type* = nullptr >
void TempFunc2()
{
    std::cout << "N " << N << std::endl;
}

template< typename T = int, T N = 0, typename std::enable_if< (N < 5) >::type* = nullptr >
void TempFunc2()
{
    std::cout << "N " << N << std::endl;
    TempFunc2< T, N + 1 >();
}

template< unsigned int N = 1, typename = void >
struct TempStruct {};

template< unsigned int N >
struct TempStruct< N, typename std::enable_if< (N < 6) >::type > {
    static const unsigned int value = TempStruct< N + 1 >::value;
};

template< unsigned int N >
struct TempStruct< N, typename std::enable_if< (N >= 6) >::type > {
    static const unsigned int value = N;
};

#endif // CXX_PRACTICE_TEMPLATE_H