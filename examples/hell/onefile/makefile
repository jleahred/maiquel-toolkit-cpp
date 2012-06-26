# include directories
INCLUDES = -I../../../src


# library paths
LIBS = -L../../../lib  -lmtkhell  -lmtksupport -lyaml  -lrt




# compiler options
include ../../../compopt_make



SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





test: $(EXECS)
	echo "FIN"


.PHONY : debug
debug: 
	echo $(EXECS)
	echo $(SRCS_CXX)



%.exec: %.cpp
	@echo $@
	@echo $@ '----------------------------------------------------------------'
	@echo $@ '  lost:-----------------------------------' >&2
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@
	$(VALGRIND) ./$@
	rm -f ./$@



.PHONY : clean
clean: 
	rm -f *.exec


#connectthis.exe : connectthis.cpp
#	$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@

.PHONY : testing
testing:
	make -C fb/ test
