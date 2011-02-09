.PHONY : default
default:
	@echo  choose a target   test, 






.PHONY : test
test:
	find . -name *.exec | xargs rm -f
	make -C onefile/ test
	make -C hp/      test
	make -C bhvm/    test
	make -C hell/    test
	make -C prj_make/    test
	make -C qt/ test
