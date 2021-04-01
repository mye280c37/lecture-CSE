if [ $# -eq 0 ]
then
	echo "Usage: phone searchfor[...searchfor]"
	echo "(You didn't tell me what you want to search for.)"
else
	for arg in $*

	# 연속될 필요는 없으나 인자들이 순서대로 데이터에 존재하는 경우에만 출력됨
	do
		args+=".*"
		args+=$arg
	done

	egrep -i "$args" data | awk -f display.awk
fi
