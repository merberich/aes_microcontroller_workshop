
# Computer Elements and Architecture

Now that we have a theories to represent digital logic and binary numbers (which we can bring to reality by use of electrical circuits), if we want that system to accomplish practical, complex tasks, we need to organize it to do so. This section will describe the fundamental elements (composed of logic gates) used to develop the hierarchy of functionality we call a "computer".

## Finite State Machines

Central to most computer elements is the concept of a **Finite State Machine (FSM)** - a model of operation describing the fixed (finite) number of operating states a system can be in at any time. FSMs are useful in documenting and understanding how a system can flow between different states. FSMs are typically documented via a **State Transition Table**, which is very similar to a truth table, but instead describes _change_. For the visually-oriented, **State Diagrams** can also be used to describe FSMs. In both cases, it is critical to document the conditions that cause state transitions, as well as the effects of the transition.

For instance, the state transition table for a mechanical turnstile could look like the following:

| Current State | Condition | Next State | Effects |
|-|-|-|-|
| Locked | coin inserted | Unlocked | Unlocks the turnstile, allows pushing through |
| Locked | customer pushes | Locked | No effect |
| Unlocked | coin inserted | Unlocked | Coin returned; already unlocked |
| Unlocked | customer pushes | Locked | Locks after one full rotation |

The equivalent transition diagram could look like the following:

<img src="res/example-state-machine.png" title="Source: https://en.wikipedia.org/wiki/File:Turnstile_state_machine_colored.svg" width="350px">

FSMs are also particularly useful when developing new systems as a means of exploring behavioral requirements and checking validity of behavior.

## Computer Elements

Computer elements generally serve the purpose of storing, transmitting, or operating on either binary numbers or raw bits. For practical purposes, this workshop will only cover a handful of possible of these "building blocks" for computers.

### Latches, Registers, and Memory

One of the simplest ways to store data is called a **Flip-Flop, or Latch**. A latch is a computer element capable of storing the state of one bit.

The simplest latch is known as a **SR Latch**, where the circuit has two inputs (Set and Reset) and two outputs (Q and NOT-Q). Implemented via NOR gates, the SR latch has the following state transition table:

<div width="40%" style="float:left; margin-right:10px;">

| \(S\) | \(R\) | \(Q_{next}\) | Action |
| - | - | - | - |
| 0 | 0 | \(Q_{curr}\) | "hold" |
| 0 | 1 | 0 | "reset"  |
| 1 | 0 | 1 | "set" |
| 1 | 1 | x | indeterminate/illegal |
</div>

<img src="res/elem-sr-latch.gif" title="Source: https://en.wikipedia.org/wiki/File:R-S_mk2.gif" width="300px">

The main value that a simple SR latch provides is that when the Set and Reset inputs are both low (false), then the latch holds its current value. Then, when one of the inputs goes high, the output changes to accommodate the new condition.

In practice, a more complex latch known as a **Gated D Latch** is used. A Gated D Latch has some special properties. Being "gated" means that the latch has a special "enable" input: the latch state is only capable of changing when the enable line is high. Secondly, the D Latch takes advantage of the fact that output only changes for a SR Latch when S is the complement of R, so "D" and "NOT-D" represent these cases, with "D" for Data being the only input. Effectively, this means that the latch buffers Data when Enabled. The Gated D Latch has the following state transition table:

<div width="40%" style="float:left; margin-right:10px;">

| \(E\) | \(D\) | \(Q_{next}\) | Action |
|-|-|-|-|
| 0 | any | \(Q_{curr}\) | "hold" |
| 1 | 0 | 0 | "reset" |
| 1 | 1 | 1 | "set" |
</div>

<img src="res/elem-d-latch.png" title="Source: https://en.wikipedia.org/wiki/File:D-Type_Transparent_Latch.svg" width="400px">

The **D Flip-Flop** is a derivative of the Gated D Latch in which the enable condition (now called Clock) is instead defined by the rising or falling edge of the signal. In addition, the D Flip-Flop may expose the Set and Reset lines from the underlying SR Latch implementation (which ignore the Enable and Data lines). For most implementations, when Set and Reset are assigned high, the output is determined high; when Set and Reset are both low, this becomes the state transition table:

<div width="40%" style="float:left; margin-right:10px;">

| \(C\) | \(D\) | \(Q_{next}\) | Action |
|-|-|-|-|
| non-rising edge | any | \(Q_{curr}\) | "hold" |
| rising edge | 0 | 0 | "reset" |
| rising edge | 1 | 1 | "set" |
</div>

<img src="res/elem-d-flip-flop.png" title="Source: https://en.wikipedia.org/wiki/File:D-Type_Flip-flop.svg" width="150px">

Now that we have a way of storing individual bits temporarily, we can move on to representing binary numbers via hardware. The simplest way to do this is by combining several D Flip-Flops as a collection known as a **hardware register**, in which all of the bits in the register can be set at once (though there are many other ways of implementing a register). For instance, a four-bit register can be implemented as follows:

<img src="res/example-four-bit-register.gif" title="Source: http://www.edwardbosworth.com/My5155Text_V07_HTM/MyText5155_Ch07_V07_files/image100.gif">

Registers are often used to control other circuit elements by setting a reference state. Note that to assign values to a register, all bits must be available at once. When several data lines hold meaning as a collection, they are referred to as a group as a **Computer Bus**.

Another way to store binary information would be in the form of **Memory**, which describes a large set of bitfields that can only be accessed in "chunks" matching the bit width of the stored fields. To identify which bitfield to access, we use a **Memory Address**, which describes the index of the bitfield to target as offset from the first bitfield in memory. Generally, memory supports **Storing** (placing new values into memory) and **Loading** (retrieving a stored value), with some memory types also supporting operations to clear chunks of memory, or the entirety of memory.

Memory can be further divided into two categories: **Volatile Memory**, in which values in memory are kept only as long as the circuit has power, and **Non-Volatile Memory**, in which stored values are preserved even after loss of power.

### Multiplexers, Demultiplexers

A **Multiplexer (Mux)** is a computer element which selects and outputs one bit from a set of parallel input data lines. A **Demultiplexer (Demux)** does precisely the opposite: given one input, it selects one out of many possible output lines to connect to the input. A four-to-one mux would have the following truth table:

<div width="40%" style="float:left; margin-right:10px;">

| \(S_1\) | \(S_0\) | \(Z\) |
|-|-|-|
| 0 | 0 | A |
| 0 | 1 | B |
| 1 | 0 | C |
| 1 | 1 | D |
</div>

<img src="res/elem-4-1-mux.png" title="Source: https://en.wikipedia.org/wiki/File:Multiplexer_4-to-1.svg" width="300px">

### Arithmetic Operation: Adders

<div width="40%" style="float:left; margin-right:10px;">

| \(A\) | \(B\) | \(C_{in}\) | \(S\) | \(C_{out}\) |
|-|-|-|-|-|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 1 | 0 |
| 0 | 1 | 1 | 0 | 1 |
| 1 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |
</div>

Addition as an operation takes two numbers and any existing carry value, and produces their sum and any resulting carry value. This paradigm also applies when adding binary numbers. An **Adder** is therefore an implementation of the addition operation in circuit.

<img src="res/elem-full-adder.png" title="Source: https://en.wikipedia.org/wiki/File:Full-adder_logic_diagram.svg" width="400px">

The Full Adder takes in two bits \(A\) and \(B\), plus any existing carry bit \(C_{in}\) and produces the sum \(S\) and a resulting carry bit \(C_{out}\) for the operation. The truth table for a full adder is as shown.

A full adder takes the sum of just two bits, however. To take the sum of two \(n\)-bit binary numbers, we can simply perform the sum of each pair of bits in each sequence, and make sure we propagate the carry value as we would when adding by hand.

<br>
<img src="res/example-chained-adder.png" title="Source: https://en.wikipedia.org/wiki/File:4-bit_ripple_carry_adder.svg" width="700px">

There are many other implementations of both arithmetic and logical operators in practice. More operators will be discussed later.

### Timers, Counters, and Clocking

One major problem in the construction of digital logic circuits is synchronization - making sure that all relevant changes in line levels are accounted for, rather than skipped or double-counted. One of the most common ways to deal with synchronization is to include a **clock signal**, which is used to step multiple computer elements simultaneously. A clock signal is one that oscillates between high and low at a deterministic rate. It is effectively a timekeeping device: anything connected to the clock signals steps in time with one edge of the clock as it toggles.

A very rudimentary clock can be constructed from an op-amp, a resistor, and capacitor in the form of an [RC Oscillator](https://www.ti.com/lit/an/snoa998/snoa998.pdf). The RC Oscillator takes advantage of the time constant involved with charging a capacitor via a current-limited resistor element. In practice, however, RC Oscillators are particularly inaccurate because the clock frequency relies on part tolerances.

A different clock implementation that is very common in embedded systems is a [Piezoelectric Crystal Oscillator (Crystal Oscillator)](https://www.youtube.com/watch?v=fPKdDCiJDok). Typically, crystal-based oscillators have a much higher accuracy and less drift over time.

Clock signals are helpful beyond just synchronizing state machines as well. We can use a **Counter** element to quantify the amount of time that has passed. A counter is a collection of flip flops whose state represents the number of clock pulses seen at input. Counters can either be synchronous (where one clock signal causes all flip-flops to update state simultaneously), or asynchronous (where the clock signal drives only the first flip-flop, which serially drives the next, etc). Synchronous counters are generally faster because they perform the state update in parallel.

For example, a three-bit up-counter can be implemented with three positive edge triggered D flip-flops:

<img src="res/elem-counter.gif" title="Made via https://circuitverse.org/simulator">

Finally, now that we can determine the amount of time that has elapsed since the last counter reset, it is possible to use this information to trigger events. A module that can send signals based on the status of a counter is known as a **Timer**. A simple implementation of a timer could maintain a target register and counter, and after each clock step, perform a bitwise equality check between the target register and counter value. The timer could then optionally trigger different events for counter overflow/return to zero, or a match on the comparison with the target register and counter value.

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
