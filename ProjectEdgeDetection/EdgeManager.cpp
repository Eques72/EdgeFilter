#include "EdgeManager.h"
#include <iostream>

void edgeCppFilterO(ImageCV& input, ImageCV& output, int startingRow, int height);

void EdgeManager::setSourceImage(std::string path, bool isToBeRbg)
{
	this->sourceImage = new ImageCV(path, isToBeRbg);
	this->sourcePath = "path";
	std::size_t pos = path.rfind('.');
	if (pos != std::string::npos)
		path.insert(pos, "_EdgeOutput_");
	else
		path = "_EdgeOutput_" + path;
	
	/* try to open file to read to check if file already exists */
	std::ifstream iffile;
	iffile.open(path);
	while (iffile)
	{
		std::size_t pos = path.rfind('.');
		if (pos != std::string::npos)
			path.insert(pos, std::to_string(1));
		else
			path += std::to_string(1);
		iffile.close();
		iffile.open(path);
	}	

	this->outputPath = path;
}

void EdgeManager::setSourceImage(ImageCV* img)
{
	this->sourceImage = img;
	this->sourcePath = "C:/";
	this->outputPath = "C:/outputImageEdgeFilter.png";
}

ImageCV* EdgeManager::getSourceImage() const
{
	return sourceImage;
}

ImageCV* EdgeManager::getOutputImage() const
{
	return outputImage;
}

std::string EdgeManager::getOutputImagePath() const
{
	return !outputPath.empty() ? outputPath : "C:/";
}

bool EdgeManager::runEdgeFilter(int libType, int threads)
{
	int width = sourceImage->getWidth();
	bool rgbImage = sourceImage->getIfIsRGB();
	outputImage = new ImageCV(sourceImage->getSize(), width, sourceImage->getHeight(), rgbImage);
	
	//set threads, divide image
	int rowsPerThread = 0;
	int rowsForLastThread = 0;
	if (threads > 1) {
		rowsForLastThread = (sourceImage->getHeight() - 2) % (threads - 1);
		rowsPerThread = (sourceImage->getHeight() - 2 - rowsForLastThread) / (threads - 1);
	}
	else
		rowsForLastThread = sourceImage->getHeight() - 2;

	if (libType == 0) //CPP
	{
		//start timer
		auto start = std::chrono::high_resolution_clock::now();

		//run threads
		std::vector<std::thread> threadsList;
		for (int i = 0; i < threads - 1; i++)
			threadsList.push_back(std::thread(edgeCppFilterO, std::ref(*sourceImage), std::ref(*outputImage), 1 + i*rowsPerThread, rowsPerThread));
		threadsList.push_back(std::thread(edgeCppFilterO, std::ref(*sourceImage), std::ref(*outputImage), 1 + (threads-1) * rowsPerThread, rowsForLastThread));

		//wait for all threads
		for (int i = 0; i < threads; i++)
			if (threadsList[i].joinable())
				threadsList[i].join();
		
		//stop timer
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		this->timeTaken = duration.count();

		saveImage(true, outputPath);//save image

		return true;
	}
	else if(libType == 1) //ASM
	{
		typedef int(_stdcall* EdgeDetectionFilter)(int, int, std::byte*, std::byte*); //width, height, size, srcTab, outTab
		HINSTANCE dllHandle = NULL;
		dllHandle = LoadLibrary(TEXT("AsmLib.dll"));
		EdgeDetectionFilter asmFilter = (EdgeDetectionFilter)GetProcAddress(dllHandle, "EdgeDetectionFilter");

		//start timer
		auto start = std::chrono::high_resolution_clock::now();

			//run threads
			std::vector<std::thread> threadsList;
			for (int i = 0; i < threads - 1; i++)
			{
				threadsList.push_back(std::thread(asmFilter, sourceImage->getWidth(), rowsPerThread,
					sourceImage->getArray() + (sourceImage->getWidth() * (i)*rowsPerThread + sourceImage->getWidth()),
					outputImage->getArray() + (sourceImage->getWidth() * (i)*rowsPerThread + sourceImage->getWidth())));
			}
			if (rowsForLastThread > 0)
				threadsList.push_back(std::thread(asmFilter, sourceImage->getWidth(),
					rowsForLastThread, sourceImage->getArray() + (sourceImage->getWidth() + sourceImage->getWidth() * (threads - 1) * rowsPerThread),
					outputImage->getArray() + (sourceImage->getWidth() + sourceImage->getWidth() * (threads - 1) * rowsPerThread)));
			else
				threadsList.push_back(std::thread());

			//wait for all threads
			for (int i = 0; i < threads; i++)
				if (threadsList[i].joinable())
					threadsList[i].join();

		//stop timer
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		this->timeTaken = duration.count();

		saveImage(true, outputPath);//save image 

		return true;
	}
	return false;
}

bool EdgeManager::runHistogram(int& R,int& B,int& G)
{
	float sumOfAll = 0.0f;
	float sumOfBlue = 0.0f;
	float sumOfGreen = 0.0f;
	float sumOfRed = 0.0f;

	if (sourceImage->getIfIsRGB()) 
	{
		for (int i = 0; i < sourceImage->getSize()-2;) 
		{
			float Blue = (float)sourceImage->getArray()[i] / 255.0f;
			float Green = (float)sourceImage->getArray()[i+1] / 255.0f;
			float Red = (float)sourceImage->getArray()[i+2] / 255.0f;
			sumOfAll += Red + Green + Blue;
			sumOfBlue += Red;
			sumOfGreen += Green;
			sumOfRed += Blue;
			i += 3;
		}
		B = (int)(100 * sumOfBlue / sumOfAll);
		G = (int)(100 * sumOfGreen / sumOfAll);
		R = (int)(100 * sumOfRed / sumOfAll);
		return true;
	}
	return false;
}

void EdgeManager::saveImage(bool saveOutputImage, std::string path)
{
	if (!path.empty()) 
	{
		if (saveOutputImage && outputImage != nullptr)
			outputImage->saveImage(path);
		else if (sourceImage != nullptr)
			sourceImage->saveImage(path);
	}
}

EdgeManager::~EdgeManager()
{
	if(sourceImage != nullptr)
	delete sourceImage;
	if(outputImage != nullptr)
	delete outputImage;
}

void edgeCppFilterO(ImageCV& input, ImageCV& output, int startingRow, int height)
{
	int matrix[9] = { 0,1,0,1,-4,1,0,1,0 };

	for (int y = startingRow; y < height + startingRow; y++)
		for (int x = 0; x < input.getWidth(); x++)
		{
			int center = y * input.getWidth() * input.getNumOfChannels() + x * input.getNumOfChannels();
			int indexMatrix[9] = {
				center - input.getWidth() * input.getNumOfChannels() - input.getNumOfChannels(),
				center - input.getWidth() * input.getNumOfChannels(),
				center - input.getWidth() * input.getNumOfChannels() + input.getNumOfChannels(),
				center - input.getNumOfChannels(),
				center,
				center + input.getNumOfChannels(),
				center + input.getWidth() * input.getNumOfChannels() - input.getNumOfChannels() ,
				center + input.getWidth() * input.getNumOfChannels() ,
				center + input.getWidth() * input.getNumOfChannels() + input.getNumOfChannels() };
			
			int newPixel = (int)input.getArray()[indexMatrix[0]] * matrix[0] + (int)input.getArray()[indexMatrix[1]] * matrix[1] + (int)input.getArray()[indexMatrix[2]] * matrix[2] +
				(int)input.getArray()[indexMatrix[3]] * matrix[3] + (int)input.getArray()[indexMatrix[4]] * matrix[4] + (int)input.getArray()[indexMatrix[5]] * matrix[5] +
				(int)input.getArray()[indexMatrix[6]] * matrix[6] + (int)input.getArray()[indexMatrix[7]] * matrix[7] + (int)input.getArray()[indexMatrix[8]] * matrix[8];
			if (newPixel > 200)
				newPixel = 255;
			else if (newPixel <= 0)
				newPixel = 0;
			output.getArray()[indexMatrix[4]] = (std::byte)newPixel;
		}
}
