.PHONY : default
default:
	@echo  choose a target   libs doc libxxx clean gitzip



allall:  libs qtlibs tools clean doc check_files
#  conviene pasar el test  time (make clean ; make libs ; make qtlibs; make tools) 2> errors.txt

# time make testjustcompile  2> errors.txt
#   time (make testrelease > full_test.txt) 2> errors.txt
#   cat full_test.txt | grep -v '^__NR__:' | grep -v '^del._='  | grep -v ccccc  | grep  -v '^   sum..______'  |  grep  -v '^code:         '  |  grep  -v '^NODE NAME:    '| grep  -v '^[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9] ' | grep -v sess_id:  > test.txt; rm full_test.txt


#  conviene pasar también el test con valgrind  
#  time (make clean; make libsdebug; make qtlibs; make testdebug 2> temp.txt)
#  if no errors on execution, continue
#  cat temp.txt | grep 'lost:' > valgrind.txt ; rm temp.txt
# revisar cat valgrind.txt

#  OLD-----------------------
# conviene pasar también el test con valgrind  make clean ; make libsdebug ; make qtlibs ; make testdebug 2> valgrind.txt
#     esto lo deja configurado con las opciones de compilación de depuración, se pondrán otra vez en release
#          en la llamada a make libs
#     cat valgrind.txt | grep 'lost:'  dará información de la memoria
#     cat valgrind.txt | grep ' possibly lost:'    tiene que salir todo a 0
#  OLD-----------------------

#  y también conviene ejecutar cppcheck
# time (find ./src/ -name *.cpp -or -name *.h -or -name *.hpp | grep -v /mig_liffe/ | grep -v /yaml/ | grep -v /fb/ | xargs cppcheck --all --verbose --style -I src 2> cppcheck.txt)


# revisar las diferencias en los ficheros test.txt valgrind.txt y cppcheck.txt

# para generar una versión nueva...


# make clean; make libs; make qtlibs; make tools; make testrelease

# todavía no... make allall  compilará todo de nuevo en versión release y generará la documentación


# actualizar modificaciones documento adoc
# editar fichero VERSION

# make allall  


#  OLD-----------------------
#               (ctrl-c p para generar doc en muse, 
#               ctrl-c v para visualizar 
#                      hay que copiar la estadística de la versión actual en el histórico)
#  OLD-----------------------

# al final se ejecuta checkfiles y tiene que volver sin error y escribir un 0 (provisionalmente está escribiendo un 1)
# commit en git
# etiquetar la nueva versión en git
# sincronizar con svn






libs : config_release deletelibs libmtksupport libmtksockets  libfirebird libmtkhell libyaml libmtk_qpid libmtk_components cleanlibs 

libsdebug : config_debug deletelibs libmtksupport  libmtksockets  libfirebird libmtkhell libyaml libmtk_qpid libmtk_components cleanlibs

libsdebugO2 : config_debugO2 deletelibs libmtksupport libmtksockets  libfirebird libmtkhell libyaml libmtk_qpid libmtk_components cleanlibs





.PHONY : deletelibs
deletelibs: cleanlibs
	rm lib/*.a -f

.PHONY : libmtksupport
libmtksupport: prepare
	make -C src/support lib

.PHONY : libmtksockets
libmtksockets : prepare
	make -C src/sockets lib


.PHONY : libfirebird
libfirebird: prepare
	make -C src/fb lib

.PHONY : libyaml
libyaml: prepare
	make -C src/yaml lib



.PHONY : libmtkhell
libmtkhell: prepare
	make -C src/hell lib

.PHONY : libmtk_qpid
libmtk_qpid: prepare
	make -C src/mtk_qpid lib

.PHONY : libmtk_components
libmtk_components: prepare
	make -C src/components lib

.PHONY : qtlibs
qtlibs: prepare
	make -C src/qt_components lib


.PHONY : tools
tools : 
	make -C tools




testjustcompile : config_just_compile test_current_config

testrelease : config_release test_current_config

testdebug : config_debug test_current_config

testdebugO2 : config_debugO2 test_current_config




.PHONY : test_current_config
test_current_config : 
	make -C examples/ test
	@echo 'to convert...  iconv --from-code=ISO-8859-1 --to-code=UTF-8 ./oldfile.htm > ./newfile.html'
	@find ./src -type f | grep -v .png | grep -v temp | grep -v doxys | grep -v .git | grep -v '*~' | grep -v '.*o' | grep -v '/bin/' | xargs isutf8
	@find ./examples -type f | grep -v .png | grep -v temp | grep -v doxys | grep -v .git | grep -v '*~'| grep -v '.*o' | grep -v '/bin/' | xargs isutf8



.PHONY : check_files
check_files :
	@echo 'to convert...  iconv --from-code=ISO-8859-1 --to-code=UTF-8 ./oldfile.html > ./newfile.html'
	@find ./src -type f | grep -v .png | grep -v temp | grep -v doxys | grep -v .git | grep -v '*~' | grep -v '.*o' | grep -v '/bin/' | xargs isutf8
	@find ./examples -type f | grep -v .png | grep -v temp | grep -v doxys | grep -v .git | grep -v '*~'| grep -v '.*o' | grep -v '/bin/' | xargs isutf8
	#verificamos si se utilizan contenedores no mtk (no seguros)
	@echo 'we don`t have to use std::containers pending!!!! to reactivate'
	#@find src/components -name '*.h' -or -name '*.cpp' -or -name '*.hpp' | xargs grep -w 'std::map\|std::vector\|std::list' -sl | wc -l




.PHONY : clean
clean: cleanlibs


.PHONY : cleanlibs
cleanlibs:
	make -C src/support clean
	make -C src/sockets clean
	make -C src/fb clean
	make -C src/hell clean
	make -C src/components clean
	make -C src/qt_components clean
	find . -name temp | xargs rm -rf


.PHONY : gitzip
gitzip :
	git archive --format=zip HEAD > gitMTK.zip



.PHONY : prepare
prepare:
	mkdir -p temp

.PHONY : config_release
config_release:
	mkdir -p temp
	rm -f compopt_make
	ln -s compopt_make.release compopt_make

.PHONY : config_debug
config_debug:
	mkdir -p temp
	rm -f compopt_make
	ln -s compopt_make.debug compopt_make


.PHONY : config_debugO2
config_debugO2:
	mkdir -p temp
	rm -f compopt_make
	ln -s compopt_make.debugO2 compopt_make

.PHONY : config_just_compile
config_just_compile:
	mkdir -p temp
	rm -f compopt_make
	ln -s compopt_make.just_compile_release compopt_make



.PHONY : doc
doc:
	mkdir -p doc
	echo '*' > doc/.gitignore
	a2x --verbose -d book --icons --dblatex-opts "-T native -P doc.pdfcreator.show=0 -P doc.collab.show=0 -P latex.output.revhistory=0 -P doc.toc.show=1 -P table.title.top" -f pdf  -D doc/ src/doc.adoc/mtk.adoc
	a2x --verbose -d book -r . --icons --icons-dir adoc.images/icons -f chunked -D doc/ src/doc.adoc/mtk.adoc

	a2x --verbose -d book --icons --dblatex-opts "-T native -P doc.pdfcreator.show=0 -P doc.collab.show=0 -P latex.output.revhistory=0 -P doc.toc.show=1 -P table.title.top" -f pdf  -D doc/   examples/prj_make/emarket/doc/emarket.adoc