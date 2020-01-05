/*--------------------------------------------------------------------
|  Source code:  multiprocessLibrary.h
|    Author: Alejandro Martinez
|   Student ID: 3625175
|   Assignment:  Program # 6 Processes & Shared Memory
|
|       Course:  [COP 4338 (Programming 3)]
|      Section:  [U04 1198]
|   Instructor:  William Feild
|     Due Date: 3 December 2019 - Class Time
|
| I hereby certify that this collective work is my own
|  and none of it is the work of any other person or entity.
|
| ___________________________________________[Alejandro Martinez]
| Language   : C
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
|
|-----------------------------------------------------------------------------
|
| Description: This library will contain all the required constants needed
|               by the program. The use of every constant is specified in
|               every constant definition. Also, all the required libraries
|               for the program to execute properly are attached here.
|
| Required Features Not Included : None
|
| Known Bugs:  None
|
*----------------------------------------------------------------------*/

#include  <stdio.h> /* Library for input and output functions*/
#include  <stdlib.h> /* Library for exit() and strcat()*/
#include  <sys/types.h> /* Library for returned process ID */
#include  <string.h> /* Library for strlen function */
#include  <sys/ipc.h> /* Library for shared memory */
#include  <sys/shm.h> /* Library for shared memory */


#define ONE 1 /* Situations when adding one */
#define SEVEN 7 /* Upper bound of arguments */
#define ENDOFSTRINGCHARACTER '\0' /* Define end of string character */
#define NO_ERRORS 0 /* Successful execution of main */
#define NO_ERROR 0 /* Succesful execution */
#define SUCCESFUL_MEM_REQUEST 0 /* Values above 0 indiacte succesful request */
#define ERROR 1 /* To indicate unsuccessful execution */
#define NO_MEMORY -1 /* To indicate unsuccessful memory attachment */
#define BUFFER_SIZE 100 /* Size of the buffer in in sprintf */
#define CHILD_SUCCESS 0 /* Indicate fork was successful */
#define FIRST_CHILD 1/* First child to be launched */
#define SIZE 4 /* Memory Size multiplier */
#define ANY_CLIENT 0666 /* Granting access for any client*/
#define INITIAL_MEMORY_START 1 /* Initial address of shared memory */
#define DOUBLE 2 /* To double value in shared memory */
#define TWO 2 /* Double the number in memory */
#define STANDARD_OUTPUT 1 /* To write standard output */
#define ATTACHMENT_FLAG 0/* Yo indicate the specific shared memory conditions */
#define FIRST_COMMAND_INPUT 1/* first command line input*/
#define BASE_TEN 10 /* To convert string to int */
#define NO_DUPLICATE 1 /* To indicate that a number is duplicate */
#define ASCII 48 /* To convert from ASCII to integer */
#define MAX_NUM_VALUES 7 /* Maximum numbers of values*/
#define CHILDEXITCODESTAP 4 /* Three taps for the exit codes */
#define ENDOFSTRING "\0" /* End of a string */
#define TRUE 1 //Used for readability
#define FALSE 0 //Used for readability

enum limits{MIN = 0, MINIMUM = 2, MAX = 9, MAXIMUM = 8};/* to check range of
                                                 command line arguments*/
enum valid {INVALID = -1, VALID = 0}; /* values to return from functions */

void displayPurpose();
void explainRequiredInput();
int duplicateSearch(int input[], int arraySize);
int convertString(char *string);
int check_range(int number, int minValue, int maxValue);
int transformInput(char *commandInput[],int convertedInput[], int length);
int validateInput(char *commandInput[],int convertedInput[],int arraySize);
int requestMemory();
int* attachMemory(int shm_id);
void populateMemory(char* argv[], int* shm_ptr, int childrens);
void multiforking (int childrens, int* ptr_memory);
void childManipulation(int* shm_ptr, int counter, int childrens);
void printMemory(int* shm_ptr, int childrens);
void childCalculation(int *shm_ptr, int childIDNumber);
void printChildMemoryChange(int* shm_ptr, int childrens, int childNumber);
void wait_for_child(int childrens, int pidsNum[], int childStatus[]);
void display_child_info(int childrens, int* pidsNum, int *childStatus);
void parentDisplaysFinalMemory(int* shm_ptr, int childrens);
void detachFromSharedMemory (int* shm_ptr);
void removeSharedMemory (int shm_id);
void parentFinishes();

