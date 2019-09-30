#pragma once
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

class save {
public:
	File file;
	void setup();
	void loop();
	void writeFile(char *str);
	void closeFile();
	void openFile(char *str);
	void saveToFile(char*str);
	void saveToFileln(char*str);
	void saveToFile(float);
	void saveToFileln(float);
};