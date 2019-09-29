#pragma once
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

class save {
public:
	File file;
	void setup();
	void loop();
	void writeFile();
	void closeFile();
	void openFile();
};