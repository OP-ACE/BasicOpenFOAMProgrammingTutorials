# include <iostream>
# include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{   
    int i;
    for ( i = 1; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
    cout << "argc = " << argc << endl;
    return 0;
}