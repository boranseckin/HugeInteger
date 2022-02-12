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
		// Required methods
		HugeInteger(const std::string& val);
		HugeInteger(int n);
		HugeInteger add(const HugeInteger& h);
		HugeInteger subtract(const HugeInteger& h) const;
		HugeInteger multiply(const HugeInteger& h);
		int compareTo(const HugeInteger& h) const;
		int compareToUnsigned(const HugeInteger& h) const;
		std::string toString();
};

#endif /* HUGEINTEGER_H_ */
