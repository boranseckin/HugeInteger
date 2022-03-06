# HugeInteger
Library for making arithmetic operations with arbitrarily large integer numbers.

### Huge Integer
This implementation of HugeInteger uses a vector to store each digit of the number as an integer. Additionally, it stores a boolean value to determine the sign of the integer. The number of digits of the integer can be found using the `size()` method of the vector.

### Comparison
The comparison function is designed to short-circuit the evaluation as soon as possible. First the sign, then, the number of digits and finally, each digit (starting from the most significant) of each integer is compared.

### Addition
In order to add two Huge Integers, the integer with the most digits is found and a new Huge Integer is created with reserved space for that many digits (plus 1 for a possible carry at the end). By reserving the space at the beginning, a reallocation for the vector is not required when a new digit is added to the result.

The digits of each number are then added to the corresponding digit of the result (starting from the least significant). The addition takes place for every digit of the greater number.

If the intermediate sum exceeds 9 for any digit, the remainder of the result after dividing by 10 is used instead and a carry flag is set. During the following addition steps, the carry is also considered in the sum. If the carry flag is still set after the addition is complete for all digits, a 1 is added to the beginning of the result.

If only one of the operands is negative this method will instead return the result of the difference of the numbers. If both operands are negative, the resulting Huge Integer is set to be negative.

### Subtraction
In order to subtract two Huge Integers, the two numbers are assigned to two variables called `bigger` and `smaller` relative to their values. These variables are used to reference the numbers throughout the algorithm.

A new Huge Integer is created with reserved space for the number of digits of the bigger number. By reserving the space at the beginning, a reallocation for the vector is not required when a new digit is added to the result.

Starting from the least significant digit, each digit of smaller number is subtracted from the bigger number. If the smaller number runs out of digits, the digit of bigger number is directly copied.

If the intermediate subtraction result is less than 0, 10 is added to the result and a borrow flag is set. During the following subtraction steps, the borrow flag is also subtracted from the bigger number.

If the resulting number has leading zeros at the beginning, they are removed.

If only one of the operands is negative this method will instead return theh result of the sum of the numbers. If both operands are negative, the first number is subtracted from the second instead.

### Multiplication
In order to subtract two Huge Integers, the two numbers are assigned to two variables called `bigger` and `smaller` relative to their values. These variables are used to reference the numbers throughout the algorithm.

A new Huge Integer is created with reserved space for the number of digits of the bigger number. By reserving the space at the beginning, a reallocation for the vector is not required when a new digit is added to the result.

Starting from the least significant digit, each digit of both numbers is multiplied and the result is saved in an interim value which is also an Huge Integer. This value then shifted to the left by the corresponding number of digits and added to the result.

If the intermediate product results in a number bigger than 9, the remainder of the result after dividing by 10 is used instead and the overflow is saved as carry. During the following multiplication steps, the amount of borrow is added to the intermediate product.

The sign of the resulting Huge Integer is set to negative if only one of the operands is negative.

If the resulting number has leading zeros at the beginning, they are removed.
