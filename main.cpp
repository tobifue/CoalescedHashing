#include <iostream>
//#include "vector.h"
#include "ADS_set.h"

using namespace std;
  
// To demonstrate String Hashing
void stringHashing()
{
  
    // Get the string
    // to get its hash value
    string hashing1 = "Lorem";
  
    // Instatiation of Object
    hash<string> mystdhash;
  
    // Using operator() to get hash value
    cout << "String hash values: "
         << mystdhash(hashing1)%5
         << endl;
}

int main(){
try{
    
        ADS_set<unsigned> g{128,45,67,8};
        g.erase(128);

        g.dump();

        //ADS_set<int,7> z{};
        //g.dump();
        //h.dump();
        //bool tes = g==h;
        //h = g;
        
       // h.erase(36);
      //   h.erase(6);
      //  h.erase(4);
    

      //  h.insert(7);
      //  h.insert(3);
        

     /*   h.erase(0);
        h.erase(49);
        h.erase(54);
        h.erase(31);
        h.insert(28);
        h.insert(50);
        h.insert(22);
        h.erase(76);
        h.insert(69);
        h.insert(20);
        h.erase(80);
        h.insert(1);
        h.erase(69);
       h.insert(74);
        h.insert(53);
        h.insert(42);
       h.erase(46);
        h.erase(70);
        h.insert(83);
        h.erase(29);
        h.insert(74);
        h.erase(40);
        h.insert(66);
        h.insert(74);
        h.insert(40);
        h.insert(46);
        h.insert(16);
      */ 
        //std::cout<<g.erase(66);
        //g.erase(17);




        /*
        for (auto idx{z.begin()}; idx!= z.end();idx++){
            std::cout<<*idx<<"HEEEEEEEE"<<std::endl;
        }
        */
        //h.x();
        //*h[5]++;

        //std::cout<<h[5]<<"HERRRRREEEEE"<<std::endl;
        //h.clear();
        //h.erase(9);
        //b.dump();
        //c.dump();

   /*         
        s.push_back(7);
        s.push_back(3.1);
        s.push_back(3.1);
        s.print();
        
        Vector<double> g(4);s
        Vector z = s+g;
        sort(z);
        z.print();
        std::cout << middle(s);

        
        s.insert(25,3.2);
        s.print();
        s.reserve(101);
        s.shrink_to_fit();
        Vector a = s;
        a.print();
        s.print();
        Vector g(0);
        Vector f(0);
        Vector h ({1,2,3,4,1,2,3,1,2,3,4,5,6,7,8});
        Vector d ({1,2,3});
        Vector z = find(h,d);
        z.print();
        std::cout << d.capacity();*/

}
catch(int& err){
    switch(err){
        case 3: std::cerr << "Ooops, the vector seems to be already empty!";
            break;
        case 4: std::cerr << "Ooops, the index seems to be out of bound!";
            break;
        case 5: std::cerr << "Ooops, vector seems to be empty!";
            break;
        case 6: std::cerr << "Ooops, error at insertion/erasing!";
            break;
        default: std::cerr << "Ooops, some error occurred!";
            break;
    }
}
	return 0;
}


