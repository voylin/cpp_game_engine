#!/bin/bash

# Creating build directory (if doesn't exist) and making it empty.
mkdir -p build
mkdir -p build/lib


# Prompt the user if engine needs compiling?
read -p "Do you want to compile the engine (Y/n)? " answer
if [ $answer == "Y" ] || [ $answer == "y" ]; then
  # Compile the engine code in 'meikyuu_engine' and create a shared object file
  # named engine.so in the build directory. Link the GLFW and GL libraries.
  rm -rf build/lib/*
  echo "Compiling engine ..."
  g++ -o build/lib/libengine.so -shared -fPIC $(find meikyuu_engine -type f -name '*.cpp') $(find meikyuu_engine -type f -name '*glad.c') -lglfw -lGL
  echo "Compiling complete!"
fi


# Prompt the user if engine needs compiling?
read -p "Do you want to compile the game (Y/n)? " answer
if [ $answer == "Y" ] || [ $answer == "y" ]; then
  # Compile the game code in 'src' and create an executable file
  # named game in the build directory. Include the engine header files
  # and link the GLFW and GL libraries.
  # The -Wl,-rpath=./build flag specifies the runtime library search path
  # so that the game executable can find the engine shared object file.
  rm -rf build/game
  rm -rf build/run.sh
  echo "Compiling game ..."
  # g++ -Wl,-rpath=./build -o build/game src/*.cpp -Imeikyuu_engine -lglfw -lGL
  g++ -fPIC -Imeikyuu_engine -o build/game src/*.cpp -lglfw -lGL -L./build/lib -lengine -Wl,-rpath=./:./lib:lib

  cp src/run.sh build/run.sh
  echo "Compiling complete!"
  
  read -p "Do you want to reload the assets (Y/n)? " answer
  if [ $answer == "Y" ] || [ $answer == "y" ]; then
    rm -rf build/shaders
    rm -rf build/textures
    rm -rf build/models
    cp -r assets/* build/
  fi
fi


# Prompt the user to run the program
read -p "Do you want to run the program (Y/n)? " answer
if [ $answer == "Y" ] || [ $answer == "y" ]; then
  echo "Running game ..."
  build/run.sh
fi