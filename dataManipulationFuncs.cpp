#include "dataManipulationFuncs.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;



/**
 * Parse data from a csv file. All datapoints in the csv are doubles
 *
 * @param[out] result data from the csv file. result[i] is the data from a column i.
 * @param[in] pathToFile path the csv
 * @param[in] numCol number of columns in the csv 
 */
vector<vector<double>> parseData(const string pathToFile, size_t numCol) {
    vector<vector<double>> result;
    for(size_t i = 0; i < numCol; i++) {
        result.push_back(vector<double>{});
    }

    ifstream csv;
    csv.open(pathToFile);
    if (!csv.is_open()) {
        cerr << "ERROR: " << pathToFile << " did not open correctly";
        exit(2);
    } else {
        //cout << "opened file" << endl;
    }

    int i;
    vector<double> row;
    string line;
    double field;
    while (getline(csv,line)) {
        stringstream ss(line);
        row.clear();
        i = 0;
        while (ss>>field) {
            row.push_back(field);
            if (ss.peek() == ',') ss.ignore();
        }

        if (row.size() == numCol) {
            for (i = 0; i < numCol; i++) {
                result.at(i).push_back(row.at(i));
            }
        }
        //cout << row.size() << endl;
        /*if (row.size() == numCol) {  
            cout << "Ma: " << row.at(0) << "ODelta: " << row.at(1) << " CDelta: " << row.at(2) << endl;
            for (i = 0; i < numCol; i++) {
                //adds values to corresponding columns
                result.at(i).push_back(row.at(i));
            }
        }*/
    }
    csv.close();
    if (csv.eof()) {
        //cout << "Read File Successfully" << endl;
    } else {
        //cerr << "Error reading file" << endl;
        exit(2);
    }

    return result;
}


/**
 * Smooth data from csv using the sliding window technique. 
   HINT: use getAvgNextNValues in this function so get that working first
 *
 * @param[out] result smoothed data. result[i] is the smoothed data from a column i.
 * @param[in] rawData the raw (not smoothed) data already gathered from parseData.  
 * @param[in] windowSize the length of the window
 */
vector<vector<double>> smoothData(vector<vector<double>>& rawData, size_t windowSize) {
    if(rawData.size() == 0){ 
        cerr << "No data provided to the smooth data function" << endl;
        exit(2);
    }

    //creates vector<vector<double>> same size as rawData
    vector<vector<double>> result(rawData);

    double value;
    for (int c = 0; c < rawData.size(); c++) {
        //computing averages with standard window lengths
        for (int i = 0; i < 100/*rawData.at(0).size()*/; i++) {
            value = getAvgNextNValues(rawData.at(c),i,windowSize);
            //cout << value << " ";
            result.at(c).at(i) = value;    
        }
        //cout << endl;
    }
    return result;
}

/**
 * filter data from csv based on its age. 
 *
 * @param[out] result data with that has ages in the range [minAge, maxAge]
 * @param[in] minAge the minAge as an int
 * @param[in] maxAge the minAge as an int
 */
vector<vector<double>> filterData(vector<vector<double>>&  rawData, int minAge, int maxAge) {
    if(rawData.size() == 0){ 
        cerr << "No data provided to the filter data function" << endl;
        exit(2);
    }

    vector<vector<double>> result;
    for(size_t i = 0; i < rawData.size(); i++){
        result.push_back(vector<double>{});
    }

    double age; 
    for(size_t r = 0; r < rawData.at(0).size(); r++) {
        age = rawData.at(0).at(r);
        if (age >= minAge && age <= maxAge) {
            for (int c = 0; c < result.size(); c++) {
                result.at(c).push_back(rawData.at(c).at(r));
                //cout << rawData.at(c).at(r) << " ";
            }
            //cout << endl;
        }
    }

    return result;
}
 
/**
 * Compute the avg of the values in a sliding window given a starting index and window length. 
    If the length of the window exceeds the length of the list, compute the avg of the remaining elements instead.
 *
 * @param[out] avg the avg of the sliding window. Don't need to round this.
 * @param[in] startIndex the starting index of the sliding window
 * @param[in] windowLength the length of the window
 * @param[in] v a vector of doubles

 * @Example 1:  
    v = [1.0,2.0,3.0,4.0,5.5]
    startIndex = 2
    windowLength = 3
    avg = (3.0 + 4.0 + 5.5) / 3 = 4.16

 * @Example 2:  
    v = [1.0,2.0,3.0,4.0,5.5]    windowLength = 3
    avg = (4.0 + 5.5) / 2 = 9.5
 */
double getAvgNextNValues(vector<double> const& v, size_t startIndex , size_t windowLength){ 
    //cout << "Vector: " << endl;
    

    double sum = 0;
    double result = 0;
    if (startIndex + windowLength <= v.size()) {
        for (int i = 0; i < windowLength; i++) {
            sum += v.at(i+startIndex);
        }
        result = sum/windowLength;

    } else {
        for (int i = startIndex; i < v.size(); i++) {
            sum += v.at(i);
        }
        result = sum/(v.size()-startIndex);
    }
    //cout << "Sum: " << sum << endl;
    //cout << "Result: " << result << endl;
    return result;
}   

/*
int main() {
    parseData("2008CompilationData.csv",3);
    return 0;
}*/