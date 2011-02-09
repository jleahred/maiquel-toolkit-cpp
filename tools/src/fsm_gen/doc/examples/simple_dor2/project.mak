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
LIBS = -L./mtk/lib -lmtksupport -lyaml  -lrt
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
	for f in `find . -type f -regex '.*\.h$$\|.*\.cpp$$\|.*\.impl$$\|.*\.fsm$$\|.*\.msg$$\|.*\makefile$$\|.*\.mak$$'` ; do cat $$f | sed 's/[ \t]*$$//' > temp.rms; mv -f temp.rms $$f;  done
