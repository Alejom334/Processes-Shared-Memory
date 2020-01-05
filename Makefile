
#===================================================================
#        Name:  Makefile
#      Author:  Alejandro Martinez
#  Student ID:  3625175
#  Assignment:  Assignment # 4 - Poker Stud
#
#      Course:  COP 4337 Programming 3
#     Section:  UO3 1198
#  Instructor:  William Feild
#    Due Date:  October 29, 2019, at the beginning of class
#
#	I hereby certify that this collective work is my own
#	and none of it is the work of any other person or entity.
#
#	Alejandro Martinez
#
#  Compile/Run: This file must be in the same directory as the 
#   			following source/header/executable files: 
#         
#	inputValidationFork.c forkingMain.c parentFunctions.c 
#	childFunctions.c multiprocessLibrary.h SharedProcess.out		
#				
#	To compile execute this file: make build
#
#   To run execute the following command: ./SharedProcess.out # # #
#
# 	As stated in the documentation of forkingMain.c: 
#
#		- Only input seven inputs after the name of 
#	          the executable file
#		- Unique integers from zero to nine are accepted 
#
#		Note: If the input does not meet these requirements 
#	        then an error message will be displayed and the 
#		program will exit.
#---------------------------------------------------------------------
#
# Purpose:
#
# This makefile is made to compile all the source files at once, 
# making it more readable. Also it creates the executable file 
# to run the program.
#
# Sources:
#
# This makefile was created using the online documentation provided 
# in class.
#
# Explanation:
#
# Macros were created to represent the source files, output files 
# and gcc. Three dependencies were created (1) "clean" cleans or 
# removes the executable file, (2) the "build" compiles the file 
# (3) and lastly the compile dependency that cleans and compiles 
# the code.
#--------------------------------------------------------------------- 


CC = gcc

SRC_FILES = inputValidationFork.c forkingMain.c parentFunctions.c childFunctions.c

OUTPUT_FILE = -o SharedProcess.out

clean:
	rm -f *.o core

compile: $(SRC_FILES)
	$(CC) $(SRC_FILES)  $(OUTPUT_FILE)

build: clean compile


