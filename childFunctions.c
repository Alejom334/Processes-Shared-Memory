/*--------------------------------------------------------------------
|   Source code:  childFunctions.c
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
|                   As stated in the psedudocode and description of the
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
| Description:
|              This source file works directly with all the other source files
|               but most importantly with the parentFunctions.c. The reason
|               why is because in the parentFunctions.c child processes are
|               launched. The functions of those child processes are shown
|               here. Every child will update the shared memory according to
|               their unique ID given from the parent. As stated below
|               each children will double their required index number
|               in the shared memory and then it will multiply it by its
|               own unique ID. Everything that the children does is sent
|               to the standard output.
|
|               NOTE: Refer to the psedudocode for a detailed explanation on
|               why to used unbuffered output when working with these
|               child processes. Also, recall that both unbuffered and
|               buffered outputs were used throughout the program.
|
|       Input: There is not a defined input for this source file as every
|               function will need specific inputs. An explanation of what
|               each function requires is in the documentation of every
|               function.
|
|      Output: There is not a defined output for this source file. The main
|               will show the interaction between the children and parent.
|     Process:
|               1. childManipulation will update status in the following way
|                  - Child starts
|                  - Child prints the current shared memory
|               2. printChildMemoryChange function is called to print
|                  the current memory.
|               3. The child will display its unique id (index).
|               4. Function childCalculation is called.
|               5. Child calculations will multiply the number in shared memory
|                   by two and the child unique ID.
|               6. Child will print the updated shared memory again.
|               7. Child prints exit code.
|
| Required Features Not Included : None
|
| Known Bugs:  None
|
*----------------------------------------------------------------------*/

#include "multiprocessLibrary.h"

const char* INDENTATION[] = {""," ","  ","   ","    ","     ","      ",
                                                        "       "};

/*---void childManipulation(int* shm_ptr, int childNumber, int childrens)---
|
| Function : void childManipulation(int* shm_ptr, int childNumber,
|                                                       int childrens)
|
| Purpose : The purpose of this function is to allow the the child process
|           to manipulate the memoery shared. This method will print
|           information of that specific child.
|           This method will serve as the brain where all the functions
|           of the child will be calculated.
|
| Explanation of Algorithm:
|           - Create an array of characters that is going to be used
|             as a buffer.
|           - Print the child id number.
|           - Print the memory before that children changes it.
|           - In order to alter the information in the shared memory
|             call the function, childCalculations().
|           - Print the alter shared memory, stating what child alter it.
|
| @param: int*, shm_ptr, pointer to the shared memory
| @param: int, childNumber, child index number that is being passed.
| @param: int, childrens, number of arguments from command line that will
|                           become children.
| @return : none
*--------------------------------------------------------------------------*/

void childManipulation(int* shm_ptr, int childNumber, int childrens)
{
   char buffer[BUFFER_SIZE] = ENDOFSTRING;

   sprintf(buffer,"%sChild # %d: starts \n", INDENTATION[childNumber],
                childNumber);
   write(STANDARD_OUTPUT,buffer,strlen(buffer));

   sprintf(buffer, "%sChild # %d: displays private unique ID - %d\n",
                INDENTATION[childNumber], childNumber, childNumber);
   write(STANDARD_OUTPUT, buffer, strlen(buffer));

   childCalculation(shm_ptr, childNumber);
    
   printChildMemoryChange(shm_ptr, childrens, childNumber);

   sprintf(buffer, "%sChild # %d: exits with code %d\n",
                    INDENTATION[childNumber],
                            childNumber, NO_ERRORS);
   write(STANDARD_OUTPUT, buffer, strlen(buffer));

}

/*-- void printChildMemoryChange (int* shm_ptr, int childrens, int childNumber) -
|
| Function : void printChildMemoryChange (int* shm_ptr, int childrens, int
|                                                       childNumber)
|
| Purpose : The purpose of this algorithm is to print the memory of the
|           children.
|
| Explanation of Algorithm:
|
|       There was an initial thought to print the children function in the
|       print memory function of the parent. Now after hundreds of testing
|       of this code, it was noticed that it is important to put everything
|       that will be printed in the buffer first before printing it
|       in the actual standard output. Therefore, sperating the parent
|       from the children becomes quite crucial. The reason why is because
|       both the parent and children have a different initial statement.
|       Therefore, if there individual statements are not saved in the
|       the buffer first, there could be a time when both processes
|       want to send their output to the standard output and things will
|       not show correctly in the console.
|
|       - Create a buffer or array of chars.
|       - Use sprint to add the statement of the children.
|       - Do a for loop to add every element in the initial array
|         of characters.
|       - The write out has to be outside the loop.
|
|  Source to Explain write: http://codewiki.wikidot.com/c:system-calls:write
|
|           Write is a system call that is used to write data out of a buffer
|           The parameters include:
|               - int: the file descriptor to write the output (standard input,
|                       standard output, standard error)
|               - A pointer to a buffer, which will be written to the file
|               - The number of bytes to write
|
| @param: int*, shm_ptr, pointer to the shared memory
| @param: int, childrens, number of arguments from command line that will
|                           become children.
| @return : none
*---------------------------------------------------------------------------*/

void printChildMemoryChange(int* shm_ptr, int childrens, int childNumber)
{
  char buffer[BUFFER_SIZE] = ENDOFSTRING;
  int counter = 0;

   sprintf(buffer,"%sChild # %d: displays shared memory: ",
                                INDENTATION[childNumber],
                                        childNumber, NO_ERRORS);

  for (counter = INITIAL_MEMORY_START; counter <= childrens; counter++)
  {
      char numToString [BUFFER_SIZE] = "";
      sprintf(numToString, "%d ", shm_ptr[counter]);
      strcat(buffer, numToString);

  }
  strcat(buffer, "\n");
  write(STANDARD_OUTPUT,buffer,strlen(buffer));

}

/*---------void childCalculation(int *shm_ptr, int childIDNumber)-----------
|
| Function : void childCalculation(int *shm_ptr, int childIDNumber)
|
| Purpose : The purpose of this function is to do the calculations of the
|           numbers that are going to be changed in the shared memory.
|
| Explanation of Algorithm:
|           - Create an array of characters that is going to be used
|             as a buffer.
|           - Multiply the number in shared memory by TWO or (2).
|           - Multiply that new number by its child id number again (index).
|           - Put the statement shown as the buffer in order to print.
|
| @param: int*, shm_ptr, pointer to the shared memory
| @param: int, childIDNumber, child index number that is being passed.
| @return : none
*--------------------------------------------------------------------------*/

void childCalculation(int *shm_ptr, int childIDNumber)
{
   char buffer[BUFFER_SIZE] = ENDOFSTRING;
   shm_ptr[childIDNumber] = shm_ptr[childIDNumber] * TWO;
   shm_ptr[childIDNumber] = shm_ptr[childIDNumber] * childIDNumber;
   sprintf(buffer, "%sChild # %d: updates shared memory \n",
                INDENTATION[childIDNumber],childIDNumber);
   write(STANDARD_OUTPUT, buffer, strlen(buffer));

}


/*--void display_child_info(int childrens, int pidsNum[], int childStatus[])---
|
| Function : void display_child_info(int childrens, int pidsNum[], int
|                                       childStatus[])
|
| Purpose : This method loop through the arrays of the pidsNum and
|              childStatus. This is done at the end of the process to
|              inform the user the status and child pids.
|
| Explanation of Algorithm:
|           - Loop through all children, and print their pidsNum and
|               exit status
|
| @param : int, childrens, the number of children process
| @param : int[], pidsNum, and array with all the pids of children
|                           processes stored.
| @param: int[], childStatus, an array of the status of all children
| @return : none
*--------------------------------------------------------------------------*/

void display_child_info(int childrens, int pidsNum[], int childStatus[])
{
  int counter = 0;

  printf("%s\n\n", "Parent: displays all child PID & exit codes - at end");
  for (counter = INITIAL_MEMORY_START; counter <= childrens;
                        counter++)
  {
       printf("%sChild with PID %d exited with exit code %d\n",
                                INDENTATION[CHILDEXITCODESTAP],
                                                    pidsNum[counter],
                                                        childStatus[counter]);
  }

}
