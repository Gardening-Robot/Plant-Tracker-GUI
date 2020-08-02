/*
 * File:   Main.h
 *
 * Class for main frame
 */

#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "wx/wx.h"
#include "wx/listctrl.h"
#include "AddPlantDialog.h"
#include "DeletePlantDialog.h"
#include "HarvestPlantDialog.h"
#include "ChangeYearDialog.h"
#include "AddWateringDialog.h"
#include "Identifiers.h"
#include "Plant.h"
#include "Year.h"

using std::vector;

class Main : public wxFrame
{
public:
	Main();
	~Main();

private:
	wxMenu* menuFile = nullptr;
	wxMenu* menuHelp = nullptr;
	wxMenuBar* menuBar = nullptr;
	wxPanel* textPanel = nullptr;
	wxStaticText* instructionsText = nullptr;
	wxListView* plantList = nullptr;
	wxListView* wateringList = nullptr;
	wxButton* addPlantBtn = nullptr;
	wxButton* deletePlantBtn = nullptr;
	wxButton* harvestPlantBtn = nullptr;
	wxButton* changeYearBtn = nullptr;
	wxButton* waterPlantsBtn = nullptr;
	wxButton* changeViewBtn = nullptr;

	wxBoxSizer* sizer;
	wxBoxSizer* btnSizer1;
	wxBoxSizer* btnSizer2;

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnAddPlantBtnClicked(wxCommandEvent& evt);
	void OnDeletePlantBtnClicked(wxCommandEvent& evt);
	void OnHarvestPlantBtnClicked(wxCommandEvent& evt);
	void OnChangeYearBtnClicked(wxCommandEvent& evt);
	void OnWaterPlantsBtnClicked(wxCommandEvent& evt);
	void OnChangeViewBtnClicked(wxCommandEvent& evt);

	vector<Plant> dataInit(std::string fileName);
	bool harvestPlant(vector<Plant>& plants, std::string plantName, std::string date);
	bool waterPlant(vector<Plant>& plants, std::string plantName, std::string date);
	void writeToFile(vector<Plant> plants, std::string year);
	bool checkDateFormat(std::string& date, int year);
	void vectorToListCtrl(vector<Plant>plants);

	vector<Plant> plantVector;
	int year;
	std::string yearS;

	wxDECLARE_EVENT_TABLE();
};

