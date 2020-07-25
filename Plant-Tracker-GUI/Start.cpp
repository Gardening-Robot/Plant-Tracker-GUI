/*
 * File:   Start.cpp
 *
 * launches main frame
 */

#include "Start.h"

wxIMPLEMENT_APP(Start); //generates main

Start::Start()
{
}

Start::~Start()
{
}

bool Start::OnInit()
{
    frame = new Main(); //shows frame from main class
    frame->Show();

    return true;
}
