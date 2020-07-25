#include "DeletePlantDialog.h"

DeletePlantDialog::DeletePlantDialog(wxWindow* parent, wxString name) 
	: wxMessageDialog(parent, "Are you sure you want to delete selected plant " + name + "?", "Delete Plant", wxOK | wxCANCEL | wxCENTER)
{
}

NotSelectedForDelete::NotSelectedForDelete(wxWindow* parent)
	: wxMessageDialog(parent, "You have not selected a plant to delete", "Delete Plant", wxOK | wxCENTER)
{
}
