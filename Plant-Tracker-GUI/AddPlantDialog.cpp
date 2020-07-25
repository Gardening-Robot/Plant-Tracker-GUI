/*
 * File:   AddPlantDialog.cpp
 *
 * Dialog for adding a plant
 */
#include "AddPlantDialog.h"

wxBEGIN_EVENT_TABLE(AddPlantDialog, wxDialog)
    EVT_BUTTON(wxID_CANCEL, AddPlantDialog::OnCancel)
wxEND_EVENT_TABLE()

AddPlantDialog::AddPlantDialog(wxWindow* parent) : wxDialog(parent, ID_AddPlantDialog, "Add Plant")
{
	sizer = new wxBoxSizer(wxVERTICAL);

    nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(
        new wxStaticText(this, ID_AddPlantInstructions1, wxString("Enter Plant name:"), wxDefaultPosition, wxSize(150, 20), wxALIGN_BOTTOM | wxALIGN_LEFT),
        wxSizerFlags().Expand().Border(wxALL, 10));
    nameEntry = new wxTextCtrl(this, ID_AddPlantText1, "", wxDefaultPosition, wxSize(100, 20), wxTE_LEFT, wxTextValidator(wxFILTER_ALPHA, &name));
    nameSizer->Add(
        nameEntry, wxSizerFlags().Expand().Border(wxALL, 10));

    dateSizer = new wxBoxSizer(wxHORIZONTAL);
    dateSizer->Add(
        new wxStaticText(this, ID_AddPlantInstructions2, wxString("Enter plant date (MM/DD):"), wxDefaultPosition, wxSize(150, 20), wxALIGN_BOTTOM | wxALIGN_LEFT),
        wxSizerFlags().Expand().Border(wxALL, 10));
    dateEntry = new wxTextCtrl(this, ID_AddPlantText2, "", wxDefaultPosition, wxSize(100, 20), wxTE_LEFT);
    dateSizer->Add(dateEntry, wxSizerFlags().Expand().Border(wxALL, 10));

    btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(
        new wxButton(this, wxID_OK, "OK"),
        wxSizerFlags().Border(wxALL, 10));
    btnSizer->Add(
        new wxButton(this, wxID_CANCEL, "Cancel"),
        wxSizerFlags().Border(wxALL, 10));
 
    sizer->Add(
        nameSizer,
        wxSizerFlags(0).Left());
    sizer->Add(
        dateSizer,
        wxSizerFlags(0).Left());
    sizer->Add(
        btnSizer,
        wxSizerFlags(0).Center());
    SetSizerAndFit(sizer);
}

wxString AddPlantDialog::GetName() const
{
    return nameEntry->GetValue();
}
wxString AddPlantDialog::GetDate() const
{
    return dateEntry->GetValue();
}
void AddPlantDialog::OnCancel(wxCommandEvent& event)
{
    nameEntry->SetValue("");
    dateEntry->SetValue("");
    EndModal(0);
}