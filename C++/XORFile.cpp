// Markus Scholtes 2025
// XOR of the first n bytes of a file
// A second call with the same parameters restores the file to its original state
// Invocation: XORFile <FILENAME> [<COUNTOFBYTES>]
// <COUNTOFBYTES> defaults to 32

// Compile with: cl XORFile.cpp

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
	int numBytes = 32;
	if (argc > 1)
	{
		if (argc > 2)
		{
			numBytes = atoi(argv[2]);
			if (numBytes < 1)
			{
				cout << "Wrong parameter for count of bytes.";
				return -2;
			}
		}
	} else {
		cout << "Invocation: XORFile <FILENAME> [<COUNTOFBYTES>]";
		return -1;
	}

  // Filestream für Binärdatei öffnen
  fstream fStream(argv[1], ios_base::binary | ios_base::in | ios_base::out);

  if (!fStream.is_open()) {
  	cout << "Cannot read file " << argv[1] << "!";
  	return -3;
  }

  char* cBuffer = new char[numBytes + 1]();

  fStream.read(cBuffer, static_cast<streamsize>(numBytes));

  if (fStream.gcount() == 0) {
  	cout << "File " << argv[1] << " is empty, cancelling.";
  	return -4;
  }

	if (fStream.gcount() != static_cast<streamsize>(numBytes)) {
		numBytes = fStream.gcount();
		cout << "Can only read " << numBytes << " bytes." << endl;
		// Fehlerflags löschen
		fStream.clear();
	}

  cout << "Original value(s): ";
  for (int i = 0; i < numBytes; i++) {
    cout << '[';
  	cout << hex << setfill('0') << setw(2) << (0xFF & cBuffer[i]);
    cout << ']';
  }

  cout << endl << "New value(s): ";
  for (int i = 0; i < numBytes; i++) {
    cBuffer[i] ^= 0xFF;
    cout << '[';
  	cout << hex << setfill('0') << setw(2) << (0xFF & cBuffer[i]);
    cout << ']';
  }

  // zum Start der Datei springen
  fStream.seekp(0, ios_base::beg);
  // und geänderte Bytes schreiben
  fStream.write(cBuffer, static_cast<streamsize>(numBytes));
	// Dateihandle schließen
  fStream.close();
  // Puffer freigeben
  delete[] cBuffer;

  return 0;
}
