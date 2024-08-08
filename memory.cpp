#include<iostream>
#include<vector>
#include<iomanip>
#include<utility>

using namespace std;

class memory
{
    vector<pair<uint32_t,int>> memo;

    public:

    void writer(uint32_t add ,int data)
    {
        add=add*4;
        memo.push_back(make_pair(add,data));
    }

    int getData(uint32_t add)
    {
        for (const  auto& kv :memo)
        {
            if(kv.first == add)
            {
                return kv.second;
            }
            
        }
        cout<<"Data is not present\n";
        return -1;
    }

    void update(uint32_t add ,int data)
    {
        for ( auto& kv :memo)
        {
            if(kv.first == add)
            {
                kv.second = data;
            }
            
        }
    }

    void displayMemory()
    {
        cout<<"Adrress\t|\tData\n";
        for (auto & kv : memo)
        {
            cout<<"0x"<<setw(8)<<setfill('0')<<hex<<kv.first<<"\t|\t"<<dec<<kv.second<<endl;
        }
    }

};

int main()
{
    memory m1;
    
    m1.displayMemory();

    m1.writer(0,10);
    m1.writer(1,20);
    m1.writer(2,30);
    m1.writer(3,40);
    m1.writer(4,50);

    m1.displayMemory();




}