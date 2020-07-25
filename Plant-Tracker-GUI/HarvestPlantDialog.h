/*
 * File:   HarvestPlantDialog.h
 *
 * Class for dialog of adding dates of harvest
 */
#pragma once
#include "wx\wx.h"
#include "Identifiers.h"

class HarvestPlantDialog : public wxDialog
{
public:
	HarvestPlantDialog(wxWindow* parent, wxString name);
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

class NotSelectedForHarvest : public wxMessageDialog
{
public:
	NotSelectedForHarvest(wxWindow* parent);
};