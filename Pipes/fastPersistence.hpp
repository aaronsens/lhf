#pragma once

// Header file for bettiPipe class - see bettiPipe.cpp for descriptions
#include <map>
#include <queue>
#include <unordered_map>
#include "basePipe.hpp"
#include "utils.hpp"


class fastPersistence : public basePipe {
  private:
  
	utils ut;
	double maxEpsilon;
	std::string twist;
  public:
	struct tArrayEntry_t{
		bool marked = false;
		int ti = -1;
		double birth;
		double death = -1;
		std::set<unsigned> simplex;
	};
	bool alterPipe = false;
	
	std::vector<tArrayEntry_t> tArray;
	
	int dim;
    fastPersistence();
    pipePacket runPipe(pipePacket inData);
    bool configPipe(std::map<std::string, std::string> configMap);
	void outputData(pipePacket);
};

