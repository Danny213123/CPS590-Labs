#!/bin/bash
#sometimes you might get 1 out of these that is not 3036
#if it is 3036, nothing printed. If not, it prints the value
for i in {1..100} ; do 
  echo  "$i. "
  DBserver 2>/dev/null | grep -v "it is 3036" 
done


#Here are results from a recent run of
#/usr/courses/cps590/Programs/race_condition: runDBserver.sh
# I killed it prematurely, but you get the idea: 
#
#1.
#2.
#3.
#4.
#5.
#6.
#7.
#1338291 total_queries should be 3036 and it is 2994
#8.
#9.
#10.
#11.
#12.
#13.
#14.
#15.
#16.
#17.
#18.
#19.
#20.
#21.
#1338325 total_queries should be 3036 and it is 2887
#22.
#23.
#24.
#25.
#26.
#27.
#1338357 total_queries should be 3036 and it is 3010
#28.
#29.
#1338367 total_queries should be 3036 and it is 3021
#30.
#31.
#32.
#33.
#34.
#35.
#36.
#37.
#38.
#39.
#40.
