// boanteam.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "stdio.h"
#include "boanteam.h"


// 내보낸 변수의 예제입니다.
BOANTEAM_API int nboanteam=0;

// 내보낸 함수의 예제입니다.
extern "C" BOANTEAM_API int fnboanteam(void)
{
	nboanteam++;
	printf("Hello boanteam - count[%d]\n", nboanteam);
	return nboanteam;
}

// 내보낸 클래스의 생성자입니다.
// 클래스 정의를 보려면 boanteam.h를 참조하십시오.
Cboanteam::Cboanteam()
{
    return;
}
