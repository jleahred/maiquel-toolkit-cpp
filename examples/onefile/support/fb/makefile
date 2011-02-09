# include directories
INCLUDES = -I../../../src


# library paths
LIBS = -L../../../external/lib/linux -L../../../lib  -lidtfirebird -lfbclient64 -lidtsoporte


# compiler options
include ../../../compopt_make



SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





default: $(EXECS)
	echo "FIN"


test : default


.PHONY : debug
debug: 
	echo $(EXECS)
	echo $(SRCS_CXX)



%.exec: %.cpp
	@echo $@ '----------------------------------------------------------------'
	@echo $@ '  lost:-----------------------------------' >&2
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@
	$(VALGRIND) ./$@
	rm -f ./$@



.PHONY : clean
clean: 
	rm -f *.exec

