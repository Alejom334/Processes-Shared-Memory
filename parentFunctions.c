/*--------------------------------------------------------------------
|   Source code:  parentFunctions.c
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
|                               copied between line.
|
|               RUN AFTER COMPILATION NOT USING MAKEFILE:
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
| Description of source file:
|
|               This description will be based only on the soruce file of
|               parentFunctions.c. This source file as the name entails,
|               will have all the functions that the parent will execute in
|               the main. The parent will request memory, it will attach the
|               memory, populate the memory, print the memory when it is
|               necessary to print it, then the most important function of the
|               child will be to fork the multiprocesses that will manipulate
|               the shared memory. Please recall that all those functions that
|               will manipulate the shared memory will be in the source file
|               childFunctions.c.
|               After all manipulations are done within the shared memory the
|               parent will detached from the shared memory and remove.
|
|       Input:  There is not a defined input for this source file as every
|               function will need specific inputs. An explanation of what
|               each function requires is in the documentation of every
|               function.
|
|      Output:  There is not a defined output for this source file. The main
|               will show the interaction between the parent and the children.
|
|     Process:
|               1. Parent request memory.
|               2. Parent attaches memory.
|               3. Parent populates memory.
|               4. Parent prints memory.
|               5. Parents forks all necessary child process.
|               6. Parent waits until all children are done.
|               7. Parent prints the changed shared memory.
|               8. Parent detaches the memory.
|               9. Parent removes the memory.
|               10. Parent finishes.
|
| Required Features Not Included : None
|
| Known Bugs:  None
|
*----------------------------------------------------------------------*/

#include "multiprocessLibrary.h"

/*---------------------- int requestMemory() ------------------------------
|   Function int requestMemory()
|
|   Purpose:  This function will request for a shared memory segment
|               with the funciton shmget().
|
|   Explanation: This method ask for a shared memory segment with
|                the first line of code shmget() from libraries
|                <sys/ipc.h> and <sys/shm.h>. These libraries
|                are located in the header file multiprocessLibrary.h
|
|    Source:
|    http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmget.html
|
|               According to the following source the input parameters of
|               this method are as follows:
|
|               IPC_PRIVATE - The key of the segment. This is the
|                               numeric key to be assigned to the
|                               returned share memory segemnt.
|
|               SIZE * sizeof(int) - This is the size of the requested
|                               memory. The constant SIZE is 4 as the
|                               header file states.
|
|               IPC_CREAT | ANY_CLIENT - This is the flag. The purpose
|                               of the flag is to specify the way that the
|                               shared memory will be used.
|                               IPC_CREAT | 0666 grants read and write access
|                               to any client.
|
|               The return value of the function shmget is either the ID of
|               the segment of memory or a negative value if the operation
|               of request of memory was not successful. If the case is not
|               successful, the program will terminate properly. Otherwise,
|               it returns the sucessful integer id.
|
|    @param  None
|
|    @return  int, shm_id, the shared memory ID.
*---------------------------------------------------------------------------*/

int requestMemory()
{
   printf("%s\n", "Parent: requests shared memory");

   int shm_id = shmget(IPC_PRIVATE, SIZE * sizeof(int), IPC_CREAT|ANY_CLIENT);

   if (shm_id < SUCCESFUL_MEM_REQUEST)
   {
      puts("Parent: shmget error...");
      exit(ERROR);
   }

   printf("%s\n", "Parent: receives shared memory");
   return shm_id;
}

/*---------------------- int* attachMemory(int shm_id) -----------------------
|   Function int* attachMemory(int shm_id)
|
|   Purpose:  The purpose of this function is to return a pointer to the
|               starting address of the shared memory space if it happens
|               to be successful.
|
|   Explanation: This function uses the function shmat() from the libraries
|               <sys/ipc.h> and <sys/shm.h>. These libraries
|                are located in the header file multiprocessLibrary.h.
|                The purpose of this function have the address of the shared
|                memory and attach it to whatever the caller happens to be.
|
|    Source:
|    http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmat.html
|
|               According to the following source the input parameters of
|               this method are as follows:
|
|               shm_id - shared memory id
|
|               NULL - Character pointer
|
|               ATTACHMENT_FLAG (0) - Access Flag; note this shared memory
|               is attached as a read only memory.
|
|               The shmat() accepts a shared memory ID and attaches the
|               indictaed shared memory to the program's address space.
|
|               As the return value of shmat() is a void pointer, the
|               algorithm will cast it in order to an integer pointer.
|
|               However, in order to not have any warning for the
|               conversion from void pointer to int pointer; we cast it
|               to long in the third statement of this function. It can
|               be shown as:
|
|               if ((long) shm_ptr == NO_MEMORY)
|
|               Explanation: If this statement is left as
|                   if ((int) shm_ptr == NO_MEMORY), the compiler will
|                   throw the following error:
|                   Warning: cast from pointer to integer of different
|                           size.
|                   For this reason, it was casted as (long), this
|                   process was suggested by Professor Feild.
|
|               If the return value of the shmat() is negative, then it
|               means there was an error finding a pointer that points
|               to that mempry ID.
|
|    @param  int, shm_id, shared memory ID
|
|    @return  int*, shm_ptr, integer pointer to the attached memory.
*---------------------------------------------------------------------------*/

int* attachMemory(int shm_id)
{
  int *shm_ptr = NULL;

  shm_ptr = (int*) shmat(shm_id, NULL, ATTACHMENT_FLAG);
  if ((long) shm_ptr == NO_MEMORY)
  {
     puts("*** Shmat error (server). No connection to shared memory! ***");
     exit(ERROR);
  }

  printf("%s\n", "Parent: attaches shared memory");

  return shm_ptr;

}

/*--------------void detachFromSharedMemory (int* shm_ptr)---------------------
| Function :  void detachFromSharedMemory (int* shm_ptr)
|
| Purpose :    This function receives a pointer that holds the address of the
|              shared memory and calls a function shmdt to detached the shared
|              memory. It must be mentioned that after the call of this
|              function the shared memory still exits in memory and the
|              pointer can eventually be reattached.
|
| Explanation: This function uses the function shmdt() from the libraries
|               <sys/ipc.h> and <sys/shm.h>. These libraries
|               are located in the header file multiprocessLibrary.h.
|               The purpose of this function is to detached the pointer from
|               the memory space.
|
|   Source:   http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmdt.html
|
|           According to this source, after a shared memory is detached, it
|           cannot be used. However, it is still there and can be re attached
|           back to a process's address space. A different address can be
|           attached.
|
|           The only parameter that this function receives is the pointer or
|           shared memory address returned by shmat(), in the function of
|           attaching the memory at the beginnig of the program.
|
|           If the dettached operation fails, then the returned function
|           value is non-zero.
|
|           Recall that the information from the last two paragraphs comes from
|           the source stated above.
|
| @param  int* , shm_ptr, a pointer to the shared memory
| @return : none
*-----------------------------------------------------------------------------*/

void detachFromSharedMemory (int* shm_ptr)
{
  shmdt(shm_ptr);

  printf("%s\n", "Parent: detaches shared memory");
}

/*-------------------void removeSharedMemory (int shm_id)----------------------
| Function :  void removeSharedMemory (int shm_id)
|
| Purpose :    This function receives the memory id from the shared memory, it
|               then calls the function schmctl() to remove the memory
|
| Explanation: This function uses the function schmctl() from the libraries
|               <sys/ipc.h> and <sys/shm.h>. These libraries
|               are located in the header file multiprocessLibrary.h.
|               The purpose of this function is to remove the shared memory.
|
|   Source:   http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmdt.html
|
|           According to this source, these are the following parameters that
|           this function will receive:
|               - shm_id the id of the memory
|               - IPC_RMID a remove operation
|               - NULL
|
| @param  int* , shm_ptr, a pointer to the shared memory
| @return : none
*-----------------------------------------------------------------------------*/

void removeSharedMemory (int shm_id)
{
  shmctl(shm_id, IPC_RMID, NULL);

  printf("%s\n", "Parent: removes shared memory.");

}


/*---------------------------void parentFinishes ()----------------------
| Function :  void parentFinishes ()
|
| Purpose :    This function will be printed when the parent has removed the
|               shared memory.
|
| Explanation: This function was done to not have print statements in the main
|               and do not have this print statement in any other procedure
|               that could not be executed.
|
| @param  : none
| @return : none
*-----------------------------------------------------------------------------*/

void parentFinishes()
{
  printf("%s\n", "Parent: finished");
}

/*----populateMemory(char *validInput[], int* shm_ptr, int childrens)-----------
| Function : populateMemory(char *validInput[], int* shm_ptr, int childrens)
|
| Purpose : The purpose of this function is populate the shared memory with the
|           indexes of the children.
|
| Explanation of Algorithm:
|
|           Initialize counter and validateNum to 0. Do a counter that starts
|           at 0 and the constant INITIAL_MEMORY_START (1).
|
|           We start the counter at INITIAL_MEMORY_START or (1) because we want
|           to start at index one for the first children and move one with the
|           index matching the number of the children to facilitate the
|           calculations.
|
|           Then the loop iterates through the share memory storing the input
|           numbers.
|
|           Note that the input is accepted as a string that is changed to an
|           int with the function atoi.
|
|  Source to Explain Atoi: DD - C How To Program 8th Edition
|
|    The C library function int atoi(const char *str) converts the string
|    argument str to an integer (type int).
|
| @param: char*[], validInput, array of strings coming from the command
| @param: int*, shm_ptr, pointer to the shared memory
| @param: int, childrens, number of arguments from command line that will
|                           become children.
| @return : none
*----------------------------------------------------------------------------*/
void populateMemory(char *validInput[], int* shm_ptr, int childrens)
{
   char buffer[BUFFER_SIZE] = ENDOFSTRING;
   int counter = 0;
   int validatedNum = 0;
   for (counter = INITIAL_MEMORY_START; counter <= childrens; counter++)
   {
      validatedNum = atoi(validInput[counter]);
      shm_ptr[counter] = validatedNum;
   }

   sprintf(buffer,"Parent: fills shared memory\n");
   write(STANDARD_OUTPUT,buffer,strlen(buffer));

   sprintf(buffer,"Parent: displays initial shared memory ");
   write(STANDARD_OUTPUT,buffer,strlen(buffer));

   printMemory(shm_ptr, childrens);

   sprintf(buffer,"\n");
   write(STANDARD_OUTPUT,buffer,strlen(buffer));

}

/*---------------void printMemory(int* shm_ptr, int childrens)----------------
|
| Function : void printMemory(int* shm_ptr, int childrens)
|
| Purpose : The purpose of this function is to print the updated shared
|           memory.
|
| Explanation of Algorithm:
|
|      - A char array was created to act as buffer. This is a very beneficial
|         tool to use with the write function. As we have many children
|         working at the same time, we need to print the memory shared
|         as soon as this function is called.
|      - Function receives a pointer to the shared memory and the number of
|         all children.
|      - Then a loop iterates through all elements of the shared function
|        each element appends it a char array that is inside the loop
|        using the sprintf function.
|      - Use the function strcat to concatenate both strings.
|      - According to the book; DD - C How to Program 8th Edition, page 349
|        strcat is defined as follows:
|               Appends string s2 to array s1. The first character of s2
|               overwrites the terminating null character of s1. The value
|               of s1 is returned.
|      - The reasoning behind using strcat was that as we are having several
|        processes, we want to make sure that the whole memory is stored in
|        the buffer before it actually is sent to the standard output to be
|        printed. This was not the initial thought as the write function
|        was inside the loop, but doing several tries it was noticed that
|        the output in the screen would not shown correctly as we have
|        different processes running at the same time.
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
void printMemory(int* shm_ptr, int childrens)
{
  char buffer[BUFFER_SIZE] = ENDOFSTRING;
  int counter = 0;

  for (counter = INITIAL_MEMORY_START; counter <= childrens; counter++)
  {
        char numToString [BUFFER_SIZE] = "";
        sprintf(numToString, "%d ", shm_ptr[counter]);
        strcat(buffer, numToString);

  }
  write(STANDARD_OUTPUT,buffer,strlen(buffer));

  sprintf(buffer,"\n");
  write(STANDARD_OUTPUT,buffer,strlen(buffer));

}

/*---------void multiforking (int childrens, int* shm_ptr)-----------------
|
| Function : void multiforking (int childrens, int* shm_ptr)
|
| Purpose : The purpose of this function is to create multiprocesses. All the
|           multiprocess will be children from the parent. Other functions
|           will be called from here for each children to manipulate each
|           index of the memory.
|
| Explanation of Algorithm:
|           - Loop through the share memory from INITIAL_MEMORY_START as (1)
|             until the total number of children.
|           - Fork everytime you loop; when you fork a child process is
|               created.
|           - If the child process is successfully created then the
|               forkNumber will be equal to 0. If the child process
|               fails then it returns a value that is less than 0, and
|               the execution the program will print that the child was not
|               successfully created.
|           - In this if statement we will get the pid of the child and
|               will also call the function childManipulation.
|           - We have to exit after the childManipulation is called.
|             This will prevent the system from creating grandchildren.
|
|  Source to Explain Fork:
|        http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html
|
|   Explanation of fork() and the exit function:
|
|      Fork creates a copy of the parent. That means the whole code is
|       duplicated. Even if the code of this whole program is designed
|       for the child to do child calculations, you need to terminate
|       these processes as soon as the child does all the required
|       calculations. The reason why is because as it was previously
|       stated, fork creates a copy of the whole code, and therefore
|       you do not want the child to do anything that the parent
|       actually needs to do. Here the exit function comes very handy.
|       The exit is a system call which terminate the current
|       process.
|
|       According to the book DD 8th edition C How to Program, the
|       function exit is defined as:
|           Exit causes a program to terminate immediately. The function
|           is used to terminate a program when an input error is
|           detected, or when a file to be processed by the program
|           cannot be opened.
|       In our implementation of the exit function, we can measure if the
|       our child process was successful or not according to the return
|       of the exit. A return value of zero or NO_ERROR, signals that
|       all is well. Nonzero values or ERROR, signals abnormal situations.
|
| @param: int, childrens, number of arguments from command line that will
|                           become children.
| @param: int*, shm_ptr, pointer to the shared memory
| @return : none
*---------------------------------------------------------------------------*/

void multiforking (int childrens, int* shm_ptr)
{
   pid_t forkNumber = 0;
   int counter = 0;
   char buffer[BUFFER_SIZE] = ENDOFSTRING;

   sprintf(buffer,"Parent: forks (each and every) child process\n\n");
   write(STANDARD_OUTPUT,buffer,strlen(buffer));

   for (counter = INITIAL_MEMORY_START; counter <= childrens; counter++)
   {
     forkNumber = fork();

     if (forkNumber == CHILD_SUCCESS)
     {
        int child_id = getpid();
        childManipulation(shm_ptr,counter, childrens);
        exit(NO_ERROR);

     }

     else if(forkNumber < CHILD_SUCCESS)
     {
        printf("\n%s\n", "Parent: Failed to fork a children.");
        exit(ERROR);
     }
   }
}

/*-- void wait_for_child(int childrens, int pidsNum[], int childStatus[]) --
|
| Function : void wait_for_child(int childrens, int pidsNum[],
|                                               int childStatus[])
|
| Purpose : This method waits for all children to get executed,
|            before the parent is done. The reason to do this is
|            because if the wait() method is not called is possible
|            for the parent to finish the process before all child
|            processes finsih their execution.
|
| Explanation of Algorithm:
|           - Create an array of characters to be used as buffer.
|           - Loop through the number of child processes we have
|             calling the function wait.
|           - The wait function takes the address of the child in the
|             memory address and returns its pid.
|           - As the function loops thorugh all the child process
|             the parent waits until all the process are completed.
|           - Use the write function as necessary with the given
|             buffer.
|
| @param : int, childrens, the number of children process
| @param : int[], pidsNum, and array with all the pids of children
|                           processes stored.
| @param: int[], childStatus, an array of the status of all children
| @return : none
*--------------------------------------------------------------------------*/

void wait_for_child(int childrens, int pidsNum[], int childStatus[])
{
   char buffer[BUFFER_SIZE] = ENDOFSTRING;
   int counterIndex = 0;

   for(counterIndex = INITIAL_MEMORY_START; counterIndex <= childrens;
                        counterIndex++)
   {
        pidsNum[counterIndex] = wait(&childStatus[counterIndex]);
   }

   sprintf(buffer, "\nParent: waits for (each) and every child\n");
   write(STANDARD_OUTPUT, buffer, strlen(buffer));

   sprintf(buffer, "Parent: detects (each) child completion \n\n");
   write(STANDARD_OUTPUT, buffer, strlen(buffer));
}

/*------- parentDisplaysFinalMemory(int* shm_ptr, int childrens) -------------
|
| Function : void parentDisplaysFinalMemory(int* shm_ptr, int childrens)
|
| Purpose : Parent will call the print memory function to print the final
|           memory.
|
| @param: int*, shm_ptr, pointer to the shared memory
| @param: int, childrens, number of arguments from command line that will
|                           become children.
| @return : none
*----------------------------------------------------------------------------*/

void parentDisplaysFinalMemory(int* shm_ptr, int childrens)
{
  char buffer[BUFFER_SIZE] = ENDOFSTRING;
    
  sprintf(buffer,"\nParent: displays final shared memory - ");
  write(STANDARD_OUTPUT,buffer,strlen(buffer));
    
  printMemory(shm_ptr, childrens);

}

