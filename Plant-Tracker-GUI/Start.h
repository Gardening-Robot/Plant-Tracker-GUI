/*
 * File:   Start.h
 *
 * launches main frame
 */

#pragma once

#include "wx/wx.h"
#include "Main.h"

class Start : public wxApp
{
public:
	Start();
	~Start();
	virtual bool OnInit();

private:
	Main* frame = nullptr;
};

