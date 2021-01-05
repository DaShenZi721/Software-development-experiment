#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

#include "mytar.h"

using namespace std;

/* 
 * src, des, password, flag, swi
*/
int main(int argc, char* argv[]) {

    if (argc != 6){
        printf("%d", ERRINPUT) ;
        return 0;
    }
    string src = argv[1];
    string des = argv[2];
    string password = argv[3];
    int flag = atoi(argv[4]);
    int swi = atoi(argv[5]);

    if(swi == 0){
        printf("%d", mytar(src, des, password, flag));
    }
    else{
        printf("%d", myuntar(src, des, password, flag));
    }
    return 0;
}