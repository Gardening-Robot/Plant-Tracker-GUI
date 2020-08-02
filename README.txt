Plant Tracker (GUI Version)
--------------------------------------
Logged plants are displayed in a table. Use the buttons toward the bottom to manipulate the data:
- Add Plant: add a plant object that will correspond to a row on the table
- Harvest Plant: Enter dates where something was harvested if that plant is selected through mouse
- Delete Plant: Delete the selected entry
- Change Year: 2020 is set as default, but the year can be changed here and all data from other year open will be saved
- Change View: Toggles between plant/harvest date info and watering info
- Water Plants: Adds a date for when all selected plants were watered on the watering info view
----------------------------------------

These buttons do not merely add an entry to a spreadsheet. The information inputted is added to a vector of type Plant.
Hopefully this will allow more advanced data manipulation to occur as this project progresses.

To build this project, set up the wxWidgets framework: https://www.wxwidgets.org/