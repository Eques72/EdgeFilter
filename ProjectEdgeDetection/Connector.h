#ifndef CONN
#define CONN

//===================================================
// File: Connector.h
// Contents: Declaration file for EdgeManager class. This class serves as controller for the projectand connets model layer with view layer
// Author: Adrian Zarêba
//===================================================

#include <windows.h>
#include <string>
#include "EdgeManager.h"

//This class serves as controller for the projectand connets model layer with view layer
class Connector 
{
private:
	static const int DEFAULT_NUM_OF_THREADS;
	static const int DEFAULT_CHOOSEN_LIB;


	/// 0 for cpp lib, 1 for asm lib
	int choosenLibrary = DEFAULT_CHOOSEN_LIB;
	int numberOfThreads = DEFAULT_NUM_OF_THREADS;

	std::string recentPath;
	bool isReady = false;

	std::string filteredImagePath;
	long timeTaken = 0;
	int rAmount = 0, gAmount = 0, bAmount = 0;
	int imgResWidth = 0;
	int imgResHeight = 0;

public:
	//Default constructor
	Connector() {};

	//Getters and setters:
	inline void setUnready() { isReady = false; }
	inline void setChoosenLib(int libSelect) { choosenLibrary = libSelect; };
	inline void setNumberOfThreads(int number) { if (number > 0 && number < 64) numberOfThreads = number; };
	inline int getNumberOfThreads() const { return numberOfThreads; };
	inline int getChoosenLibrary() const { return choosenLibrary; };
	inline bool isReadyToFilter() const { return isReady; };
	inline int getRAmount() const { return rAmount; }
	inline int getGAmount() const { return gAmount; }
	inline int getBAmount() const { return bAmount; }
	inline std::string getFilteredImgPath() const { return filteredImagePath;}
	inline long getTime() const { return timeTaken; }
	void setImage(std::string path);

	//Converts System::String to sdt::string
	std::string converSysStrToStdStr(System::String^ s);
	//Converts sdt::string to System::String
	System::String^ converStdStrToSysStr(std::string s);

	//Creates information about last succesful filter oparetion in form of a string 
	//Contains details about threads used, image size, library used, time taken to complete
	//Returns a string containing mentioned info
	System::String^ createFilterRaport(int index);

	//Crates EdgeManager instance and orders generation of histogram data form provided image. 
	//Resoulting data is stored in fields rAmount, gAmount, bAmount
	//Image that is beeing analysed is stored under the path from recentPath field
	bool startHistogram();

	//Crates EdgeManager instance and orders generation of new image filtered with use of edge detection algorithm
	//Details of how it will be used are taken from fields: choosenLibrary and numberOfThreads and recentPath
	//Image will be saved and its location will be stored in filteredImagePath
	//Field timeTaken will also be filled with ms taken to complete this algorithm
	bool startFilterManager();
};

#endif //!CONN
