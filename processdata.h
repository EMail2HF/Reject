#ifndef PROCESSDATA_H
#define PROCESSDATA_H
#include "hash_util.h"
#include <string>
#include <list>

class ProcessData
{

public:
    ProcessData();
    ~ProcessData();
    
public:
    int DataProcess(const char * fileA,const char *FileB);
private:    
    std::list<std::string> ref_file_list;
};

#endif // PROCESSDATA_H
