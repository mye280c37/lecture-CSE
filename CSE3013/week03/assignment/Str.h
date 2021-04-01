#include <string.h>

class Str{
	private:
		char *str; // string 내용
		int len; // string 길이
	public:
		Str(int leng); // string 길이로 인스턴스 생성
		Str(char *neyong); // string 내용으로 인스턴스 생성
		~Str();
		int length(void); // string 길이를 리턴하는 함수
		char *contents(void); // string의 내용을 리턴하는 함수
		int compare(class Str& a); // a의 내용과 문자열 비교(strcmp)
		int compare(char *a);// a와 문자열 비교(strcmp)
		void operator=(char *a);// string 값을 대입
		void operator=(class Str& a);// Str의 내용을 대입
};

