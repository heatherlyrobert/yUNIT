#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = yUNIT
# additional standard and outside libraries
LIB_STD    = -lncurses -ltinfo
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lyVAR_debug
# directory for production code, no trailing slash
INST_DIR   = 



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/zeno_make



#===(post-processing)======================================#
# create a rule for...
#remove_post        :
install_post       :
	gcc -c unit_base.c
	gcc -o unit_base  unit_base.o $(OBJ_NORM) $(LIB_STD) $(LIB_MINE)



##================================[[ end-code ]]================================#
