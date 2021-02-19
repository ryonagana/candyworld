#!/bin/bash


cp -v tiles.h ../include/tiles.h

shopt -s globstar
files=$(find ./* -type f -name "*.cbmap"  -not -path '*/\.*'  ) 


for d in $files; do
  cp  -v $d ../resources/map
done

shopt -u globstar

