#include <iostream>

template <int N> struct Factorial {
	enum { result = N * Factorial<N - 1>::result };
};

template <> struct Factorial<0> {
	enum { result = 1 };
};

template <int N, int D> struct Frak {
	enum {
		Num = N,
		Den = D
	};
};

template <int N, class F> struct ScalarMultiplication {
	using result = typename Frak<N*F::Num, N*F::Den> ;
};

template <int X, int Y>   struct MCD {
	enum {
		result = MCD<Y, X % Y>::result
	};
};

template <int X> struct MCD<X, 0> {
	enum {
		result = X
	};
};

template <class F> struct Simpl {
	enum { mcd = MCD<F::Num, F::Den>::result };
	using result = typename Frak< F::Num / mcd, F::Den / mcd >;
};

template <class X1, class X2> struct SameBase{
	using X = typename ScalarMultiplication<X2::Den , X1>::result;
	using Y = typename ScalarMultiplication<X1::Den , X2>::result;
};

template <class X1, class X2> struct Sum{
	using temp = SameBase<X1 , X2>;
	using result = typename Simpl< Frak< temp::X::Num + temp::Y::Num, temp::X::Den> >::result;
};

// e = S(1/n!) = 1/0! + 1/1! + 1/2! + ...

template <int N> struct E{
	using tmp = Frak< 1, Factorial<N>::result >;
	using next_temp = typename E<N-1>::result;
	using result = typename Sum< tmp , next_temp >::result;
};

template <> struct E<0> {
	using result = typename Frak<1, 1>; 
};

/*
int main() {
	using e8 = E<8>::result;
	std::cout << e8::Num << "/" << e8::Den << "\n";
}

*/
