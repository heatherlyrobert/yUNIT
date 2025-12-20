

single () {

   ./${1}_munit    --list
   cat ${1}.murun  | head --lines=1

   ./${1}_munit
   cat ${1}.murun  | tail --lines=2

}

printf "./master.sh unit-testing script ŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽ\n\n"
single "yUNIT_base"
single "yUNIT_scrp"
single "yUNIT_share"
single "yUNIT_reuse"
single "yUNIT_cond"
single "yUNIT_step"
single "yUNIT_ditto"
single "yUNIT_spec"
single "yUNIT_disp"
single "yUNIT_stats"
single "yUNIT_actual"
single "yUNIT_final"
single "yUNIT_wave"
printf "end-of-execution.  done, finito, completare ŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽŽ\n"



