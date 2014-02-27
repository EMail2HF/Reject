#include "hash_util.h"
#include <stdio.h>
#include <ctype.h>
Hash_util::Hash_util()
{
    hashTable_=NULL;
    hashSize_=0;
    bHashInited=false;
}
Hash_util::~Hash_util()
{
    if (hashTable_)
    {
        delete [] hashTable_;
    }
}

//以下的函数生成一个长度为0x500（合10进制数：1280）的cryptTable[0x500]
void Hash_util::prepareCryptTable()
{
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for( index1 = 0; index1 < 0x100; index1++ )
    {
        for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )
        {
            unsigned long temp1, temp2;

            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;

            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);

            cryptTable[index2] = ( temp1 | temp2 );
       }
   }
}

int Hash_util::InitHashTable(unsigned int uSize)
{
    if (uSize==0||bHashInited)
    {
        return -1;
    }

    prepareCryptTable();

    hashSize_=uSize;

    hashTable_ = new HashTable_t[hashSize_];

    bHashInited=true;

     return 0;

}
int Hash_util::ResetHashTable(unsigned int uSize)
{
    if (uSize==0 || bHashInited==false)
    {
        return -1;
    }

    hashSize_=uSize;

    if (hashTable_)
    {
        delete hashTable_;

        hashTable_=NULL;
    }

    hashTable_ = new HashTable_t[hashSize_];

    bHashInited=true;

    return 0;
}


//直接调用上面的hashstring，nHashPos就是对应的HASH值。  
int Hash_util::InsertString(const char *lpszString)  
{
    if (!bHashInited)
    {
        return -1;
    }

    unsigned int nHash = HashString(lpszString, HASH_OFFSET);  

    unsigned int nHashA = HashString(lpszString, HASH_A);  

    unsigned int nHashB = HashString(lpszString, HASH_B);  

    unsigned int nHashStart = nHash % hashSize_;  

    unsigned int nHashPos = nHashStart;  

  
    while (hashTable_[nHashPos].bExist)  
    {  
//      if (TestHashCTable[nHashPos]  == (int) nHashC && TestHashDTable[nHashPos] == (int) nHashD)  
//          break;  
//      //...  
//      else  
        //如之前所提示读者的那般，暴雪的Hash算法对于查询那样处理可以，但对插入就不能那么解决  
            nHashPos = (nHashPos + 1) % hashSize_;  
  
        if (nHashPos == nHashStart)  
            return -2;
    }  
  

    if (!hashTable_[nHashPos].bExist)  
    {   
        hashTable_[nHashPos].hashA = nHashA; 

        hashTable_[nHashPos].hashB = nHashB;  

        hashTable_[nHashPos].bExist = 1;  
    }  
    else  
    {  
        return -1;  
    }  
    return nHashPos; 
}
//函数GetHashTablePos中，lpszString 为要在hash表中查找的字符串；
int Hash_util::FindString(const char * lpszString)
{
    if (!bHashInited)
    {
        return -1;
    }

    unsigned int nHash = HashString(lpszString, HASH_OFFSET);  

    unsigned int nHashA = HashString(lpszString, HASH_A);  

    unsigned int nHashB = HashString(lpszString, HASH_B);  

    unsigned int nHashStart = nHash % hashSize_;  

    unsigned int nHashPos = nHashStart; 

    while ( hashTable_[nHashPos].bExist )  
   {  
//     如果仅仅是判断在该表中时候存在这个字符串，就比较这两个hash值就可以了，不用对结构体中的字符串进行比较。  
 
        if ( hashTable_[nHashPos].hashA == nHashA &&  hashTable_[nHashPos].hashB == nHashB )  
       {  
            return nHashPos;  
       }  
       else  
       {  
            nHashPos = (nHashPos + 1) % hashSize_;  
       }  
   
        if (nHashPos == nHashStart)  
              break;  
    }  
     return -1;  


}

//以下函数计算lpszFileName 字符串的hash值，其中dwHashType 为hash的类型，
//在下面GetHashTablePos函数里面调用本函数，其可以取的值为0、1、2；该函数
//返回lpszFileName 字符串的hash值；
unsigned long Hash_util::HashString( const char *lpszFileName, unsigned long dwHashType )
{
    unsigned char *key  = (unsigned char *)lpszFileName;
    unsigned long seed1 = 0x7FED7FED;
    unsigned long seed2 = 0xEEEEEEEE;
    int ch;

    while( *key != 0 )
    {
        ch = toupper(*key++);

        seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed1;

}
