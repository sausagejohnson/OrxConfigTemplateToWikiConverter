#include <stdio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string.h>
#include <regex>
#include <algorithm>
#include <sstream>

using namespace std;


int convertFile(std::string fileName){
	string orxEnv = std::getenv("ORX");
	cout << "orxEnvironment is: " << orxEnv << endl;

	string pathToSettingsConfigFile = orxEnv + "\\bin\\" + fileName + ".ini";
	cout << "Path to " + fileName + ".ini is: " << pathToSettingsConfigFile << endl;
	
	string pathToWikiConfigFile = orxEnv + "\\bin\\" + fileName + "WikiFormat.ini";
	cout << "Path to " + fileName + "WikiFormat.ini is: " << pathToWikiConfigFile << endl;

	ifstream configFile;
	configFile.open(pathToSettingsConfigFile, ios::in);
	
	ofstream wikiFormattedFile;
	wikiFormattedFile.open (pathToWikiConfigFile, ofstream::out);
	
	std::stringstream infoBuffer;
    std::stringstream detailsBuffer;
	
	if (configFile.fail()){
		cout << "Couldn't write the new file. Sorry. It most likely due to not having rights to create a file in that location. Quitting out." << '\n';
		getchar();
		return 0;
	} 

	cout << "Start conversion..." << endl << endl;
	
	std::string line;
	if (configFile.good()){
		while ( getline(configFile, line) ){
			if (line[0] != ';' && line.length() > 0){ //ignore all lines starting with a comment, or empty lines.
				int commentSeparatorPosition = line.find_first_of(";");
				
				if (commentSeparatorPosition == -1){ //no comments, take the whole line
					//if a new section, dump buffers to file and continue
					wikiFormattedFile << infoBuffer.str() << endl << endl << detailsBuffer.str() << endl;
					infoBuffer.str("");	
					infoBuffer.clear();
					detailsBuffer.str("");	
					detailsBuffer.clear();
					
					//now move onto the next section
					infoBuffer << line << endl;
				} else {
					std::string information = line.substr(0, commentSeparatorPosition);
					std::string detailPart = line.substr(commentSeparatorPosition+1, line.length()-1);
					int detailsNBPosition = detailPart.find_first_of("; NB: ");
					std::string details = (detailsNBPosition == -1) ? "" : detailPart.substr(detailsNBPosition+5, detailPart.length()-1);
					
					int keyValueSeparatorPosition = information.find_first_of("=");
					std::string informationKeyName = information.substr(0, keyValueSeparatorPosition-1);
					
					std::regex leftBracket("\\[");
					std::regex rightBracket("\\]");
					std::regex angleBracketContent("<(.*?)>");
					std::regex pipeSpace("\\|");

					std::string infoWithCorrectedLeftBracket = std::regex_replace(information, leftBracket, "<");
					std::string infoWithCorrectedBrackets = std::regex_replace(infoWithCorrectedLeftBracket, rightBracket, ">");
					std::string finalFormattedInfo = std::regex_replace(infoWithCorrectedBrackets, pipeSpace, " | ");
					
					std::smatch typeNamematch;
					std::regex_search(finalFormattedInfo, typeNamematch, angleBracketContent);

					std::string typeNameString = typeNamematch[0];
					std::transform(typeNameString.begin(), typeNameString.end(), typeNameString.begin(), ::tolower);
					if (typeNamematch.size() > 0){
						infoBuffer << typeNamematch.prefix() << typeNameString << endl;	
					} else {
						infoBuffer << finalFormattedInfo << endl;
					}
					
					if (details.length() > 0){
						detailsBuffer << "* ''" << informationKeyName << "'': " << details << endl;
					}
					
				}
			}
			cout << "#";
		}
	}
	
	wikiFormattedFile.flush();
	wikiFormattedFile.close();
	configFile.close();
	
	cout << endl << endl << "Conversion complete. " << pathToWikiConfigFile << " has been saved." << endl << endl;
	
	return 1;
}

int main(int argc, char **argv)
{
	cout << "Running as: " << argv[0] << endl;
	
	convertFile("CreationTemplate");
	convertFile("SettingsTemplate");

	cout << "Press any key to close." << endl;
	
	getchar();
	return 0;
}
