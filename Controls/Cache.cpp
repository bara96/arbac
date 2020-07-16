//
// Created by mbaratella on 15/07/2020.
//

#include <string>
#include <fstream>
#include <utility>
#include "../Models/Policy/Policy.h"

using namespace std;

class Cache {
private:
    bool showLogs;
    string filename;
    string bufferName = "buffer.txt";

public:
    const enum Source {BUFFER, CACHE};

public:
    explicit Cache(string filename = "cache.txt", bool showLogs = false) : showLogs(showLogs), filename(std::move(filename)) {
        wipeAll();
    }

    const string &getFilename() const {
        return filename;
    }

    void setFilename(const string &filenameVal) {
        Cache::filename = filenameVal;
    }

    const string &getBufferName() const {
        return bufferName;
    }

    void setBufferName(const string &bufferNameVal) {
        Cache::bufferName = bufferNameVal;
    }

    bool isShowLogs() const {
        return showLogs;
    }

    void setShowLogs(bool showLogsVal) {
        Cache::showLogs = showLogsVal;
    }

    void wipeAll() {
        wipeCache();
        wipeBuffer();
    }

    void wipeBuffer() {
        ofstream cache(bufferName, std::ios::trunc);
        cache.close();
    }

    void wipeCache() {
        ofstream cache(filename, std::ios::trunc);
        cache.close();
    }

    void copyBufferOnCache() {
        ifstream buffer(bufferName);
        ofstream cache;
        cache.open(filename, fstream::app);
        for (string str; getline(buffer, str); )
        {
            cache << str << '\n';
        }
        wipeBuffer();
    }

    template<typename Index>
    void storeSet(const map<Index, vector<string>>& roleSet, Source source = Source::CACHE) {
        string sourceFile;
        switch (source) {
            case Source::CACHE:
                sourceFile = filename;
                break;
            case Source::BUFFER:
                sourceFile = bufferName;
                break;
            default:
                sourceFile = filename;
                break;
        }

        ofstream cache;
        cache.open(sourceFile, fstream::app);

        for(auto& set : roleSet) {
            cache << set.first << ' ';
            for(const string& role : set.second) {
                cache << role << ' ';
            }
            cache << ',';
        }
        cache << '\n';
        cache.close();
    }

    template<typename Index>
    map<Index, vector<string>> readSet(ifstream &cache) {
        map<Index, vector<string>> set;
        string line;
        if (cache.good()){
            getline(cache, line);
            istringstream ss(line);
            vector<string> roleSetValues = Utility::split(line, ',');
            for(const string& roleSetValue : roleSetValues) {
                vector<string> values = Utility::split(roleSetValue, ' ');
                Index index = values.at(0);
                values.erase(values.begin());
                set.insert(pair<Index, vector<string>>(index, values));
            }
        }
        return set;
    }

};
