#include "app/cli/cli.hpp"
#include "app/engine/foxwatch.hpp"
#include <iostream>
#include <unordered_map>
#include <string>

namespace cli { 


    CLI::CLI(int argc , char* argv[]){

        engine::FoxWatch mainInstance(argc , argv , [&](const inotify_event * ev , std::unordered_map<int,std::string>&wdToPath){
            auto it = wdToPath.find(ev->wd);
            if(it != wdToPath.end()){
                printEvents(ev , it->second);
            }

        });
        //Periodically run the readevents function in order to maintain periodicity!
        mainInstance.readEvents();
    }

    void CLI::printEvents(const inotify_event *event , std::string &dirPath){

        std::cout<<"DirName: "<<dirPath<<std::endl; //Prints directory at where the event occured;
        std::string s = "| ";

        std::cout<<"Event mask"<<event->mask<<" \n";
        if(event->mask & IN_MODIFY) s+="Modifed | ";
        else if(event->mask & IN_ISDIR) s+="Directory | ";
        else if(event->mask & IN_CREATE) s+="Created |";
        else if(event->mask & IN_DELETE) s+="Deleted |";
        else if(event->mask & IN_CLOSE) s+="Closed |";
        else{
            std::cerr<<"Other events also captured, extend events to capture them"<<std::endl;
        }

        std::cout<<s<<std::endl;
    }   
}