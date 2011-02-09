#
# Output...
OUT = bin/emarket
#
#
# Directories with source code
DIR_SRC_CXX = src
#
#
# library paths
LIBS = -L./mtk/external/lib/linux -L./mtk/lib -lmtk_components -lmtksupport -lmtk_qpid -lqpidclient
#
#
# include directories
INCLUDES = -I./src -I./mtk/src


.PHONY : default__
default__:  default
	@echo "make fsm"
	@echo "--------------"
	@echo "it will compile de fsm files..."
	@echo
	@echo
	@echo
	@echo "make msg"
	@echo "--------------"
	@echo "it will compile de messages files..."
	@echo
	@echo
	@echo
	@echo


.PHONY : fsm
fsm:
	find . -name '*.fsm' | xargs python tools/fsm_gen.py


.PHONY : msg
msg:
	find . -name '*.msg' | xargs python tools/build_msg.py
