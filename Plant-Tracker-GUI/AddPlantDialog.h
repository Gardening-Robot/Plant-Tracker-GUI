/*
 * File:   AddPlantDialog.h
 *
 * Dialog for adding a plant
 */

#pragma once

#include "wx\wx.h"
#include "Identifiers.h"

class AddPlantDialog : public wxDialog
{
public:
	AddPlantDialog(wxWindow* parent);
	wxString GetName() const;
	wxString GetDate() const;

private:
	wxTextCtrl* nameEntry;
	wxTextCtrl* dateEntry;
	wxBoxSizer* sizer;
	wxBoxSizer* nameSizer;
	wxBoxSizer* dateSizer;
	wxBoxSizer* btnSizer;

	wxString name;
	wxString date;

	void OnCancel(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};