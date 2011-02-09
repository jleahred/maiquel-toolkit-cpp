#
# Output...
OUT = bin/testing
#
#
# Directories with source code
DIR_SRC_CXX = .
#
#
# library paths
LIBS = -L./mtk/lib -lmtksupport -lyaml -lmtk_qpid -lqpidclient -lqpidmessaging -lqpidtypes
#
#
# include directories
INCLUDES = -I. -I./mtk/src



.PHONY : _def
_def:  default
	@echo "make build_msg"
	@echo "--------------"
	@echo "it will compile all the *.msg in current directory and nested"
	@echo
	@echo
	@echo




.PHONY : build_msg
build_msg:
	find . -name '*.msg' | xargs python tools/build_msg.py
    #./tools/build_msg.py test_messages.msg
	for f in `find . -type f -regex '.*\.h$$\|.*\.cpp$$\|.*\.impl$$\|.*\.fsm$$\|.*\.msg$$\|.*\makefile$$\|.*\.mak$$'` ; do cat $$f | sed 's/[ \t]*$$//' > temp.rms; mv -f temp.rms $$f;  done
