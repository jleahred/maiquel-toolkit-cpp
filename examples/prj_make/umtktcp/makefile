

.PHONY: test
test:
	make -C client release
	make -C mono_server release
	mono_server/bin/utibtcp_monoserver & client/bin/utibtcp_cli