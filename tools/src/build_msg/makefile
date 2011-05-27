.PHONY : default
default: 
	chmod u+x build_msg.py
	mkdir -p ../../bin
	echo  '*' > ../../bin/.gitignore
	ln -s -f -t ../../bin ../src/build_msg/build_msg.gram
	ln -s -f -t ../../bin ../src/build_msg/build_msg.py
	ln -s -f -t ../../bin ../src/build_msg/msg_analysis.py
	chmod u+x build_msg.py
	make -C doc/examples/  # testing
