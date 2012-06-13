# VERSION 1.1   2010-03-17
# VERSION 1.0   2009-11-16



include project.mak



include mtk/compopt_make









## ---------------------------------------------------------


LINE2COMPRESS =	zip  -R copy '*.cpp' '*.h' '*.c' '*.txt' makefile compopt_make* project.mak '*.a' '*.hpp' '*.bld' '*.so' '*.cfg' '*.ini'

LINE2UNCOMPRESS = unzip copy.zip


# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))


# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), temp/$(notdir $(file)))



# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))




## ---------------------------------------------------------


.PHONY : default
default:
	@echo
	@echo
	@echo
	@echo "make all"
	@echo "--------------"
	@echo "it will compile the mtk library and the program on release mode."
	@echo
	@echo
	@echo "make alldebug"
	@echo "--------------"
	@echo "it will compile the mtk library and the program on debug mode."
	@echo
	@echo
	@echo "make alldebugO2"
	@echo "--------------"
	@echo "it will compile the mtk library and the program on debug mode with performance optimizations O2."
	@echo
	@echo
	@echo "make this"
	@echo "--------------"
	@echo "it will compile the program not the library (the mode will depend of last call  make allxxx)"
	@echo ""
	@echo
	@echo
	@echo "make clean"
	@echo "--------------"
	@echo "it will delete de temp files (objects .o)"
	@echo
	@echo
	@echo "make compress"
	@echo "--------------"
	@echo "it will create a file with the program and library code, Executing next command..."
	@echo
	@echo "${LINE2COMPRESS}"
	@echo
	@echo
	@echo



.PHONY : all
all: clean mtk this


.PHONY : alldebug
alldebug: clean mtk_debug this
	@echo "para probar con valgrind ejecutar... (el rendimiento será muy bajo)"
	@echo "---------------------------------------------------------------------------------"
	@echo 'valgrind --tool=memcheck --leak-check=full  <nombre_programa>  2>  valgrind.txt'
	@echo "---------------------------------------------------------------------------------"

.PHONY : alldebugO2
alldebugO2: clean mtk_debugO2 this
	@echo "para revisar rendimento con valgrind ejecutar..."
	@echo "---------------------------------------------------------------------------------"
	@echo 'valgrind --tool=callgrind <nombre_programa>'
	@echo 'Esto generará un fichero que se puede analizar con kcachevalgrind'
	@echo "---------------------------------------------------------------------------------"



.PHONY : prepare
prepare: 
	mkdir -p bin
	cp $(OUT) $(OUT).old
	mkdir -p temp


this: clean prepare $(OUT)


incremental: $(OUT)


.PHONY : mtk
mtk:
	make -C mtk libs


.PHONY : mtk_debug
mtk_debug:
	make -C mtk libsdebug

.PHONY : mtk_debugO2
mtk_debugO2:
	make -C mtk libsdebugO2


.PHONY : clean
clean:
	rm -f $(OBJS_CXX)


.PHONY : debug
debug:
	@echo $(VPATH);


.PHONY : compress
compress:
	$(LINE2COMPRESS)
	@echo
	@echo
	@echo 'To un compress execute...'
	@echo $(LINE2UNCOMPRESS)
	@echo




temp/%.o: %.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) -o $@ $<


$(OUT): $(OBJS_CXX)
	$(CXX)  $(OBJS_CXX) $(LIBS)  -o $(OUT)





#mtk/compopt_make: mtk/compopt_make.release
#	rm -f mtk/compopt_make
#	ln -s mtk/compopt_make.release  mtk/compopt_make
