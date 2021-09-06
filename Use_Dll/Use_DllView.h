
// Use_DllView.h: CUseDllView 클래스의 인터페이스
// 출력과 관련된 요소들

#pragma once


class CUseDllView : public CView
{
protected: // serialization에서만 만들어집니다.
	CUseDllView() noexcept;
	DECLARE_DYNCREATE(CUseDllView)

// 특성입니다.
public:
	CUseDllDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CUseDllView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Use_DllView.cpp의 디버그 버전
inline CUseDllDoc* CUseDllView::GetDocument() const
   { return reinterpret_cast<CUseDllDoc*>(m_pDocument); }
#endif

