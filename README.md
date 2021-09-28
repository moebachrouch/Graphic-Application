# Design of an RLC Circuit
## This program was completed as part of the class curriculum for Introduction to Engineering Computation.
### Design of an RLC Electrical Circuit.

This program plots the function described in Equation 1, asks the user to select an interval for finding roots. An incremental search root finding method is used. A total of 100 points are used to plot. 

Equation 1: 

<a href="https://www.codecogs.com/eqnedit.php?latex=g(R)=e^{-R*T_{d}/{2L}}*cos\left&space;[&space;\left&space;(&space;\sqrt{\frac{1}{LC}-\left&space;(&space;\frac{R}{2L}&space;\right&space;)^{2}}&space;\right&space;)*t_{d}&space;\right&space;]-p_{c}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?g(R)=e^{-R*T_{d}/{2L}}*cos\left&space;[&space;\left&space;(&space;\sqrt{\frac{1}{LC}-\left&space;(&space;\frac{R}{2L}&space;\right&space;)^{2}}&space;\right&space;)*t_{d}&space;\right&space;]-p_{c}" title="g(R)=e^{-R*T_{d}/{2L}}*cos\left [ \left ( \sqrt{\frac{1}{LC}-\left ( \frac{R}{2L} \right )^{2}} \right )*t_{d} \right ]-p_{c}" /></a>

Equation 1 was derived using Kirchhoff's second law, which states that the total sum of voltage drops around a closed electrical circuit is zero.

We need to find the roots of g(R), or R such that g(R) = 0. This will give the proper value of resistance R to dissipate energy knowing the rate of dissipation td, the inductance L, the percentage of original charge pc, and the capacitance C.

The procedure used is described below:

1.	At the start of the program, the user will be asked to input a set of specific (constant) parameters in the equation used to compute the resistance R, which we will define in the input/output subsection right after. When new input values are given, the user is given the option to save them into a file; up to five sets of values can be stored, and each new inputted value will replace a value which was stored beforehand inside of the file. We will create the file beforehand in parallel to the development of the code.

2.	The software first calculates an upper bound for the resistor using the square root term in the function g(R) (equation 1) and will then plot the function for root finding. 

3.	After this, the user will be allowed to select an appropriate interval for searching the root of the function. The user will be allowed to repeatedly provide upper and lower bounds (a different interval) to replot g(R) until he is satisfied with the bounds.

4.	The program then uses a root-searching method, the bisection method which we have mentioned in order to get as close as possible to the root, which will be equal to the resistance. This value will be marked with a red crosshair on the graph. Multiple roots/solutions may exist, in which case the user will be asked if he wishes for the program to calculate the next root, by giving the user the choice to redefine the interval.
