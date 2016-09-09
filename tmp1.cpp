#include <iostream>

template <int N> struct Factorial {
	enum { result = N * Factorial<N - 1>::result };
};

template <> struct Factorial<0> {
	enum { result = 1 };
};

/*
int main() {
	std::cout << Factorial<5>::result << "\n";
	return 0;
}

*/