#include <iostream>

struct NIL {
	using Head = typename NIL;
	using Tail = typename NIL;
};

template <class H, class T = NIL> struct Lst {
	using Head = typename H;
	using Tail = typename T;
};

template <int N> struct Int {
	enum {
		result = N
	};
};

template <class T> struct Length{
	enum {
		result = 1 + Length<T::Tail>::result
	};
};

template <> struct Length<NIL> {
	enum {
		result = 0
	};
};

template <class T , int N> struct Nth {
	using result = typename Nth<typename T::Tail, N - 1>::result;
};

template <class T> struct Nth<T , 0> {
	using result = typename T::Head;
};

template <class T, int N> struct Includes {
	enum {
		result = T::Head::result == N || Includes<T::Tail , N>::result
	};	
};

template <int N> struct Includes<NIL, N> {
	enum {
		result = 0
	};
};

template <class T, class N> struct Includes2 {
	enum {
		result = Eq<T::Head , N>::result || Includes2<T::Tail, N>::result
	};
};

template <class N> struct Includes2<NIL, N> {
	enum {
		result = 0
	};
};

template <class X, class Y> struct Eq {
	enum {
		result = 0
	};
};

template <class X> struct Eq<X, X> {
	enum {
		result = 1
	};
};

template <class T, class N> struct Prepend {	
	using result = typename Lst<N, T>;
};

template <class T, class N> struct Append {
	using result = typename Lst< typename T::Head , typename Append<typename T::Tail , N>::result >;
};

template <class N> struct Append<NIL , N> {
	using result = typename Lst<N>;
};

template <class T, class N> struct Position {
	enum {
		result = NEq<T::Head, N>::result ? (1 + Position<T::Tail, N>::result) : 0
	};
};

template <class N> struct Position<NIL, N> {
	enum {
		result = 0
	};
};

template <class X, class Y> struct NEq {
	enum {
		result = 1
	};
};

template <class X> struct NEq<X, X> {
	enum {
		result = 0
	};
};

int main()
{
	using OneTwoThree = Lst< Int<1>, Lst< Int<2>, Lst< Int<3> > > > ;
	std::cout<< " length is : " << Length<OneTwoThree>::result<<std::endl;
	std::cout << " 2nd Element  is : " << Nth<OneTwoThree , 1>::result::result << std::endl;
	std::cout << " element 2 exists : " << Includes<OneTwoThree, 2>::result << std::endl;
	std::cout << " element 5 exists : " << Includes<OneTwoThree, 5>::result << std::endl;

	std::cout << " element 2 exists : " << Includes2<OneTwoThree, Int<2> >::result << std::endl;
	std::cout << " element 5 exists : " << Includes2<OneTwoThree, Int<5> >::result << std::endl;

	using FourOneTwoThree = Prepend<OneTwoThree, Int<4> >::result;
	std::cout << " prepend 4 : " << Length<FourOneTwoThree>::result << std::endl;

	using OneTwoThreeFour = Append<OneTwoThree, Int<4> >::result;
	std::cout << " Append 4 : " << Length<OneTwoThreeFour>::result << std::endl;

	std::cout << " Position of 4 in OneTwoThree is : " << Position<OneTwoThree , Int<6> >::result << std::endl;
}

