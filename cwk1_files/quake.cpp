// COMP2811 Coursework 1: Quake class

#include <stdexcept>
#include "quake.hpp"

using namespace std;


Quake::Quake(const string& tm, double lat, double lon, double dep, double mag):
  time(tm), latitude(lat), longitude(lon), depth(dep), magnitude(mag)
{
  if (lat > 90 || lat < -90)
  {
    throw range_error("Latitude out of bounds.");
  }
  
  if (lon > 180 || lon < -180)
  {
    throw range_error("Longitude out of bounds");
  }

  if (dep < 0 || mag < 0)
  {
    throw range_error("Depth or Magnitude cant be negative.");
  }

}


ostream& operator<<(ostream& out, const Quake& quake)
{
  return out << "Time: " << quake.getTime()
             << "\nLatitude: " << quake.getLatitude() << " deg"
             << "\nLongitude: " << quake.getLongitude() << " deg"
             << "\nDepth: " << quake.getDepth() << " km"
             << "\nMagnitude: " << quake.getMagnitude() << endl;
}
