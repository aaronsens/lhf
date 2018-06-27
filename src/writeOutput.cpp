/*
 * writeOutput hpp + cpp protoype and define a class for writing output from
 * the LFH system (https://github.com/wilseypa/LFH). The class is designed
 * to hold all functions corresponding to wiriting output data to .csv files,
 * .mat files, console, and other additional files as they are added to the system.
 * 
 *  
 * 
 */

#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include "writeOutput.hpp"

// writeOutput constructor, currently no needed information for the class constructor
writeOutput::writeOutput(){

}

// writeStat -> write the pipeline statistics to a csv formatted file
bool writeOutput::writeStats(std::string stats, std::string filename){
	std::ofstream file(filename + "_stats.csv");
	file << "PipeName,PhysExecutionTime,MemorySize,MemoryUnits\n";
	file << stats;
	return true;	
}


// writeCSV -> write a csv formatted file of data input
bool writeOutput::writeCSV(std::string filename, std::vector<std::vector<double>>){
	std::vector<std::vector<double>> result;
	
	std::ifstream file(filename);
	
	if(!file){
		std::cout << "Failed to open file: " << filename << std::endl;
		return false;
	}
	
	// We are going to iterate through each line of the file until we reach the end
	while(!file.eof()){
		std::string line;			// Temporary (current) line
		std::vector<double> tmp;	// Temporary (current) vector
		getline(file, line);		// Read the next line from file
		std::size_t pos = std::string::npos;
		
		// Replace whitespace in the current line
		line = std::regex_replace(line, std::regex(" "), "");
		
		// Check if the line has a length (is not a blank line)
		if(line.size() > 0){
			
			// Iterate through each comma of the csv
			while((pos = line.find_first_of(",")) != std::string::npos){
				
				// Push the value found before the comma, remove from the line
				tmp.push_back(std::stod(line.substr(0,pos)));
				line.erase(0,pos + 1);
				
			}
			
			// Get the last value of the line
			tmp.push_back(std::stod(line.substr(0,pos)));
		}
		result.push_back(tmp);
		
	}
	return true;
}


// writeMAT -> write in a mat formatted file of data input
bool writeOutput::writeMAT(std::string filename, std::vector<std::vector<double>>){
	std::vector<std::vector<double>> result;
	
	std::ifstream file;
	file.open(filename);
	
	std::string line;			//Temporary (current) line
	
	// Get the number of vectors
	getline(file,line);
	line = std::regex_replace(line,std::regex(" "),"");
	int vectors = std::stoi(line);
	
	// Get the number of dimensions
	getline(file,line);
	line = std::regex_replace(line,std::regex(" "),"");
	int dimensions = std::stoi(line);
	
	// We are going to iterate through each line of the file until we reach the end
	while(!file.eof()){
		std::vector<double> tmp;	//Temporary (current) vector
		getline(file, line);		//Read the next line from file
		std::size_t p = std::string::npos;
		
		// Replace whitespace in the current line
		line = std::regex_replace(line, std::regex(" "), "");
		
		// Check if the line has a length (is not a blank line)
		if(line.size() > 0){
			
			// Iterate through each comma of the csv
			while((p = line.find_first_of(",")) != std::string::npos){
				
				// Push the value found before the comma, remove from the line
				tmp.push_back(std::stod(line.substr(0,p)));
				line.erase(0,p + 1);
				
			}
			
			// Get the last value of the line
			tmp.push_back(std::stod(line.substr(0,p)));
		}
		result.push_back(tmp);
		
	}
	return true;
}


// writeConsole -> write data input to console (hopefully pretty-print)
bool writeOutput::writeConsole(pipePacket* workData){
	std::vector<std::vector<double>> result;
	
	std::cout << "_________workingData OUTPUT__________" << std::endl;
		
	for(unsigned i = 0; i < workData->workData.workingData.size(); i++){
		for(unsigned j = 0; j < workData->workData.workingData[i].size(); j++){
			std::cout << workData->workData.workingData[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	return true;
	
}
