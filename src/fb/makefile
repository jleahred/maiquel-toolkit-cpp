# Directories with source code
DIR_SRC_CXX = .



# library paths
#LIBS = -L../../mtk/external/lib/tibco/libLinux   -ltibrvcpp64 -ltibrv64


# include directories
INCLUDES = -I..





# Output...
OUT = ../../lib/libmtkfirebird.a




# compiler options
include ../../compopt_make


# compiler flags (-g -O2 -Wall)
CXXFLAGS = -O2 -Wall

# linker flags
LDFLAGS = -O2








## ---------------------------------------------------------



# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))


# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), ../../temp/$(notdir $(file)))



# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))



## ---------------------------------------------------------

.PHONY: default
default: 
	@echo choose a target    lib, clean...


lib: $(OUT)



.PHONY : clean
clean:
	rm -f $(OBJS_CXX)


.PHONY : debug
debug:
	@echo $(VPATH);





../../temp/%.o: %.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) -o $@ $<


$(OUT): $(OBJS_CXX)
	ar rcs   $(OUT) $(OBJS_CXX)



