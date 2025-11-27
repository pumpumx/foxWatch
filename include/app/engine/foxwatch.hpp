

#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace engine
{

    class FoxWatch
    { // Initialise the constructor -> it'll intialise inotify!!
    public:
        using EventCallBack = std::function<void(const inotify_event * , std::unordered_map<int,std::string> &wdToPath)>;

        FoxWatch(int argc, char *argv[], EventCallBack cb);
        void addWatch(const std::string &path);
        void readEvents();

    private:
        int fd_;
        EventCallBack callback_; //Call back function used to bridge the foxwatch main engine and the cli
        std::vector<std::string> paths_;
        std::unordered_map<int, std::string> wd_to_path_;
    };
}