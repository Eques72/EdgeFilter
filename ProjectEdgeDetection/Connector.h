#ifndef CONN
#define CONN

#include <windows.h>
#include <string>
#include "EdgeManager.h"
// 
//for "testing"
//#include <iostream>
//int testF();


class Connector 
{
private:
	static const int DEFAULT_NUM_OF_THREADS;
	static const int DEFAULT_CHOOSEN_LIB;


	/// <summary>
	/// 0 for cpp lib, 1 for asm lib
	/// </summary>
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
	Connector() {};

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
	std::string converSysStrToStdStr(System::String^ s);
	System::String^ converStdStrToSysStr(std::string s);
	System::String^ createFilterRaport(int index);

	bool startHistogram();
	bool startFilterManager();

};

#endif // !CONN
