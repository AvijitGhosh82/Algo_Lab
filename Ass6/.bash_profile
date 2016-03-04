#!/bin/bash
 
# This script gets a random available cow with `cowsay -l` and prints some text, default fortune
 
FORTUNE="fortune"
 
for COWNAME in `cowsay -l | tail -n +2`
do
COWS+=$COWNAME
COWS+='\n'
done
COWS=${COWS%??}
RANDOMCOW=$(echo -e $COWS | sort -R | head -n 1)
$FORTUNE | cowsay -f $RANDOMCOW