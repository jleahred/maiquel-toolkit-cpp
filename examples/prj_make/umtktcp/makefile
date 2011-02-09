

.PHONY: test
test:
	make -C client this
	make -C mono_server this
	mono_server/bin/utibtcp_monoserver & client/bin/utibtcp_cli 