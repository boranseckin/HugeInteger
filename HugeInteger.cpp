#include "HugeInteger.h"

#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std::chrono;

HugeInteger::HugeInteger(const std::string& val) {
	if (!val.size()) throw std::invalid_argument("invalid value");
	isNegative = (val[0] == '-');

	value.reserve(val.size() + 1);

	for (int i = isNegative ? 1 : 0; i < val.size(); i++) {
		if (!val.length() || !std::isdigit(val[i])) {
			throw std::invalid_argument("invalid value");
		}
		value.push_back(val[i] - '0');
	}
}

HugeInteger::HugeInteger(int n) {
	if (n < 1) throw std::invalid_argument("invalid value");
	isNegative = false;

	value.reserve(n + 1);

	std::srand(std::time(nullptr));

	int digit;

	do {
		digit = std::rand() % 10;
	} while (digit == 0);
	value.push_back(digit);

	for (int i = 0; i < n - 1; i++) value.push_back(std::rand() % 10);
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	// TODO: implement negative support

	int size = (h.value.size() >= value.size()) ? h.value.size() : value.size();
	int carry = 0, offset, index;

	HugeInteger sum = HugeInteger("0");
	sum.value.reserve(size + 1);
	for (int i = 0; i < size - 1; i++) sum.value.push_back(0);

	for (offset = 1; offset <= size; offset++) {
		// std::cout << sum.toString() << std::endl;

		index = size - offset;

		if (value.size() >= offset) sum.value[index] += value[value.size() - offset];
		if (h.value.size() >= offset) sum.value[index] += h.value[h.value.size() - offset];
		if (carry) sum.value[index] += carry--;

		if (sum.value[index] > 9) {
			// std::cout << "carry" << std::endl;
			sum.value[index] %= 10;
			carry++;
		}

		// std::cout <<
		// 	((value.size() >= offset) ? value[value.size() - offset] : 0)
		// << " + " <<
		// 	((h.value.size() >= offset) ? h.value[h.value.size() - offset] : 0)
		// << " = " <<
		// 	sum.value[index]
		// << std::endl;
	}

	if (carry) {
		// std::cout << "carry " << std::endl;
		sum.value.insert(sum.value.begin(), carry--);
	}

	return sum;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	const HugeInteger& bigger = compareTo(h) == -1 ? h : *this;
	const HugeInteger& smaller = compareTo(h) == -1 ? *this : h;

	int size = bigger.value.size();

	int borrow = 0, offset, index, smallIndex;
	
	HugeInteger diff = HugeInteger("0");
	diff.value.reserve(size);
	for (int i = 0; i < size - 1; i++) diff.value.push_back(0);

	for (offset = 1; offset <= size; offset++) {
		index = size - offset;
		smallIndex = smaller.value.size() - offset;

		// std::cout << diff.toString()
		// 	<< " - " <<
		// 	offset
		// 	<< " - " <<
		// 	index
		// 	<< " - " <<
		// 	smallIndex
		// << std::endl;

		if (smallIndex >= 0) {
			if (bigger.value[index] >= smaller.value[smallIndex] + borrow) {
				diff.value[index] = bigger.value[index] - smaller.value[smallIndex] - borrow;
				borrow = 0;
			} else {
				diff.value[index] = bigger.value[index] + 10 - smaller.value[smallIndex] - borrow;
				borrow = 1;
			}

			// std::cout <<
			// 	((value.size() >= offset) ? bigger.value[index] : 0)
			// << " - " <<
			// 	((h.value.size() >= offset) ? smaller.value[smallIndex] : 0)
			// << " = " <<
			// 	diff.value[index]
			// << std::endl;
		} else {
			diff.value[index] = bigger.value[index] - borrow;
			borrow = 0;
			// std::cout <<
			// 	bigger.value[index]
			// << " - 0 = " <<
			// 	diff.value[index]
			// << std::endl;
		}
	}

	return diff;
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// Check for sign
	if (!isNegative && h.isNegative) return 1;
	if (isNegative && !h.isNegative) return -1;

	// Check for size
	if (value.size() > h.value.size()) return (isNegative ? -1 : 1);
	if (value.size() < h.value.size()) return (isNegative ? 1 : -1);

	// Check for each digit
	for (int i = 0; i < value.size(); i++) {
		if (value[i] > h.value[i]) return (isNegative ? -1 : 1);
		if (value[i] < h.value[i]) return (isNegative ? 1 : -1);
	}

	return 0;
}

std::string HugeInteger::toString() {
	std::string str = isNegative ? "-" : "";
	for (int i = 0; i < value.size(); i++) str += value[i] + '0';
	return str;
}

int main() {
	HugeInteger a = HugeInteger("123");
	HugeInteger b = HugeInteger("2");
	std::cout << a.subtract(b).toString() << std::endl;
}

#define MAXNUMINTS 100
#define MAXRUN 30000

double HugeIntTiming(int n) {
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
		HugeInteger huge1(n); //creates a random integer of n digits
		HugeInteger huge2(n); //creates a random integer of n digits
		startTime = system_clock::now();

		for (int numRun = 0; numRun < MAXRUN; numRun++) {
			HugeInteger huge3 = huge1.add(huge2);
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / ((double) MAXRUN);
		std::cout << durationMs << std::endl;
	}

	runTime = runTime/((double) MAXNUMINTS);
	return runTime;
}

double BoostHugeIntTiming(int n) {
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
		cpp_int huge1(n); //creates a random integer of n digits
		cpp_int huge2(n); //creates a random integer of n digits
		startTime = system_clock::now();

		for (int numRun = 0; numRun < MAXRUN; numRun++) {
			cpp_int huge3 = huge1 + huge2;
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / ((double) MAXRUN);
		std::cout << durationMs << std::endl;
	}

	runTime = runTime/((double) MAXNUMINTS);
	return runTime;
}

// int main() {
// 	double time1 = HugeIntTiming(500);
// 	double time2 = BoostHugeIntTiming(500);
// 	std::cout << "Average time for " << MAXRUN << " runs of add() on " << MAXNUMINTS << " integers of size 500 with custom class: " << time1 << " ms" << std::endl;
// 	std::cout << "Average time for " << MAXRUN << " runs of add() on " << MAXNUMINTS << " integers of size 500 with Boost class: " << time2 << " ms" << std::endl;
// 	return 0;
// }
