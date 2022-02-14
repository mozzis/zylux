// RepInfoList.cpp : implementation file
//

#include "stdafx.h"
#include "sk.h"
#include "RepInfoList.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepInfoList

CRepInfoList::CRepInfoList() : m_adjustedcols(false)
{
}

CRepInfoList::~CRepInfoList()
{
}


BEGIN_MESSAGE_MAP(CRepInfoList, CCheckListBox)
	//{{AFX_MSG_MAP(CRepInfoList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepInfoList message handlers

void CRepInfoList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CCheckListBox::DrawItem(lpDrawItemStruct);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT item = lpDrawItemStruct->itemID;

	if (((LONG)item >= 0) &&
		((int)item < m_info.GetSize()) &&
		(lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)))
	{
		int col_width = 75;
		CRect rect = lpDrawItemStruct->rcItem;

		// Adjust cols
		if ((item == 0) && !m_adjustedcols)
		{
			m_adjustedcols = true;

			CPoint point(rect.left, 0);
			CWnd* view = GetParent();
			CWnd *label;
			CRect lrect;

			ClientToScreen(&point);
			view->ScreenToClient(&point);

			// col 1
			label = view->GetDlgItem(IDC_STATIC1_COL1);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}

			// col 2
			point.x += col_width;
			label = view->GetDlgItem(IDC_STATIC1_COL2);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			label = view->GetDlgItem(IDC_STATIC2_COL2);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}

			// col 3
			point.x += col_width;
			label = view->GetDlgItem(IDC_STATIC1_COL3);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			label = view->GetDlgItem(IDC_STATIC2_COL3);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}

			// col 4
			point.x += col_width;
			label = view->GetDlgItem(IDC_STATIC1_COL4);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}

			// col 5
			point.x += col_width;
			label = view->GetDlgItem(IDC_STATIC1_COL5);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			label = view->GetDlgItem(IDC_STATIC2_COL5);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}

			// col 6
			point.x += col_width;
			label = view->GetDlgItem(IDC_STATIC1_COL6);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			label = view->GetDlgItem(IDC_STATIC2_COL6);
			if (label)
			{
				label->GetWindowRect(lrect);
				view->ScreenToClient(lrect);
				label->SetWindowPos(NULL, point.x, lrect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
		}

		if (GetCheck(item) == 1)
		{
			int cyItem = GetItemHeight(item);
			BOOL fDisabled = !IsWindowEnabled() || !IsEnabled(item);

			COLORREF newTextColor = fDisabled ?
				RGB(0x80, 0x80, 0x80) : GetSysColor(COLOR_WINDOWTEXT);  // light gray
			COLORREF oldTextColor = pDC->SetTextColor(newTextColor);

			COLORREF newBkColor = GetSysColor(COLOR_WINDOW);
			COLORREF oldBkColor = pDC->SetBkColor(newBkColor);

			if (newTextColor == newBkColor)
				newTextColor = RGB(0xC0, 0xC0, 0xC0);   // dark gray

			if (!fDisabled && ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0))
			{
				pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
			}

			if (m_cyText == 0)
				VERIFY(cyItem >= CalcMinimumItemHeight());

			// column width
			CString strText;
			RepInfo& rep_info = m_info[item];

			// Draw integral
			rect.left += col_width;
			if (rep_info.m_integral >= 0)
			{
				strText.Format("%ld", rep_info.m_integral);
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText, strText.GetLength(), NULL);
			}

			// Draw peak height
			rect.left += col_width;
			if (rep_info.m_peak >= 0)
			{
				strText.Format("%ld", rep_info.m_peak);
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText, strText.GetLength(), NULL);
			}

			// Draw peak at
			rect.left += col_width;
			if (rep_info.m_peaktime >= 0)
			{
				strText = SCFormatDeciseconds(rep_info.m_peaktime);
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText,
					strText.GetLength(), NULL);
			}

			// Draw time of half max
			rect.left += col_width;
			if (rep_info.m_halfrise >= 0)
			{
				strText = SCFormatDeciseconds(rep_info.m_halfrise);
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText,
					strText.GetLength(), NULL);
			}
			else if (rep_info.m_halfrise == -2)
			{
				strText = "N/A";
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText,
					strText.GetLength(), NULL);
			}

			// Draw time of max decay
			rect.left += col_width;
			if (rep_info.m_halfdecay >= 0)
			{
				strText = SCFormatDeciseconds(rep_info.m_halfdecay);
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText,
					strText.GetLength(), NULL);
			}
			else if (rep_info.m_halfdecay == -2)
			{
				strText = "N/A";
				pDC->ExtTextOut(rect.left,
					rect.top + max(0, (cyItem - m_cyText) / 2),
					ETO_OPAQUE, &(rect), strText,
					strText.GetLength(), NULL);
			}

			pDC->SetTextColor(oldTextColor);
			pDC->SetBkColor(oldBkColor);
		}
	}
}

void CRepInfoList::SetInfo(int rep, long integral, long peak, int peak_time, int half_rise, int half_decay)
{
	m_info.SetAtGrow(rep, RepInfo(integral, peak, peak_time, half_rise, half_decay));
}

void CRepInfoList::SetInfo(int rep, RepInfo& rep_info)
{
	m_info.SetAtGrow(rep, rep_info);
}

RepInfo& CRepInfoList::GetInfo(int rep)
{
	if ((rep >= 0) &&
		(rep < m_info.GetSize()))
	{
		return m_info[rep];
	}
	else
	{
		return RepInfo();
	}
}

void CRepInfoList::AdjustSize()
{
	int count = GetCount();
	if (count > 0)
	{
		CRect rect;
		GetWindowRect(rect);
		SetWindowPos(NULL, 0, 0, rect.Width(), count * GetItemHeight(0) + 4,
			SWP_NOZORDER | SWP_NOMOVE);
	}
}
