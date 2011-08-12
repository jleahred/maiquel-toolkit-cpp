#
# Output...
OUT = bin/ct__prodinfo_grant
#
#
# Directories with source code
DIR_SRC_CXX = src src/db
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
	@echo "make doc"
	@echo "--------------"
	@echo "it will compile de adoc files..."
	@echo
	@echo
	@echo
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


.PHONY : doc
doc:
	mkdir -p doc
	a2x --verbose -d book --icons --dblatex-opts "-T native -P doc.pdfcreator.show=0 -P doc.collab.show=0 -P latex.output.revhistory=0 -P doc.toc.show=1 -P table.title.top" -f pdf  -D doc/ src/tree_server_cfg.adoc



