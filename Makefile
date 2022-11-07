#
# 'make'        build executable file 'fed'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# For clean on different OS
ifeq ($(OS),Windows_NT)
    #Windows
	RM = del
else
    #Linux
	RM = rm
endif

# define any compile-time flags
CFLAGS = -Wall -g

# define the C source files
SRCS = fed.c utils.c commands/add.c commands/help.c commands/ls.c commands/clean.c commands/cd.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = fed

.PHONY: clean

all: $(MAIN)
	@echo  Simple compiler named 'fed' has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) *.o commands\*.o $(MAIN).exe $(MAIN)


# DO NOT DELETE THIS LINE -- make depend needs it