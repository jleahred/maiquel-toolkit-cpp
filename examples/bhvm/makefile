# include directories
INCLUDES = -I../../src


# library paths
LIBS = -L../../external/lib/linux -L../../lib  -lmtksupport -lyaml  -lrt




# compiler options
include ../../compopt_make




SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





default: bhvmt.exec
	cat program.hellt  | ./dhp hellt_compiler.rules | ./bhvmt.exec
	rm -f *.exec
	echo "FIN"

test : default



.PHONY : debug
debug: 
	echo $(EXECS)
	echo $(SRCS_CXX)



play: bhvmt.exec



bhvmt.exec : bhvmt.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@




.PHONY : clean
clean: 
	rm -f *.exec




