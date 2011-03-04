default: 
	make -C support/
	make -C admin/
	make -C trading/
	echo "FIN"


.PHONY : test
test:  default



.PHONY : clean
clean: 
	make -C trading/ clean
	make -C support/ clean
	make -C admin/   clean


