#Variables
CC= gcc
CFLAGS = -Wall -Wextra
TARGET = program
OBJS = weekfive.o weeksix.o weekseven.o


# .PHONY tells makefile that all and clean are recipes not actual rules
.PHONY: all clean

#target: dependecies                <- This holistically is a rule
#	recipe 														<- This holistically is a recipe

all: $(TARGET)

program: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# % is a wildcard, which means any alphanumeric characters that end of with .c and .o
# $< means everything on the right hand side of : in target and $@ everything on the left hand side of : in target
# It only chooses the OBJS because program relies on OBJS and OBJS relies on .c files, so implicitly '%.o: %.c' says
# .o files in OBJS depend on its equivalents that end in .c, and the system does the magic of finding it for us
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)