
// GraphicsView.cpp : CGraphicsView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Graphics.h"
#endif

#include "GraphicsDoc.h"
#include "GraphicsView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CGraphicsView::OnDDALine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32772, &CGraphicsView::OnMidline)
	ON_COMMAND(ID_32773, &CGraphicsView::OnBresenham)
END_MESSAGE_MAP()

// CGraphicsView ����/����

CGraphicsView::CGraphicsView()
{
	// TODO: �ڴ˴���ӹ������
	col_black = RGB(0,0,0);
	col_red = RGB(255,0,0);
	col_blue = RGB(0, 0, 255);
}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGraphicsView ����

void CGraphicsView::OnDraw(CDC* /*pDC*/)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGraphicsView ��ӡ


void CGraphicsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicsView ���

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsView ��Ϣ�������


void CGraphicsView::OnDDALine()
{
	// TODO: �ڴ���������������
	flag = 1;
	Invalidate();
}


void CGraphicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDC();
	CView::OnLButtonDown(nFlags, point);
	p1_x = point.x;
	p1_y = point.y;
}


void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);
	p2_x = point.x;
	p2_y = point.y;
	switch(flag)
	{
	case 1:
		DDAline(p1_x, p1_y, p2_x, p2_y);
		break;
	case 2:
		Midline(p1_x, p1_y, p2_x, p2_y);
		break;
	case 3:
		Bresenhamline(p1_x, p1_y, p2_x, p2_y);
		break;
	}
}


void CGraphicsView::DDAline(int B_x, int B_y, int E_x, int E_y){
	//CWnd* pMainWnd = AfxGetMainWnd();
	CDC * pDC = GetDC();
	pDC->TextOut(450, 18, _T("DDA���߷��ɹ���"));
	float x, y, dx, dy, k, _k;
	float xm, ym;
	dx = E_x - B_x;
	dy = E_y - B_y;
	k = dy / dx;
	_k = dx / dy;
	x = E_x; xm = B_x;
	y = E_y; ym = B_y;

	if(abs(dx) > abs(dy))
	{
		if(B_x <= E_x){ x = B_x; xm = E_x; y = B_y; ym = E_y; }
		for(x; x <= xm; x++)
		{
			pDC->SetPixel(x, (int)(y+0.5), col_black);
			y += k;
		}
	}
	else
	{
		if(B_y <= E_y){ x = B_x; xm = E_x; y = B_y; ym = E_y; }
		for(y; x <= ym; x++)
		{
			pDC->SetPixel((int)(x+0.5), y, col_black);
			x += k;
		}
	}
}

void CGraphicsView::OnMidline()
{
	// TODO: �ڴ���������������
	flag = 2; 
	Invalidate();
}


void CGraphicsView::Midline(int B_x, int B_y, int E_x, int E_y){
	CDC *pDC = GetDC();
	pDC->TextOut(450, 18, _T("�е㻭�߷��ɹ��ˣ�"));
	int a, b, d1, d2, d, x, y;
	int dx, dy, num;
	int p, p1, q, q1;
	x = B_x; y = B_y;
	a = B_y - E_y;
	b = E_x - B_x;
	dx = abs(B_x - E_x);
	dy = abs(B_y - E_y);
	if(((E_x - B_x >= 0) && (E_y - B_y < 0)) ||((E_x - B_x <= 0) && (E_y - B_y > 0)))
	{
		if((E_x - B_x <= 0) && (E_y - B_y > 0))
		{
			a = -a; b = -b; x = E_x; y = E_y;
		}
		if(dx >= dy)
		{
			num = dx;
			p = 1; p1 = 0; q = 1; q1 = -1;
			d = 2 * a - b; d2 = 2 * a; d1 = 2 * (a - b);
		}
		else
		{
			num = dy; 
			p = 1; p1 = -1; q = 0; q1 = -1; 
			d = a - 2 * b; d1 = -(2 * b); d2 = 2 * (a - b);
		}
	}
	else
	{
		if ((E_x - B_x <= 0) && (E_y - B_y < 0)) 
		{
			a = -a; b = -b; x = E_x; y = E_y;
		}
		if(dx >= dy)
		{
			num = dx; 
			p = 1; p1 = 1; q = 1; q1 = 0; 
			d = 2 * a + b; d1 = 2 * a; d2 = 2 * (a + b);
		}
		else
		{
			num = dy; 
			p = 0; p1 = 1; q = 1; q1 = 1; 
			d = 2 * b + a; d2 = 2 * b; d1 = 2 * (a + b);
		}
	}
	pDC->SetPixel(x, y, col_red);

	for(int i = 0; i <= num; i++)
	{
		if (d < 0) 
		{ 
			x += p; y += p1; d += d2;
		} 
		else 
		{ 
			x += q; y += q1; d += d1; 
		} 
		pDC->SetPixel(x, y, col_red);
	}
}

void CGraphicsView::OnBresenham()
{
	// TODO: �ڴ���������������
	flag = 3;
	Invalidate();
}


void CGraphicsView::Bresenhamline(int B_x, int B_y, int E_x, int E_y)
{
	int dx = abs(E_x - B_x);
	int dy = abs(E_y - B_y);
	int x = B_x;
	int y = B_y;
	int stepX = 1;
	int stepY = 1;
	CDC *pDC = GetDC();
	pDC->TextOut(450, 18, _T("Bresenham���߷��ɹ��ˣ�"));
	if(B_x > E_x)
		stepX = -1;
	if(B_y > E_y)
		stepY = -1;

	if(dx > dy)
	{
		int e = dy * 2 - dx;
		for(int i = 0; i <= dx; i++)
		{
			pDC->SetPixel(x, y, col_blue);
			x += stepX;
			e += dy;
			if(e >= 0)
			{
				y += stepY;
				e -= dx;
			}
		}
	}
	else
	{
		int e = 2 * dx - dy;
		for(int i = 0; i <= dy; i++)
		{
			pDC->SetPixel(x, y, col_blue);
			y += stepY;
			e += dx;
			if(e >= 0)
			{
				x += stepX;
				e -= dy;
			}
		}
	}
}