if [ $# -eq 0 ]

then
	echo "Usage: phone searchfor[...searchfor]"
	echo "(You didn't tell me what you want to search for.)"
else
	cp data tmp
	
	# 인자의 순서에 상관없이 입력된 인자를 모두 갖고 있는 데이터만 출력됨 
	for arg in $*
	do
		egrep "$arg" tmp > result
		cp result tmp
	done 

	rm tmp

	awk -f display.awk result
	rm result
fi
