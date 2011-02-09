# Include directories
INCLUDES = -I../../../../src


# library paths
LIBS = -L../../../../lib  -lmtksupport -lyaml  -lrt


# compiler options
include ../../../../compopt_make



SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





default: $(EXECS)
	#make -C components
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



.PHONY : testing
testing:
	@echo nothing now
