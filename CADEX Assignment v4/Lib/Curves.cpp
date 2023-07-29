#define _USE_MATH_DEFINES

#define DLLBuild
#include "Curves.h"

namespace Curves {
    class Point3D {
        double x,y,z;
    public:
        void set(double inX, double inY, double inZ) {
            x = inX;
            y = inY;
            z = inZ;
        }
        
        Point3D()
        {set(0,0,0);}

        Point3D(
            double inX, double inY, double inZ
        ) 
        {set(inX,inY,inZ);}

        double getX() {
            return x;
        }
        
        double getY() {
            return y;
        }

        double getZ() {
            return z;
        }
    };

    typedef Point3D Vector3D;

    class Ellipse : public Curve {
        double xRadius;
        double yRadius;
    public:
        void set(
            double inXRadius,
            double inYRadius
        ) {
            xRadius=inXRadius;
            yRadius=inYRadius;
        }

        double getXRadius() {return xRadius;}
        double getYRadius() {return yRadius;}


        Ellipse(
            double inXRadius,
            double inYRadius
        ) 
        {
            if (inXRadius < 0 || inYRadius < 0) {
                throw std::invalid_argument("Curve has a negative radius.");
            }
            set(inXRadius, inYRadius);
        };

        CurveType getType() const override {
            return Type_Ellipse;
        }

        Point3D calcPoint(
            double t
        ) const override {
            double _x = std::cos(t)*xRadius;
            double _y = std::sin(t)*yRadius;
            return Point3D(_x,_y,0);
        };

        Vector3D calcDerivative(
            double t
        ) const override {
            double _x = -1*sin(t)*xRadius;
            double _y = cos(t)*yRadius;
            return Vector3D(_x,_y,0);
        }
    };

    class Circle : public Curve {
        Ellipse ellipse;
    public:
        void set(double inRadius) {
            ellipse.set(inRadius,inRadius);
        }

        Circle(
            double inRadius
        ) : ellipse(inRadius,inRadius)
        {set(inRadius);};
        

        double getRadius() {return ellipse.getXRadius();}

        CurveType getType() const override {
            return Type_Circle;
        }

        Point3D calcPoint(double t) const override {return ellipse.calcPoint(t);}
        Vector3D calcDerivative(double t) const override {return ellipse.calcDerivative(t);}
    };

    class Helix3D : public Curve {
        Circle circle;
        double step;
    public:
        void set(double inRadius, double inStep) {
            step = inStep;
            circle = Circle(inRadius);
        }

        Helix3D(
            double inRadius,
            double inStep
        ) : circle(inRadius)
        {set(inRadius, inStep);}

        double getRadius() {return circle.getRadius();}
        double getStep() {return step;}

        Point3D calcPoint(
            double t
        ) const override {
            Point3D _point = circle.calcPoint(t);
            _point.set(_point.getX(), _point.getY(), t/(PI*2)*step);
            return _point;
        };

        Point3D calcDerivative(
            double t
        ) const override {
            Vector3D _derivative = circle.calcDerivative(t);
            _derivative.set(_derivative.getX(), _derivative.getY(), step/(PI*2));
            return _derivative;
        };

        CurveType getType() const override {
            return Type_Helix3D;
        }
    };

    std::vector<std::unique_ptr<Curves::Curve>> createRandomCurves(int inAmount) {
        std::vector<std::unique_ptr<Curves::Curve>> curves;
        for (int i=0; i<inAmount; i++) {
            std::unique_ptr<Curve> newCurve;
            switch (rand()%3) {
                case 0:
                    curves.push_back(std::unique_ptr<Curves::Curve>(new Curves::Ellipse(rand()%20+1, rand()%20+1)));
                    break;
                case 1:
                    curves.push_back(std::unique_ptr<Curves::Curve>(new Curves::Circle(rand()%20+1)));
                    break;
                case 2:
                    curves.push_back(std::unique_ptr<Curves::Curve>(new Curves::Helix3D(rand()%20+1, rand()%20+1)));
                    break;
                default:
                    break;
            }
        }
        return curves;
    }

    std::vector<Curve*> getCurvePointers(std::vector<std::unique_ptr<Curve>>& inCurves) {
        std::vector<Curve*> curvePointerVector;
        for (std::unique_ptr<Curve>& uniquePtrCurve : inCurves) {
            curvePointerVector.push_back(uniquePtrCurve.get());
        }
        return curvePointerVector;
    }

    void printCurvesAtT(std::vector<Curve*> inCurves, double t) {
        int i = 0;
        for (Curve* oneCurve : inCurves) {
            Point3D curvePoint = oneCurve->calcPoint(t);
            Vector3D curveDerivative = oneCurve->calcDerivative(t);

            std::cout << "Curve " << ++i;

            switch (oneCurve->getType()) {
                case Type_Ellipse:
                    std::cout << " (Ellipse xr=" << ((Ellipse*)oneCurve)->getXRadius() << " yr=" << ((Ellipse*)oneCurve)->getYRadius() << ")" << std::endl;
                    break;
                case Type_Circle:
                    std::cout << " (Circle r=" << ((Circle*)oneCurve)->getRadius() << ")" << std::endl;
                    break;
                case Type_Helix3D:
                    std::cout << " (Helix3D r=" << ((Helix3D*)oneCurve)->getRadius() << " s=" << ((Helix3D*)oneCurve)->getStep() << ")" << std::endl;
                    break;
            }

            std::cout << "f(" << t << "):  x " << curvePoint.getX() << " y " << curvePoint.getY() << " z " << curvePoint.getZ() << std::endl; 
            std::cout << "f'(" << t << "): x " << curveDerivative.getX() << " y " << curveDerivative.getY() << " z " << curveDerivative.getZ() << std::endl;

            std::cout << std::endl;
        }
    }

    void printCirclesAtT(std::vector<Circle*> inCircles, double t) {
        int i = 0;
        for (Circle* oneCurve : inCircles) {
            Point3D curvePoint = oneCurve->calcPoint(t);
            Vector3D curveDerivative = oneCurve->calcDerivative(t);

            std::cout << "Curve " << ++i;

            std::cout << " (Circle r=" << oneCurve->getRadius() << ")" << std::endl;

            std::cout << "f(" << t << "):  x " << curvePoint.getX() << " y " << curvePoint.getY() << " z " << curvePoint.getZ() << std::endl; 
            std::cout << "f'(" << t << "): x " << curveDerivative.getX() << " y " << curveDerivative.getY() << " z " << curveDerivative.getZ() << std::endl;

            std::cout << std::endl;
        }
    }

    std::vector<Circle*> getCircles(std::vector<Curve*>& inCurves) {
        std::vector<Circle*> all;
        for (Curve* oneCurve : inCurves) {
            if (oneCurve->getType() == Type_Circle){
                all.push_back((Circle*)oneCurve);
            }
        }
        return all;
    }

    bool compareCirclesRadiusAsc(Circle* inCircle1, Circle* inCircle2) {
        return (((Circle*)inCircle1)->getRadius() < ((Circle*)inCircle2)->getRadius());
    }

    std::vector<Circle*> sortCirclesRadiusAsc(std::vector<Circle*>& inCircles) {
        std::sort(inCircles.begin(), inCircles.end(), compareCirclesRadiusAsc);
        return inCircles;
    }

    double computeSumOfCirclesRadii(std::vector<Circle*>& inCircles) {
        double sum = 0;
        #pragma omp parallel for reduction(+:sum)
        for (Circle* oneCircle : inCircles) {
            sum += oneCircle->getRadius();
        }
        return sum;
    };
};
