#include <iostream>
#include <unistd.h>
#include "app/cli/cli.hpp"
#include <chrono>

int main(int argc, char *argv[])
{

    if(argc < 2){
        std::cerr<<"Usage: FoxWatch [PATH1] [PATH2] ..."<<std::endl;
        exit(EXIT_FAILURE);
    }

    cli::CLI cliInstance(argc , argv); //Cli instance

}


