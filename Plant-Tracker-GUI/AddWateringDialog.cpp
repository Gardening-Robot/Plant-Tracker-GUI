/*
 * File:   AddPlantDialog.cpp
 *
 * Dialog for adding a plant
 */
#include "AddWateringDialog.h"

wxBEGIN_EVENT_TABLE(AddWateringDialog, wxDialog)
EVT_BUTTON(wxID_CANCEL, AddWateringDialog::OnCancel)
wxEND_EVENT_TABLE()

AddWateringDialog::AddWateringDialog(wxWindow* parent) : wxDialog(parent, ID_AddWateringDialog, "Add Watering Date")
{
    sizer = new wxBoxSizer(wxVERTICAL);
    dateSizer = new wxBoxSizer(wxHORIZONTAL);
    dateSizer->Add(
        new wxStaticText(this, ID_AddWateringInstructions, wxString("Enter water date (MM/DD):"), wxDefaultPosition, wxSize(150, 20), wxALIGN_BOTTOM | wxALIGN_LEFT),
        wxSizerFlags().Expand().Border(wxALL, 10));
    dateEntry = new wxTextCtrl(this, ID_AddWateringText, "", wxDefaultPosition, wxSize(100, 20), wxTE_LEFT);
    dateSizer->Add(dateEntry, wxSizerFlags().Expand().Border(wxALL, 10));

    btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(
        new wxButton(this, wxID_OK, "OK"),
        wxSizerFlags().Border(wxALL, 10));
    btnSizer->Add(
        new wxButton(this, wxID_CANCEL, "Cancel"),
        wxSizerFlags().Border(wxALL, 10));

    sizer->Add(
        dateSizer,
        wxSizerFlags(0).Left());
    sizer->Add(
        btnSizer,
        wxSizerFlags(0).Center());
    SetSizerAndFit(sizer);
}

wxString AddWateringDialog::GetDate() const
{
    return dateEntry->GetValue();
}
void AddWateringDialog::OnCancel(wxCommandEvent& event)
{
    dateEntry->SetValue("");
    EndModal(0);
}
NotSelectedForWater::NotSelectedForWater(wxWindow* parent)
    : wxMessageDialog(parent, "You have not selected a plant to be watered from the watering screen", "Add Watering Date", wxOK | wxCENTER)
{
}