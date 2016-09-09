#include <iostream>

template <int N, int D> struct Frak {
	enum {
		Num = N,
		Den = D
	};
};

template <int N, class F> struct ScalarMultiplication {
	using result = Frak<N*F::Num, F::Den>;
};

/*
int main() {
	using Two_Thirds = Frak< 2, 3 >;
	using Four_Thirds = ScalarMultiplication< 2, Two_Thirds >::result;
	std::cout << Four_Thirds::Num << "/" << Four_Thirds::Den << "\n";
}

*/
