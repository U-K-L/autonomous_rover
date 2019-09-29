#include "save.h"

void save::setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}


	Serial.print("Initializing SD card...");

	if (!SD.begin(SDCARD_SS_PIN)) {
		Serial.println("initialization failed!");
		while (1);
	}
	Serial.println("initialization done.");
}

void writeFile(char *str) {
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	file = SD.open(str, FILE_WRITE);
	Serial.println(str);

}
void closeFile() {
	file.close();

}

void openFile(char *str) {
	// re-open the file for reading:
	file = SD.open(str);
	if (file) {

		// read from the file until there's nothing else in it:
		while (file.available()) {
			Serial.write(file.read());
		}
		// close the file:
		file.close();
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}

void save :: loop() {
}