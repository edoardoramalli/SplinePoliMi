#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

#include "Utilities.h"
#include "BasisFunction.h"
#include "Spline.h"
#include "Settings.h"
#include "ComputeSpline.h"



extern "C"
void compute_spline_cpp(double* x, double* y, int length,
            int* numberOfKnots, int* numberOfPolynomials, double* coeffDO, double* knots,
            bool verbose,
            int m_, int g_, int lambdaSearchInterval_, int numberOfStepsLambda_, int numberOfRatiolkForAICcUse_,
            double fractionOfOrdinateRangeForAsymptoteIdentification_, double fractionOfOrdinateRangeForMaximumIdentification_,
            bool possibleNegativeOrdinates_, bool removeAsymptotes_, int graphPoints_, char* criterion_){


    // ----------  SET VARIABLE  ----------

    vector<double> x_vector(x, x + length);
    vector<double> y_vector(y, y + length);





    // ----------  SET SETTINGS  ----------

    m = m_;
    g = g_;
    lambdaSearchInterval = lambdaSearchInterval_;
    numberOfStepsLambda = numberOfStepsLambda_;
    numberOfRatiolkForAICcUse = numberOfRatiolkForAICcUse_;
    fractionOfOrdinateRangeForAsymptoteIdentification = fractionOfOrdinateRangeForAsymptoteIdentification_;
    fractionOfOrdinateRangeForMaximumIdentification = fractionOfOrdinateRangeForMaximumIdentification_;
    possibleNegativeOrdinates = possibleNegativeOrdinates_;
    removeAsymptotes = removeAsymptotes_;
    graphPoints = graphPoints_;
    criterion = string(criterion_);



    // ----------  COMPUTE BEST SPLINE  ----------


    vector<Spline> possibleSplines = calculateSplines(x_vector, y_vector, true);

    int index_best = calculateBestSpline(x_vector, y_vector, criterion, possibleSplines);

    Spline best_spline = possibleSplines[index_best];


    // ---------- VERBOSE ----------
    if(verbose){
        cout << "X:" << endl;
        printV_inLine(x_vector);
        cout << "Y:" << endl;
        printV_inLine(y_vector);
        cout << "KNOTS:" << endl;
        printV_inLine(best_spline.knots);
        cout << "CoeffD0:" << endl;
        printM(best_spline.coeffD0);
        cout << "SETTINGS:" << endl;
        printSettings();
        cout << "D0:" << endl;
        printM(evaluateBestSplineD0(best_spline));
    }



    // ----------  PASS BACK THE RESULTS  ----------

    *numberOfKnots = best_spline.numberOfKnots;
    *numberOfPolynomials = best_spline.numberOfPolynomials;

    for(int i = 0; i < best_spline.coeffD0.size(); i++){
        for(int j = 0; j < best_spline.coeffD0[i].size(); j++){
            coeffDO[i * best_spline.coeffD0[i].size() + j] = best_spline.coeffD0[i][j];
        }
    }

    for(int i = 0; i < best_spline.numberOfKnots; i++){
        knots[i] = best_spline.knots[i];
    }



    return;
}

int main() {
//    vector<vector<double>> splineD0;
//    vector<vector<double>> splineD1;
//
//    cout << "\nRunning Spline Calculations\n";
//
//    // qui scrivo io
//    // DATI DI INPUT
//    // NB!!!!! devono essere ordinate rispetto x
//    vector<double> x = {0.0 ,0.1, 0.2, 0.4};
//    vector<double> y = {97,98, 99, 100};
//
//    vector<Spline> possibleSplines = calculateSplines(x,y,removeAsymptotes);
//    int index_best = calculateBestSpline(x,y,criterion, possibleSplines);
//    splineD0 = evaluateBestSplineD0(possibleSplines[index_best]);
//    splineD1 = evaluateBestSplineD1(possibleSplines[index_best]);

    return 0;

}

