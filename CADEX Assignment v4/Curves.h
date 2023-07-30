#define _USE_MATH_DEFINES

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <omp.h>

#ifndef CURVES_H
#define CURVES_H

#ifdef DLLBuild
    #define DLLExport __declspec(dllexport) 
#endif
#ifndef DLLBuild
    #define DLLExport __declspec(dllimport) 
#endif

extern "C" {

#define PI 3.14159265358979
// A library for curves.
namespace Curves {

    //============= CLASSES =============

    // A class to hold data of a 3D point.
    // Has X,Y,Z coordinates.
    class DLLExport Point3D;

    // 3D vector is defined by a 3D point. 
    DLLExport typedef Point3D Vector3D;

    // An enumerator to hold data of a curve's type.
    enum CurveType {
        Type_Ellipse,
        Type_Circle,
        Type_Helix3D
    };

    // A pure abstract class for any type of curve.
    class DLLExport Curve {
    public:
        virtual Point3D calcPoint(
            double t
        ) const = 0;
        virtual Vector3D calcDerivative(
            double t
        ) const = 0;
        virtual CurveType getType() const = 0;
    };

    // A class to define a ellipse-type curve.
    // Defined by its X and Y radii.
    class DLLExport Ellipse;

    // A class to define a circle-type curve.
    // It is a special case of an ellipse where X and Y radii are the same.
    class DLLExport Circle;

    // A class to define a 3D helix type curve.
    // It is built on a circle curve with an added Z step.
    class DLLExport Helix3D;

    //============= FUNCTIONS =============

    // Create a vector of unique pointers to randomly generated curves.
    DLLExport std::vector<std::unique_ptr<Curve>> createRandomCurves(int inAmount);

    // From a storage vector of unique pointers to curves, get a vector of simple pointers to curves.
    DLLExport std::vector<Curve*> getCurvePointers(std::vector<std::unique_ptr<Curve>>& inCurves);

    // Print points and derivatives of curves at T.
    DLLExport void printCurvesAtT(std::vector<Curve*> inCurves, double t);
    
    // Print points and derivatives of circles at T.
    DLLExport void printCirclesAtT(std::vector<Circle*> inCurves, double t);

    // From a vector of curves, return a vector of just circles.
    DLLExport std::vector<Circle*> getCircles(std::vector<Curve*>& inCurves);

    // Comparator for sort() to use to sort a vector of circles in ascending order of their radii.
    bool compareCirclesRadiusAsc(Circle* inCircle1, Circle* inCircle2);

    // Sort a vector of circles in ascending order of their radii.
    DLLExport std::vector<Circle*> sortCirclesRadiusAsc(std::vector<Circle*>& inCircles);

    // Sum up all of the circles' radii from a vector of pointers.
    DLLExport double computeSumOfCirclesRadii(std::vector<Circle*>& inCircles);

    //===================== FUNCTION TABLE ==========================

    //A definition for a table of all DLL functions
    struct func_table {
        std::vector<std::unique_ptr<Curve>> (*createRandomCurves)(int);
        std::vector<Curve*> (*getCurvePointers)(std::vector<std::unique_ptr<Curve>>& inCurves);
        void (*printCurvesAtT)(std::vector<Curve*>,double);
        void (*printCirclesAtT)(std::vector<Circle*>, double);
        std::vector<Circle*> (*getCircles)(std::vector<Curve*>&);
        std::vector<Circle*> (*sortCirclesRadiusAsc)(std::vector<Circle*>&);
        double (*computeSumOfCirclesRadii)(std::vector<Circle*>&);
    };

    #ifdef DLLBuild
        //An actual table of pointers to functions to use in DLL.
        static struct func_table table = {
            &createRandomCurves,
            &getCurvePointers,
            &printCurvesAtT,
            &printCirclesAtT,
            &getCircles,
            &sortCirclesRadiusAsc,
            &computeSumOfCirclesRadii
        };

        //A function to get the function table.
        DLLExport struct func_table *getFuncTable(void) {
            return &table;
        }
    #endif
};

}
#endif
