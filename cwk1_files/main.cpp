// COMP2811 Coursework 1: quaketool application
#include "tabulate.hpp"
#include "argparse.hpp"
#include "dataset.hpp"

int main(int argc, char* argv[])
{

  argparse::ArgumentParser program("main");

  program.add_argument("filename")
  .required()
  .help("File to be proccessed");

  program.add_argument("-table")
  .help("Displays the details of quakes in the dataset in a table")
  .default_value(false)
  .implicit_value(true);

  program.add_argument("-m")
  .nargs(1)
  .default_value(0)
  .help("Only quakes with >= the specified magntitude will be shown in the table")
  .scan<'m', double>();

  program.add_argument("-help")
  .flag();

  try
  {
    program.parse_args(argc, argv);
  }
  catch(const std::exception& err)
  {    
    std:: cerr << err.what() << std::endl;
    std:: cerr << program;
    std:: exit(1);
  }

  auto filename = program.get<std::string>("filename");
  auto mag = program.get<double>("-number");

  //help
  if (program["-help"] == true)
  {
      std::cout << program;
      exit(0);
  }

  //no extra args
  if (argc == 1)
  {
    NormalMode(filename);
  }


  if (program["-table"] == true)
  {
    TableMode(filename, mag);
  }


  return 0;
}

void NormalMode(std::string filename)
{
  QuakeDataset data;
  data.loadData(filename);

  cout << "Number of Quakes in file: " << data.size() << endl;
  cout << "Strongest Quake: " << data.strongest() << endl;
  cout << "Shallowest Quake: " << data.shallowest() << endl;
  cout << "Mean depths of Quakes: " << data.meanDepth() << endl;
  cout << "Mean magnitude of Quakes: " << data.meanMagnitude() << endl;

}

void TableMode(std::string filename, double mag)
{
  QuakeDataset data;
  data.loadData(filename);

  tabulate::Table quakes;

  quakes.add_row({"Time", "Latitude", "Longitude", "Depth", "Magnitude"});
  quakes[0].format().border_bottom("30");

  for (int i = 0; i < data.size(); i++)
  {
      quakes.add_row(tabulate::RowStream{} << data[i].getTime() << data[i].getLatitude() << data[i].getLongitude() << data[i].getDepth() << data[i].getMagnitude());
  }

  cout << quakes << endl;
}