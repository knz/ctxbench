#! /bin/sh
for i in $(find . -perm +0111|grep -v git); do for j in 1 2 3; do $i 200000; done; done
