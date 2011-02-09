.PHONY : default
default: 
	chmod u+x fsm_gen.py
	mkdir -p ../../bin
	echo  '*' > ../../bin/.gitignore
	ln -s -f -t ../../bin ../src/fsm_gen/fsm_gen.gram
	ln -s -f -t ../../bin ../src/fsm_gen/fsm_gen.py
	chmod u+x fsm_gen.py
	make -C doc/examples/  # testing
