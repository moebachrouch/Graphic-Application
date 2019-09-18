/*---------------------------------------------------------------------------------------------------------------------------------------
File: FinalVersion.c

Author: Mohamed Bachrouch

Description: This program calculates the root of the function of an Equation and plots it and marks the root. It
starts off by checking if the file exists or not. If it does not, the it gives the user the option to input 5 sets of values with which
the root is calculated and the graph is plotted, and it creates the file. Once the file is created, the user runs the program a second
time and sees all the sets contained in the file, and has the choice to either use of the existing sets to calculate the root, or enter
a new set of values to calculate the root. The user then has the option to save those values in an empty, or full slot in the file.
-----------------------s----------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <gng1106plplot.h>
#include "plplot.h"
#include <math.h>
#include <float.h>

#define BIN_FILE "projectdata.bin" // The data is stored in a binary file
#define NUM_POINTS 100 // We will use 100 points to plot the function
#define NUM_VALUES 5
#define EPSILON 1e-8 // A value assumed to be equal to zero
#define X_IX 0
#define FX_IX 1

#define TRUE 1
#define FALSE 0

typedef struct
{
    double start; // Start value for the plotting
    double end; // End value for the plotting
    double inductance;
    double capacitance;
    double dissipationRate;
    double chargePercentage;
    double root; // To simplify the coding, we included the root inside this structure, even though it is not an input
    int full; // Indicates whether each of the array sets is contains values or not

} INPUT;

int plotted; // Global variable used to help with marking the root after the user chooses his interval

// Functions for interacting with the user:
void userInput(INPUT *); // prompts the user for the input values in the structure
void displayFile(INPUT *); // displays what the sets currently contained in the file
void choiceInput(INPUT*, int *); // plots the function using a preexisting set of values and prompts the user for the start and end
// values for replotting and calculating the root. Similar to userInput

// Functions for plotting:
void computeDataPoints(INPUT *); // Fills an array for plotting
double getMin(double []); // Gets minimum value of array for plotting
double getMax(double []);// Gets maximum value of array for plotting
void plot(INPUT *, double [][NUM_POINTS]); // Plots the function

// Functions for calculations:
double func(INPUT *, double); // Function of Equation (3) in deliverable 1
double bisectionSearch(INPUT *); // Searches for root using bisection method
double computeFuncBounds(INPUT *); // Computes the function's lower and upper bounds

// Functions for filing:
void readBin(INPUT*); // Reads from the file
void writeBin(INPUT*); // Writes in the file
void saveInFile(INPUT *, INPUT *, int *); // Saves the input values in the file

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: main

Parameters: none

Returns: nothing

Description: the main function controls the rest of the program. It allows for the user to make appropriate choices by calling different
functions. Partly interacts with the user just to allow him to enter his choices, and which "path" he wants the program to take. the main
function is quite long, but only because it takes into account each and every possibility: it corrects any mistake the user makes when
entering invalid choices and goes through all possible paths.
---------------------------------------------------------------------------------------------------------------------------------------*/
void main()
{
    INPUT input[NUM_VALUES]= {0,0,0,0,0}, newSet; //input is the set that will be saved each time and newSet is the set that the user
    // enter. input[NUM_VALUES] is set to 0 everywhere because we do not want the program to give junk values if each set contains
    // nothing
    char choice, save;
    int set, slot, answer, ix, flag;

    ix=1; // ix is a counter for the while loop that is initalized at 1 because it is then passed to the function saveInFile, which
    // will then use ix-1. If we had initialized it at 0, then saveInFile would use the -1th set of the array which doesn't make sense.

    readBin(input); // Reads from the file

    // If the file does not yet exist (first time running the program)
    if ((input[0].full == FALSE) && (input[1].full == FALSE) && (input[2].full == FALSE) && (input[3].full == FALSE) && (input[4].full == FALSE))
    {
        printf("A file does not yet exist. Please enter up to 5 sets of values to create a new file.\n\n");

        do
        {
            do
            {
                flag=TRUE;
                userInput(&newSet);
                computeDataPoints(&newSet);
                bisectionSearch(&newSet);

                printf("\nThe root (resistance) is R=%lf ohms and f(R)=%lf\n\n",newSet.root, func(&newSet, newSet.root));

                // gives error if the root is negative
                if(newSet.root<0)
                {
                    flag=FALSE;
                    printf("The root is negative. Please enter a different set.\n\n");
                }
            }
            while(flag==FALSE);

            // the inputted values are saved in the file
            saveInFile(&newSet,input,&ix);

            printf("Your set has been saved in slot #%d. Would you like to enter a new set of values? (y/n): ", ix);;
            scanf(" %c",&choice);

            while(choice!='n' && choice!='y')
            {
                printf("Please enter a valid response. Would you like to enter a new set of values? (y/n): ");
                scanf(" %c",&choice);
            }

            // moves on to the next set in the array by incrementing ix by 1
            ix=ix+1;
        }
        // repeats the loop a maximum of 5 times, and at the user's request
        while((ix<NUM_VALUES) && (choice=='y'));
        printf("\nYour sets have been saved. You can run the program again to see what the file contains and to use it.\n");
    }

    // if the file already exists
    else
        do
        {
            printf("File already exists. Here are the current sets of values in the file: \n\n");

            displayFile(&input);

            printf("\nWould you like to use one of the existing sets of values (1), or would you like to enter a new set of values (2)?: ");
            scanf("%d",&answer);


            while(answer!=1 && answer!=2)
            {
                printf("Please enter a valid response. Would you like to use one of the existing sets of values (1), or would you like to enter a new set of values (2)?: ");
                scanf("%d",&answer);
            }

            // if the user wants to use an existing set of values
            if(answer==1)

            {
                printf("Which set would you like to use? Please enter a number from 1 to 5: ");
                scanf("%d",&set);

                while(set!= 1 && set!=2 && set!=3 && set!=4 && set!=5)
                {
                    printf("Please enter a valid response. Which set would you like to use? Please enter a number from 1 to 5: ");
                    scanf("%d",&set);
                }

                do
                {
                    choiceInput(&input,&set);
                }
                while(plotted==FALSE);

                printf("Would you like to continue? (y/n): ");
                scanf(" %c",&choice);
                printf("\n");

                while (choice!='y' && choice != 'n')
                {
                    printf("Please enter a valid response. Would you like to continue?");
                    scanf(" %c",&choice);
                    printf("\n");
                }
            }

            // if the user wants to input his own values
            else if(answer==2)

            {
                do
                {
                    flag=TRUE;
                    userInput(&newSet);
                    computeDataPoints(&newSet);
                    bisectionSearch(&newSet);

                    printf("\nThe root (resistance) is R=%lf ohms and f(R)=%lf\n\n",newSet.root, func(&newSet, newSet.root));

                    // gives error if the root is negative
                    if(newSet.root<0)
                    {
                        flag=FALSE;
                        printf("The root is negative. Please enter a different set.\n\n");
                    }
                }
                while(flag==FALSE);

                printf("Would you like to save this set of values? (y/n): ");
                scanf(" %c",&save);

                while(save!='y' && save!='n')
                {
                    printf("Please enter a valid response. Would you like to save this set of values? (y/n): ");
                    scanf(" %c",&save);
                }

                // if the user chooses to save the values
                if(save=='y')
                {
                    printf("In which slot would you like to save the current set? Please enter a number from 1 to 5: ");
                    scanf("%d",&slot);

                    while(slot!=1 && slot!=2 && slot!=3 && slot!=4 && slot != 5)
                    {
                        printf("Please enter a valid response. In which slot would you like to save the current set? Please enter a number from 1 to 5: ");
                        scanf("%d",&slot);
                    }

                    // the values are saved in the slot that the user chooses
                    saveInFile(&newSet, &input, &slot);
                }

                printf("Would you like to continue? (y/n): ");
                scanf(" %c",&choice);

                while (choice!='y' && choice != 'n')
                {
                    printf("Please enter a valid response. Would you like to continue?");
                    scanf(" %c",&choice);
                }
            }
        }
    // repeats the entire loop starting from the part which asks the user whether he wants to use preexisting values or enter a new
    // set of values, and gives the user the same choices
        while(choice=='y');
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: displayFile

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user


Returns: nothing

Description: displays the saved contents in the input array (actually in the file).
---------------------------------------------------------------------------------------------------------------------------------------*/
void displayFile(INPUT *inputPtr)
{
    int cntr;

    for(cntr=0; cntr<NUM_VALUES; cntr++)
    {
        printf("SET #%d\n\n",cntr+1);
        printf("Capacitance = %0.3lf\n",inputPtr[cntr].capacitance);
        printf("Inductance = %0.3lf\n",inputPtr[cntr].inductance);
        printf("Dissipation rate = %0.3lf\n",inputPtr[cntr].dissipationRate);
        printf("Charge percentage = %0.3lf\n",inputPtr[cntr].chargePercentage);
        printf("-------------------------------------------------------------------------------\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: saveInFile

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user
values[] - pointer to the structure variable input, used to save all inputed values
slot - pointer to slot, an integer used to indicate the index inside the array for the set to be saved

Returns: nothing

Description: saves the inputted values inside of a the array of structures one by one depending on the index, then calls the function
writeBin to save those values in the file.
---------------------------------------------------------------------------------------------------------------------------------------*/
void saveInFile(INPUT *inputPtr, INPUT values[], int *slot)
{
    // We use slot-1 because if the user inputs 2 for example, the program has to fill in the 2-1 = 1st slot in the array that ranges
    // from 0 to 4
    values[*slot-1].capacitance=inputPtr->capacitance;
    values[*slot-1].inductance=inputPtr->inductance;
    values[*slot-1].dissipationRate=inputPtr->dissipationRate;
    values[*slot-1].chargePercentage=inputPtr->chargePercentage;
    values[*slot-1].root=inputPtr->root;

    writeBin(values);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: readBin

Parameters:
values[] - pointer to the structure variable input, used to save all inputed values

Returns: nothing

Description: reads from the binary file and checks whether the file exists or not. If it does not, it assigns the value FALSE (0) to the
full component of values[]. This is used in the beginning of the code to check if the file exists.
---------------------------------------------------------------------------------------------------------------------------------------*/
void readBin(INPUT values[])
{
    FILE *filePtr;
    int ix;

    filePtr = fopen(BIN_FILE,"rb");
    if(filePtr == NULL) // if the file does not exist
    {
        for(ix = 0; ix < NUM_VALUES; ix = ix+1)
            values[ix].full = FALSE;
        writeBin(values);

    }
    else
    {
        fread(values,sizeof(INPUT),NUM_VALUES,filePtr);
        for(ix = 0; ix < NUM_VALUES; ix = ix+1) values[ix].full = TRUE;
        fclose(filePtr);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: writeBin

Parameters:
values[] - pointer to the structure variable input, used to save all inputed values

Returns: nothing

Description: writes in the binary file. This function saves the updated values inside the file every time the user wishes for it.
Displays error message if there is a problem opening the file.
---------------------------------------------------------------------------------------------------------------------------------------*/
void writeBin(INPUT values[])
{
    FILE *filePtr;
    int ix;

    filePtr = fopen(BIN_FILE, "wb");

    if(filePtr == NULL)
    {
        printf("Error encountered opening file.\n");
    }
    else
    {
        fwrite(values,sizeof(INPUT),NUM_VALUES,filePtr); // writes the values in the file
        fclose(filePtr);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: userInput

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns: nothing

Description: prompts the user to input the values of capacitance, inductance, dissipation rate, charge percentage, then plots the
function and once that is done, plotted is set to TRUE, so that the plotting function plot can now mark the root. Then, the function
prompts the user for the start and end values to replot and calculate the root
---------------------------------------------------------------------------------------------------------------------------------------*/
void userInput(INPUT *inputPtr)
{
    plotted=FALSE; // initializes the global variable plotted at FALSE (0) so that the program doesn't mark the root before the user
    // inputs the start and end values

    int answer;
    int slot;

    do
    {
        printf("Please enter strictly positive values of capacitance, inductance, dissipation rate and charge percentage respectiveley:\n");
        scanf("%lf %lf %lf %lf",&inputPtr->capacitance,&inputPtr->inductance,&inputPtr->dissipationRate,&inputPtr->chargePercentage);
        fflush(stdin);

        while (inputPtr->capacitance<=0 || inputPtr->inductance<=0 || inputPtr->dissipationRate<=0 || inputPtr->chargePercentage<=0)
        {
            printf("Please enter values that are strictly positive:\n");
            scanf("%lf %lf %lf %lf",&inputPtr->capacitance,&inputPtr->inductance,&inputPtr->dissipationRate,&inputPtr->chargePercentage);
            fflush(stdin);
        }
        inputPtr->start=-computeFuncBounds(inputPtr); // Lower bound
        inputPtr->end=computeFuncBounds(inputPtr); // Upper bound
        computeDataPoints(inputPtr);

        plotted=TRUE; // once the function is plotted with the natural bounds of the function, plotted is initialized to TRUE (1)
        printf("\nThe function exists on the interval [%lf, %lf]\n",inputPtr->start,inputPtr->end);

        // now that plotted is initialized at TRUE (1), the program can mark the root on the plot
        printf("\nPlease enter start and end values for replotting the function and searching for the root:\n");
        scanf("%lf %lf",&inputPtr->start,&inputPtr->end);

        while (inputPtr->start>=inputPtr->end)
        {
            printf("Please enter a smaller start value than end value:\n");
            scanf("%lf %lf",&inputPtr->start,&inputPtr->end);
            fflush(stdin);
        }

        while ((inputPtr->start < -computeFuncBounds(inputPtr) || inputPtr->end > computeFuncBounds(inputPtr)))
        {
            printf("Please enter start and end values within the function bounds:\n");
            scanf("%lf %lf",&inputPtr->start,&inputPtr->end);
            fflush(stdin);
        }
    }
    while(plotted==FALSE);

}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: choiceInput

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns: nothing

Description: similar to the userInput function. This time, the number of the set is passed and this function uses one of the
preexisting sets in the file to calculate the root and plot the function, so the user does not have to input the electrical
properties of the circuit, but only the start and end values for replotting
---------------------------------------------------------------------------------------------------------------------------------------*/
void choiceInput(INPUT *inputPtr, int *set)
{
    plotted=FALSE;

    inputPtr[*set-1].start=-computeFuncBounds(&inputPtr[*set-1]); // Lower bound
    inputPtr[*set-1].end=computeFuncBounds(&inputPtr[*set-1]); // Upper bound

    computeDataPoints(&inputPtr[*set-1]);

    plotted=TRUE;
    printf("\nThe function exists on the interval [%lf, %lf]\n",inputPtr[*set-1].start,inputPtr[*set-1].end);

    printf("\nPlease enter start and end values for replotting the function and searching for the root:\n");
    scanf("%lf %lf",&inputPtr[*set-1].start,&inputPtr[*set-1].end);

    while (inputPtr->start>=inputPtr->end)
    {
        printf("Please enter a smaller start value than end value:\n");
        scanf("%lf %lf",&inputPtr[*set-1].start,&inputPtr[*set-1].end);
        fflush(stdin);
    }

    while ((inputPtr[*set-1].start < -computeFuncBounds(&inputPtr[*set-1]) || inputPtr[*set-1].end > computeFuncBounds(&inputPtr[*set-1])))
    {
        printf("Please enter start and end values within the function bounds:\n");
        scanf("%lf %lf",&inputPtr[*set-1].start,&inputPtr[*set-1].end);
        fflush(stdin);
    }

    computeDataPoints(&inputPtr[*set-1]);
    bisectionSearch(&inputPtr[*set-1]);

    printf("\nThe root (resistance) is R=%lf ohms and f(R)=%lf\n\n",inputPtr[*set-1].root, func(&inputPtr[*set-1], inputPtr[*set-1].root));
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: computeFuncBounds

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns:
The absolute value of the bounds of the function

Description: Calculates the absolute value of the bounds of the function and returns it
---------------------------------------------------------------------------------------------------------------------------------------*/
double computeFuncBounds(INPUT *inputPtr)
{
    double bound = 2*sqrt(inputPtr->inductance/inputPtr->capacitance);
    return bound;
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: computeDataPoints

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns:
fx - the y component of x, in our case the function with respect to the resistance

Description: Calculates the y component of the resistance in Equation (3) of the deliverables, using the inputted values of capacitance,
inductance, dissipation rate and charge percentage.
---------------------------------------------------------------------------------------------------------------------------------------*/
double func(INPUT *inputPtr, double x)
{
    double fx;

    fx=(1/(inputPtr->inductance*inputPtr->capacitance)) - pow((x/(2*inputPtr->inductance)),2);
    fx=sqrt(fx)*inputPtr->dissipationRate;
    fx=cos(fx)*exp((-x*inputPtr->dissipationRate)/(2*inputPtr->inductance));
    fx=fx-inputPtr->chargePercentage;

    return(fx);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: computeDataPoints

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns:
fx - the y component of x, in our case the function with respect to the resistance

Description: computes 100 data points and fills a 2 dimensional array, later used for the plotting. Calls plot and passes those points
in order to draw the graph of the function.
---------------------------------------------------------------------------------------------------------------------------------------*/
void computeDataPoints(INPUT *inputPtr)
{
    double points[2][NUM_POINTS];
    double inc;
    int ix;

    inc = (inputPtr->end - inputPtr->start)/NUM_POINTS;
    points[X_IX][0] = inputPtr->start;
    points[FX_IX][0] = func(inputPtr, points[X_IX][0]);
    for(ix = 1; ix < NUM_POINTS; ix = ix + 1)
    {
        points[X_IX][ix] = points[X_IX][ix-1] + inc;
        points[FX_IX][ix] = func(inputPtr, points[X_IX][ix]);
    }
    plot(inputPtr, points);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: plot

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user
points[][NUM_POINTS] - a two dimensional array that points to the 2D array in the function computeDataPoints, and contains the x and y-
components of the function

Returns: nothing

Description: uses the previously calculated data points which were saved in a 2D array, and PLplot library functions to help plot the
function. If plotted=TRUE, this function is also free to mark the root on the graph.
---------------------------------------------------------------------------------------------------------------------------------------*/
void plot(INPUT *inputPtr, double points[][NUM_POINTS])
{
    double minFx, maxFx;
    int flag=FALSE;
    plsdev("wingcc");

    // initializes the plotting
    plinit();
    plwidth(3);

    minFx = getMin(points[FX_IX]);
    maxFx = getMax(points[FX_IX]);

    // the plotting happens here
    plenv(points[X_IX][0],points[X_IX][NUM_POINTS-1],
          minFx, maxFx, 0, 1);
    plcol0(BLACK);

    pllab("R", "f(R)", "Plot of f(R) versus R");
    plcol0(BLUE);

    plline(NUM_POINTS, points[X_IX], points[FX_IX]);

    if (fabs(bisectionSearch(inputPtr)))
    {
        flag=TRUE;
    }

    // this part of the function is for marking the root. It works if the function finds bisectionSearch finds a root, and also once
    // plotted takes the value TRUE (1).
    if ((flag==TRUE) && (plotted==TRUE))

    {
        plcol0(RED);
        plptex(inputPtr->root,0,0,0,0.5,"x");
        printf("\nThe root has been marked\n");
    }

    // stops the plotting
    plend();
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: getMin

Parameters:
arr[] – pointer to the y-component of the previous points[][NUM_POINT] which contains all the values for plotting.

Returns:
min - the value of the minumum

Description: traverses the array in order to find minimum value. At the end, the function returns the minimum value found in the array.
---------------------------------------------------------------------------------------------------------------------------------------*/
double getMin(double arr[])
{
    double min;
    int ix;

    for(ix = 0; ix < NUM_POINTS; ix = ix + 1)
    {
        if(min > arr[ix]) min = arr[ix];
    }
    return(min);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: getMax

Parameters:
arr[] – pointer to the y-component of the previous points[][NUM_POINT] which contains all the values for plotting.

Returns:
min - the value of the maximum

Description: traverses the array in order to find maximum value. At the end, the function returns the maximum value found in the array.
---------------------------------------------------------------------------------------------------------------------------------------*/
double getMax(double arr[])
{
    double max;
    int ix;

    for(ix = 0; ix < NUM_POINTS; ix = ix + 1)
    {
        if(max < arr[ix]) max = arr[ix];
    }
    return(max);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
Function: bisectionSearch

Parameters:
inputPtr - pointer to the structure variable newSet, used to input new sets of values by the user

Returns: does not return anything, but it is defined as a double because its value is used in the plotting function to tell whether a
root is found or not

Description: uses the bisection method to converge to a more and more approximate value of the root of a function plotted. The algorithm
consists of repeatedly diving an interval into two subintervals and checking if the root is located in the first or the second, until
the f(root) becomes smaller than a critical value EPSILON which is assumed to be equal to 0.
---------------------------------------------------------------------------------------------------------------------------------------*/
double bisectionSearch(INPUT *inputPtr)
{
    double est;
    int flag;

    double left = inputPtr->start;
    double right = inputPtr->end;

    do
    {
        flag = TRUE;
        est = (left + right)/2.0;

        // if the root is located in the left interval
        if((func(inputPtr,left)*func(inputPtr,est))<0)
        {
            flag=FALSE;

            // redefine the right bound as the estimate
            right=est;
        }

        // if the root is located in the right interval
        if((func(inputPtr,left)*func(inputPtr,est))>0)
        {
            flag=FALSE;

            // redefine the right bound as the estimate
            left=est;
        }

        // once f(root) is close enough to 0
        if(fabs((func(inputPtr,left)*func(inputPtr,est)))<EPSILON)
        {
            // the root is now found
            inputPtr->root=est;
            flag=TRUE;
        }
    }
    while(flag==FALSE);
}
