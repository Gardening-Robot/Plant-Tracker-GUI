/*
 * File:   Main.cpp
 *
 * Class for main frame
 */

#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_MENU(wxID_EXIT, Main::OnExit)
	EVT_MENU(wxID_ABOUT, Main::OnAbout)
    EVT_BUTTON(ID_AddPlantBtn, Main::OnAddPlantBtnClicked)
    EVT_BUTTON(ID_DeletePlantBtn, Main::OnDeletePlantBtnClicked)
    EVT_BUTTON(ID_HarvestPlantBtn, Main::OnHarvestPlantBtnClicked)
    EVT_BUTTON(ID_ChangeYearBtn, Main::OnChangeYearBtnClicked)
    EVT_BUTTON(ID_WaterPlantsBtn, Main::OnWaterPlantsBtnClicked)
    EVT_BUTTON(ID_ChangeViewBtn, Main::OnChangeViewBtnClicked)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame (nullptr, ID_Main, "Main Window", wxDefaultPosition, wxDefaultSize) 
{
    /* Top menu bar */
    menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    /* Status bar */
    CreateStatusBar(1);

    /* User instructions (static text) */
    sizer = new wxBoxSizer(wxVERTICAL);
    textPanel = new wxPanel(this, ID_InstructionsPanel, wxPoint(5, 5), wxSize(330, 70), wxALIGN_CENTRE_HORIZONTAL);
    wxString instructions ("*Instructions*\nTo harvest or delete a plant, select the particular plant first\nTo water a plant, change the view to water info before selecting");
    instructionsText = new wxStaticText (textPanel, ID_Instructions, instructions, wxPoint(5, 5), wxSize(330, 70), wxALIGN_CENTER);
    sizer->Add(textPanel, 0, wxEXPAND | wxALL, 10);

    /* List of current plants (list ctrl) */
    plantList = new wxListView(this, ID_PlantList, wxPoint(10, 80), wxSize(250, 170), wxLC_REPORT | wxLC_SINGLE_SEL, wxDefaultValidator);
    plantList->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    plantList->InsertColumn(1, "Plant Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    sizer->Add(plantList, 1, wxEXPAND | wxALL, 10);

    wateringList = new wxListView(this, ID_WateringList, wxPoint(10, 80), wxSize(250, 170), wxLC_REPORT, wxDefaultValidator);
    wateringList->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    wateringList->InsertColumn(1, "Water Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
    wateringList->Hide();
    sizer->Add(wateringList, 1, wxEXPAND | wxALL, 10);

    /* Buttons */
    btnSizer1 = new wxBoxSizer(wxHORIZONTAL);
    addPlantBtn = new wxButton(this, ID_AddPlantBtn, "Add Plant", wxPoint(10, 400), wxSize(100, 30));
    harvestPlantBtn = new wxButton(this, ID_HarvestPlantBtn, "Harvest Plant", wxPoint(10, 440), wxSize(100, 30));
    deletePlantBtn = new wxButton(this, ID_DeletePlantBtn, "Delete Plant", wxPoint(10, 480), wxSize(100, 30));
    btnSizer1->Add(addPlantBtn, 0, wxEXPAND | wxALL, 10);
    btnSizer1->Add(harvestPlantBtn, 0, wxEXPAND | wxALL, 10);
    btnSizer1->Add(deletePlantBtn, 0, wxEXPAND | wxALL, 10);

    btnSizer2 = new wxBoxSizer(wxHORIZONTAL);
    waterPlantsBtn = new wxButton(this, ID_WaterPlantsBtn, "Water Plants", wxPoint(400, 400), wxSize(100, 30));
    changeYearBtn = new wxButton(this, ID_ChangeYearBtn, "Change Year", wxPoint(400, 440), wxSize(100, 30));
    changeViewBtn = new wxButton(this, ID_ChangeViewBtn, "Change View", wxPoint(400, 480), wxSize(100, 30));
    btnSizer2->Add(waterPlantsBtn, 0, wxEXPAND | wxALL, 10);
    btnSizer2->Add(changeYearBtn, 0, wxEXPAND | wxALL, 10);
    btnSizer2->Add(changeViewBtn, 0, wxEXPAND | wxALL, 10);

    sizer->Add(btnSizer1, wxSizerFlags().Left());
    sizer->Add(btnSizer2, wxSizerFlags().Left());
    SetSizerAndFit(sizer);

    yearS = "2020";
    SetStatusText("Year: " + yearS);
    year = stoi(yearS);
    plantVector = dataInit(yearS + ".csv");
}

Main::~Main()
{
    writeToFile(plantVector, yearS);
}

void Main::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void Main::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This keeps track of your plants",
        "About Plant Tracker", wxOK | wxICON_INFORMATION);
}

/* UI functions */

void Main::OnAddPlantBtnClicked(wxCommandEvent& evt)
{
    AddPlantDialog* plantDialog = new AddPlantDialog(this);
    plantDialog->ShowModal();
    wxString name = plantDialog->GetName();
    wxString date = plantDialog->GetDate();
    if (name.size() > 0 && date.size() > 0) {
        std::string dateS = date.ToStdString();
        std::string nameS = name.ToStdString();
        if (checkDateFormat(dateS, year)) {
            plantVector.push_back(Plant(nameS, dateS, year));
            long index = plantList->InsertItem(0, name);
            plantList->SetItem(index, 1, date);
            long index2 = wateringList->InsertItem(0, name);
        }
    }
    delete plantDialog;
    evt.Skip();
}

void Main::OnDeletePlantBtnClicked(wxCommandEvent& evt)
{
    long listSelection = -1;
    listSelection = plantList->GetFirstSelected();
 
    if (listSelection != -1) {
        wxString nameSelected = plantList->GetItemText(listSelection);
        DeletePlantDialog* plantDialog = new DeletePlantDialog(this, nameSelected);
        long confirm = plantDialog->ShowModal();
        if (confirm == wxID_OK) {
            plantList->DeleteItem(listSelection);
            wateringList->DeleteItem(listSelection);
            plantVector.erase(plantVector.begin() + listSelection);
        }
        delete plantDialog;
    }
    else {
        NotSelectedForDelete* notSelected = new NotSelectedForDelete(this);
        notSelected->ShowModal();
        delete notSelected;

    }
    evt.Skip();
}

void Main::OnHarvestPlantBtnClicked(wxCommandEvent& evt)
{
    long listSelection = -1;
    listSelection = plantList->GetFirstSelected();
    if (listSelection != -1) {
        wxString nameSelected = plantList->GetItemText(listSelection);
        HarvestPlantDialog* plantDialog = new HarvestPlantDialog(this, nameSelected);
        long confirm = plantDialog->ShowModal();
        if (confirm == wxID_OK) {
            wxString date = plantDialog->GetDate();
            if (date.size() > 0) {
                std::string nameS = nameSelected.ToStdString();
                std::string dateS = date.ToStdString();
                if (checkDateFormat(dateS, year)) {
                    harvestPlant(plantVector, nameS, dateS);
                    int columnNum = plantList->GetColumnCount();
                    bool needToAddColumn = true;
                    for (int i = 0; i < columnNum; i++) {
                        if (plantList->GetItemText(listSelection, i).IsSameAs("")) {
                            columnNum = i;
                            needToAddColumn = false;
                        }
                    }
                    if (needToAddColumn) {
                        plantList->InsertColumn(columnNum, "Harvest Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
                    }
                    plantList->SetItem(listSelection, columnNum, date);
                }
            }
        }
        delete plantDialog;
    }
    else {
        NotSelectedForHarvest* notSelected = new NotSelectedForHarvest(this);
        notSelected->ShowModal();
        delete notSelected;

    }
    evt.Skip();
}

void Main::OnChangeYearBtnClicked(wxCommandEvent& evt)
{
    ChangeYearDialog* yearDialog = new ChangeYearDialog(this);
    yearDialog->ShowModal();
    wxString tempYear = yearDialog->GetYear();
    if ( tempYear.size() > 0) {
        writeToFile(plantVector, yearS);
        yearS = tempYear.ToStdString();
        year = wxAtoi(tempYear);
        plantVector.clear();
        plantList->DeleteAllItems();
        wateringList->DeleteAllItems();
        plantVector = dataInit(yearS + ".csv");
        SetStatusText("Year: " + tempYear);
    }
    delete yearDialog;
    evt.Skip();
}

void Main::OnWaterPlantsBtnClicked(wxCommandEvent& evt)
{
    long listSelection = -1;
    listSelection = wateringList->GetFirstSelected();
    if (listSelection != -1) {
        AddWateringDialog* wateringDialog = new AddWateringDialog(this);
        long confirm = wateringDialog->ShowModal();
        if (confirm == wxID_OK) {
            while (listSelection != -1) {
                wxString nameSelected = wateringList->GetItemText(listSelection);
                wxString date = wateringDialog->GetDate();
                if (date.size() > 0) {
                    std::string nameS = nameSelected.ToStdString();
                    std::string dateS = date.ToStdString();
                    if (checkDateFormat(dateS, year)) {
                        waterPlant(plantVector, nameS, dateS);
                        int columnNum = wateringList->GetColumnCount();
                        bool needToAddColumn = true;
                        for (int i = 0; i < columnNum; i++) {
                            if (wateringList->GetItemText(listSelection, i).IsSameAs("")) {
                                columnNum = i;
                                needToAddColumn = false;
                            }
                        }
                        if (needToAddColumn) {
                            wateringList->InsertColumn(columnNum, "Water Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
                        }
                        wateringList->SetItem(listSelection, columnNum, date);
                    }
                }
                listSelection = wateringList->GetNextSelected(listSelection);
            }
        }
        delete wateringDialog;
    }
    else {
        NotSelectedForWater* notSelected = new NotSelectedForWater(this);
        notSelected->ShowModal();
        delete notSelected;

    }
    evt.Skip();
}

void Main::OnChangeViewBtnClicked(wxCommandEvent& evt)
{
    if (plantList->Hide()) {
        wxRect size = plantList->GetRect();
        plantList->Hide();
        wateringList->Show();
        wateringList->SetSize(size, 1);
    }
    else {
        wxRect size = wateringList->GetRect();
        wateringList->Hide();
        plantList->Show();
        plantList->SetSize(size, 1);
    }

}

/* Plant functions */

vector<Plant> Main::dataInit(std::string fileName)
{
    vector<Plant> plants;
    std::ifstream plantFile;
    plantFile.open(fileName);
    if (plantFile.is_open()) {
        int year = stoi(fileName.substr(0, 4));
        vector<std::string> row;
        std::string line, word;
        int plantCount = 0; // plantCount = current row
        while (plantFile >> line && line.compare("##") != 0) {
            row.clear();
            std::stringstream s(line);
            while (getline(s, word, ',')) {
                row.push_back(word);
            }
            if (row.size() >= 2) //has name and plant date
                plants.push_back(Plant(row.at(0), row.at(1), year));
            if (row.size() > 2) { // also has harvest dates
                for (int i = 2; i < row.size(); i++) // add as many harvest dates as needed 
                    plants.at(plantCount).addHarvestDate(row.at(i));
            }
            plantCount++;
        }
        if (line.compare("##") == 0) {
            while (plantFile >> line) {
                row.clear();
                std::stringstream s(line);
                while (getline(s, word, ',')) {
                    row.push_back(word);
                }
                if (row.size() >= 2) {
                    bool found = false;
                    int i = 0;
                    while (i < plants.size()) {
                        if (row.at(0).compare(plants.at(i).getName()) == 0) {
                            found = true;
                            break;
                        }
                        i++;
                    }
                    if (found) {
                        for (int j = 1; j < row.size(); j++) {
                            plants.at(i).addWaterDate(row.at(j));
                        }
                    }
                }
            }
        }
    }
    vectorToListCtrl(plants);
    plantFile.close();
    return plants;
}

void Main::vectorToListCtrl(vector<Plant>plants)
{
    for (Plant plant : plants) {
        wxString name (plant.getName());
        wxString date (plant.getPlantDate());
        long index = plantList->InsertItem(0, name);
        plantList->SetItem(index, 1, date);
        std::stringstream s(plant.getHarvestDates());
        std::string word;
        int currentColumn = 1;
        while (getline(s, word, ',')) {
            currentColumn++;
            if (plantList->GetColumnCount() <= currentColumn)
                plantList->InsertColumn(currentColumn, "Harvest Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
            wxString temp = _(word);
            plantList->SetItem(index, currentColumn, temp);

        }
        long index2 = wateringList->InsertItem(0, name);
        std::stringstream s2(plant.getWaterDates());
        currentColumn = 0;
        while (getline(s2, word, ',')) {
            currentColumn++;
            if (wateringList->GetColumnCount() <= currentColumn)
                wateringList->InsertColumn(currentColumn, "Water Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
            wxString temp = _(word);
            wateringList->SetItem(index2, currentColumn, temp);
        }
    }
}

bool Main::harvestPlant(vector<Plant>& plants, std::string plantName, std::string date)
{
    bool plantPlanted = false;
    for (std::vector<int>::size_type i = 0; i != plants.size(); i++)
    {
        if (plants.at(i).getName().compare(plantName) == 0) // search for entered name
        {
            plantPlanted = true;
            plants.at(i).addHarvestDate(date);
        }
    }
    return plantPlanted;
}

bool Main::waterPlant(vector<Plant>& plants, std::string plantName, std::string date)
{
    bool plantPlanted = false;
    for (std::vector<int>::size_type i = 0; i != plants.size(); i++)
    {
        if (plants.at(i).getName().compare(plantName) == 0) // search for entered name
        {
            plantPlanted = true;
            plants.at(i).addWaterDate(date);
        }
    }
    return plantPlanted;
}

void Main::writeToFile(vector<Plant> plants, std::string year)
{
    std::ofstream plantFile;
    plantFile.open(year + ".csv", std::ofstream::trunc); //open and clear file
    for (Plant plant : plants) { //input plant/harvest info
        plantFile << plant.getName() << ","
            << plant.getPlantDate() << ","
            << plant.getHarvestDates() << std::endl;
    }
    plantFile << "##" << std::endl;
    for (Plant plant : plants) { //input water info
        plantFile << plant.getName() << ","
            << plant.getWaterDates() << std::endl;
    }
    plantFile.close();
}

bool Main::checkDateFormat(std::string& date, int year)
{
    if (date.length() != 5) {
        return false;
    }
    int month = atoi(date.substr(0, 2).c_str());
    if (month > 12 || month < 1) { // checks month validity
        return false;
    }
    if (atoi(date.substr(3, 5).c_str()) > getDaysInMonth(month - 1, year) && atoi(date.substr(3, 5).c_str()) > 0) { //checks day validity
        return false;
    }
    return true;
}