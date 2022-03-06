#include "HugeInteger.h"

#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std::chrono;
using namespace boost::multiprecision;

double ComparisonTiming(int n) {
	std::cout << "Timing comparison of " << n << " digit numbers..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		HugeInteger huge1(numInts);
		HugeInteger huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 30000; numRun++) {
			int result = huge1.compareTo(huge2);
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 30000;
		std::cout << durationMs / (double) 30000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double AdditionTiming(int n) {
	std::cout << "Timing addition of " << n << " digit numbers..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		HugeInteger huge1(numInts);
		HugeInteger huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 30000; numRun++) {
			HugeInteger huge3 = huge1.add(huge2);
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 30000;
		std::cout << durationMs / (double) 30000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double SubtractionTiming(int n) {
	std::cout << "Timing subtraction of " << n << " digit numbers..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		HugeInteger huge1(numInts);
		HugeInteger huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 10000; numRun++) {
			HugeInteger huge3 = huge1.subtract(huge2);
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 10000;
		std::cout << durationMs / (double) 10000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double MultiplicationTiming(int n) {
	std::cout << "Timing multiplication of " << n << " digit numbers..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		HugeInteger huge1(numInts);
		HugeInteger huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 500; numRun++) {
			HugeInteger huge3 = huge1.multiply(huge2);
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 500;
		std::cout << numInts << " - " << durationMs / (double) 500 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double BoostComparisonTiming(int n) {
	std::cout << "Timing comparison of " << n << " digit numbers using Boost..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		cpp_int huge1(numInts);
		cpp_int huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 30000; numRun++) {
			bool result = huge1 > huge2;
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 30000;
		std::cout << durationMs / (double) 30000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double BoostAdditionTiming(int n) {
	std::cout << "Timing addition of " << n << " digit numbers using Boost..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		cpp_int huge1(numInts);
		cpp_int huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 30000; numRun++) {
			cpp_int huge3 = huge1 + huge2;
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 30000;
		std::cout << durationMs / (double) 30000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double BoostSubtractionTiming(int n) {
	std::cout << "Timing subtraction of " << n << " digit numbers using Boost..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 1; numInts < n; numInts++) {
		cpp_int huge1(numInts);
		cpp_int huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 0; numRun < 10000; numRun++) {
			cpp_int huge3 = huge1 - huge2;
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 10000;
		std::cout << durationMs / (double) 10000 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

double BoostMultiplicationTiming(int n) {
	std::cout << "Timing multiplication of " << n << " digit numbers using Boost..." << std::endl;
	system_clock::time_point startTime, endTime;

	double runTime = 0.0;
	double durationMs = 0.0;

	for (int numInts = 0; numInts < n; numInts++) {
		cpp_int huge1(numInts);
		cpp_int huge2(numInts);
		startTime = system_clock::now();

		for (int numRun = 1; numRun < 500; numRun++) {
			cpp_int huge3 = huge1 * huge2;
		}

		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		runTime += durationMs / (double) 500;
		std::cout << durationMs / (double) 500 << std::endl;
	}

	runTime = runTime / (double) n;
	return runTime;
}

int main() {
	std::cout << "Timing arithmetic operations..." << std::endl;

	double time1 = ComparisonTiming(500);
	double time2 = BoostComparisonTiming(500);

	double time3 = AdditionTiming(500);
	double time4 = BoostAdditionTiming(500);

	double time5 = SubtractionTiming(500);
	double time6 = BoostSubtractionTiming(500);

	double time7 = MultiplicationTiming(500);
	double time8 = BoostMultiplicationTiming(500);

	std::cout << std::endl;

	std::cout << "Average time for comparison:" << std::endl;
	std::cout << "\t HugeInteger: " << time1 << std::endl;
	std::cout << "\t Boost: " << time2 << std::endl;

	std::cout << "Average time for addition:" << std::endl;
	std::cout << "\t HugeInteger: " << time3 << std::endl;
	std::cout << "\t Boost: " << time4 << std::endl;

	std::cout << "Average time for subtraction:" << std::endl;
	std::cout << "\t HugeInteger: " << time5 << std::endl;
	std::cout << "\t Boost: " << time6 << std::endl;

	std::cout << "Average time for multiplication:" << std::endl;
	std::cout << "\t HugeInteger: " << time7 << std::endl;
	std::cout << "\t Boost: " << time8 << std::endl;

	return 0;
}