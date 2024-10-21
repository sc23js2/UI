// COMP2811 Coursework 1: QuakeDataset class
#pragma once

#include <vector>
#include "quake.hpp"
#include <stdexcept>

using namespace std;

class QuakeDataset
{
  public:

    QuakeDataset() {};
    QuakeDataset(std::string filename) {loadData(filename);}
    void loadData(std::string filename);
    int size() const {return data.size();}
    Quake operator[] (int index) {if (index < 0) {throw range_error("Index out of range.");} return data.at(index);}
    Quake strongest();
    Quake shallowest();
    double meanDepth();
    double meanMagnitude();

  private:
    std::vector<Quake> data;
};
