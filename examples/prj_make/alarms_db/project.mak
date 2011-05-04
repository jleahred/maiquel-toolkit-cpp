#
# Output...
OUT = bin/ct__alarms_db
#
#
# Directories with source code
DIR_SRC_CXX = src
#
#
# library paths
LIBS = -L./mtk/external/lib/linux -L./mtk/lib -lmtk_components -lmtkfirebird -lmtksupport -lyaml -lmtk_qpid -lqpidclient -lqpidmessaging -lfbclient64
#
#
# include directories
INCLUDES = -I./src -I./mtk/src


.PHONY : default__
default__:  default
	@echo "make doc"
	@echo "--------------"
	@echo "it will compile the adoc file..."
	@echo
	@echo
	@echo
	@echo


.PHONY : doc
doc:
	a2x --verbose -d book --icons --dblatex-opts "-T native -P doc.pdfcreator.show=0 -P doc.collab.show=0 -P latex.output.revhistory=0 -P doc.toc.show=1 -P table.title.top" -f pdf  -D doc/ src/alarms_db.adoc



