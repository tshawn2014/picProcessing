#include "BMP.h"
#include <stdio.h>
#include "stdlib.h"
#include <iostream>

using namespace std;

BMP::BMP()
{
    //ctor
}
int BMP::isImported = 0;
int BMP::isSharped = 0;
BMP::~BMP()
{
    //dtor
}
void BMP::readbmp(char bmpname[26])
{
    int width,height;//图片的宽度和高度
    FILE *fpi;
    fpi=fopen(bmpname,"rb");
    if(fpi != NULL){
        //先读取文件类型
        WORD bfType;
        fread(&bfType,1,sizeof(WORD),fpi);
        if(0x4d42!=bfType)
        {
            cout<<"the file is not a bmp file!"<<endl;
            exit(0) ;
        }
        fread(&strHead,1,sizeof(tagBITMAPFILEHEADER),fpi);
        fread(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpi);
        for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)
        {
            //存储的时候，一般去掉保留字rgbReserved
            fread((char *)&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpi);
        }
        width = strInfo.biWidth;
        height = strInfo.biHeight;
        imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
        fread(imagedata,sizeof(struct tagIMAGEDATA) * width,height,fpi);
        fclose(fpi);
    }
    else
    {
        cout<<"file open error!"<<endl;
        exit(0);
    }
}

void BMP::greybmp(char bmpname[26])
{
    int width,height;
    width = strInfo.biWidth;
    height = strInfo.biHeight;
    IMAGEDATA *imagedataRot = NULL;
    imagedataRot = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
    for(int i = 0;i <height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            BYTE grey=((*(imagedata + i * width + j)).blue*0.11 +
                (*(imagedata + i * width + j)).green*0.59 +
                (*(imagedata + i *  width + j)).red*0.3 );
            (*(imagedataRot + i * width + j)).blue = grey;
            (*(imagedataRot + i * width + j)).green = grey;
            (*(imagedataRot + i * width + j)).red= grey;
        }
    }
    //保存bmp图片
    FILE *fpw;
    if((fpw=fopen(bmpname,"wb"))==NULL)
    {
        cout<<"create the bmp file error!"<<endl;
        exit(0);
    }
    WORD bfType_w=0x4d42;
    fwrite(&bfType_w,1,sizeof(WORD),fpw);
    fwrite(&strHead,1,sizeof(tagBITMAPFILEHEADER),fpw);
    fwrite(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpw);
    //保存调色板数据
    for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)
    {
        fwrite(&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpw);
    }
    //保存像素数据
    for(int i =0;i < height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            fwrite( &(*(imagedataRot + i * width + j)).blue,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).green,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).red,1,sizeof(BYTE),fpw);
        }
    }
    fclose(fpw);
    delete[] imagedataRot;
}

void BMP::smoothbmp(char bmpname[26])
{
    int width,height;
    width = strInfo.biWidth;
    height = strInfo.biHeight;
    IMAGEDATA *imagedataRot = NULL;
    imagedataRot = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
    for(int i = 0;i <height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            if(i>0&&j>0&&i<height-1&&j<width-1)
            {
                BYTE grey=((*(imagedata + (i-1) * width + j-1)).blue*0.125 +
                    (*(imagedata + (i-1) * width + j)).blue*0.125 +
                    (*(imagedata + (i-1) * width + j+1)).blue*0.125 +
                    (*(imagedata + i * width + j-1)).blue*0.125 +
                    // (*(imagedata + i * width + j)).blue*0.125 +
                    (*(imagedata + i * width + j+1)).blue*0.125 +
                    (*(imagedata + (i+1) * width + j-1)).blue*0.125 +
                    (*(imagedata + (i+1) * width + j)).blue*0.125 +
                    (*(imagedata + (i+1) * width + j+1)).blue*0.125);

                (*(imagedataRot + i * width + j)).blue = grey;
                (*(imagedataRot + i * width + j)).green = grey;
                (*(imagedataRot + i * width + j)).red= grey;
            }
            else
            {
                BYTE grey=(*(imagedata + i * width + j)).blue;

                (*(imagedataRot + i * width + j)).blue = grey;
                (*(imagedataRot + i * width + j)).green = grey;
                (*(imagedataRot + i * width + j)).red= grey;
            }
        }
    }
    //保存bmp图片
    FILE *fpw;
    if((fpw=fopen(bmpname,"wb"))==NULL)
    {
        cout<<"create the bmp file error!"<<endl;
        exit(0);
    }
    WORD bfType_w=0x4d42;
    fwrite(&bfType_w,1,sizeof(WORD),fpw);
    fwrite(&strHead,1,sizeof(tagBITMAPFILEHEADER),fpw);
    fwrite(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpw);
    //保存调色板数据
    for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)
    {
        fwrite(&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpw);
    }
    //保存像素数据
    for(int i =0;i < height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            fwrite( &(*(imagedataRot + i * width + j)).blue,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).green,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).red,1,sizeof(BYTE),fpw);
        }
    }
    fclose(fpw);
    delete[] imagedataRot;
}


void BMP::sharpbmp(char bmpname[26])
{
    int width,height;
    width = strInfo.biWidth;
    height = strInfo.biHeight;
    IMAGEDATA *imagedataRot = NULL;
    imagedataRot = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
    for(int i = 0;i <height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            if(i>0&&j>0&&i<height-1&&j<width-1)
            {
                double grey=
                   ((double)(*(imagedata + (i-1) * width + j-1)).blue*0 +
                    (double)(*(imagedata + (i-1) * width + j)).blue +
                    (double)(*(imagedata + (i-1) * width + j+1)).blue*0 +
                    (double)(*(imagedata + i     * width + j-1)).blue +
                   // (double)(*(imagedata + i     * width + j)).blue +
                    (double)(*(imagedata + i     * width + j+1)).blue +
                    (double)(*(imagedata + (i+1) * width + j-1)).blue*0 +
                    (double)(*(imagedata + (i+1) * width + j)).blue +
                    (double)(*(imagedata + (i+1) * width + j+1)).blue*0 -
                    (double)(*(imagedata + i     * width + j)).blue*4);

                grey = grey>=0?grey:0;
                grey = grey>=256?255:grey;

                //=grey += (double)(*(imagedata + i     * width + j)).blue;







                (*(imagedataRot + i * width + j)).blue = grey;
                (*(imagedataRot + i * width + j)).green = grey;
                (*(imagedataRot + i * width + j)).red = grey;

            }
            else
            {
                BYTE grey=(*(imagedata + i * width + j)).blue;

                (*(imagedataRot + i * width + j)).blue = grey;
                (*(imagedataRot + i * width + j)).green = grey;
                (*(imagedataRot + i * width + j)).red= grey;
            }
        }
    }
    //保存bmp图片
    FILE *fpw;
    if((fpw=fopen(bmpname,"wb"))==NULL)
    {
        cout<<"create the bmp file error!"<<endl;
        exit(0);
    }
    WORD bfType_w=0x4d42;
    fwrite(&bfType_w,1,sizeof(WORD),fpw);
    fwrite(&strHead,1,sizeof(tagBITMAPFILEHEADER),fpw);
    fwrite(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpw);
    //保存调色板数据
    for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)
    {
        fwrite(&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpw);
        fwrite(&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpw);
    }
    //保存像素数据
    for(int i =0;i < height;++i)
    {
        for(int j = 0;j <width;++j)
        {
            fwrite( &(*(imagedataRot + i * width + j)).blue,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).green,1,sizeof(BYTE),fpw);
            fwrite( &(*(imagedataRot + i * width + j)).red,1,sizeof(BYTE),fpw);
        }
    }
    fclose(fpw);
    delete[] imagedataRot;
}
