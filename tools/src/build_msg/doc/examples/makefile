
.PHONY : all
all:
	make -C ex1 build_msg
	make -C ex1 release
	@echo .
	@echo .
	@echo '-----------------------------------------------------'
	@echo .
	cd ex1; ./bin/testing
	@echo .
	@echo '-----------------------------------------------------'
	@echo .
	make -C ex2 build_msg
	make -C ex2 release
	@echo .
	@echo .
	@echo '-----------------------------------------------------'
	@echo .
	cd ex2; ./bin/testing
	@echo .
	@echo '-----------------------------------------------------'
	@echo .
