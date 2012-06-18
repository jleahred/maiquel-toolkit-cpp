#
# Output...
OUT = bin/utibtcp_cli
#
#
# Directories with source code
DIR_SRC_CXX = src
#
#
# library paths
LIBS = -L./mtk/external/lib/linux -L./mtk/lib -lmtksockets -lmtksupport -lyaml  -lrt
#
#
# include directories
INCLUDES = -I./src -I./mtk/src
