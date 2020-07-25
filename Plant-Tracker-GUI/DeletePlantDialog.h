/*
 * File:   DeletePlantDialog.h
 *
 * Class for deleting plants
 */
#pragma once
#include "wx\wx.h"

class DeletePlantDialog : public wxMessageDialog
{
public:
	DeletePlantDialog(wxWindow* parent, wxString name);	
};

class NotSelectedForDelete : public wxMessageDialog
{
public:
	NotSelectedForDelete(wxWindow* parent);
};