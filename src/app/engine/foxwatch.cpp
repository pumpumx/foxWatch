#include <iostream>
#include <chrono> 
#include <sys/inotify.h>
#include "app/engine/foxwatch.hpp"
#include <unistd.h>
#include "app/cli/cli.hpp"
#include <memory>
#include <string>

namespace engine // Main engine logic
{

    FoxWatch::FoxWatch(int argc, char *argv[], EventCallBack cb) : callback_(std::move(cb))
    {                                               // Initialises the main constructor
        FoxWatch::fd_ = inotify_init1(IN_NONBLOCK); // In_nonblock -> inotify should not block on read!!! , initialises instance of the inotify_init!

        for (int i = 1; i < argc; i++) // Initialises the paths_ vector;
        {
            FoxWatch::paths_.push_back(argv[i]);
            addWatch(argv[i]); // Add watch simultaneously
        }
    }

    void FoxWatch::readEvents()
    {

        // Keeping the buf 4096 -> 1 memory page is of 4096 bytes -> 4kb to keep the things fast !

        char buf[4096] __attribute__((aligned(__alignof__(struct inotify_event))));
        const struct inotify_event *events;
        while (true)
        {
            // set watch !!
            // Read for event
            ssize_t events_len = read(FoxWatch::fd_, buf, sizeof(buf)); // Reads for events published by kernel

            if (events_len == -1)
            {
                if (errno == EAGAIN)
                    continue;
                else
                {
                    perror("Read error");
                    break;
                }
            }

            if (events_len <= 0)
                break; // If read finds no
            // Loop over all the events that occured yet

            for (char *ptr = buf; ptr < buf + events_len; ptr += sizeof(struct inotify_event) + events->len)
            {
                events = (const struct inotify_event *)ptr;

                // Last part print the events that occured
                callback_(events, wd_to_path_);
            }
        }
    }

    // void FoxWatch::handleDateTime(){

    //     std::chrono::system_clock timeObj;
        
    //     auto currTime = timeObj.now();

    //     std::cout<<currTime;
    // }

    void FoxWatch::addWatch(const std::string &path)
    {
        constexpr uint32_t mask = IN_CREATE | IN_CLOSE | IN_DELETE | IN_MODIFY; // even listen for all events!! , will learn about it and implement later , but using it would increase overhead!

        int wd = inotify_add_watch(FoxWatch::fd_, path.c_str(), mask);

        if (wd < 1)
        {
            std::cerr << "Error while adding watch descriptor to pathName: " << path;
            return; // Not exiting because we have several other paths too!
        }

        // Watch descriptor addded successfully !!
        FoxWatch::wd_to_path_[wd] = path;                                                   // Links the watch descriptor to the respective filepath
        std::cout << "Watch desriptor: " << wd << " added for path: " << path << std::endl; // This is cli task !! added it's functionality later!
    }

}