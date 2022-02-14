// ProtocolGridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolGridWnd.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#import "xl5en32.olb" rename_namespace("XL95") rename("DialogBox", "DialogBoxXL")

CString CProtocolGridWnd::SendToExcel95(LPCTSTR macroname, LPCTSTR workbookname,
		LPCTSTR worksheetname, WORD cell_col, WORD cell_row)
{
	CString error_str;

	using namespace XL95;

	bool macro_valid = (macroname && (strlen(macroname) > 0)) ? true : false;
	bool workbook_valid = (workbookname && (strlen(workbookname) > 0)) ? true : false;
	bool worksheet_valid = (worksheetname && (strlen(worksheetname) > 0)) ? true : false;

	WorksheetPtr pSheet;
	bool sheet_used = false;

	ApplicationPtr pXL;

	try
	{
		bool i_started_excel = false;
		char ole_str[] = "Excel.Application.5";
		try
		{
			if (FAILED(pXL.GetActiveObject(ole_str)))
			{
				pXL.CreateInstance(ole_str);
				i_started_excel = true;
			}
		}
		catch(_com_error&)
		{
			pXL.CreateInstance(ole_str);
			i_started_excel = true;
		}

		// Get a handle of the Workbooks collection
		WorkbooksPtr pBooks = pXL->Workbooks();

		// Try to open the user's personal workbook,
		// if I started Excel
		if (macro_valid && i_started_excel)
		{
			CString startup_path((LPCTSTR)(_bstr_t)pXL->StartupPath);
			CFileFind finder;
			BOOL bWorking = finder.FindFile(startup_path + "\\*.xls");
			CString xls_name;
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				xls_name = finder.GetFilePath();
				try
				{
					pBooks->Open((LPCTSTR)xls_name);
				}
				catch(_com_error&)
				{
					SetFocus();
					CString err_str("Unable to open your startup workbook in Excel (TM) 95.\n\n");
					SCMessageBox(err_str + xls_name);
				}
			}
		}

		WorkbookPtr pBook;
		bool book_found = false;
		bool create_book = false;
		if (workbook_valid)
		{
			// See if user's workbook is already loaded
			long i;
			for (i = 1; i <= (long)pBooks->GetCount(); i++)
			{
				pBook = pBooks->Item(i);
				_bstr_t fullname = pBook->FullName;
				_bstr_t wbpathname(workbookname);
				if (fullname == wbpathname)
				{
					book_found = true;
					break;
				}
			}
			if (!book_found)
			{
				// Workbook was not already loaded, so try to open it
				try
				{
					pBook = pBooks->Open(workbookname);
					book_found = true;
				}
				catch(_com_error&)
				{
					SetFocus();
					CString err_str("Unable to open workbook in Excel (TM) 95.\n\n");
					err_str += workbookname;
					err_str += "\n\nWould you like to create the workbook?";
					if (SCMessageBox(err_str, MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						create_book = true;
					}
				}
			}
		}
		if (!book_found)
		{
			// Add a new workbook and get a handle to it
			pBook = pBooks->Add((long)xlWorksheet);
			book_found = true;
			if (create_book)
			{
				_variant_t opt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				pBook->SaveAs(workbookname, opt, opt, opt, opt, opt, opt, opt);
			}
		}

		if (book_found)
		{
			SheetsPtr pSheets = pBook->Worksheets();
			bool sheet_found = false;
			if (worksheet_valid)
			{
				// See if user's worksheet already exists
				long i;
				for (i = 1; i <= (long)pSheets->GetCount(); i++)
				{
					pSheet = pSheets->Item(i);
					_bstr_t name = pSheet->Name;
					_bstr_t wsname(worksheetname);
					if (name == wsname)
					{
						sheet_found = true;
						sheet_used = true;
						break;
					}
					pSheet->Release();
				}
				if (!sheet_found)
				{
					// Worksheet did not already exist, so try to create it
					try
					{
						pSheet = pSheets->Add();
						pSheet->Name = worksheetname;
						sheet_found = true;
						sheet_used = true;
					}
					catch(_com_error&)
					{
						SetFocus();
						CString err_str("Unable to create worksheet in Excel (TM) 95.\n\n");
						SCMessageBox(err_str + worksheetname);
					}
				}
			}
			if (!sheet_found)
			{
				// Get a handle to the first Worksheet in the new Workbook
				pSheet = ((WorksheetsPtr)pBook->Worksheets())->Item(1L);
				sheet_used = true;
				sheet_found = true;
			}

			if (sheet_found)
			{
				// Determine how many rows we can send
				ROWCOL rows = GetRowCount() + 1;
				ROWCOL cols = GetColCount();
				if (rows > 65536)
				{
					// Oops, Excel only supports 65536 rows
					rows = 65536;
				}
				if (cols > 256)
				{
					// Oops, Excel only supports 256 cols
					cols = 256;
				}

				// Create the array to send to Excel
				SAFEARRAYBOUND bounds[2];
				bounds[0].cElements = rows;
				bounds[0].lLbound = 1;
				bounds[1].cElements = cols;
				bounds[1].lLbound = 1;
				SAFEARRAY *psa = SafeArrayCreate(VT_VARIANT, 2, bounds);
				if (psa)
				{
					// Gain access to the array
					_variant_t* data;
					if (SUCCEEDED(SafeArrayAccessData(psa, (void **)&data)))
					{
						// Build the array from the grid
						ROWCOL row, col;
						for (row = 0; row < rows; row++)
						{
							for (col = 0; col < cols; col++)
							{
								CString value_str = GetValueRowCol(row, col + 1);
								data[col * rows + row] = value_str;
							}
						}
						SafeArrayUnaccessData(psa);

						//COleVariant varr;
						_variant_t varr;
						varr.vt = VT_ARRAY | VT_VARIANT;
						varr.parray = psa;

						// Determine the range where to send the array
						CString rng_str;
						rng_str.Format("%s%d:%s%d",
							SCGetExcelColString(cell_col + 1), cell_row + 1,
							SCGetExcelColString(cell_col + (WORD)cols), cell_row + (WORD)rows);

						// Make Excel visible to the user
						pXL->Visible = VARIANT_TRUE;

						// Make Excel unminimized
						pXL->WindowState = (long)xlNormal;

						// Activate the sheet
						pSheet->Activate();

						// Send the array to Excel
						((RangePtr)pSheet->Range((LPCTSTR)rng_str))->Value = varr;

						// Execute a macro if available
						if (macro_valid)
						{
							try
							{
								pXL->Run(macroname);
							}
							catch(_com_error& e)
							{
								SetFocus();
								error_str = "An error occurred while executing a macro in Excel (TM) 95.";
								error_str += "\n\nError Message:\n";
								error_str += (LPCTSTR)e.ErrorMessage();
								if (e.Description().length() > 0)
								{
									error_str += "\n\nCOM reports:\n";
									error_str += (LPCTSTR)e.Description();
								}
								SCMessageBox(error_str);
								error_str = "";
							}
						}
					}
					else
					{
						error_str = "Excel (TM) 95 setup problem:\n\nCould not get access to array data.";
					}

					SafeArrayDestroy(psa);
				}
				else
				{
					error_str = "Excel (TM) 95 setup problem:\n\nCould not allocate array for data.";
				}
			}
		}
	}
	catch(_com_error& e)
	{
		error_str = "Error communicating with Excel (TM) 95.";
		error_str += "\n\nError Message:\n";
		error_str += (LPCTSTR)e.ErrorMessage();
		if (e.Description().length() > 0)
		{
			error_str += "\n\nCOM reports:\n";
			error_str += (LPCTSTR)e.Description();
		}
	}

	return error_str;
}
