# Output...
OUT = bin/test_calculator




# Directories with source code
DIR_SRC_CXX = src



# library paths
LIBS = -L../../../lib -lmtksupport -lyaml  -lrt


# include directories
INCLUDES = -I./src -I../../../src





# compiler options
include ../../../compopt_make






## ---------------------------------------------------------



# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))


# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), temp/$(notdir $(file)))



# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))



## ---------------------------------------------------------


.PHONY : default
default: all


.PHONY : test
test: all




.PHONY :
all: prepare $(OUT) clean


.PHONY : no_delete_bin
no_delete_bin: $(OUT)



.PHONY : clean
clean:
	rm -f $(OBJS_CXX)
	rm -f $(OUT)


.PHONY : debug
debug:
	@echo $(VPATH);


.PHONY : compress
compress:
	zip  -R copy '*.cpp' '*.h' '*.c' '*.txt' makefile '*.a' '*.hpp' '*.bld' '*.so' '*.cfg' '*.ini'



.PHONY : prepare
prepare :
	mkdir -p bin





temp/%.o: %.cpp
	mkdir temp -p
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) -o $@ $<


$(OUT): $(OBJS_CXX)
	$(CXX)  $(OBJS_CXX) $(LIBS)  -o $(OUT)
	$(OUT)



