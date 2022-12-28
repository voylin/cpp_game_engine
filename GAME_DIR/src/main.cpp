#include <iostream>
#include "mke_core.hpp"



const String GAME_NAME = "Meikyuu Kazan";
const Version GAME_VERSION = Version{0,1,0};


int main(){
  std::cout << "Hello ... hello? Anybody there?" << std::endl;
  mke::startEngine(&GAME_NAME, &GAME_VERSION);
  return 0;
}