/*
 * File:   AddWateringDialog.h
 *
 * Dialog for adding a water date
 */

#pragma once

#include "wx\wx.h"
#include "Identifiers.h"

class AddWateringDialog : public wxDialog
{
public:
	AddWateringDialog(wxWindow* parent);
	wxString GetDate() const;

private:
	wxTextCtrl* dateEntry;
	wxBoxSizer* sizer;
	wxBoxSizer* dateSizer;
	wxBoxSizer* btnSizer;

	wxString date;

	void OnCancel(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

class NotSelectedForWater : public wxMessageDialog
{
public:
	NotSelectedForWater(wxWindow* parent);
};