# include directories
INCLUDES = -I../../../src


# library paths
LIBS = -L../../../external/lib/linux -L../../../lib  -lmtksockets  -lmtksupport -lyaml  -lrt



# compiler options
include ../../../compopt_make  #si es de depuración, las opciones de compilación serán -O0 -g y definirá la macro VALGRIND



SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





default: $(EXECS)
	#make -C fb
	#make -C components
	#make -C clicompo
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


#connectthis.exe : connectthis.cpp
#	$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@

#.PHONY : test
#test:
#	make -C fb

#test: tcp_socket1.exec