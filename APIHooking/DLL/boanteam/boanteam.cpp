// boanteam.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "stdio.h"
#include "boanteam.h"


// ������ ������ �����Դϴ�.
BOANTEAM_API int nboanteam=0;

// ������ �Լ��� �����Դϴ�.
extern "C" BOANTEAM_API int fnboanteam(void)
{
	nboanteam++;
	printf("Hello boanteam - count[%d]\n", nboanteam);
	return nboanteam;
}

// ������ Ŭ������ �������Դϴ�.
// Ŭ���� ���Ǹ� ������ boanteam.h�� �����Ͻʽÿ�.
Cboanteam::Cboanteam()
{
    return;
}
