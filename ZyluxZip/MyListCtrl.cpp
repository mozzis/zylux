// Copyright (C) 1998 Mayn Idea Software
// All rights reserved
//////////////////////////////////////////////////////////////////////////
// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// InPlaceEdit.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit window
#define IDC_IPEDIT 101

class CInPlaceEdit : public CEdit
{
  // Construction
public:
	CInPlaceEdit(int iItem, int iSubItem, CString sInitText);
  // Attributes
public:
  // Operations
public:
  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEdit)	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
  //}}AFX_VIRTUAL
  // Implementation
public:	
  virtual ~CInPlaceEdit();	
  // Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEdit)	
  afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
  //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:	
  int m_iItem;	
  int m_iSubItem;	
  CString m_sInitText;
	BOOL    m_bESC;	 	// To indicate whether ESC key was pressed
};



// InPlaceEdit.cpp : implementation file
//

//#include "stdafx.h"
//#include "InPlaceEdit.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit

CInPlaceEdit::CInPlaceEdit(int iItem, int iSubItem, CString sInitText)
:m_sInitText( sInitText )
{
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_bESC = FALSE;
}

CInPlaceEdit::~CInPlaceEdit()
{
}


BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
	//{{AFX_MSG_MAP(CInPlaceEdit)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit message handlers

BOOL CInPlaceEdit::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN
				|| pMsg->wParam == VK_DELETE
				|| pMsg->wParam == VK_ESCAPE
				|| GetKeyState( VK_CONTROL)
				)
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;		    	// DO NOT process further
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}


void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	CString str;
	GetWindowText(str);

	// Send Notification to parent of ListView ctrl
	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
	dispinfo.item.cchTextMax = str.GetLength();

	GetParent()->GetParent()->SendMessage( WM_NOTIFY, GetParent()->GetDlgCtrlID(), 
					(LPARAM)&dispinfo );

	DestroyWindow();
}

void CInPlaceEdit::OnNcDestroy()
{
	CEdit::OnNcDestroy();

	delete this;
}


void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if( nChar == VK_ESCAPE )
			m_bESC = TRUE;
		GetParent()->SetFocus();
		return;
	}


	CEdit::OnChar(nChar, nRepCnt, nFlags);

	// Resize edit control if needed

	// Get text extent
	CString str;

	GetWindowText( str );
	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject( pFont );
	CSize size = dc.GetTextExtent( str );
	dc.SelectObject( pFontDC );
	size.cx += 5;			   	// add some extra buffer

	// Get client rect
	CRect rect, parentrect;
	GetClientRect( &rect );
	GetParent()->GetClientRect( &parentrect );

	// Transform rect to parent coordinates
	ClientToScreen( &rect );
	GetParent()->ScreenToClient( &rect );

	// Check whether control needs to be resized
	// and whether there is space to grow
	if( size.cx > rect.Width() )
	{
		if( size.cx + rect.left < parentrect.right )
			rect.right = rect.left + size.cx;
		else
			rect.right = parentrect.right;
		MoveWindow( &rect );
	}
}

int CInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set the proper font
	CFont* font = GetParent()->GetFont();
	SetFont(font);

	SetWindowText( m_sInitText );
	SetFocus();
	SetSel( 0, -1 );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_nHighlight = HIGHLIGHT_ROW;
}

CMyListCtrl::~CMyListCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

// EditSubLabel		- Start edit of a sub item label
// Returns		- Temporary pointer to the new edit control
// nItem		- The row index of the item to edit
// nCol			- The column of the sub item.
CEdit* CMyListCtrl::EditSubLabel( int nItem, int nCol )
{
	// The returned pointer should not be saved
	// Make sure that the item is visible
	if( !EnsureVisible( nItem, TRUE ) ) 
    return NULL;
	// Make sure that nCol is valid
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if( nCol >= nColumnCount || GetColumnWidth(nCol) < 5 )		
    return NULL;
	// Get the column offset	
  int offset = 0;	
  for( int i = 0; i < nCol; i++ )
		offset += GetColumnWidth( i );	CRect rect;
	GetItemRect( nItem, &rect, LVIR_BOUNDS );
	// Now scroll if we need to expose the column	
  CRect rcClient;
	GetClientRect( &rcClient );
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )	
    {
		CSize size;		size.cx = offset + rect.left;		size.cy = 0;		Scroll( size );
		rect.left -= size.cx;	
    }	
  // Get Column alignment	
  LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;	GetColumn( nCol, &lvcol );	DWORD dwStyle ;
	if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)		
    dwStyle = ES_LEFT;
  else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)		
    dwStyle = ES_RIGHT;
	else dwStyle = ES_CENTER;	rect.left += offset+4;
	rect.right = rect.left + GetColumnWidth( nCol ) - 3 ;
	if( rect.right > rcClient.right) rect.right = rcClient.right;
	dwStyle |= WS_BORDER|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL;
	CEdit *pEdit = new CInPlaceEdit(nItem, nCol, GetItemText( nItem, nCol ));
	pEdit->Create( dwStyle, rect, this, IDC_IPEDIT );	
  return pEdit;
}

// HitTestEx    - Determine the row index and column index for a point
// Returns      - the row index or -1 if point is not over a row
// point        - point to be tested.// col          - to hold the column index
int CMyListCtrl::HitTestEx(CPoint &point, int *col) const
{
  int colnum = 0;        
  int row = HitTest( point, NULL );        
  if( col ) *col = 0;        
//  if( row != -1 )        
//    return row;        

  // Make sure that the ListView is in LVS_REPORT
  if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
    return row;        // Get the top and bottom row visible
  row = GetTopIndex();        
  int bottom = row + GetCountPerPage();
  if( bottom > GetItemCount() )                
    bottom = GetItemCount();
  // Get the number of columns
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  int nColumnCount = pHeader->GetItemCount();
  // Loop through the visible rows        
  for( ;row <=bottom;row++)
    {
    // Get bounding rect of item and check whether point falls in it.
    CRect rect;
    GetItemRect( row, &rect, LVIR_BOUNDS );
    if( rect.PtInRect(point) )                
      {
      // Now find the column
      for( colnum = 0; colnum < nColumnCount; colnum++ )
        {
        int colwidth = GetColumnWidth(colnum);
        if( point.x >= rect.left 
            && point.x <= (rect.left + colwidth ) )
          {
          if( col ) *col = colnum;
            return row;
          }
        rect.left += colwidth;                        
        }
      }
    }        
  return -1;
}

void CMyListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( GetFocus() != this ) SetFocus();
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMyListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( GetFocus() != this ) SetFocus();
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyListCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
  LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
  LV_ITEM	*plvItem = &plvDispInfo->item;	
  if (plvItem->pszText != NULL)	
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);	
//  SortTextItems(0, TRUE);
  *pResult = FALSE;
}

void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	int index;
	CListCtrl::OnLButtonDown(nFlags, point);

	int colnum;
	if( ( index = HitTestEx( point, &colnum )) != -1 )
	{
		UINT flag = LVIS_FOCUSED;
		if( (GetItemState( index, flag ) & flag) == flag && colnum > 0)
		{
			if( GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS )
				EditSubLabel( index, colnum );
		}
		else
      {
			SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED ,
				    	LVIS_SELECTED | LVIS_FOCUSED); 
			if( GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS )
				EditLabel( index);
      }
	}
}

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	int nItem = lpDrawItemStruct->itemID;
	CImageList* pImageList;

	// Save dc state
	int nSavedDC = pDC->SaveDC();

	// Get item image and state info
	LV_ITEM lvi;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetItem(&lvi);

	// Should the item be highlighted
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)
				|| ( (lvi.state & LVIS_SELECTED)
					&& ((GetFocus() == this)
						|| (GetStyle() & LVS_SHOWSELALWAYS)
						)
					)
				);

	// Get rectangles for drawing
	CRect rcBounds, rcLabel, rcIcon;
	GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
	GetItemRect(nItem, rcLabel, LVIR_LABEL);
	GetItemRect(nItem, rcIcon, LVIR_ICON);
	CRect rcCol( rcBounds ); 

	CString sLabel = GetItemText( nItem, 0 );

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;

	CRect rcHighlight;
	CRect rcWnd;
	int nExt;
	switch( m_nHighlight )
	{
	case 0: 
		nExt = pDC->GetOutputTextExtent(sLabel).cx + offset;
		rcHighlight = rcLabel;
		if( rcLabel.left + nExt < rcLabel.right )
			rcHighlight.right = rcLabel.left + nExt;
		break;
	case 1:
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		break;
	case 2:
		GetClientRect(&rcWnd);
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		rcHighlight.right = rcWnd.right;
		break;
	default:
		rcHighlight = rcLabel;
	}

	// Draw the background color
	if( bHighlight )
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
		pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW)));

	// Set clip region
	rcCol.right = rcCol.left + GetColumnWidth(0);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcCol);
	pDC->SelectClipRgn(&rgn);
	rgn.DeleteObject();

	// Draw state icon
	if (lvi.state & LVIS_STATEIMAGEMASK)
	{
		int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
		pImageList = GetImageList(LVSIL_STATE);
		if (pImageList)
		{
			pImageList->Draw(pDC, nImage,
				CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
		}
	}
	
	// Draw normal and overlay icon
	pImageList = GetImageList(LVSIL_SMALL);
	if (pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		pImageList->Draw(pDC, lvi.iImage, 
			CPoint(rcIcon.left, rcIcon.top),
			(bHighlight?ILD_BLEND50:0) | ILD_TRANSPARENT | nOvlImageMask );
	}

	// Draw item label - Column 0
	rcLabel.left += offset/2;
	rcLabel.right -= offset;

	pDC->DrawText(sLabel,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
				| DT_VCENTER | DT_END_ELLIPSIS);


	// Draw labels for remaining columns
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

	if( m_nHighlight == 0 )		// Highlight only first column
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
	}
	
	rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
							rcBounds.right;
	rgn.CreateRectRgnIndirect(&rcBounds);
	pDC->SelectClipRgn(&rgn);
				   
	for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
	{
		rcCol.left = rcCol.right;
		rcCol.right += lvc.cx;

		sLabel = GetItemText(nItem, nColumn);
		if (sLabel.GetLength() == 0)
			continue;

		// Get the text justification
		UINT nJustify = DT_LEFT;
		switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
		{
		case LVCFMT_RIGHT:
			nJustify = DT_RIGHT;
			break;
		case LVCFMT_CENTER:
			nJustify = DT_CENTER;
			break;
		default:
			break;
		}

		rcLabel = rcCol;
		rcLabel.left += offset;
		rcLabel.right -= offset;

		pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE | 
					DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
	}

	// Draw focus rectangle if item has focus
	if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
		pDC->DrawFocusRect(rcHighlight);

	
	// Restore dc
	pDC->RestoreDC( nSavedDC );
}

void CMyListCtrl::RepaintSelectedItems()
{	
  CRect rcBounds, rcLabel;
	// Invalidate focused item so it can repaint 
	int nItem = GetNextItem(-1, LVNI_FOCUSED);	
  if(nItem != -1)	
    {
		GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
		GetItemRect(nItem, rcLabel, LVIR_LABEL);		
    rcBounds.left = rcLabel.left;
		InvalidateRect(rcBounds, FALSE);	
    }
	// Invalidate selected items depending on LVS_SHOWSELALWAYS
	if(!(GetStyle() & LVS_SHOWSELALWAYS))	
    {
		for(nItem = GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))		
      {
			GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
			GetItemRect(nItem, rcLabel, LVIR_LABEL);			
      rcBounds.left = rcLabel.left;
			InvalidateRect(rcBounds, FALSE);		
      } 	
    }	
  UpdateWindow();
}

void CMyListCtrl::OnPaint() 
{
	// in full row select mode, we need to extend the clipping region
	// so we can paint a selection all the way to the right
	if (m_nHighlight == HIGHLIGHT_ROW &&
		(GetStyle() & LVS_TYPEMASK) == LVS_REPORT )	
    {		
    CRect rcBounds;
		GetItemRect(0, rcBounds, LVIR_BOUNDS);		
    CRect rcClient;
		GetClientRect(&rcClient);		
    if(rcBounds.right < rcClient.right)		
      {
			CPaintDC dc(this);			
      CRect rcClip;			
      dc.GetClipBox(rcClip);
			rcClip.left = min(rcBounds.right-1, rcClip.left);
			rcClip.right = rcClient.right;			
      InvalidateRect(rcClip, FALSE);		
      }	
    }
	CListCtrl::OnPaint();
}

void CMyListCtrl::OnKillFocus(CWnd* pNewWnd) 
{	
  CListCtrl::OnKillFocus(pNewWnd);
	// check if we are losing focus to label edit box
	if(pNewWnd != NULL && pNewWnd->GetParent() == this)		
    return;
	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)		
    RepaintSelectedItems();
}

void CMyListCtrl::OnSetFocus(CWnd* pOldWnd) 
{	
  CListCtrl::OnSetFocus(pOldWnd);	
	// check if we are getting focus from label edit box
	if(pOldWnd!=NULL && IsWindow(pOldWnd->m_hWnd) && pOldWnd->GetParent() == this)
    return;
	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK)==LVS_REPORT)		
    RepaintSelectedItems();
}

int CMyListCtrl::SetHighlightType(EHighlight hilite)
{
	int oldhilite = m_nHighlight;
	if( hilite <= HIGHLIGHT_ROW )
	{
		m_nHighlight = hilite;
		Invalidate();
	}
	return oldhilite;
}
  
BOOL CMyListCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~LVS_TYPEMASK;	
  cs.style &= ~LVS_SHOWSELALWAYS;
	cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED;	
  cs.style |= LVS_EDITLABELS;	
	return CListCtrl::PreCreateWindow(cs);
}

// SortTextItems	- Sort the list based on column text
// Returns		- Returns true for success
// nCol			- column that contains the text to be sorted
// bAscending		- indicate sort order
// low			- row to start scanning from - default row is 0
// high			- row to end scan. -1 indicates last row
BOOL CMyListCtrl::SortTextItems( int nCol, BOOL bAscending, int low /*= 0*/, int high /*= -1*/ )
{
	if( nCol >= ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount() )
		return FALSE;

	if( high == -1 ) high = GetItemCount() - 1;

	int lo = low;
	int hi = high;
	CString midItem;

	if( hi <= lo ) return FALSE;

	midItem = GetItemText( (lo+hi)/2, nCol );

	// loop through the list until indices cross
	while(lo <= hi)
	{
		// rowText will hold all column text for one row
		CStringArray rowText;

		// find the first element that is greater than or equal to 
		// the partition element starting from the left Index.
		if( bAscending )
			while(( lo < high ) && (GetItemText(lo, nCol).CompareNoCase(midItem) < 0))
				++lo;
		else
			while( ( lo < high ) && (GetItemText(lo, nCol).CompareNoCase(midItem) > 0))
				++lo;

		// find an element that is smaller than or equal to 
		// the partition element starting from the right Index.
		if( bAscending )
			while( ( hi > low ) && (GetItemText(hi, nCol).CompareNoCase(midItem) > 0))
				--hi;
		else
			while( ( hi > low ) && (GetItemText(hi, nCol).CompareNoCase(midItem) < 0))
				--hi;

		// if the indexes have not crossed, swap
		// and if the items are not equal
		if( lo <= hi )
		{
			// swap only if the items are not equal
			if( GetItemText(lo, nCol) != GetItemText(hi, nCol))
			{
				// swap the rows
				LV_ITEM lvitemlo, lvitemhi;
				int nColCount = 
					((CHeaderCtrl*)GetDlgItem(0))->GetItemCount();
				rowText.SetSize( nColCount );
				int i;
				for( i=0; i<nColCount; i++)
					rowText[i] = GetItemText(lo, i);
				lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
				lvitemlo.iItem = lo;
				lvitemlo.iSubItem = 0;
				lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED | 
						LVIS_FOCUSED |  LVIS_SELECTED | 
						LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;

				lvitemhi = lvitemlo;
				lvitemhi.iItem = hi;

				GetItem( &lvitemlo );
				GetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					SetItemText(lo, i, GetItemText(hi, i));

				lvitemhi.iItem = lo;
				SetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					SetItemText(hi, i, rowText[i]);

				lvitemlo.iItem = hi;
				SetItem( &lvitemlo );
			}
		++lo;
			--hi;
		}
	}

	// If the right index has not reached the left side of array
	// must now sort the left partition.
	if( low < hi )
		SortTextItems(nCol, bAscending , low, hi);

	// If the left index has not reached the right side of array
	// must now sort the right partition.
	if( lo < high )
		SortTextItems(nCol, bAscending , lo, high );

	return TRUE;
}
 
int CMyListCtrl::GetColumnCount()
{     
  // get the header control
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  // return the number of items in it - ie. the number of columns
  return pHeader->GetItemCount();
}

#define MINCOLWIDTH 20

/////////////////////////////////////////////////////////////////////////////
void CMyListCtrl::AutoSizeColumns(int col /*= -1*/)
{
     SetRedraw(false);     
     int mincol = col < 0 ? 0 : col;
     int maxcol = col < 0 ? GetColumnCount()-1 : col;
     for (col = mincol; col <= maxcol; col++) 
       {
       SetColumnWidth(col, LVSCW_AUTOSIZE);
       int wc1 = GetColumnWidth(col);
       SetColumnWidth(col, LVSCW_AUTOSIZE_USEHEADER);
       int wc2 = GetColumnWidth(col);
       int wc = max(MINCOLWIDTH, max(wc1,wc2));
       SetColumnWidth(col,wc);     
       }
    SetRedraw(true);
}
