#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>

class HugeInteger
{
	private:
		std::vector<int> value;
		bool isNegative;

	public:
		HugeInteger(const std::string& val);
		HugeInteger(int n);
		HugeInteger add(const HugeInteger& h, bool ignoreSign = false) const;
		HugeInteger subtract(const HugeInteger& h, bool ignoreSign = false) const;
		HugeInteger multiply(const HugeInteger& h) const;
		int compareTo(const HugeInteger& h) const;
		int compareToUnsigned(const HugeInteger& h) const;
		std::string toString() const;
		HugeInteger negate();
};

#endif /* HUGEINTEGER_H_ */
