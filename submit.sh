#########################################################################
# File Name: submit.sh
# Author: HouJP
# mail: houjp1992@gmail.com
# Created Time: 三  9/16 21:58:46 2015
#########################################################################
# !/bin/bash

git add ./
git commit -m "add "`date +%Y/%m/%d`
git push -u acm_bc master
