/*
 * File:   ChangeYearDialog.cpp
 *
 * Dialog  for changing the year
 */
#include "ChangeYearDialog.h"

wxBEGIN_EVENT_TABLE(ChangeYearDialog, wxDialog)
    EVT_BUTTON(wxID_CANCEL, ChangeYearDialog::OnCancel)
wxEND_EVENT_TABLE()

ChangeYearDialog::ChangeYearDialog(wxWindow* parent) : wxDialog(parent, ID_ChangeYearDialog, "Change Year")
{
    sizer = new wxBoxSizer(wxVERTICAL);

    entrySizer = new wxBoxSizer(wxHORIZONTAL);
    entrySizer->Add(
        new wxStaticText(this, ID_ChangeYearInstructions, wxString("Enter the new year:"), wxDefaultPosition, wxSize(150, 20), wxALIGN_BOTTOM | wxALIGN_LEFT),
        wxSizerFlags().Expand().Border(wxALL, 10));
    yearEntry = new wxTextCtrl(this, ID_ChangeYearText, "", wxDefaultPosition, wxSize(100, 20), wxTE_LEFT, wxTextValidator(wxFILTER_DIGITS, &yearEntered));
    entrySizer->Add(
        yearEntry, wxSizerFlags().Expand().Border(wxALL, 10));

    btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(
        new wxButton(this, wxID_OK, "OK"),
        wxSizerFlags().Border(wxALL, 10));
    btnSizer->Add(
        new wxButton(this, wxID_CANCEL, "Cancel"),
        wxSizerFlags().Border(wxALL, 10));

    sizer->Add(
        entrySizer,
        wxSizerFlags(0).Left());
    sizer->Add(
        btnSizer,
        wxSizerFlags(0).Center());
    SetSizerAndFit(sizer);
}

wxString ChangeYearDialog::GetYear() const
{
    return yearEntry->GetValue();
}

void ChangeYearDialog::OnCancel(wxCommandEvent& event)
{
    yearEntry->SetValue("");
    EndModal(0);
}