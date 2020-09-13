
# Electronics and Digital Logic

## Electronics Fundamentals

**Electricity** is the presence and movement of charge through conductive paths. We use several terms to quantify this movement of charge (denoted by dimensional value Q, with SI unit Coulomb [C]):

**Current** describes the rate of flow of charge past a reference point or through a reference surface.
- Dimensional value: Current \(I\) with SI unit: Ampere [A] = [C/s]
- Relation: \(I = Q / t\)

**Voltage** (aka Electric Potential or Electro-Motive Force) describes the amount of energy needed to move a unit charge between reference points in an electric field.
- Dimensional value: Voltage \(V\) with SI unit: Volt [V] = [J/C]
- Relation: \(V = E / Q\)

**Power** describes a rate of energy transfer. For electrical systems, this rate of energy transfer is in the form of charge crossing a potential over time.
- Dimensional value: Power \(P\) with SI unit: Watt [W] = [J/s]
- Relation: \(P = E/t = VQ/t = VI\)

These concepts together (thanks Wikipedia):
<img src="res/wiki-electric-load.gif" style="display: block; margin-left: auto; margin-right: auto">

**Electronics** is the discipline using movement of charge to achieve engineering goals by use of circuits (any closed loop of conductors through which current can flow). Electrical circuits are documented in diagrams known as **Schematics**, which use common symbols for different types of circuit elements. Elements are connected via lines indicating conductive path, where a "close" indicates connection, and an "open" indicates lack of connection.

Within the field of electronics, elements in circuits are divided into two categories: passive elements, and active elements. **Active elements** can add electrical energy to a system, control the flow of charge, or amplify power. **Passive elements** can only dissipate, absorb, or store electrical energy.

The passive elements most common in circuits (not an exhaustive list):

**Resistors** are passive elements that only dissipate energy.
- Dimensional value: Resistance \(R\) with SI unit Ohm [\(\Omega\)]
- Relation: "Ohm's law": \(\Delta V = IR\)
- Schematic symbol: <img src="res/schematic-resistor.png" width="15%">

**Capacitors** are passive elements that store energy proportional to the voltage difference across the element.
- Dimensional value: Capacitance \(C\) with SI unit Farad [F]
- Relation: \(\Delta V = \frac{1}{C}\int I dt\)
- Energy storage relation: \(E_C = \frac{1}{2}C V_C^2\)
- Schematic symbol: <img src="res/schematic-capacitor.jpg" width="15%">

**Inductors** are passive elements that store energy proportional to the current through the element.
- Dimensional value: Inductance \(L\) with SI unit Henry [H]
- Relation: \(\Delta V = -L \frac{dI}{dt}\)
- Energy storage relation: \(E_L = \frac{1}{2} L I_L^2\)
- Schematic symbol: <img src="res/schematic-inductor.png" width="15%">

The active elements most common in circuits (not an exhaustive list):

**Voltage sources** are active elements that supply power by means of controlled voltage (either static or dynamic). The current provided to the circuit will be determined by the load of the circuit, up to the power limit of the source (recall \(P = IV\)).
- Schematic symbol: <img src="res/schematic-voltage-source.png" width="10%">

**Current sources** are active elements that supply power by means of controlled current (either static or dynamic). The voltage provided to the circuit will be determined by the load of the circuit, up to the power limit of the source (recall \(P = IV\)).
- Schematic symbol: <img src="res/schematic-current-source.png" width="10%">

**Transistors** are active elements that amplify or switch power within a circuit. They will be discussed in detail in the next section.

This section does not cover common configurations for circuits of passive and active elements. While relevant to the greater field of embedded systems, they are only tangentially related to being able to design systems using microcontrollers. For independent study purposes, some industry-common combinations to know include:
- Resistive Voltage Dividers
- Operational Amplifiers
- RC Low-Pass Filters
- Level Shifters
- Voltage Regulators

Note that most circuit design is done via schematic programs such as [Altium](https://www.altium.com/), [Autodesk EAGLE](https://www.autodesk.com/products/eagle/overview), or [KiCad](https://kicad-pcb.org/).

Circuit simulation is typically done with a [SPICE](https://en.wikipedia.org/wiki/SPICE) program such as [LTspice](https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html), [ngspice](http://ngspice.sourceforge.net/xspice.html), or a simulator built-in with the chosen circuit design software suite.

_Demo_: Simple voltage divider with [PartSim](https://www.partsim.com/simulator).

## Transistors and Common Configurations

`@todo basic relationships and common use cases`
`@todo the idea of reducing electrical signals from analog to digital via standards`
`@todo flip flops, and how to build logic from them`

## Digital Logic

`@todo all gates / operators "propositional logic"`
`@todo interactive demo for logic circuits, maybe "Circuit Scramble" on Android`

## Binary Number Theory

`@todo twos-complement, how this relates to logic`
`@todo another interactive demo`

[Home](index.md)
