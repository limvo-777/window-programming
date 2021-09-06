// drawText.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "drawText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에	
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//




// CdrawTextApp

BEGIN_MESSAGE_MAP(CdrawTextApp, CWinApp)
END_MESSAGE_MAP()


// CdrawTextApp 생성

CdrawTextApp::CdrawTextApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CdrawTextApp 개체입니다.

CdrawTextApp theApp;


// CdrawTextApp 초기화

BOOL CdrawTextApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#pragma data_seg("jedi_area")
int count = 200; // 전역
#pragma data_seg()

// 함수호출규약 
// dll로 활용할 함수에 대한 선언
extern "C" __declspec(dllexport)

/*
라이브러리
textout : 글씨 출력 - 함수
함수 내에서 글씨 출력 - 출력 권한 필요 (DC - 출력 핸들을 얻어옴)
DC - 출력하게 해주는 도구
APP - 핸들링하는 최상위 클래스
*/

void TextOutDLL(CDC * pDC, CPoint point)
{
	//static int count = 1;
	CString string;
	string.Format(L"(%d, %d) Count : %d", point.x, point.y, count++);

	//화면 출력
	pDC->TextOut(point.x, point.y, string);

}