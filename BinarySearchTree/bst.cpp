#include "class.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

  Table<int> table;

  table.Insert("Akashi", 65);
  table.Insert("Watanabe", 70);
  table.Insert("Tomizawa", 80);
  table.Insert("Tahata", 55);
  table.Insert("Takimoto", 90);
  table.Insert("Miyamoto", 80);
  table.Insert("Iriyama", 60);
  table.Insert("Katsurada", 40);
  table.Insert("Noguchi", 40);
  table.Insert("Sato", 95);
  table.Insert("Matsuzawa", 20);
  table.PrintTree();
  std::cout << std::endl;

  if(table("Tahata")) std::cout << "Work Well" << std::endl;
  if(!table("Miyazawa")) std::cout << "Work Well" << std::endl;

  table-="Tahata";
  table-="Miyazawa";
  table.PrintTree();
  std::cout << std::endl;
}
  
