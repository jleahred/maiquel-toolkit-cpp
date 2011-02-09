.PHONY : default
default:
	@echo  choose a target   test,






.PHONY : test
test:
	rm -rf temp; mkdir -p temp; cd temp; mkdir bin; cd bin; qmake ../../hpgui/src/hpgui.pro; make; cp hpgui ../../hpgui/bin/.; ./hpgui
	rm -rf temp; mkdir -p temp; cd temp; qmake ../logview/src/logview.pro; make; cp logview ../logview/bin/. ; ./logview

