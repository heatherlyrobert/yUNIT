#*============================----beg-of-source---============================*#

#*---(current variables)--------------*#
BASE    = yUNIT

#*---(standard variables)-------------*#
COMP    = gcc -c -std=gnu89 -g -pg -Wall -Wextra
INCS    =
LINK    = gcc
LIBS    = -lyVAR_debug
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
PRINTF  = @printf


all                : ${BASE}.so.1.0


${BASE}.so.1.0     : ${BASE}.o
	${PRINTF} "\n#---((make dynamic version))--------------\n"
	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1  ${LIBS}  -o lib${BASE}.so.1.0  ${BASE}.o

${BASE}.o          : ${BASE}.h ${BASE}.c
	${PRINTF} "\n#---((compile source code))---------------\n"
	${COMP}  -fPIC ${INCS} ${BASE}.c



#*---(utilities)----------------------*#
bigclean           :
	${PRINTF} "\n#---((remove swap files))-----------------\n"
	${CLEAN}  '.'*.sw?

clean              :
	${PRINTF} "\n#---((remove working files))--------------\n"
	${CLEAN}  *.o
	${CLEAN}  *~
	${CLEAN}  temp*
	${CLEAN}  lib${BASE}.so.1.0
	${CLEAN}  lib${BASE}.a

remove             :
	${PRINTF} "\n#---((remove existing version))-----------\n"
	${CLEAN} /usr/local/lib/lib${BASE}*
	${CLEAN} /usr/local/include/${BASE}*
	${CLEAN} /usr/local/sbin/${BASE}_gen.awk
	${CLEAN} /usr/local/sbin/uUNIT
	_lib      -d  ${BASE}
	ldconfig

install            :
	${PRINTF} "\n#---((install current version))-----------\n"
	@sha1sum   lib${BASE}.so.1.0
	_lib -s ${BASE}
	_inst --sbin yUNIT_gen
	_inst --sbin uUNIT
	ldconfig
	rm -f     /usr/share/man/man3/${BASE}.3.bz2
	cp -f     ${BASE}.3    /usr/share/man/man3/
	bzip2     /usr/share/man/man3/${BASE}.3
	chmod     0644  /usr/share/man/man3/${BASE}.3.bz2

#*============================----end-of-source---============================*#
