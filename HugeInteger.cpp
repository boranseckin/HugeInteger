#include "HugeInteger.h"

HugeInteger::HugeInteger(const std::string& val) {
	if (!val.size()) throw std::invalid_argument("invalid value");
	isNegative = (val[0] == '-');

	for (int i = isNegative ? 1 : 0; i < val.size(); i++) {
		if (!val.length() || !std::isdigit(val[i])) {
			// std::cout << val[i] << std::endl;
			throw std::invalid_argument("invalid value");
		}
		value.push_back(val[i] - '0');
	}
}

HugeInteger::HugeInteger(int n) {
	if (n < 1) throw std::invalid_argument("invalid value");
	isNegative = false;

	value.push_back(1);
	for (int i = 0; i < n - 1; i++) value.push_back(0);
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	int size = (h.value.size() >= value.size()) ? h.value.size() : value.size();
	int carry = 0, offset, index;

	HugeInteger sum = HugeInteger(size);
	sum.value[0] = 0;

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
	// TODO
	return HugeInteger("");
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	return 0;
}

std::string HugeInteger::toString() {
	std::string str = isNegative ? "-" : "";
	for (int i = 0; i < value.size(); i++) str += value[i] + '0';

	return str;
}

// int main() {
// 	HugeInteger integer = HugeInteger("11111");
// 	HugeInteger integer2 = HugeInteger("89111");
// 	std::cout << integer.toString() << std::endl;
// 	std::cout << integer2.toString() << std::endl;
// 	std::cout << integer.add(integer2).toString() << std::endl;
// 	return 1;
// }
