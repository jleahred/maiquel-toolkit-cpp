# Directories with source code
DIR_SRC_CXX = .



# library paths
#LIBS =



# compiler options
include ../../compopt_make




# Output...
OUT = ../../lib/libmtkhell.a

# include directories
INCLUDES = -I..






## ---------------------------------------------------------



# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))

# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), ../../temp/$(notdir $(file)))


# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))


## ---------------------------------------------------------



default: all



all:  lib clean



lib: $(OUT)






.PHONY : clean
clean:
	rm -f $(OBJS_CXX)



../../temp/%.o: %.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) -o $@ $<


$(OUT): $(OBJS_CXX)
	ar rcs $(OUT) $(OBJS_CXX)



.PHONY : debug
debug:
	@echo $(SRCS_CXX);
	@echo $(VPATH);
	@echo $(OBJS_CXX);
