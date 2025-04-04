#ifndef OBJ_TO_STL_CONVERTER_H
#define OBJ_TO_STL_CONVERTER_H

#include <string>
#include <vector>
#include <utility>
#include "stl_shape.h" // Include STLShape for plotting

class ObjToStlConverter
{
public:
    void convertAndPlot(const std::string &objFilename, const std::string &stlFilename);
    static bool convert(const std::string &objFilename, const std::string &stlFilename);
    
private:
    static std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> readObj(const std::string &filename);
    static void writeStl(const std::vector<std::vector<double>> &vertices, const std::vector<std::vector<int>> &faces, const std::string &filename);
};

#endif
