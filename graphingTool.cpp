#include "dataManipulationFuncs.h"
#include "matplotlibcpp.h"
#include <vector>

using namespace std;
namespace plt = matplotlibcpp;

/**
 * Generates a scatterPlot using matplotlib and saves it as {title}.png
 *
 * @param[in] x x data points
 * @param[in] y y data points 
 * @param[in] xLabel x-axis label on graph
 * @param[in] yLabel y-axis label on graph
 * @param[in] title title of graph
 * @param[in] color color of scatter points on graph
 */
void scatterPlot(
    const vector<double>& x, 
    const vector<double>& y, 
    const string xlabel, 
    const string ylabel, 
    const string title, 
    const string color) {    
    
    /* Plot line from given x and y data and set the color. */
    /* 
    Hint: You can use a scatter function to create a scatter plot here. Keywords variable is a map that stores the styles of the plot.
    Ref: https://github.com/lava/matplotlib-cpp/blob/master/matplotlibcpp.h#L993
    */
    plt::figure();
    plt::scatter(x,y,1.0,{{"color",color}});
    /* set x and y labels */
    plt::xlabel(xlabel);
    plt::ylabel(ylabel);

    /* Add graph title */
    plt::title(title);

    /* Save the image as {title}.png */
    plt::save("./"+title+".png");
}

void printVector(vector<double> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    } cout << endl;
}

int main() {
    const size_t NUM_COLUMNS = 3;
    const size_t WINDOW_SIZE = 15;
    const int MIN_AGE = 53;
    const int MAX_AGE = 57;
   
    /* Deliverable 1 */
    vector<vector<double>> data = parseData("./2008CompilationData.csv", NUM_COLUMNS);
    
    /* Deliverable 2 */
    scatterPlot(data[0], data[1], "Age (ma)", "d18O", "d18O vs Age (ma)", "blue");
    scatterPlot(data[0], data[2], "Age (ma)", "d13C", "d13C vs Age (ma)", "red");

    /* Deliverable 3 */
    vector<vector<double>> smoothedData = smoothData(data, WINDOW_SIZE);


/*
    vector<double> testVector = {1.1, 5.6, 3.3, 4.2, 6.1, 100.9};
    vector<double> smoothedTestData1 = smoothData(testVector, 1);
    printVector(smoothedTestData1);
  */ 

    /* Deliverable 4 */
    //cout << "smoothed" << endl;
    scatterPlot(smoothedData[0], smoothedData[1], "Age (ma)", "d18O", "d18O Smoothed vs Age (ma)", "blue");
    scatterPlot(smoothedData[0], smoothedData[2], "Age (ma)", "d13C", "d13C Smoothed vs Age (ma)", "red");

    /* Deliverable 5 */
    vector<vector<double>> filteredData = filterData(data, MIN_AGE, MAX_AGE);

    /* Deliverable 6 */
    //cout << "filtered" << endl;
    scatterPlot(filteredData[0], filteredData[1], "Age (ma)", "d18O", "d18O Filtered vs Age (ma)", "blue");
    scatterPlot(filteredData[0], filteredData[2], "Age (ma)", "d13C", "d13C Filtered vs Age (ma)", "red");
   return 0;   
}

