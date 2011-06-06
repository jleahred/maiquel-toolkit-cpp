
# Directories with source code

DIR_SRC_CXX = . trading trading/accounts  prices admin gen acs acs/cli acs/serv fb  
DIR_SRC_C = 



# library paths
#LIBS = 


# compiler options
include ../../compopt_make



# Output...
OUT = ../../lib/libmtk_components.a

# include directories
INCLUDES = -I../











## ---------------------------------------------------------



# getting the source files
SRCS_CXX = $(foreach dir, $(DIR_SRC_CXX), $(wildcard $(dir)/*.cpp))
SRCS_C = $(foreach dir, $(DIR_SRC_C), $(wildcard $(dir)/*.c))

# source to objects
OBJS_CXX = $(foreach file,$(SRCS_CXX:%.cpp=%.o), ../../temp/$(notdir $(file)))
OBJS_C = $(foreach file,$(SRCS_C:%.c=%.o), ../../temp/$(notdir $(file)))


# preparing VPATH
VPATH =  $(foreach dir, $(DIR_SRC_CXX), $(dir))
VPATH += $(foreach dir, $(DIR_SRC_C), $(dir))


## ---------------------------------------------------------



default: all



all:  prepare lib clean



lib: prepare $(OUT)
	#make -C trading/ lib
	#make -C prices/ lib




.PHONY : prepare
prepare:
	rm $(OUT) -f
	mkdir -p ../../temp
	find . -name '*.msg' | xargs python tools/build_msg.py
	find . -name '*.fsm' | xargs python tools/fsm_gen.py


.PHONY : clean
clean:
	rm -f $(OBJS_CXX) $(OBJS_C)



../../temp/%.o: %.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) -o $@ $<

../../temp/%.o: %.c
	$(CC) -c $(INCLUDES) $(CFLAGS) -o $@ $<

$(OUT): $(OBJS_CXX) $(OBJS_C)
	ar rcs $(OUT) $(OBJS_CXX)  $(OBJS_C)



.PHONY : debug
debug:
	@echo $(SRCS_CXX);
	@echo $(SRCS_C);
	@echo $(VPATH);
	@echo $(OBJS_CXX);
	@echo $(OBJS_C);
