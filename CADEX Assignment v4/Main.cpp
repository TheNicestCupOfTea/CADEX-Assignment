#include "Main.h"

// Function to fetch functions from a DLL library.
template <typename T>
std::function<T> loadDllFunc(const std::string& dllName, const std::string& funcName) {
    // Load DLL.
    HINSTANCE hGetProcIDDLL = LoadLibrary(dllName.c_str());

    // Check if DLL is loaded.
    if (hGetProcIDDLL == NULL) {
        std::cerr << "Could not load DLL \"" << dllName << "\"" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Locate function in DLL.
    FARPROC lpfnGetProcessID = GetProcAddress(hGetProcIDDLL, funcName.c_str());

    // Check if function was located.
    if (!lpfnGetProcessID) {
        std::cerr << "Could not locate the function \"" << funcName << "\" in DLL\"" << dllName << "\"" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create function object from function pointer.
    std::function<T> func(reinterpret_cast<__stdcall T*>(lpfnGetProcessID));

    return func;
}

//Function to load a table of functions from a DLL library.
Curves::func_table* loadFuncTable(const std::string libname) {
    auto getFuncTable = loadDllFunc<
        Curves::func_table*
        (void)
    >(libname, "getFuncTable");
    Curves::func_table* funcs = getFuncTable();
    return funcs;
}

int main() {
    //Load the functions table.
    Curves::func_table* dllFuncs = loadFuncTable("libCurves.dll");

    std::srand(std::time(0));
    std::cout << std::fixed << std::setprecision(3);

    //Creating the main storage of curves.
    std::vector<std::unique_ptr<Curves::Curve>> curveStorage;
    
    curveStorage = dllFuncs->createRandomCurves(20);

    // Creating a vector of pointers to curves to work with.
    std::vector<Curves::Curve*> allCurvePointers = dllFuncs->getCurvePointers(curveStorage);
    
    //Printing all curves at T = Pi/4.
     std::cout << "=== All curves at PI/4 ===" << std::endl << std::endl;
    dllFuncs->printCurvesAtT(allCurvePointers,PI/4);

    //Getting all circles, sorting them.
    std::vector<Curves::Circle*> circles;
    circles = dllFuncs->getCircles(allCurvePointers);
    circles = dllFuncs->sortCirclesRadiusAsc(circles);
    std::cout << "=== All circles at PI/3 ===" << std::endl << std::endl;
    dllFuncs->printCirclesAtT(circles,PI/3);

    // Computing the sum of circles' radii
    std::cout << "Sum of circles' radii: " << dllFuncs->computeSumOfCirclesRadii(circles) << std::endl;
    
    // Pausing the console app.
    std::cin.get();

    return 0;
}