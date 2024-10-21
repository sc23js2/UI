// COMP2811 Coursework 1: QuakeDataset class
#include "dataset.hpp"
#include "csv.hpp"

void QuakeDataset::loadData(std::string filename)
{
    csv::CSVReader reader(filename);

    for (auto& row: reader)
    {
        std::string date = row["time"].get<string>();
        double lat = row["latitude"].get<double>();
        double lon = row["longitude"].get<double>();
        double dep = row["depth"].get<double>();
        double mag = row["mag"].get<double>();

        data.push_back(Quake(date,lat,lon,dep,mag));
    }
}

Quake QuakeDataset::strongest()
{
    if (data.size() == 0)
        throw out_of_range("Empty Dataset.");

    int strongest = 0;
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i].getMagnitude() > data[strongest].getMagnitude())
            strongest = i;
    }
     return data[strongest];
}

Quake QuakeDataset::shallowest()
{
    if (data.size() == 0)
        throw out_of_range("Empty Dataset.");

    int shallowest = 0;
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i].getDepth() < data[shallowest].getDepth())
            shallowest = i;
    }
     return data[shallowest];
}

double QuakeDataset::meanDepth()
{
    if (data.size() == 0)
        throw out_of_range("Empty Dataset.");

    double sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i].getDepth();
    }
     return sum/data.size();
}

double QuakeDataset::meanMagnitude()
{
    if (data.size() == 0)
        throw out_of_range("Empty Dataset.");

    double sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i].getMagnitude();
    }

     return sum/data.size();
}