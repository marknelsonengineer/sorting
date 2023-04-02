#!/bin/bash

function partition {
	let i=$2-1
	let pivot=$((${randomList[$3]}))

	for(( j="$2"; j<"$3"; j++ ))
	do
		if [ "${randomList[$j]}" -lt "$pivot" ]
		then
			let i=i+1
			let temp=${randomList[$i]}
			randomList[$i]=${randomList[$j]}
			randomList[$j]=$temp
		fi
	done

	let temp=${randomList[$((i+1))]}
	randomList[$((i+1))]=${randomList[$3]}
	randomList[$3]=$temp

	k=$((i+1))
}


function quicksort {
	if [ "$2" -lt "$3" ]
	then
		partition randomList $2 $3
		let pi=k
		quicksort randomList $2 $((pi-1))
		quicksort randomList $((pi+1)) $3
	fi
}


function doRun {
	randomList=()
	
	for ((i=0;i<$1;i++))
	do
		randomList+=($RANDOM)
	done

	start=$(date +%s%N)
	quicksort randomList 0 $1
	end=$(date +%s%N)
	echo "$1: $(($(($end-$start))/1000000)) ms"

#	for i in "${randomList[@]}"
#	do
#		echo "$i"
#	done
}



echo "Quicksort"

for i in {2..32}
do
	let n=$((2**i))
	doRun $n
done
