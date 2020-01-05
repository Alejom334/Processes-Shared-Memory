/*--------------------------------------------------------------------
|   Source code:  inputValidationFork.c
|   Author: Alejandro Martinez
|   Student ID: 3625175
|   Assignment:  Program # 6 Processes & Shared Memory
|
|    Course:  [COP 4338 (Programming 3)]
|      Section:  [U04 1198]
|   Instructor:  William Feild
|     Due Date: 3 December 2019 - Class Time
|
| I hereby certify that this collective work is my own
|  and none of it is the work of any other person or entity.
|
| ___________________________________________[Alejandro Martinez]
| Language : C
|
|Compile/Run :
|              There are two ways to compile with the make file or the regular
|              gcc compilation. Both will be explained below.
|
|              COMPILATION NOT USING MAKEFILE:
|
|                   The following source files and header files must be in the
|                   same directory
|
|                   Source Files: forkingMain.c childFunctions.c
|                                 inputValidationFork.c parentFunctions.c
|                   Header Files: multiprocessLibrary.h
|
|                   Execute this command to compile:
|
|                        gcc forkingMain.c inputValidationFork.c
|                            parentFunctions.c childFunctions.c -o
|                                                       SharedProcess.out
|
|                        Note: This is a very long line, please input
|                               correctly, if one is copying and pasting
|                               please do it by parts as the '|' will be
|                               copied between lines.
|
|               RUN AFTER COMPILATION NOT USING MAKEFILE:
|
|                   NOTE: program is runned the same way. It does not matter
|                         how is compiled. However, it is expressed here how
|                         to run the file so there is continuity:
|
|                   ./SharedProcess.out # # # # # # #
|
|                       where # is an integer from zero to nine, inclusive
|
|                   Example:
|                           ./SharedProcess.out 1 2 3 4 5 6 7
|
|                   As stated in the psedudo code and description of the
|                   program, the command input should be up to seven inputs
|                   after the name of the file that runs. In other words,
|                   user can input one to seven inputs after the name of the
|                   file.
|
|                   Also, as stated in the psedudo code and description of
|                   the program, only numbers from zero to nine, inclusive,
|                   should be input. That means that any number below one or
|                   above 9 will not allow the program to run.
|
|                   To know more details about user input validation please
|                   visit class: inputValidationFork.c
|
|               COMPILATION USING THE MAKEFILE:
|
|                   The make file must be in the same directory as the
|                   following source/header/executable files:
|
|                    Source Files: forkingMain.c childFunctions.c
|                                   inputValidationFork.c parentFunctions.c
|                    Header Files: multiprocessLibrary.h
|
|                    Execute this command to compile:
|
|                       make build
|
|               RUN AFTER COMPILATION USING MAKEFILE:
|
|                   NOTE: program is runned the same way. It does not matter
|                         how is compile. However, it is expressed here how
|                         to run the file so there is continuity:
|
|                   ./SharedProcess.out # # # # # # #
|
|                       where # is an integer from zero to nine, inclusive
|
|                   Example:
|                           ./SharedProcess.out 1 2 3 4 5 6 7
|
|                   As stated in the psedudo code and description of the
|                   program, the command input should be up to seven inputs
|                   after the name of the file that runs. In other words,
|                   user can input one to seven inputs after the name of the
|                   file
|
|                   Also, as stated in the psedudo code and description of
|                   the program, only numbers from zero to nine, inclusive,
|                   should be input. That means that any number below one or
|                   above 9 will not allow the program to run.
|
|                   To know more details about user input validation please
|                   visit class: inputValidationFork.c
|-----------------------------------------------------------------------------
|
| Description of Source File:
|               The purpose of the source file inputValidationFork.c is to
|               validate the input from the command line that the user will
|               enter.
|               According to the specification, a valid input can be from
|               one input to seven inputs. Then to be clear input could be
|               from one to seven, inclusive or [1-7]. This means that
|               the user can enter any number of inputs within that range.
|               Also, according to the specifications, the command input
|               should be integers from zero to nine. That means that numbers
|               that are below zero or above nine are not allowed. This
|               also means that no strings are allowed or empty input.
|               Lastly, expanding from the previous requirement, all numbers
|               should be unique. This means that no duplicates are allowed.
|
|       Input:  This source file receives different inputs according to what
|               each function needs. All this input will come either from
|               the header file or the source code where the main is.
|               It is important to notice that the primary input this file
|               is validating comes from the command line.
|
|      Output:  The source code of inputValidationFork.c will state if the
|               command input was valid or not in a call in the main source
|               file.
|               If the command input is validated then an array in the main
|               with the proper command input will be populated. Otherwise,
|               messages indicating to the user what is a right input will
|               be displayed.
|
|     Process:  1. Function int validateInput(char *input[],int
|                   convertedInput[],int arraySize). This function will
|                   act as the brain of this source file. This function
|                   is in charge of calling all the other functions that
|                   will be performing validations. If all these
|                   functions are validated then an array is populated
|                   in the source file that contains the main. Otherwise,
|                   an error message is displayed.
|               2. Function check_range is called to check if the user
|                   input the right number of required inputs.
|               3. Function transformInput is called to convert the array
|                   of strings to an array of integers. If this is the
|                   case that will be a temporary array for the following
|                   check.
|               4. Function duplicateSearch will try to find any duplicates
|                   in the temporary array. If that is not the case, then
|                   an array of right inputs will be populated in the
|                   main.
|               NOTE: There are other functions that serve as helper
|                       functions in this source file. The documentation
|                       of every function is above the function.
|
|
| Required Features Not Included : None
|
| Known Bugs:  None
|
*----------------------------------------------------------------------*/

#include "multiprocessLibrary.h"



/*----------------------- void displayPurpose() -------------------------
| Function :  void displayPurpose()
|
| Purpose :    The purpose of this function was to state the purpose of this
|              program. This function will be called in main and it will
|              print disregarding if the user input the correct or incorrect
|              input.
|
| @param  : none
| @return : none
*-----------------------------------------------------------------------*/
void displayPurpose()
{
   printf("\n\n%s\n","EXPLANATION OF PROGRAM:");
   printf("\n%s\n","This program is to demonstrate the execution of ");
   printf("%s\n", "multiprocesses using fork. Trace messages will be ");
   printf("%s\n", "displayed to the user for understanding of what each");
   printf("%s\n\n", "is doing. Enjoy!");
}

/*-------------------------void explainRequiredInput()--------------------
| Function :  void explainRequiredInput()
|
| Purpose :  The purpose of this function is to advice the user if they
|            happened to input anything that is not in the specifications
|            in the command line.
|
| @param  : none
| @return : none
*------------------------------------------------------------------------*/
void explainRequiredInput()
{
   printf("\n\n\t%s\n","You need to put the proper input for the program to ");
   printf("\t%s\n", "run. There must only integers from zero to nine, ");
   printf("\t%s\n", "inclusive. Meaning that there cannot be integers above");
   printf("\t%s\n", "nine or lower than zero.");
   printf("\t%s\n", "The allowed number of inputs is from one to seven, inclusive.");
   printf("\t%s\n\n", "An example will be ./nameOfProgram 1 2 3 4 5 6 7");

}

/*----int validateInput(char *input[],int convertedInput[],int arraySize)----
| Function : int validateInput(char *input[],int convertedInput[],
|                                                       int arraySize)
|
| Purpose :  This function will act as the brain of the program in regards
|            of input validation. This function will call three functions
|            to check if the input thats was inserted in the command line
|            happens to be the correct input.
|
| Explanation of Algorithm:
|            - Call function check_range to make sure that the arguments that
|               were put in the command line are within the requirements;
|               one to seven. If that is not the case return INVALID.
|            - Call function transformInput to make sure that the input that
|               was put can be converted to an integer digit.
|            - Call function duplicateSearch to make sire that the partially
|               approve array has no duplicates.
|
| @param :  char*, input[], a pointer to an int array containing
|                                                       command line arguments
| @param : int[], convertedInput, a pointer to an empty integer array
| @param : int, arraySize,  an integer that is the length of the array
| @return : int constant, FALSE, returns zero as not valid input or
|           int constant, TRUE, returns one as valid input.
*--------------------------------------------------------------------------*/

int validateInput(char *commandInput[],int convertedInput[],int arraySize)
{

    if(check_range(arraySize,MINIMUM,MAXIMUM) == INVALID)
    {
       printf("%s\n", "PROVIDE RIGHT INPUT FROM THE COMMAND LINE!");
       printf("%s", "Number of inputs need to be between ");
       printf("%d and %d.\n", ONE, SEVEN);
       explainRequiredInput();
       return FALSE;
    }

    else if((transformInput(*(&commandInput),
                            convertedInput,arraySize)) == INVALID)
    {
       printf("%s\n", "PROVIDE RIGHT INPUT FROM THE COMMAND LINE!");
       printf("%s", "The command input should only be integers between");
       printf(" %d and %d.\n", MIN,MAX);
       explainRequiredInput();
       return FALSE;
    }

    else if((duplicateSearch(convertedInput,
                              arraySize)) == INVALID)
    {
       printf("%s\n", "PROVIDE RIGHT INPUT FROM THE COMMAND LINE!");
       printf("%s","Duplicate values are not allowed!\n");
       explainRequiredInput();
       return FALSE;
    }
    
    else
    {
       return TRUE;
    }
}

/*------- int check_range(int number, int minValue, int maxValue) -----------
| Function :  int check_range(int number, int minimum, int maximum)
|
| Purpose :  The purpose of this function is to check if the desired
|            number happened to be withtin the required range that will be
|            passed.
|
| Explanation of Algorithm:
|               - If number is less than the required minimum and more than
|                 the required maximum return INVALID or (-1)
|
| @param : int, number, number that will be checked.
| @param : int, minValue, lower boundary for number check
| @param : int, maxValues, highest boundaty fot number check
|
| @return : int, VALID (0), number that represents that all the tests were
|                               satisfied.
| @return : int, INVALID (-1), number that represents that the tests were not
|                               satisfied
*--------------------------------------------------------------------------*/

int check_range(int number, int minValue, int maxValue)
{
   if(number < minValue || number > maxValue)
   {
     return INVALID;
   }
   else
   {
     return VALID;
   }
}

/*------------ int duplicateSearch(int input[], int arraySize) -----------
|
| Function : int duplicateSearch(int input[], int arraySize)
|
| Purpose : This function goes through all the elements of the array to see
|               if they happened to be the same. If they are then it returns
|               invalid. Otherwise, returns valid.
|
| Explanation of Algorithm:
|           - This function takes two parameters, an integer array containing
|             the converted input, and the length of that array.
|           - There is one outer loop that iterates through the entire array
|             saving each element temporarily.
|           - The inner loop compares that temporarily element with the rest of
|             elements.
|           - There is a counter that counts if a number is duplicated; if
|             this is the case then a return of invalid is returned, otherwise
|             a return value of valid is returned.
|
| @param :  int, input[], an array with partially validated input
| @param : int, arraySize,  an integer that is the length of the array
|
| @return : int, VALID (0), number that represents that all the tests were
|                               satisfied.
| @return : int, INVALID (-1), number that represents that the tests were not
|                               satisfied
*------------------------------------------------------------------------*/

int duplicateSearch(int input[], int arraySize)
{
 int indexInput = 0;
 int innerCounter = 0;
 int duplicateCounter = 0;
 int temporaryVariable = 0;

 for(indexInput = FIRST_COMMAND_INPUT; indexInput < arraySize; indexInput++)
    {
        duplicateCounter = 0;
        temporaryVariable = input[indexInput];

        for(innerCounter = FIRST_COMMAND_INPUT; innerCounter < arraySize;
                                                            innerCounter++)
        {
             if(temporaryVariable == input[innerCounter])
             {
                  duplicateCounter++;
             }
    }

    if(duplicateCounter > NO_DUPLICATE)
    {
        return INVALID;
    }
 }
 return VALID;
}

/*- int transformInput(char *commandInput[],int convertedInput[], int length) -
|
| Function : int transformInput(char *commandInput[],int convertedInput[],
|                                                                 int length)
|
| Purpose : Converted input stores numbers in an array that are validated.
|           By validation, we mean numbers that each character can be
|           be converted to an integer digit and also that the integer
|           digit can be between the parameters established zero to nine
|           inclusive.
|
| Explanation of Algorithm:
|           - This function takes three parameters; an array of strings
|             coming from the command input, a new array that will store
|             the validated input, and length that is argc.
|           - This function loops through all the inputs of the command line.
|           - If the input of the command line is invalid return invalid.
|           - If not add that element into the array.
|           - if that element that was just added does not happened to be
|             in the invalid range then return.
|
| @param :  char*, commandInput[], a pointer to an int array containing
|                                                       command line arguments
| @param : int[], convertedInput, a pointer to an empty integer array
| @param : int, length,  an integer that is the length of the array
|
| @return : int, VALID (0), number that represents that all the tests were
|                               satisfied.
| @return : int, INVALID (-1), number that represents that the tests were not
|                               satisfied
*--------------------------------------------------------------------------*/

int transformInput(char *commandInput[],int convertedInput[], int length)
{

 int indexInput = 0;

 for(indexInput = FIRST_COMMAND_INPUT; indexInput < length; indexInput++)
    {
       if(convertString(commandInput[indexInput]) == INVALID)
       {
         return INVALID;
       }

       convertedInput[indexInput] = convertString(commandInput[indexInput]);

       if(check_range(convertedInput[indexInput],MIN,MAX) == INVALID)
       {
         return INVALID;
       }
    }
 return VALID;

}

/*------------------- int convertString(char *string)  -----------------
|
| Function : int convertString(char *string)
|
| Purpose : The purpose of this function is to convert a character into a
|               a number for further analysis in the above funtions.
|
| Explanation of Algorithm:
|         - While the string passed does not get to the end of string
|           or null character, iterate through that string
|         - Use the function isdigit(c) that checks if the passed character
|           is a decimal digit character. The function isdigit(c) is from
|           the <stdlib.h> library
|         - According to the book DD - C How to 8th Edition the function
|           isdigit(c) returns a true value if c is a digit and 0 (false)
|           otherwise.
|         - If the character passed is a digit, then we convert it into
|           an integer with the line of code
|           number = number * (base of ten) + (c - ASCII number)
|         - Advance through all characters of that string.
|         - If the character is not a digit then return INVALID CHARACTER
|         - return the converted character.
|
| @param : int*, string, a pointer to the character string that must be
|                               converted.
| @return : int, number, digit converted into an integer
*---------------------------------------------------------------------*/

int convertString(char *string)
{
    int number = 0;

    while(*string != ENDOFSTRINGCHARACTER)
    {
        char element = *string;

        if(isdigit(element))
        {
            number = number * BASE_TEN + (element - ASCII);
        }
        
        else
        {
            return INVALID;
        }
        
        *string++;
    }
    
    return number;
}
