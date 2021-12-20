CC = g++
target = robot
outputdir = ./output/
objdir = ./obj/
src = $(wildcard ./src/*.cpp)
srcdir = ./src/
source = $(notdir $(src))
obj = $(patsubst %.cpp,$(objdir)%.o,$(source))
inc = ./inc/
CCobj = -I$(inc) -c -o

$(target):$(obj)
	$(CC) $^ -lwiringPi -o $(outputdir)$(target)

$(objdir)%.o:$(srcdir)%.cpp
	$(CC) $< $(CCobj) $@

clean:
	rm $(obj) $(outputdir)$(target)
