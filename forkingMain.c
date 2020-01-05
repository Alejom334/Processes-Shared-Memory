/*--------------------------------------------------------------------
|  Source code:  forkingMain.c
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
|                   Also, as stated in the psedudocode and description of
|                   the program, only numbers from zero to nine, inclusive,
|                   could be input. That means that any number below one or
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
| Description: This program allow us to work with shared memory space.
|               The program launches children processes by the technique
|               of fork(). All these children run independently but they
|               all have accessed to a shared memory space that
|               is requested at the beginning of the program if the
|               input from the command line happens to be validated.
|
|               The amount of children that are created depends on the
|               amount of inputs that are validated in the command line.
|               The inputs from the command line will be integers from
|               zero to nine, inclusive or [0-9] and a maximum of seven
|               inputs or [1-7], inclusive. In other words, the user can
|               input up to seven commands after the name of the
|               file that runs, and single digits from zero to nine.
|               The children will get their assigned integer according
|               to their index value. Then, these child processes
|               will do some calculations with this integer and then
|               put it back to the shared memory.
|
|               As the children execute the calculations the parent
|               will wait until all children are done. As soon as that
|               happens the parent will print the updated shared memory
|               array, the pids of the children and their exit codes.
|
|               After all of these procedures are performed the shared
|               memory will be detached and removed.
|
|    Input:  User needs to enter in the command line up to seven inputs.
|               In other words, at least one (1) input and up to seven(7),
|               inclusive. These inputs must be integers. Each integer should
|               be from [0-9]
|
|               Example of correct input:
|
|                       ./SharedProcess.out 4 6 8 7 3 5
|
|      Output:  The program will print statements indicating the status
|               and executions that either the parent or the children
|               happened to be doing at that time.
|
|               Program will show when the parent starts, validates command
|               line, request shared memory, receives shared memory, attaches
|               shared memory, fills shared memory, displays initial share
|               memory, when forking process start, when waiting for the
|               children to execute their tasks and when they finish their
|               execution, display all the pids and exit codes, display final
|               shared memory, when it detaches from shared memory, when it
|               removes from shared memory, and when the whole process
|               is completed.
|
|               Program will shown when the children starts, displays the
|               current memory at that specific time, display its unique id,
|               when it updates the memory, re-displays the updated memory,
|               and when each children process is exited.
|
|     Process:  The global steps of the program are as follows after
|                       compilation is completed:
|
|               1. Allow and accept comman line input.
|               2. Validate the input as stated in description.
|                  If input is not validated the program will finish
|                  gracefully.
|               3. Request the shared memory that all children wil have
|                  access to.
|               4. Fork parent and launch all children process.
|               5. Each children perform operations and update the
|                  shared memory.
|               6. Wait until children complete their execution
|               7. Print all final results.
|               8. Finish.
|
|
|   NOTE: EXPLANATION HOW THE PROGRAM USES BUFFER AND UNBUFFERED OUTPUT
|
|   Unbuffered output causes its output to appear immediately to
|   the screen. Unbuffered outputs are usually used to show errors.
|   The necessity to use this type of output stream is because, one
|   needs to know exactly what each child happens to be doing
|   every time. For this, you are going to see in some functions
|   the use of a char buffer that sprintf() adds things to that
|   buffer, and write that prints what was add to that buffer.
|
|   Buffered output is an I/O performance-enhancement technique.
|   Buffered outputs cause its output to be held in a buffer
|   (that is, an area in memory) until the buffer is filled or
|   until the buffer is flushed. The used of this type of
|   output will be when using printf().
|
|   The technical information explained in the two paragraphs above
|   is from the book DD - C How to program 8th Edition from
|   page # 817.
|
|
|   NOTE: EXPLANATION WHY THE VARIABLES ARRAYS IN THE MAIN WHERE NOT
|           INITIALIZED:
|
|    (This was previously discussed with Professor Feild)
|
|    int inputValidation[argc], pid_t pids [NUM_OF_CHILDREN], and
|    int childStatus[NUM_OF_CHILDREN] cannot be initialized. The
|    reason why is because their size comes from a constant that
|    is not in the header file. For this reason, at compile time
|    the compiler does not know the size of the array, then it
|    cannot be initialized at that time as we do with all other
|    variables. Note that I could have change the size of the array
|    to be a define constant. However, that means that the size of
|    the array would not be dynamic in the sense that user can change
|    the size depending on the amount of input. This means,
|    that the array will change in size according to the user input.
|
|    These arrays are initialized in the following functions:
|
|    int inputToValidate[argc] is initialized in function
|    transformInput(char *commandInput[],int convertedInput[],int length),
|    this function is called by the brain of input validation;
|    int validateInput(char *commandInput[],int convertedInput[],
|                                                       int arraySize)
|
|    pid_t pids[NUM_OF_CHILDREN] is initialized in function
|    wait_for_child(int childrens, int pidsNum[], int childStatus[]).
|
|    int childStatus[NUM_OF_CHILDREN] is initialzied in function
|    wait_for_child(int childrens, int pidsNum[], int childStatus[])
|
|
| Required Features Not Included : None
|
| Known Bugs:  None
|
*----------------------------------------------------------------------*/

#include "multiprocessLibrary.h"

int main(int argc, char* argv[])
{
  const int NUM_OF_CHILDREN = argc - ONE;
  int inputToValidate[argc];//Read Documentation for intialization
  pid_t pids[NUM_OF_CHILDREN];//Read Documentation for intialization
  int childStatus[NUM_OF_CHILDREN];//Read Documentation for intialization

  displayPurpose();
    
  if (validateInput(argv,inputToValidate,argc))
  {

      int memory_id = requestMemory();
    
      int* ptr_memory = attachMemory(memory_id);

      populateMemory(argv, ptr_memory, NUM_OF_CHILDREN);
    
      multiforking(NUM_OF_CHILDREN, ptr_memory);
    
      wait_for_child(NUM_OF_CHILDREN, pids, childStatus);

      display_child_info(NUM_OF_CHILDREN, pids, childStatus);

      parentDisplaysFinalMemory(ptr_memory, NUM_OF_CHILDREN);

      detachFromSharedMemory(ptr_memory);

      removeSharedMemory(memory_id);

      parentFinishes();
    
      return NO_ERROR;
  }

  else
  {
      return ERROR;
  }
    
}
