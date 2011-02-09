# Directories with source code
DIR_SRC_CXX = .




# library paths
#LIBS =







# Output...
OUT = ../../lib/libyaml.a

# include directories
INCLUDES = -I.. -I.



#compiler options
include ../../compopt_make


# compiler flags (-g -O2 -Wall)  (overriding)
CXXFLAGS = -O2
CFLAGS = -O2












## ---------------------------------------------------------



# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))


# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), ../../temp/$(notdir $(file)))



# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))



## ---------------------------------------------------------



default: all



all:  prepare lib clean



lib: $(OUT)




.PHONY : prepare
prepare:
	mkdir -p ../../temp

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
