#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <io.h>
#include <sys/stat.h>
#include <direct.h>

#include "mytar.h"

using namespace std;

/* 
 * src : xxx\xxx\xxx
 * des : xxx\xxx\filename
*/

unsigned char buf[BUFFSIZE];

int mytar(string src, string des, string password, int flag){
    struct tar_header th;
    struct file_record fr;
    th.flag = flag;
    if(th.flag == HAVE_PASSWORD){
        strcpy(th.password, password.c_str());
    }

    //判断src是文件还是文件夹
    struct stat s;
    if (stat(src.c_str(),&s) == 0){
        if(s.st_mode & S_IFDIR){
            int filecnt =0;
            int subdircnt = 0;

            vector<string> files, subdirs;

            long hFile = 0;
            struct _finddata_t fileInfo;
            string pathName;
                        // \\* 代表要遍历所有的类型,如改成\\*.jpg表示遍历jpg类型文件
            if ((hFile = _findfirst(pathName.assign(src).append("\\*").c_str(), &fileInfo)) == -1) {
                return ERRINVALIDPATH;
            }
            do
            {
                        //判断文件的属性是文件夹还是文件
                if(fileInfo.attrib&_A_SUBDIR){
                    if(fileInfo.name[0] == '.')
                        continue;
                    subdirs.push_back(string(fileInfo.name));
                    subdircnt++;
                }
                else{
                    files.push_back(string(fileInfo.name));
                    filecnt++;
                }
            } while (_findnext(hFile, &fileInfo) == 0);
            _findclose(hFile);

            th.filecnt = filecnt + subdircnt;

            FILE *outfile, *infile;
            outfile = fopen(des.c_str(), "wb");
            fwrite(&th, sizeof(th), 1, outfile);

            for(int i = 0; i < filecnt; i++){
                infile = fopen(pathName.assign(src).append("\\").append(files[i]).c_str(), "rb");
                fr.size = _filelength(_fileno(infile));
                fr.issubdir = 0;
                strcpy(fr.name, files[i].c_str());
                fwrite(&fr, sizeof(fr), 1, outfile);

                int rc;
                while((rc = fread(buf, sizeof(unsigned char), BUFFSIZE, infile)) != 0){
                    fwrite(buf, sizeof(unsigned char), rc, outfile);
                }

                fclose(infile);
            }

            for(int i = 0; i < subdircnt; i++){
                string filename = subdirs[i] + ".114514";
                mytar(pathName.assign(src).append("\\").append(subdirs[i]), pathName.assign(src).append("\\").append(filename), password, 0);

                infile = fopen(pathName.assign(src).append("\\").append(filename).c_str(), "rb");
                fr.size = _filelength(_fileno(infile));
                fr.issubdir = 1;
                strcpy(fr.name, filename.c_str());
                fwrite(&fr, sizeof(fr), 1, outfile);

                int rc;
                while((rc = fread(buf, sizeof(unsigned char), BUFFSIZE, infile)) != 0){
                    fwrite(buf, sizeof(unsigned char), rc, outfile);
                }

                fclose(infile);
                remove(pathName.assign(src).append("\\").append(filename).c_str());
            }
           fclose(outfile);
           return 0;

        }
        else if (s.st_mode & S_IFREG){
            th.filecnt = 1;
            int i = src.length() - 1;
            while(i >= 0 && src[i] != '\\'){
                i--;
            }
            i++;
            if(i < 0){
                return ERRINVALIDPATH;
            }
            int j = 0;
            while(i < src.length()){
                fr.name[j] = src[i];
                i++;
                j++;
            }
            fr.name[j] = '\0';

            FILE *outfile, *infile;
            outfile = fopen(des.c_str(), "wb");
            infile = fopen(src.c_str(), "rb");

            fr.size = _filelength(_fileno(infile));
            fr.issubdir = 0;

            fwrite(&th, sizeof(struct tar_header), 1, outfile);
            fwrite(&fr, sizeof(struct file_record), 1, outfile);

            int rc;
            while(rc = fread(buf, sizeof(unsigned char), BUFFSIZE, infile) != 0){
                fwrite(buf, sizeof(unsigned char), rc, outfile);
            }
            fclose(infile);
            fclose(outfile);
            return 0;
        }
        else{
            std::cout<<"not file not directory"<<std::endl;
            return ERRINVALIDPATH;
        }
    }
    else{
        std::cout<<"error, doesn't exist"<<std::endl;
        return ERRINVALIDPATH;
    }
}

/* 
 * src : xxx\xxx\filename
 * des : xxx\xxx\xxx\
*/
int myuntar(string src, string des, string password, int flag){
    struct tar_header th;
    struct file_record fr = {0};
    FILE *outfile, *infile;
    infile = fopen(src.c_str(), "rb");
    fread(&th, sizeof(unsigned char), sizeof(th), infile);
    if(th.flag == HAVE_PASSWORD && strcmp(password.c_str(), th.password) != 0){
        return ERRPASSWORD;
    }

    for(int i = 0; i < th.filecnt; i++){
        int frreadsize;
        if ((frreadsize = fread(&fr, sizeof(unsigned char), sizeof(fr), infile)) == 0)
        {
            return ERRREADFILE;
        }
        string filepath = des + fr.name;
        outfile = fopen(filepath.c_str(), "wb");
        int res = fr.size;
        int cplen;
        while(res){
            cplen = res < BUFFSIZE ? res : BUFFSIZE;
            res -= cplen;
            int rc;
            rc = fread(buf, sizeof(unsigned char), cplen, infile);
            fwrite(buf, sizeof(unsigned char), rc, outfile);
        }
        fclose(outfile);

        if(fr.issubdir){
            string subdirpath = string(fr.name);
            subdirpath = subdirpath.substr(0, subdirpath.length()-7);
            subdirpath = des + subdirpath;
            if (_access(subdirpath.c_str(), 0) == -1)
            {
                _mkdir(subdirpath.c_str());
            }
            myuntar(filepath, subdirpath + "\\", password, 0);
            remove(filepath.c_str());

        }

        
    }
    fclose(infile);
    return 0;
}