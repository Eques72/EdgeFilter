#include "EdgeManager.h"
#include <iostream>

void edgeCppFilterO(ImageCV& input, ImageCV& output, int startingRow, int height, bool isRGB);

void EdgeManager::setSourceImage(std::string path, bool isToBeRbg)
{
	this->sourceImage = new ImageCV(path, isToBeRbg);
	this->sourcePath = "path";
	std::size_t pos = path.rfind('.');
	if (pos != std::string::npos)
		path.insert(pos, "_EdgeOutput_");
	else
		path = "_EdgeOutput_" + path;

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
//	outputImage = new ImageCV(*sourceImage);
	
	//set threads, divide image
	int rowsPerThread = 0;
	int rowsForLastThread = 0;
	if (threads > 1) {
		rowsForLastThread = (sourceImage->getHeight() - 2) % (threads);
		rowsPerThread = (sourceImage->getHeight() - 2 - rowsForLastThread) / threads;
		rowsForLastThread += rowsPerThread;
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
			threadsList.push_back(std::thread(edgeCppFilterO, std::ref(*sourceImage), std::ref(*outputImage), 1 + i*rowsPerThread, rowsPerThread, rgbImage));
		threadsList.push_back(std::thread(edgeCppFilterO, std::ref(*sourceImage), std::ref(*outputImage), 1 + (threads-1) * rowsPerThread, rowsForLastThread, rgbImage));

		//wait for all threads
		for (int i = 0; i < threads; i++)
			if (threadsList[i].joinable())
				threadsList[i].join();
		
		//stop timer
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		this->timeTaken = duration.count();

		saveImage(true, outputPath);//save image
		//outputImage->saveImage(outputPath); 

		return true;
	}
	else if(libType == 1) //ASM
	{
		//typedef int(_stdcall* MyProc)(); //width, height, size, srcTab, outTab
		typedef int(_stdcall* MyProc)(int, int, std::byte*, std::byte*); //width, height, size, srcTab, outTab
		HINSTANCE dllHandle = NULL;
		dllHandle = LoadLibrary(TEXT("JaAsm.dll"));
		MyProc procedura = (MyProc)GetProcAddress(dllHandle, "MyProc");

		//start timer
		auto start = std::chrono::high_resolution_clock::now();

		std::cout << "Before thread" << std::endl;
		//run threads
		std::vector<std::thread> threadsList;
		for (int i = 0; i < threads - 1; i++)
		{
			threadsList.push_back(std::thread(procedura, sourceImage->getWidth(), rowsPerThread, sourceImage->getArray() + (sourceImage->getWidth() * (i)*rowsPerThread + sourceImage->getWidth()), outputImage->getArray() + (sourceImage->getWidth() * (i + 1) * rowsPerThread + sourceImage->getWidth())));
		}
		threadsList.push_back(std::thread(procedura, sourceImage->getWidth(), rowsForLastThread, sourceImage->getArray() + (sourceImage->getWidth() + sourceImage->getWidth() * (threads - 1) * rowsPerThread), outputImage->getArray() + (sourceImage->getWidth() + sourceImage->getWidth() * (threads - 1) * rowsPerThread)));

			//procedura(sourceImage->getWidth(), sourceImage->getHeight(), sourceImage->getArray(), outputImage->getArray());
			//	procedura(sourceImage->getWidth(), sourceImage->getHeight()-1, sourceImage->getArray()+(sourceImage->getWidth()*3), outputImage->getArray() + (sourceImage->getWidth() * 3));
			//procedura(w, h, inI, outI);

		//wait for all threads
		for (int i = 0; i < threads; i++)
			if (threadsList[i].joinable())
				threadsList[i].join();

		//stop timer
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		this->timeTaken = duration.count();

		saveImage(true, outputPath);//save image 
		//		outputImage->saveImage(outputPath); 
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

//void EdgeManager::edgeCppFilter(ImageCV& input, ImageCV& output)
//{
//
//	//Image oldCopy(image);
//	//	int matrix[9] = { 1,1,1,1,1,1,1,1,1 };
//	//int matrix[9] = { 0.5,1,0.5,1,-6,1,0.5,1,0.5 };
//	int matrix[9] = { 0,1,0,1,-4,1,0,1,0 };
//	//for (int y = 0; y < input.getHeight(); y++)
//	//	for (int x = 0; x < input.getWidth(); x++)
//	for (int y = 3; y < input.getHeight()-3; y++)
//		for (int x = 3; x < input.getWidth()-3; x++)
//		{
//
//			int center = y * input.getWidth() * 3 + x * 3;
//			int indexMatrix[9] = { 
//				center - input.getWidth()*3 - 3,
//				center - input.getWidth() * 3,
//				center - input.getWidth() * 3 + 3,
//			center - 3,
//					center, 
//				center + 3,
//			center + input.getWidth() * 3 - 3 ,
//				center + input.getWidth() * 3 ,
//				center + input.getWidth() * 3 + 3 };
//
//			//if (indexMatrix[4] - x == 0)
//			//{
//			//	indexMatrix[0] = indexMatrix[4]; indexMatrix[1] = indexMatrix[4]; indexMatrix[2] = indexMatrix[4];
//			//}
//			//else if (((indexMatrix[4] - x) % input.getWidth()) == 0)
//			//{
//			//	indexMatrix[6] = indexMatrix[4]; indexMatrix[7] = indexMatrix[4]; indexMatrix[8] = indexMatrix[4];
//			//}
//			//if (indexMatrix[4] % input.getWidth() == 0)
//			//{
//			//	indexMatrix[0] = indexMatrix[4]; indexMatrix[3] = indexMatrix[4]; indexMatrix[6] = indexMatrix[4];
//			//}
//			//else if (((indexMatrix[4] + 1) % input.getWidth()) == 0)
//			//{
//			//	indexMatrix[2] = indexMatrix[4]; indexMatrix[5] = indexMatrix[4]; indexMatrix[8] = indexMatrix[4];
//			//}
//
//			int newR = input.getArray()[indexMatrix[0]] * matrix[0] + input.getArray()[indexMatrix[1]] * matrix[1] + input.getArray()[indexMatrix[2]] * matrix[2] +
//				input.getArray()[indexMatrix[3]] * matrix[3] + input.getArray()[indexMatrix[4]] * matrix[4] + input.getArray()[indexMatrix[5]] * matrix[5] +
//				input.getArray()[indexMatrix[6]] * matrix[6] + input.getArray()[indexMatrix[7]] * matrix[7] + input.getArray()[indexMatrix[8]] * matrix[8];
//			if (newR > 255)
//				newR = 255;
//			else if (newR <= 0)
//				newR = 0;
//
//			int newG = input.getArray()[indexMatrix[0]+1] * matrix[0] + input.getArray()[indexMatrix[1] + 1] * matrix[1] + input.getArray()[indexMatrix[2] + 1] * matrix[2] +
//				input.getArray()[indexMatrix[3] + 1] * matrix[3] + input.getArray()[indexMatrix[4] + 1] * matrix[4] + input.getArray()[indexMatrix[5] + 1] * matrix[5] +
//				input.getArray()[indexMatrix[6] + 1] * matrix[6] + input.getArray()[indexMatrix[7] + 1] * matrix[7] + input.getArray()[indexMatrix[8] + 1] * matrix[8];
//			if(newG > 255)
//				newG = 255;
//			else if (newG <= 0)
//				newG = 0;
//
//
//			int newB = input.getArray()[indexMatrix[0] + 2] * matrix[0] + input.getArray()[indexMatrix[1] + 2] * matrix[1] + input.getArray()[indexMatrix[2] + 2] * matrix[2] +
//				input.getArray()[indexMatrix[3] + 2] * matrix[3] + input.getArray()[indexMatrix[4] + 2] * matrix[4] + input.getArray()[indexMatrix[5] + 2] * matrix[5] +
//				input.getArray()[indexMatrix[6] + 2] * matrix[6] + input.getArray()[indexMatrix[7] + 2] * matrix[7] + input.getArray()[indexMatrix[8] + 2] * matrix[8];
//			if(newB > 255)
//				newB = 255;
//			else if (newB <= 0)
//				newB = 0;
//
//			//Kind of zmniejsza efekt kolorow
//			//if (newR > 50 && newG < 50 && newB < 50)
//			//	newR = 0;
//			//if (newG > 50 && newG < 50 && newR < 50)
//			//	newG = 0;
//			//if (newB > 50 && newG < 50 && newR < 50)
//			//	newB = 0;
//
//			output.getArray()[indexMatrix[4]] = newR;
//			output.getArray()[indexMatrix[4] + 1] = newG;
//			output.getArray()[indexMatrix[4]+2] = newB;
//		}
//}

EdgeManager::~EdgeManager()
{
	if(sourceImage != nullptr)
	delete sourceImage;
	if(outputImage != nullptr)
	delete outputImage;
}

void edgeCppFilterO(ImageCV& input, ImageCV& output, int startingRow, int height, bool isRGB)
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
			
			if(isRGB)
			{
				int newB = (int)input.getArray()[indexMatrix[0]] * matrix[0] + (int)input.getArray()[indexMatrix[1]] * matrix[1] + (int)input.getArray()[indexMatrix[2]] * matrix[2] +
					(int)input.getArray()[indexMatrix[3]] * matrix[3] + (int)input.getArray()[indexMatrix[4]] * matrix[4] + (int)input.getArray()[indexMatrix[5]] * matrix[5] +
					(int)input.getArray()[indexMatrix[6]] * matrix[6] + (int)input.getArray()[indexMatrix[7]] * matrix[7] + (int)input.getArray()[indexMatrix[8]] * matrix[8];
				if (newB > 200)
					newB = 255;
				else if (newB <= 0)
					newB = 0;

				int newG = (int)input.getArray()[indexMatrix[0] + 1] * matrix[0] + (int)input.getArray()[indexMatrix[1] + 1] * matrix[1] + (int)input.getArray()[indexMatrix[2] + 1] * matrix[2] +
					(int)input.getArray()[indexMatrix[3] + 1] * matrix[3] + (int)input.getArray()[indexMatrix[4] + 1] * matrix[4] + (int)input.getArray()[indexMatrix[5] + 1] * matrix[5] +
					(int)input.getArray()[indexMatrix[6] + 1] * matrix[6] + (int)input.getArray()[indexMatrix[7] + 1] * matrix[7] + (int)input.getArray()[indexMatrix[8] + 1] * matrix[8];
				if (newG > 200)
					newG = 255;
				else if (newG <= 0)
					newG = 0;

				int newR = (int)input.getArray()[indexMatrix[0] + 2] * matrix[0] + (int)input.getArray()[indexMatrix[1] + 2] * matrix[1] + (int)input.getArray()[indexMatrix[2] + 2] * matrix[2] +
					(int)input.getArray()[indexMatrix[3] + 2] * matrix[3] + (int)input.getArray()[indexMatrix[4] + 2] * matrix[4] + (int)input.getArray()[indexMatrix[5] + 2] * matrix[5] +
					(int)input.getArray()[indexMatrix[6] + 2] * matrix[6] + (int)input.getArray()[indexMatrix[7] + 2] * matrix[7] + (int)input.getArray()[indexMatrix[8] + 2] * matrix[8];
				if (newR > 200)
					newR = 255;
				else if (newR <= 0)
					newR = 0;

				output.getArray()[indexMatrix[4]] = (std::byte)newB;
				output.getArray()[indexMatrix[4] + 1] = (std::byte)newG;
				output.getArray()[indexMatrix[4] + 2] = (std::byte)newR;
			}
			
			else
			{
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
}