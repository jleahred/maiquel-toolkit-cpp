# include directories
INCLUDES = -I../../../src


# library paths
LIBS = -L../../../lib  -lmtksupport -lyaml -lrt



# compiler options
include ../../../compopt_make





SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%)





default: $(EXECS)
	echo "FIN"


.PHONY : debug
debug: 
	@echo "ejecutables " $(EXECS)
	@echo "fuentes " $(SRCS_CXX)



%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o ../../bin/$@




.PHONY : clean
clean: 
	rm -f *.exec



.PHONY : test
test:

