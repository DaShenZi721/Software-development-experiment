#pragma once
#include <string>

using namespace std;

#define HAVE_PASSWORD 1
#define BUFFSIZE 65536

#define ERRINVALIDPATH -1
#define ERRREADFILE -2
#define ERRPASSWORD -3
#define ERRINPUT -4

struct tar_header {
    int flag;
    int filecnt;
    char password[256];
};

struct file_record {
    char name[256];
    int size;
    int issubdir;
};

int mytar(string src, string des, string password, int flag);
int myuntar(string src, string des, string password, int flag);