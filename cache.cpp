#include<iostream>
#include<vector>

using namespace std;

class cacheline
{
    int tag;
    bool valid;
    vector<int> data;


    public:
    cacheline()
    {
        tag=-1;
        valid=false;
        data.assign(0,0);
    }

    cacheline(int blockSize)
    {
        tag=-1;
        valid=false;
        data.assign(blockSize,0);
    }

    int getTag()
    {
        return tag;
    }

    int getValid()
    {
        return valid;
    }

    vector<int> getData()
    {
        return data;
    }

    void putTag(int ntag)
    {
        tag=ntag;
    }

    void putValid(bool nvalid)
    {
        valid=nvalid;
    }

    void putData(int offset, int ndata)
    {
        data[offset/4]=ndata;
    }


};

class DirectMappedCache{
    cacheline* cacheBlock;
    int numBlocks;
    int blockSize;

    public:
        DirectMappedCache(int nblocks, int size)
        {
            numBlocks=nblocks;
            blockSize=size;

            cacheBlock= new cacheline[numBlocks];
            for (int i=0; i<numBlocks;i++)
            {
                cacheBlock[i] = cacheline(blockSize);
            }

        }

        int get(int address)
        {
            int tag = address >> 3;
            int index= (address >> 3) & 0x7;
            int offset = 0;

            if (cacheBlock[index].getValid() && cacheBlock[index].getTag() == tag)
            {
                vector<int> data=cacheBlock[index].getData();
                cout<<"cache hit\n Data: "<<data[offset/4]<<endl;
                return data[offset /4];
            }
            else
            {
                cout<< "Cache miss!\n";
                return -1;
            }

        }

        void put(int address, int value)
        {
            int tag = address >> 3;
            int index= address & 0x7;
            int offset = 0;
            bool valid=true;

            cacheBlock[index].putTag(tag);
            cacheBlock[index].putValid(valid);
            cacheBlock[index].putData(offset,value);
        }

        void display()
        {
            cout<<" Cache Content\n";
            

            for(int i=0;i<numBlocks;i++)
            {
                cout<< "Index " << i << ": Tag = " << cacheBlock[i].getTag() 
                    << ", Valid = " << (cacheBlock[i].getValid() ? "true" : "false") 
                    << ", Data = ";
                vector<int> data=cacheBlock[i].getData();
            for (int j = 0; j < blockSize; ++j) {
                cout<<data[j]<<" ";
            }
            cout<<endl;
            }
        }




    
};




int main()
{
    int numBlocks = 8; 
    int blockSize = 1; 
    DirectMappedCache cache(numBlocks, blockSize);
    cout<<"befare adding into cache \n";
    cache.display();

    cache.put(0x00000000, 10);  // Address 0x00000000
    cache.put(0x00000004, 20);  // Address 0x00000004
    cache.put(0x00000007, 30);  // Address 0x00000008
    cache.put(0x0000000C, 40);  // Address 0x0000000C
    cache.put(0x00000010, 50);  // Address 0x00000010
    cout<<"after inserting into cache\n";
    cache.display();

    cache.get(0x00000000);  // Cache hit
    cache.get(0x00000004);  // Cache hit
    cache.get(0x00000010);  // Cache hit
    cache.get(0x00000014);  // Cache miss (assuming it wasn't put in the cache yet)

}