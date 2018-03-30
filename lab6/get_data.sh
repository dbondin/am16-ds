for Y in `seq 2007 2017`
do
    for M in `seq 1 12`
    do
	for D in `seq 1 31`
	do
	    #DAT="31/02/2008"
	    DAT=`printf "%.2d/%.2d/%.4d" $D $M $Y`
	    URL="http://www.cbr.ru/scripts/XML_daily.asp?date_req=$DAT"
	    wget -o /dev/null -O data.xml "$URL"
	    ./parse.sh $DAT < data.xml
	    #exit 1
	done
    done
done
