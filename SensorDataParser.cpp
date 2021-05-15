#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int main()
{
    const string mDelimiter = ",";
    //File names
    string mainFileName = "Input Files/Estimation.csv";
    string acceleratorFileName = "Input Files/Acceleration.csv";
    string gyroFileName = "Input Files/Gyro.csv";
    string magneticFileName = "Input Files/Magnetic.csv";
    string outputFileName = "Output Files/Parsed.csv";

    // C++ File representations
    vector<vector<double>> mainFile;
    vector<vector<double>> accelerationFile;
    vector<vector<double>> gyroFile;
    vector<vector<double>> magneticFile;
    double mainZeroTime = 0;

    vector<vector<double>> outputFile;

    // File instances
    ifstream mainFileStream(mainFileName);
    if (!mainFileStream)
    {
        cout << "Main file not found" << endl;
    }
    ifstream accelerationFileStream(acceleratorFileName);
    ifstream gyroFileStream(gyroFileName);
    ifstream magneticFileStream(magneticFileName);
    ofstream outputFileStream(outputFileName);


    cout << "Reading files...\n";
    
    
    string lineBuff;
    while (getline(mainFileStream, lineBuff))
    {
        //Split line
        vector<string> line;
        size_t pos = 0;
        string token;
        vector<double> dblLine;
        while ((pos = lineBuff.find(mDelimiter)) != string::npos)
        {
            token = lineBuff.substr(0, pos);
            if (token.size() > 0)
            {
                line.push_back(token);
            }
            lineBuff.erase(0, pos + mDelimiter.length());
        }
        if (lineBuff.length() != 0)
        {
            line.push_back(lineBuff);
        }
        if (line.size() != 4)
        {
           // throw "Main file dimensions not ok\n";
        }
        dblLine.push_back(atof(line.at(0).c_str()));
        dblLine.push_back(atof(line.at(1).c_str()));
        dblLine.push_back(atof(line.at(2).c_str()));
        dblLine.push_back(atof(line.at(3).c_str()));
        mainFile.push_back(dblLine);
    }

   while (getline(accelerationFileStream, lineBuff))
    {
        //Split line
        vector<string> line;
        size_t pos = 0;
        string token;
        vector<double> dblLine;
        while ((pos = lineBuff.find(mDelimiter)) != string::npos)
        {
            token = lineBuff.substr(0, pos);
            line.push_back(token);
            lineBuff.erase(0, pos + mDelimiter.length());
        }
        if (lineBuff.length() != 0)
        {
            line.push_back(lineBuff);
        }
        if (line.size() != 4)
        {
            throw "Main file dimensions not ok\n";
        }
        dblLine.push_back(atof(line.at(0).c_str()));
        dblLine.push_back(atof(line.at(1).c_str()));
        dblLine.push_back(atof(line.at(2).c_str()));
        dblLine.push_back(atof(line.at(3).c_str()));
        accelerationFile.push_back(dblLine);
    }

   while (getline(gyroFileStream, lineBuff))
   {
       //Split line
       vector<string> line;
       size_t pos = 0;
       string token;
       vector<double> dblLine;
       while ((pos = lineBuff.find(mDelimiter)) != string::npos)
       {
           token = lineBuff.substr(0, pos);
           line.push_back(token);
           lineBuff.erase(0, pos + mDelimiter.length());
       }
       if (lineBuff.length() != 0)
       {
           line.push_back(lineBuff);
       }
       if (line.size() != 4)
       {
           throw "Main file dimensions not ok\n";
       }
       dblLine.push_back(atof(line.at(0).c_str()));
       dblLine.push_back(atof(line.at(1).c_str()));
       dblLine.push_back(atof(line.at(2).c_str()));
       dblLine.push_back(atof(line.at(3).c_str()));
       gyroFile.push_back(dblLine);
   }

   while (getline(magneticFileStream, lineBuff))
   {
       //Split line
       vector<string> line;
       size_t pos = 0;
       string token;
       vector<double> dblLine;
       while ((pos = lineBuff.find(mDelimiter)) != string::npos)
       {
           token = lineBuff.substr(0, pos);
           line.push_back(token);
           lineBuff.erase(0, pos + mDelimiter.length());
       }
       if (lineBuff.length() != 0)
       {
           line.push_back(lineBuff);
       }
       if (line.size() != 4)
       {
           throw "Main file dimensions not ok\n";
       }
       dblLine.push_back(atof(line.at(0).c_str()));
       dblLine.push_back(atof(line.at(1).c_str()));
       dblLine.push_back(atof(line.at(2).c_str()));
       dblLine.push_back(atof(line.at(3).c_str()));
       magneticFile.push_back(dblLine);
   }
   int i = 0;
   mainZeroTime = mainFile.at(0).at(0);

   cout << "Parsing in progress...\n";
   double maxAccDiff = -1;
   double maxGyroDeff = -1;
   double maxMagDiff = -1;
   for (int i = 0; i < mainFile.size(); i++)
   {
       //Add Main file to output
       vector<double> outputLine;

       //Multiply by -1 and change sequency to make compatible with the other datasets
       outputLine.push_back(mainFile.at(i).at(0));
       outputLine.push_back(-1 * mainFile.at(i).at(2));
       outputLine.push_back(-1 * mainFile.at(i).at(3));
       outputLine.push_back(-1 * mainFile.at(i).at(1));

       //Add best acceleration
       double mindiff = 99999.0;
       int minDiffIndex = 0;
       for (int j = 0; j < accelerationFile.size(); j++)
       {
           if (abs(accelerationFile.at(j).at(0) - mainFile.at(i).at(0)) <= mindiff)
           {
               mindiff = abs(accelerationFile.at(j).at(0) - mainFile.at(i).at(0));
               minDiffIndex = j;
           }
       }
       if (maxAccDiff < abs(accelerationFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0)))
       {
           maxAccDiff = abs(accelerationFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0));
       }
       outputLine.push_back(accelerationFile.at(minDiffIndex).at(1));
       outputLine.push_back(accelerationFile.at(minDiffIndex).at(2));
       outputLine.push_back(accelerationFile.at(minDiffIndex).at(3));
       
       //Add best gyro
       mindiff = 99999.0;
       minDiffIndex = 0;
       for (int j = 0; j < gyroFile.size(); j++)
       {
           if (abs(gyroFile.at(j).at(0) - mainFile.at(i).at(0)) <= mindiff)
           {
               mindiff = abs(gyroFile.at(j).at(0) - mainFile.at(i).at(0));
               minDiffIndex = j;
           }
       }
       if (maxGyroDeff < abs(gyroFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0)))
       {
           maxGyroDeff = abs(gyroFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0));
       }
       outputLine.push_back(gyroFile.at(minDiffIndex).at(1));
       outputLine.push_back(gyroFile.at(minDiffIndex).at(2));
       outputLine.push_back(gyroFile.at(minDiffIndex).at(3));
       
       //Add best magneto
       mindiff = 99999.0;
       minDiffIndex = 0;
       for (int j = 0; j < magneticFile.size(); j++)
       {
           if (abs(magneticFile.at(j).at(0) - mainFile.at(i).at(0)) <= mindiff)
           {
               mindiff = abs(magneticFile.at(j).at(0) - mainFile.at(i).at(0));
               minDiffIndex = j;
           }
       }
       if (maxMagDiff < abs(magneticFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0)))
       {
           maxMagDiff = abs(magneticFile.at(minDiffIndex).at(0) - mainFile.at(i).at(0));
       }
       outputLine.push_back(magneticFile.at(minDiffIndex).at(1));
       outputLine.push_back(magneticFile.at(minDiffIndex).at(2));
       outputLine.push_back(magneticFile.at(minDiffIndex).at(3));

       //Add the line to the final file
       outputFile.push_back(outputLine);

   }

   //Shifting time
   for (int i = 0; i < outputFile.size(); i++)
   {
       outputFile.at(i).at(0) = (outputFile.at(i).at(0) - mainZeroTime) / 1000;
   }

   cout << "Max acceleration time difference: " << maxAccDiff << endl;
   cout << "Max Gyro time difference: " << maxGyroDeff << endl;
   cout << "Max Magnetometer time difference: " << maxMagDiff << endl;
   cout << "Writing output file" << endl;

   for (int i = 0; i < outputFile.size(); i++)
   {
       string outputLine;
       for (int j = 0; j < outputFile.at(i).size(); j++)
       {
           outputLine += to_string(outputFile.at(i).at(j));
           if (j < outputFile.at(i).size() - 1)
           {
               outputLine += ",";
           }
       }
       outputFileStream << outputLine << endl;
   }
}