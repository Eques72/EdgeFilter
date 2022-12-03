#include "Connector.h"

const int Connector::DEFAULT_NUM_OF_THREADS = 1;
const int Connector::DEFAULT_CHOOSEN_LIB = 0;

void Connector::setImage(std::string path) 
{
	if (!path.empty()) {
		recentPath = path;
		isReady = true;
	}
};

std::string Connector::converSysStrToStdStr(System::String^ s) 
{
	using namespace System::Runtime::InteropServices;
	std::string convertedString;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	convertedString = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));

	return convertedString;
}

System::String^ Connector::converStdStrToSysStr(std::string s) 
{
	System::String^ str = gcnew System::String(s.c_str());
	return str;
}

bool Connector::startHistogram()
{
	bool isSucces = false;
	EdgeManager eM;
	eM.setSourceImage(recentPath, true);
	isSucces = eM.runHistogram(rAmount, gAmount, bAmount);
	return isSucces;
}

bool Connector::startFilterManager() 
{
	bool isSucces = false;

	if (isReady) 
	{
		EdgeManager eM;
		eM.setSourceImage(recentPath, false);
		isSucces = eM.runEdgeFilter(choosenLibrary, numberOfThreads);
		filteredImagePath = eM.getOutputImagePath();
		timeTaken = eM.getTimeTaken();
		imgResHeight = eM.getSourceImage()->getHeight();
		imgResWidth = eM.getSourceImage()->getWidth();
	}
	return isSucces;
};

System::String^ Connector::createFilterRaport(int index) 
{
	System::String^ s = (index+1).ToString() + ". " + timeTaken.ToString();
	s += "ms, ";
	s += numberOfThreads.ToString() + "thr, ";
	if (choosenLibrary == 0)
		s += "C++, ";
	else
		s += "Asm, ";
	s += imgResWidth.ToString() + "x" + imgResHeight + "px;";
	return s;
}