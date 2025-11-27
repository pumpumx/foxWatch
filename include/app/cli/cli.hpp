
#pragma once
#include <sys/inotify.h>
#include <string>

namespace cli {
    
    struct parseFlags{
        bool recursive = false; //if set to true then searches for recursive options
    };

    class CLI { 
        public: 
            CLI(int argc ,char *argv[]);
            void printEvents(const inotify_event* events, std::string &dirPath);
    };
}