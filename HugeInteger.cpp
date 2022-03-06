#include "HugeInteger.h"

/**
 * @brief Construct a new HugeInteger given the string representaiton of the number.
 * A negative sign before the number indicates a negative value.
 * 
 * @param val String representation of the number.
 */
HugeInteger::HugeInteger(const std::string& val) {
	if (!val.size()) throw std::invalid_argument("invalid value");
	isNegative = (val[0] == '-');

	// Reserve space for the number in the memory
	value.reserve(val.size() + 1);

	// Depending on whether the number is negative, start from 0 or 1
	for (int i = isNegative ? 1 : 0; i < val.size(); i++) {
		if (!val.length() || !std::isdigit(val[i])) {
			throw std::invalid_argument("invalid value");
		}

		// Substract ASCII 0 (48) to get the integer value, then push it to the vector
		value.push_back(val[i] - '0');
	}
}

/**
 * @brief Construct a new random HugeInteger given the size of the number.
 * 
 * @param n Number of digits.
 */
HugeInteger::HugeInteger(int n) {
	if (n < 1) throw std::invalid_argument("invalid value");
	isNegative = false;

	// Reserve space in the memory for the number
	value.reserve(n + 1);

	std::srand(std::time(nullptr));

	int digit;

	// The first digit cannot be 0
	do {
		digit = std::rand() % 10;
	} while (digit == 0);
	value.push_back(digit);

	for (int i = 0; i < n - 1; i++) value.push_back(std::rand() % 10);
}

/**
 * @brief Returns a new HugeInteger representing the sum of this HugeInteger and h.
 * 
 * @param h HugeInteger to be added.
 * @param ignoreSign Only used by other methods. Ignores the sign of the numbers.
 * @return HugeInteger The sum of this HugeInteger and h.
 */
HugeInteger HugeInteger::add(const HugeInteger& h, bool ignoreSign) const {
	if (!ignoreSign) {
		// If this number is positive and h is negative subtract instead.
		if (!isNegative && h.isNegative) return subtract(h, true);
		// If this number is negative and h is positive, subtract from h instead.
		if (isNegative && !h.isNegative) return h.subtract(*this, true);
	}

	// Find the size of the longer number.
	int size = (h.value.size() >= value.size()) ? h.value.size() : value.size();
	int carry = 0, offset, index;

	// Create a new HugeInteger to store the result. Reserve space for size + 1 digits.
	HugeInteger sum = HugeInteger("0");
	sum.value.reserve(size + 1);
	for (int i = 0; i < size - 1; i++) sum.value.push_back(0);

	// If both numbers are negative, the result will also be negative.
	if (isNegative && h.isNegative) sum.isNegative = true;

	/**
	 * Starting from the least significant digit, add digits of both numbers.
	 * Add the carry from the last addition (if any).
	 * Store the carry for the next digit (if any).
	 */
	for (offset = 1; offset <= size; offset++) {
		index = size - offset;

		if (value.size() >= offset) sum.value[index] += value[value.size() - offset];
		if (h.value.size() >= offset) sum.value[index] += h.value[h.value.size() - offset];
		if (carry) sum.value[index] += carry--;

		if (sum.value[index] > 9) {
			sum.value[index] %= 10;
			carry++;
		}
	}

	// If there is a carry, add it to the beginning of the number.
	if (carry) sum.value.insert(sum.value.begin(), carry--);

	return sum;
}

/**
 * @brief Returns a new HugeInteger representing the difference of this HugeInteger and h.
 * 
 * @param h HugeInteger to be subtracted.
 * @param ignoreSign Only used by other methods. Ignores the sign of the numbers.
 * @return HugeInteger The difference of this HugeInteger and h.
 */
HugeInteger HugeInteger::subtract(const HugeInteger& h, bool ignoreSign) const {
	if (!ignoreSign) {
		// If this number is positive and h is negative, add instead.
		if (!isNegative && h.isNegative) return add(h, true);
		// If this number is negative and h is positive, add and negate instead.
		if (isNegative && !h.isNegative) return add(h, true).negate();
		// If this number is negative and h is negative, subtract frorm h instead.
		if (isNegative && h.isNegative) {
			HugeInteger diff = h.subtract(*this, true);
			// If h is absolutely bigger than this, negate the result.
			if (h.compareToUnsigned(*this) == 1) diff.negate();
			return diff;
		}
	}

	// Create references to the bigger and the smaller numbers.
	const HugeInteger& bigger = compareToUnsigned(h) == -1 ? h : *this;
	const HugeInteger& smaller = compareToUnsigned(h) == -1 ? *this : h;

	int size = bigger.value.size();

	int borrow = 0, offset, index, smallIndex;
	
	// Create a new HugeInteger to store the result. Reserve space for size digits.
	HugeInteger diff = HugeInteger("0");
	diff.value.reserve(size);
	for (int i = 0; i < size - 1; i++) diff.value.push_back(0);

	// If bigger number is negative or h is bigger than this, the result will be negative.
	if (bigger.isNegative) diff.isNegative = true;
	if (compareTo(h) == -1) diff.isNegative = true;

	/**
	 * Starting from the least significant digit, subtract smaller from bigger.
	 * Subtract the borrow from the last subtraction (if any).
	 * Store the borrow for the next digit (if any).
	 */
	for (offset = 1; offset <= size; offset++) {
		index = size - offset;
		smallIndex = smaller.value.size() - offset;

		if (smallIndex >= 0) {
			if (bigger.value[index] >= smaller.value[smallIndex] + borrow) {
				diff.value[index] = bigger.value[index] - smaller.value[smallIndex] - borrow;
				borrow = 0;
			} else {
				diff.value[index] = bigger.value[index] + 10 - smaller.value[smallIndex] - borrow;
				borrow = 1;
			}
		} else {
			if (bigger.value[index] >= borrow) {
				diff.value[index] = bigger.value[index] - borrow;
				borrow = 0;
			} else {
				diff.value[index] = bigger.value[index] + 10 - borrow;
				borrow = 1;
			}
		}
	}

	// Make sure there are no leading zeros.
	while (diff.value.size() > 1 && diff.value[0] == 0) {
		diff.value.erase(diff.value.begin());
	}

	// If the result is 0, make sure it is positive.
	if (diff.value[0] == 0) diff.isNegative = false;

	return diff;
}

/**
 * @brief Returns a new HugeInteger representing the product of this HugeInteger and h.
 * 
 * @param h HugeInteger to be multiplied.
 * @return HugeInteger The product of this HugeInteger and h.
 */
HugeInteger HugeInteger::multiply(const HugeInteger& h) const {
	// Create references to the bigger and the smaller numbers.
	const HugeInteger& bigger = compareToUnsigned(h) == -1 ? h : *this;
	const HugeInteger& smaller = compareToUnsigned(h) == -1 ? *this : h;

	int carry = 0, shift, offset, bigIndex, smallIndex;

	// Create a new HugeInteger to store the final result. Reserve space for size + 1 digits.
	HugeInteger product = HugeInteger("0");
	product.value.reserve(bigger.value.size() + 1);
	for (int i = 0; i < bigger.value.size() - 1; i++) product.value.push_back(0);

	/**
	 * For each digit of the smaller number, multiply it with the bigger number.
	 * Add the carry from the last addition (if any).
	 * Store the carry for the next digit (if any).
	 * Add the intermediate result to the final result by left shifting it on each iteration.
	 */
	for (shift = 1; shift <= smaller.value.size(); shift++) {
		smallIndex = smaller.value.size() - shift;

		// Create a new HugeInteger to store the intermediate result. Reserve space for size + 1 digits.
		HugeInteger interm = HugeInteger("0");
		interm.value.reserve(bigger.value.size() + 1);
		for (int i = 0; i < bigger.value.size() - 1; i++) interm.value.push_back(0);

		for (offset = 1; offset <= bigger.value.size(); offset++) {
			bigIndex = bigger.value.size() - offset;

			interm.value[bigIndex] = smaller.value[smallIndex] * bigger.value[bigIndex] + carry;

			// If the result is bigger than 9, store the carry. Else, clear it.
			if (interm.value[bigIndex] > 9) {
				carry = interm.value[bigIndex] / 10;
				interm.value[bigIndex] %= 10;
			} else {
				carry = 0;
			}
		}

		// If there is a leading carry from the last multiplication, add it to the beginning of the number.
		if (carry) {
			interm.value.insert(interm.value.begin(), carry);
			carry = 0;
		}

		// Left shift the intermediate result and add it to the final result.
		for (int i = 0; i < shift - 1; i++) interm.value.push_back(0);
		product = product.add(interm);
	}

	// Make sure there are no leading zeros.
	while (product.value.size() > 1 && product.value[0] == 0) {
		product.value.erase(product.value.begin());
	}

	// Set the sign of the result.
	if (isNegative && !h.isNegative) product.isNegative = true;
	if (!isNegative && h.isNegative) product.isNegative = true;

	// If the result is 0, make sure it is positive.
	if (product.value[0] == 0) product.isNegative = false;

	return product;
}

/**
 * @brief Compares two HugeIntegers and returns -1 if this HugeInteger is smaller, 0 if they are equal, and
 * 1 if this HugeInteger is bigger.
 * 
 * @param h HugeInteger to be compared.
 * @return int The result of the comparison.
 */
int HugeInteger::compareTo(const HugeInteger& h) const {
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

/**
 * @brief Compares the absolute values of two HugeIntegers and returns -1 if this HugeInteger is smaller,
 * 0 if they are equal, and 1 if this HugeInteger is bigger.
 * 
 * @param h HugeInteger to be compared.
 * @return int The result of the comparison.
 */
int HugeInteger::compareToUnsigned(const HugeInteger& h) const {
	// Check for size
	if (value.size() > h.value.size()) return 1;
	if (value.size() < h.value.size()) return -1;

	// Check for each digit
	for (int i = 0; i < value.size(); i++) {
		if (value[i] > h.value[i]) return 1;
		if (value[i] < h.value[i]) return -1;
	}

	return 0;
}

/**
 * @brief Returns the string representation of the HugeInteger.
 * If the number is negative, the string will start with a minus sign.
 * 
 * @return std::string The string representation of the HugeInteger.
 */
std::string HugeInteger::toString() const {
	std::string str = isNegative ? "-" : "";
	// Add ASCII 0 (48) to each digit to convert them to ASCII characters
	for (int i = 0; i < value.size(); i++) str += value[i] + '0';
	return str;
}

/**
 * @brief Negates the sign of the digit.
 * 
 * @return HugeInteger with a negated sign.
 */
HugeInteger HugeInteger::negate() {
	isNegative = !isNegative;
	return *this;
}
