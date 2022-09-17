#!bin/sh

INFILE="../ex03/hh_positions.csv"
OUTFILE="hh_uniq_positions.csv"

head -n 1 INFILE > $OUTFILE

tail -n 20 $INFILE \
| awk \
'BEGIN
{
	FS=",";
	OFS=",";
}
{
	print $3;
}' \
| uniq -c \
| awk \
'BEGIN
{
	OFS=","
}
{
	print $2, $1;
}' \
| sort -k2 >> $OUTPUT_FILE
