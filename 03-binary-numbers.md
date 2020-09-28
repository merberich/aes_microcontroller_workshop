# Binary Number Theory

Up to this point, the theory and implementations have allowed us to create systems of simple logic circuits, but we need to be able to accomplish more complex tasks than logic alone can drive. First and foremost, we need a way to represent values that have meaning in engineering contexts: we need to represent numbers with logic systems.

First we must review how number systems work. In any number system, a value is represented by some sequence of "numeral" symbols in positions indexed as "digits". The "base" of a system is the count of different symbol corresponding to the first few natural numbers, including zero.

For example, in the decimal system (base 10), an integer \(a\) with three digits (denoted by subscript) holds value where:

\(a_2a_1a_0 = (a_2 * 10^2) + (a_1 * 10^1) + (a_0 * 10^0)\)

Generalizing, for any number system representing integer values, a number \(a\) with \(n\) digits in base \(b\) will have value such that:

\((a_na_{n-1}...a_1a_0)_b = \sum_{k=0}^{n} a_kb^k\)

where digit \(k\) holds value \(a_k * b^k\).

Naturally, this means there are other number systems we could use (base 8, base 16, etc), but more importantly, it implies that values are transferrable between different base systems. So, logic circuits, which are capable of representing only values true (1), or false (0), can represent a base 2 system: a binary number system. In binary, we consider digits as "bits". The "resolution" of a number can be described by the number of bits used to contain the value: the bit-width, or bit length.

The remainder of this section will describe how we represent increasingly complex kinds of numbers within a binary number system.

## Unsigned Integers

Unsigned integers are also know as the set of positive integers, including zero. They simply follow the case above, namely that unsigned integers expressed in binary have value:
\((a_na_{n-1}...a_1a_0)_2 = \sum_{k=0}^{n} a_k2^k\)

For a three-bit unsigned integers, counting upwards gives us:
| Binary | Decimal |
|-|-|
| 000 | 0 |
| 001 | 1 |
| 010 | 2 |
| 011 | 3 |
| 100 | 4 |
| 101 | 5 |
| 110 | 6 |
| 111 | 7 |

So, a \(n\)-bit unsigned integer can express \(2^n\) unique values with a minimum value of zero and a maximum value of \(2^n - 1\).

## Signed Integers

Signed integers can express a much more expansive set than unsigned integers, since they represent all integers (positive and negative).

To represent signed integers, we could use a system where we dedicate a bit to indicate sign, and the remaining bits hold the value (known as **sign-magnitude format**). In this format, the Most Significant Bit (MSb) holds the sign, and remaining bits hold the value with that sign. For instance, the four-bit signed integer 1001 in sign-magnitude format represents decimal value -1. In this system, the value zero has two distinct representations (signed zero is not meaningfully different). Where this system fails, however, is that we cannot do traditional arithmetic with the raw representation. For instance:
```
  0001 (decimal 1)
+ 1001 (decimal -1)
= 1010 (decimal -2) -> this is incorrect: should be decimal 0
```

To remedy this problem (incorrect resulting sign and incorrect carry), a system known as **Two's Complement** is used. In two's complement, to find the negative of a number in binary representation:
1) Take the complement of the unsigned representation of the number (flip all bits)
2) Add one

For instance (again for a four-bit signed integer):
```
  0001 (decimal 1)
  1110 (complement of decimal 1)
  1111 (two's complement representation of -1)
```

And we can check with a simple addition (assume 4 bits):
```
  0001 (decimal 1)
+ 1111 (decimal -1)
= 0000 (zero, carry 1, which is discarded) -> correct!
```

Then for a three-bit unsigned integer, counting downwards gives us:
| Binary | Decimal |
|-|-|
| 011 | 3 |
| 010 | 2 |
| 001 | 1 |
| 000 | 0 |
| 111 | -1 |
| 110 | -2 |
| 101 | -3 |
| 100 | -4 |

Notice that for two's complement, the inflection occurs between positive and negative numbers, counting zero as a positive number. Also note that there are no repeat values in this representation - zero has one representation only. Lastly, two's complement retains the ability to tell a number's sign using only the MSb. Using the two's complement system, signed integer numbers of bit-width \(n\) can also express \(2^n\) values, but the range now spans across zero from \(2^{n-1}-1\) to \(-2^{n-1}\).

## Floating Point Numbers

Floating point numbers are real numbers (positive or negative), which includes fractional numbers. Generally, floating point numbers have a format similar to:
\(\texttt{significand}*\texttt{base}^\texttt{exponent}\)
where the significand is the set of significant figures (digits) the number contains, and the base and exponent serve to move the radix - the point at which following digits represent fractional values. For instance, decimal value 1.2345 could have significand 12345, base 10, and exponent -4.

Then, the term "floating point" refers to the fact that the exponent is capable of "moving" the radix point to exist anywhere in the represented number (as opposed to "fixed point" representations, where the radix is in a fixed position). The tradeoff for floating point numbers - of having the radix move - is that the resolution of the number follows an uneven distribution depending on where along the number line the value is sampled (where fixed point representations do have an even distribution). Note that almost all representations of fractional values are estimates in practice - the trick is then determining the resolution requirements of the fractional values to be handled.

To ensure reasonable resolution at various points, the floating point standard [IEEE754](https://en.wikipedia.org/wiki/IEEE_754) was developed, which specifies a common binary representation for floating point numbers. It is the most common floating point standard in industry today (with widespread hardware and software support).

IEEE754 describes several precision levels. We'll discuss single precision numbers for brevity, which are colloquially known as "floats". Float format then follows in order as:
\(s\) - sign - one bit: zero for positive, one for negative
\(e\) - exponent - 8 bits: unsigned integer with built-in bias / offset
\(f\) - fraction - 23 bits: unsigned fractional value (MSb is \(2^{-1}\), etc...)

Note that IEEE754 floats are stored in sign-magnitude format, which again means we can't do direct arithmetic with them. IEEE754 floats carry value equal tot he following formula:
\(v = (1-2s)*(1+f)*2^{e-\texttt{bias}}\) (for decimal values \(s\), \(f\), and \(e\))
where "bias" = 127 for single precision floats.

IEEE754 floats do have some special cases:
- zero can be represented by an all-zero exponent with all-zero fraction (with both positive and negative sign equating to zero)
- positive or negative infinity can be represented by an all-ones exponent field with a zero fractional field
- "not a number" condition (catching non-real values like divide-by-zero or imaginary/complex numbers) can be represented by a zero sign bit, all-ones exponent, and nonzero fraction field

It is extremely uncommon to need to manually convert to and from floating point operation. That need may arise when dealing with arbitrary-precision applications, or resource-constrained applications requiring high speed, however.

## Bitwise Operations

Now that we have representations for the classes of numbers we will likely need to use in practice for most simple engineering problems, we can discuss operators for these representations.

We have already discussed adding binary numbers; all other arithmetic operators also apply to binary numbers. However, since the number representation is in a digital format, there are other operators we can also apply - namely, bitwise operations.

"Bitwise" describes the approach of manipulating individual bits within a binary number, treating it as a field (or sequence) of bits rather than a representation of numerical value. Typically, bitwise operations are done using unsigned integers only (on basis of semantics, to prevent confusion), though in theory any bit field can be manipulated in this manner.

In practice, the bitwise operators are identical to logical operators on a bit level, but when applied to bit fields, they perform the operation for all bits in both fields.

Examples of each bitwise operator:
```
NOT 0001
  = 1110

    0011
AND 0101
  = 0001

    1010
OR  1100
  = 1110

    1010
XOR 1100
  = 0110
```

There is one bitwise operator not accounted for by the logical operators (which arrives through the positional relationship of bits in a field): the "bit-shift", or "shift". A **Bit-Shift** is an operation which either adds or subtracts one to the positional index of all bits in a bit field. Shifts can therefore occur in a "leftward" direction, introducing a new bit as the LSb and discarding the MSb, or in a "rightward" direction, introducing a new bit as the MSb and discarding the LSb. An **Arithmetic Shift** is one which preserves the sign bit in rightward shifts (shifts in a new "1" bit for negative numbers, or zero for positive numbers), where a **Logical Shift** always introduces a "0" bit.

```
ALSHIFT 1001
      = 0010

ARSHIFT 1001
      = 1100

LLSHIFT 1001
      = 0010

LRSHIFT 1001
      = 0100
```

Note: a right-shift is equivalent to multiplying the value by two, and a left-shift is equivalent to diving the value by two.

[Home](index.md)
