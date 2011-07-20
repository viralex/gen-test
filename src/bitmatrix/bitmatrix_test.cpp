#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>

#include "bitmatrix.h"

using namespace std;

int main()
{
    bitmatrix b1(4,4),b2(5,5);
    string s("1,1\n1,1,1,1\n0,0");
    
    srand(time(NULL));

    b1.Set(0,0);
    b1.Unset(0,1);
    b1.Set(0,2);
    
    b1.Unset(1,0);
    b1.Set(2,0);
    
    b2.UnsetAll();
    b2.SetRow(b1,0);
    b2.SetCol(b1,0);
    
    b2.Set(2,2);
    
    b2.Print();
    
    printf("\n");
    
    b2.FlipAll();
    b2.Print();
    
    printf("\n");        
    b2.RandomizeAll();
    b1.RandomizeAll();
    b2.Print();
    printf("\n");
    b1.Print();
    printf("\n");
    b2.Import(b1);
    b2.Print();    
    printf("\n");

    b2.SetCol(s, 0);
    
    printf("%s\n",s.c_str());
    printf("\n");
    b2.Print();    
    printf("\n");


    b1.RandomizeAll();
    b1.Print();
    printf("\n");
    b1.Resize(2,4);    
    b1.UnsetRow(0);
    b1.UnsetRow(1);
    b1.Print();
    printf("\n");   
    b1.Import(s);
    b1.Print();
    printf("\n"); 
 
    //string s1 =  b1.GetRow(1);
    //printf("%s\n",s1.c_str());
    
    // s = b2.ToString();
    // printf("%s\n",s.c_str());
    
    return 0;
}
