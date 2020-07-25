/*
 * File:   ChangeYearDialog.h
 *
 * Dialog  for changing the year
 */
#pragma once
#include "wx\wx.h"
#include "Identifiers.h"

class ChangeYearDialog : public wxDialog
{
public:
	ChangeYearDialog(wxWindow* parent);
	wxString GetYear() const;

private:
	wxTextCtrl* yearEntry;
	wxBoxSizer* sizer;
	wxBoxSizer* entrySizer;
	wxBoxSizer* btnSizer;

	wxString yearEntered;

	void OnCancel(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

