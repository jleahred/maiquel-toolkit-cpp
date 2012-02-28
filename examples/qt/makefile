.PHONY : default
default:
	@echo  choose a target   test, 






.PHONY : test
test:
	rm -rf temp; mkdir -p temp; cd temp; mkdir -p bin; cd bin; qmake ../../monitor/src/monitor.pro; make; ./monitor
	rm -rf temp; mkdir -p temp; cd temp; mkdir -p bin; cd bin; qmake ../../ex_cont_widget/src/ex_cont_widget.pro; make; ./ex_cont_widget
	rm -rf temp; mkdir -p temp; cd temp; mkdir -p bin; cd bin; qmake ../../ex_min_qt/src/ex_min_qt.pro; make; ./ex_min_qt
	rm -rf temp; mkdir -p temp; cd temp; mkdir -p bin; cd bin; qmake ../../ex_send_order/src/ex_send_order.pro; make; cd ..; cp -r ../ex_send_order/etc . ; ./bin/ex_send_order etc/config.cfg

