#include <iostream>

template <int N, int D> struct Frak {
	enum {
		Num = N,
		Den = D
	};
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
	static const long mcd = MCD<F::Num, F::Den>::result;
	typedef Frak< F::Num / mcd, F::Den / mcd > result;
};

/*
int main() {
	using Two_Fourths = Frak< 2, 4 >;
	using own_twos = Simpl<Two_Fourths>::result;
	std::cout << own_twos::Num << "/" << own_twos::Den << "\n";
}
*/