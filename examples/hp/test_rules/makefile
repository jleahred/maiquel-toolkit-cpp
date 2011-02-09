# Include directories
INCLUDES = -I../../../src


# library paths
LIBS = -L../../../lib  -lmtksupport


# compiler options
include ../../../compopt_make




SRCS_CXX = $(wildcard *.cpp)
EXECS = $(SRCS_CXX:%.cpp=%.exec)





default: $(EXECS)
	# primero sin parámetros
	./prog_trans_from_file.exec
	# luego ejecutar cargando ficheros de reglas
	./prog_trans_from_file.exec test_rules.txt test_input.txt test_input.txt
	# una última prueba desde cin
	cat test_input.txt | ./prog_trans_from_file.exec test_rules.txt
	for f in test_i*.txt; do cat $$f | ./prog_trans_from_file.exec test_rules.txt ; done
	# prueba de reglas (están en directorios)
	@for d in $$(find . -type d |grep -v '^\.$$') ; do cat $$d/*input.txt | ./prog_trans_from_file.exec $$d/*rules.txt ; echo -------------------------; echo . ; done
	rm -f *.exec
	echo "FIN"


.PHONY : debug
debug: 
	echo $(EXECS)
	echo $(SRCS_CXX)



%.exec: %.cpp
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $<  $(LIBS) -o $@



.PHONY : clean
clean: 
	rm -f *.exec



.PHONY : test
test:
	@echo nothing now
