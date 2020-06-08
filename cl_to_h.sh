#!/bin/bash

INFILE=$1
OUTFILE=$2
TEMPFILE=$2h
VARNAME=$(echo $INFILE | sed 's/\.cl//g')

#echo INFILE $INFILE
#echo OUTFILE $OUTFILE
#echo TEMPFILE $TEMPFILE

#echo $VARNAME

echo const char* $VARNAME = '"\n"\' > $TEMPFILE
sed -e 's/\(.*.\)/\" \1 \\n\"\\/g' $INFILE >> $TEMPFILE
sed '$ s/.$/;/' $TEMPFILE > $OUTFILE
rm $TEMPFILE
