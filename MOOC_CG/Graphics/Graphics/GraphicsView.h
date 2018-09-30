
// GraphicsView.h : CGraphicsView ��Ľӿ�
//

#pragma once


class CGraphicsView : public CView
{
protected: // �������л�����
	CGraphicsView();
	DECLARE_DYNCREATE(CGraphicsView)

// ����
public:
	CGraphicsDoc* GetDocument() const;

// ����
public:
	int p1_x, p1_y, p2_x, p2_y, flag;
	COLORREF col_black;
	COLORREF col_red;
	COLORREF col_blue;
	void DDAline(int B_x, int B_y, int E_x, int E_y);
	void Midline(int B_x, int B_y, int E_x, int E_y);
	void Bresenhamline(int B_x, int B_y, int E_x, int E_y);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGraphicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDDALine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMidline();
	afx_msg void OnBresenham();
};

#ifndef _DEBUG  // GraphicsView.cpp �еĵ��԰汾
inline CGraphicsDoc* CGraphicsView::GetDocument() const
   { return reinterpret_cast<CGraphicsDoc*>(m_pDocument); }
#endif

