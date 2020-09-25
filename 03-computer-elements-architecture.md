
# Computer Elements and Architecture

Now that we have a theory to represent digital logic which we can bring to reality by use of electrical circuits, if we want that system to accomplish practical, complex tasks, we need to organize it in a way that it is capable of doing so. This section will describe how we use digital logic to build up valuable functionality in a hierarchy we know as a "computer".

## Binary Number Theory

Up to this point, the theory and implementations have allowed us to create systems of simple logic circuits, but we need to be able to accomplish more complex tasks than logic alone can drive. First and foremost, we need a way to represent values that have meaning in engineering contexts: we need to represent numbers with logic systems.

First we must review how number systems work. In any number system, a value is represented by some sequence of "numeral" symbols in positions indexed as "digits". The "base" of a system is the count of different symbol corresponding to the first few natural numbers, including zero.

For example, in the decimal system (base 10), an integer \(a\) with three digits (denoted by subscript) holds value where:

\(a_2a_1a_0 = (a_2 * 10^2) + (a_1 * 10^1) + (a_0 * 10^0)\)

Generalizing, for any number system representing integer values, a number \(a\) with \(n\) digits in base \(b\) will have value such that:

\((a_na_{n-1}...a_1a_0)_b = \sum_{k=0}^{n} a_kb^k\)

where digit \(k\) holds value \(a_k * b^k\).

Naturally, this means there are other number systems we could use (base 8, base 16, etc), but more importantly, it implies that values are transferrable between different base systems. So, logic circuits, which are capable of representing only values true (1), or false (0), can represent a base 2 system: a binary number system.

The remainder of this section will describe how we represent specific kinds of numbers within a binary number system.

### Unsigned Integers

`@todo this`

### Signed Integers

`@todo twos-complement`

### Floating Point Numbers

`@todo this`

### Logical Operations and Bitwise Operations

`@todo this`

`@todo another interactive demo`

## Computer Elements

`@todo flip-flops`
`@todo registers and memory`
`@todo counter`
`@todo shifter`
`@todo adder`

## Finite State Machines

`@todo concept and applications`

## Computer Architecture

`@todo formal definition of computer`
`@todo primary functional elements`
`@todo instructions, CPU cycle finite state machine`
`@todo practical computer architectures`

## Computer Programming Interface

`@todo instruction set architecture`
`@todo common operations coverage`
`@todo briefly cover assembly`
`@todo demo with webassembly (?)`

[Home](index.md)
