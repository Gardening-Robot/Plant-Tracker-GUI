/*
 * File:   HarvestPlantDialog.cpp
 *
 * Class for dialog of adding dates of harvest
 */
#include "HarvestPlantDialog.h"

wxBEGIN_EVENT_TABLE(HarvestPlantDialog, wxDialog)
    EVT_BUTTON(wxID_CANCEL, HarvestPlantDialog::OnCancel)
wxEND_EVENT_TABLE()

HarvestPlantDialog::HarvestPlantDialog(wxWindow* parent, wxString name) : wxDialog(parent, ID_HarvestPlantDialog, "Harvest " + name + " Plant")
{
    sizer = new wxBoxSizer(wxVERTICAL);
    dateSizer = new wxBoxSizer(wxHORIZONTAL);
    dateSizer->Add(
        new wxStaticText(this, ID_HarvestPlantInstructions, wxString("Enter harvest date (MM/DD):"), wxDefaultPosition, wxSize(160, 20), wxALIGN_BOTTOM | wxALIGN_LEFT),
        wxSizerFlags().Expand().Border(wxALL, 10));
    dateEntry = new wxTextCtrl(this, ID_HarvestPlantInstructions, "", wxDefaultPosition, wxSize(100, 20), wxTE_LEFT);
    dateSizer->Add(dateEntry, 0, wxEXPAND | wxALL, 10);

    btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(
        new wxButton(this, wxID_OK, "OK"),
        wxSizerFlags().Border(wxALL, 10));
    btnSizer->Add(
        new wxButton(this, wxID_CANCEL, "Cancel"),
        wxSizerFlags().Border(wxALL, 10));

    sizer->Add(dateSizer, 0, wxEXPAND | wxALL, 10);
    sizer->Add(btnSizer, 0, wxEXPAND | wxALL, 10);
    SetSizerAndFit(sizer);
}

wxString HarvestPlantDialog::GetDate() const
{
    return dateEntry->GetValue();
}

void HarvestPlantDialog::OnCancel(wxCommandEvent& event)
{
    dateEntry->SetValue("");
    EndModal(0);
}

NotSelectedForHarvest::NotSelectedForHarvest(wxWindow* parent)
    : wxMessageDialog(parent, "You have not selected a plant to harvest", "Harvest Plant", wxOK | wxCENTER)
{
}