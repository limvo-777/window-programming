
// Use_DllView.cpp: CUseDllView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Use_Dll.h"
#endif

#include "Use_DllDoc.h"
#include "Use_DllView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUseDllView

IMPLEMENT_DYNCREATE(CUseDllView, CView)

BEGIN_MESSAGE_MAP(CUseDllView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUseDllView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CUseDllView 생성/소멸

CUseDllView::CUseDllView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CUseDllView::~CUseDllView()
{
}

BOOL CUseDllView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CUseDllView 그리기

void CUseDllView::OnDraw(CDC* /*pDC*/)
{
	CUseDllDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CUseDllView 인쇄


void CUseDllView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUseDllView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CUseDllView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CUseDllView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CUseDllView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUseDllView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUseDllView 진단

#ifdef _DEBUG
void CUseDllView::AssertValid() const
{
	CView::AssertValid();
}

void CUseDllView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUseDllDoc* CUseDllView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUseDllDoc)));
	return (CUseDllDoc*)m_pDocument;
}
#endif //_DEBUG


// CUseDllView 메시지 처리기

// 선언 -> header
extern "C" __declspec(dllimport) void TextOutDLL(CDC * pDC, CPoint point);


// 정의 -> cpp /c -> DLL
void CUseDllView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	
	CClientDC dc(this);
	TextOutDLL(&dc, point);
	CView::OnLButtonDown(nFlags, point);
}
