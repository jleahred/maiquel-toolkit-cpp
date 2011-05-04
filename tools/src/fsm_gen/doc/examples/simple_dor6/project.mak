#
# Output...
OUT = bin/testing
#
#
# Directories with source code
DIR_SRC_CXX = . generated
#
#
# library paths
LIBS = -L./mtk/lib -lmtksupport  -lyaml
#
#
# include directories
INCLUDES = -I. -I./mtk/src



.PHONY : _def
_def:  default




.PHONY : fsm
fsm:
	mkdir -p generated
	./tools/fsm_gen.py simple_dor.fsm
