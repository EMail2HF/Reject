#ifndef HASH_UTIL_H
#define HASH_UTIL_H

typedef struct HashTable
{
    unsigned long hashA;
    unsigned long hashB;
    unsigned char bExist;
}HashTable_t;

class Hash_util
{
public:
    enum HashType 
    {
      HASH_OFFSET = 0,
      HASH_A = 1, 
      HASH_B = 2
      };
public:
    Hash_util();
    ~Hash_util();
    int           InitHashTable(unsigned int uSize);
    int           ResetHashTable(unsigned int uSize); 
    //以下函数计算lpszFileName 字符串的hash值，其中dwHashType 为hash的类型，
    //在下面GetHashTablePos函数里面调用本函数，其可以取的值为0、1、2；该函数
    //返回lpszFileName 字符串的hash值；
    unsigned long HashString( const char *lpszFileName, unsigned long dwHashType );
    int           InsertString(const char * lpszString);
    int           FindString(const char * lpszString);
private:
    //以下的函数生成一个长度为0x500（合10进制数：1280）的cryptTable[0x500]
    void prepareCryptTable();

private:
    //crytTable[]里面保存的是HashString函数里面将会用到的一些数据，在prepareCryptTable
    //函数里面初始化
    unsigned long cryptTable[0x500];
    HashTable_t * hashTable_;
    unsigned long hashSize_;
    bool          bHashInited;
};

#endif // HASH_UTIL_H
