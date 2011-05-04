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
	./tools/build_msg.py test_messages.msg
