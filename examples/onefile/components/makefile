default: 
	make -C support/
	make -C admin/
	make -C trading/
	make -C acs/
	make -C yaml/
	make -C fb/
	echo "FIN"


.PHONY : test
test:  default



.PHONY : clean
clean: 
	make -C trading/ clean
	make -C support/ clean
	make -C admin/   clean
	make -C acs/   clean
	make -C yaml/  clean


