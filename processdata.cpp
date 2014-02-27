#include "processdata.h"
#include <stdio.h>
#include <list>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include "hash_util.h"
using namespace std;


  ProcessData::ProcessData()
    {

    }
  ProcessData:: ~ProcessData()
    {

    }

int ProcessData:: DataProcess(const char * fileA,const char *fileB)
{

    if (fileA==NULL || fileB ==NULL)
    {
      return -1;
    }

    string fileNameA = fileA;

    string fileNameB = fileB;

    string fileNameA_New=fileNameA.substr(0,fileNameA.find('.'));
    fileNameA_New+=".bak";

    string fileNameB_New=fileNameB.substr(0,fileNameB.find('.'));
    fileNameB_New+=".bak";

    // process ref_file section
    {

       ifstream ref_file_a(fileA);

      if(ref_file_a.fail())
          return -2;

      string line; 

      ref_file_list.clear();

      while(getline(ref_file_a,line))
      {
          if(line.empty())
          {
              continue;
          }
   
          ref_file_list.push_back(line);
      }
      ref_file_a.close();
    }

    int uSize = ref_file_list.size();

    if (!uSize)
    {
      return -3;
    }

    Hash_util hash_util_t;

    if (hash_util_t.InitHashTable(uSize))
    {
        return -4;
    }

    std::list<std::string>::iterator it;

    for(it=ref_file_list.begin();it!=ref_file_list.end();it++)
    {

         cout<<"string line =  "<< (*it)<<endl;

         hash_util_t.InsertString((*it).c_str());

    }

    //backup fileA end file B

   int iret =  rename(fileNameA.c_str(),fileNameA_New.c_str());

   if(iret)
       return -5;
    iret =  rename(fileNameB.c_str(),fileNameB_New.c_str());

   if(iret)
       return -6;

   //process file b
   {

      ifstream infile(fileNameB_New.c_str());

     if(infile.fail())
         return -7;

     string line;

     ofstream outfileB(fileNameB.c_str());

     int hashPos;

     while(getline(infile,line))
     {
         if(line.empty())
         {
             continue;
         }
         hashPos =hash_util_t.FindString(line.c_str());

         if(hashPos < 0)
         {
            outfileB<<line<<std::endl;
         }  
      }

      outfileB.close();

   }// endl of process file b


    //process file a
   {         
      ofstream outfileA(fileNameA.c_str());

      std::list<std::string>::iterator it;

      int hashPos;

      for(it=ref_file_list.begin();it!=ref_file_list.end();it++)
      {
          hashPos =hash_util_t.FindString((*it).c_str());

         if(hashPos < 0)
         {
            outfileA<<(*it)<<std::endl;
         }  
       }

      outfileA.close();

   } //end of process file A

    return 0;
}

