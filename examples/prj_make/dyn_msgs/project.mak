#
# Output...
OUT = bin/ct__dyn_msgs
#
#
# Directories with source code
DIR_SRC_CXX = src
#
#
# library paths
LIBS = -L./mtk/external/lib/linux -L./mtk/lib -lmtk_components -lmtksupport -lyaml -lmtk_qpid -lqpidclient -lqpidmessaging
#
#
# include directories
INCLUDES = -I./src -I./mtk/src



.PHONY : default__
default__:  default
	@echo "make msg"
	@echo "--------------"
	@echo "it will compile de messages files..."
	@echo
	@echo
	@echo
	@echo




.PHONY : msg
msg:
	find . -name '*.msg' | xargs python tools/build_msg.py

