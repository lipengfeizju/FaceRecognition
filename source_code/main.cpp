//
//  main.c
//  Test
//
//  Created by 陈欢 on 2016/12/12.
//  Copyright ? 2016年 陈欢. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Inf1 1e-5
//#define FigureNum 80
typedef double ElementType;

struct Matrix { /* 队列中的结点 */
    ElementType **Data;
    int row;
    int column;
};

int CreateMatrix(ElementType *a,int row,int column,struct Matrix *A);//根据二维数组新建矩阵
void DisplayMatrix(struct Matrix A);// 显示矩阵
int CopyMatrix(struct Matrix A,struct Matrix *B);// 复制矩阵
int AddMatrix(struct Matrix A, struct Matrix B,struct Matrix *C);  // 矩阵相加
int MinusMatrix(struct Matrix A, struct Matrix B,struct Matrix *C); //矩阵相减
int MultiplyMatrix(struct Matrix A, struct Matrix B,struct Matrix *C);// 矩阵相乘
int TransposeMatrix(struct Matrix A, struct Matrix *B);// 矩阵转置
int MergeMatrix(struct Matrix A, struct Matrix *B); //矩阵合并
int DeleteMatrix(struct Matrix *A);  // 矩阵删除
int CreateIdentityMatrix(struct Matrix *A,int size);// 新建单位阵
int JudgeSymmetry(struct Matrix A);// 判断对称性
int FindSMatrixElement(struct Matrix A,int *row,int *column);//寻找 最大元素，只用于对称矩阵情况
int StandradMatrixR(struct Matrix A,struct Matrix *B);// 对于行向量，进行标准化
int StandradMatrixC(struct Matrix A,struct Matrix *B);// 对于列向量，进行标准化
int SwapBuffer(struct Matrix A,struct Matrix *B); // 手动交换空间
int EigMatrix(struct Matrix A, struct Matrix *B, struct Matrix *C,int Nmax,double prec);//求取特征值函数
int FindOrder(struct Matrix A,double *order);// 按照大小顺序排列特征值


int main(int argc, const char * argv[]) {
    FILE *fp, *fpout;
    int FigureNum=80;
    struct Matrix FigureStore,FigureStoreTrans,A,ATrans,AMultiply,EigenValue,EigenVector,M,Result,CoMatrix,B,EigenFace;
    double b[FigureNum];
    ElementType sum=0;
    char buf1[128],buf2[128],buf3[128];
    int Height,Width,depth;
    int temp = 0;
    int k =0 ;
    int i = 0,j = 0;
    fp= fopen("1A.pgm","rb");
    fgets(buf1,128,fp);
    puts(buf1);
    fgets(buf2,128,fp);
    puts(buf2);
    sscanf(buf2,"%d %d",&Width,&Height);
    fgets(buf3,128,fp);
    puts(buf3);
    sscanf(buf3,"%d",&depth);
    fclose(fp);
    
    double MeanVector[Height*Width];
    temp = Height*Width;
    temp = (int)temp;
    ElementType **a;
    
    a = (ElementType **)malloc(FigureNum*sizeof(ElementType *));
    for(i = 0;i<FigureNum; i++){
    	a[i] = (ElementType *)malloc(Height*Width*sizeof(ElementType *));
    }
	ElementType c[20][FigureNum];
    //c储存选取的特征向量个数
    char* chin[]=
    {
        "1A.pgm",
        "1B.pgm",
        "1C.pgm",
        "1D.pgm",
        "1E.pgm",
        "1F.pgm",
        "1G.pgm",
        "1H.pgm",
        "1I.pgm",
        "1J.pgm",
        "2A.pgm",
        "2B.pgm",
        "2C.pgm",
        "2D.pgm",
        "2E.pgm",
        "2F.pgm",
        "2G.pgm",
        "2H.pgm",
        "2I.pgm",
        "2J.pgm",
        "3A.pgm",
        "3B.pgm",
        "3C.pgm",
        "3D.pgm",
        "3E.pgm",
        "3F.pgm",
        "3G.pgm",
        "3H.pgm",
        "3I.pgm",
        "3J.pgm",
        "4A.pgm",
        "4B.pgm",
        "4C.pgm",
        "4D.pgm",
        "4E.pgm",
        "4F.pgm",
        "4G.pgm",
        "4H.pgm",
        "4I.pgm",
        "4J.pgm",
        "5A.pgm",
        "5B.pgm",
        "5C.pgm",
        "5D.pgm",
        "5E.pgm",
        "5F.pgm",
        "5G.pgm",
        "5H.pgm",
        "5I.pgm",
        "5J.pgm",
        "6A.pgm",
        "6B.pgm",
        "6C.pgm",
        "6D.pgm",
        "6E.pgm",
        "6F.pgm",
        "6G.pgm",
        "6H.pgm",
        "6I.pgm",
        "6J.pgm",
        "7A.pgm",
        "7B.pgm",
        "7C.pgm",
        "7D.pgm",
        "7E.pgm",
        "7F.pgm",
        "7G.pgm",
        "7H.pgm",
        "7I.pgm",
        "7J.pgm",
        "8A.pgm",
        "8B.pgm",
        "8C.pgm",
        "8D.pgm",
        "8E.pgm",
        "8F.pgm",
        "8G.pgm",
        "8H.pgm",
        "8I.pgm",
        "8J.pgm",
        "9A.pgm",
        "9B.pgm",
        "9C.pgm",
        "9D.pgm",
        "9E.pgm",
        "9F.pgm",
        "9G.pgm",
        "9H.pgm",
        "9I.pgm",
        "9J.pgm",
        "10A.pgm",
        "10B.pgm",
        "10C.pgm",
        "10D.pgm",
        "10E.pgm",
        "10F.pgm",
        "10G.pgm",
        "10H.pgm",
        "10I.pgm",
        "10J.pgm"
		};
	
    int count=0;
    int m =0;
    int n = 0;

    for (m =0 ; m < 10 ; m++)
    {
        for ( n =0 ; n < 8 ; n++)
        {
            k = 0;
            fp= fopen(chin[m*10+n],"rb");
            fgets(buf1,128,fp);
            fgets(buf2,128,fp);
            fgets(buf3,128,fp);
            for(i=0;i<=Height*Width-1;i++)
            {
                a[count][i] = fgetc(fp);
            }
            fclose(fp);
            count++;
        }
    }
    
    
    
//    CreateMatrix((ElementType *)a,FigureNum,Height*Width,&FigureStore);
	FigureStore.Data = a;
	FigureStore.row = FigureNum;
	FigureStore.column = Height*Width;
	
	
    TransposeMatrix(FigureStore,&FigureStoreTrans);
    StandradMatrixR(FigureStore,&A);
    TransposeMatrix(A,&ATrans);
    MultiplyMatrix(A,ATrans,&AMultiply);
    EigMatrix(AMultiply, &EigenValue, &EigenVector,500,0.00001);
    FindOrder(EigenValue,b);
    
    //求解均值向量
    for ( i = 0; i <= Height*Width-1; i++)
    {
        MeanVector[i]=0;
        for (j = 0; j < FigureNum; j++)
        {
            MeanVector[i]=MeanVector[i]+FigureStore.Data[j][i];
        }
        MeanVector[i]=MeanVector[i]/FigureNum;
    }
    
    for ( i = 0 ; i < 20; i++)//选取20个特征向量
    {
        for (j = 0; j <= FigureNum-1; j++)
        {
            c[i][j]=EigenVector.Data[j][(short)b[i]];
        }
    }
    CreateMatrix((ElementType *)c, 20, FigureNum, &M);//M中存储了前20个需要的特征向量
    MultiplyMatrix(M, A, &Result);
    
    
    char *cheigen[]={
        "EIGEN1.pgm",
        "EIGEN2.pgm",
        "EIGEN3.pgm",
        "EIGEN4.pgm",
        "EIGEN5.pgm",
        "EIGEN6.pgm",
        "EIGEN7.pgm",
        "EIGEN8.pgm",
        "EIGEN9.pgm",
        "EIGEN10.pgm",
        "EIGEN11.pgm",
        "EIGEN12.pgm",
        "EIGEN13.pgm",
        "EIGEN14.pgm",
        "EIGEN15.pgm",
        "EIGEN16.pgm",
        "EIGEN17.pgm",
        "EIGEN18.pgm",
        "EIGEN19.pgm",
        "EIGEN20.pgm",
        "EIGEN21.pgm",
        "EIGEN22.pgm",
        "EIGEN23.pgm",
        "EIGEN24.pgm",
        "EIGEN25.pgm",
        "EIGEN26.pgm",
        "EIGEN27.pgm",
        "EIGEN28.pgm",
        "EIGEN29.pgm",
        "EIGEN30.pgm",
        "EIGEN31.pgm",
        "EIGEN32.pgm",
        "EIGEN33.pgm",
        "EIGEN34.pgm",
        "EIGEN35.pgm",
        "EIGEN36.pgm",
        "EIGEN37.pgm",
        "EIGEN38.pgm",
        "EIGEN39.pgm",
        "EIGEN40.pgm",
        "EIGEN41.pgm",
        "EIGEN42.pgm",
        "EIGEN43.pgm",
        "EIGEN44.pgm",
        "EIGEN45.pgm",
        "EIGEN46.pgm",
        "EIGEN47.pgm",
        "EIGEN48.pgm",
        "EIGEN49.pgm",
        "EIGEN50.pgm"
    };
    
    

    
    //输出EigenFace
    CopyMatrix(A,&EigenFace);
    for ( i = 0; i < 20; i++)
    {
        for ( j = 0 ;j <= Height*Width-1; j++)
        {
            EigenFace.Data[i][j]=0;
        }
    }
    
    for ( i = 0; i < 20; i++)
    {
        for ( j = 0 ;j <= Height*Width-1; j++)
        {
            EigenFace.Data[i][j]=MeanVector[j]+Result.Data[i][j];
        }
    }
    
    //输出EigenFace至文件中
    for( i = 0; i <= 19; i++)
    {
        fp= fopen(cheigen[i],"wb");
        if (fp==NULL){
            printf("error!!");
            exit(0);
        }
        fputs(buf1,fp);
        fputs(buf2,fp);
        fputs(buf3,fp);
        for(j = 0; j<Height*Width; j++)
        {
            fputc((short)EigenFace.Data[i][j],fp);
        }
        fclose(fp);
    }
    
    //对于EigenFace进行标准化
    for ( i = 0; i <= 19; i++)
    {
        sum=0;
        for ( j = 0; j <= Height*Width-1;j++)
        {
            sum=sum+Result.Data[i][j]*Result.Data[i][j];
        }
        sum=sqrt(sum);
        for ( j = 0; j <= Height*Width-1;j++)
        {
            Result.Data[i][j]=Result.Data[i][j]/sum;
        }
    }
    //printf("%d",FigureStoreMultiply.row);
    MultiplyMatrix(Result, ATrans, &CoMatrix);
    
    
    
    //求每一个人的10张脸的平均值，更确切地说，是10张脸在20个特征维度上每一维的平均值
    ElementType p[10][Height*Width],MeanPerson[10][20];
    struct Matrix PersonStore,P,PTrans,PMatrix;
    
    for ( m = 0; m < 10; m++)
    {
        for ( n =0 ; n < 10 ; n++)
        {
            fp= fopen(chin[m*10+n],"rb");
            fgets(buf1,128,fp);
            fgets(buf2,128,fp);
            fgets(buf3,128,fp);
            for( i=0;i<=Height*Width-1;i++)
            {
                p[n][i] = fgetc(fp);
                p[n][i] -= MeanVector[i];
            }
            fclose(fp);
        }
        CreateMatrix((ElementType *)p,10,Height*Width,&PersonStore);
        //StandradMatrixR(PersonStore,&P);
        TransposeMatrix(PersonStore,&PTrans);
        MultiplyMatrix(Result, PTrans, &PMatrix);
        
        for ( k =0 ; k < 20 ; k++)
        {
            MeanPerson[m][k]=0;
            for ( n =0 ; n < 10 ; n++)
            {
                MeanPerson[m][k]=MeanPerson[m][k]+PMatrix.Data[k][n];
            }
            MeanPerson[m][k]=MeanPerson[m][k]/10;//第m个人第k个维度
            //printf("MeanPerson[%d][%d]=%f\n",m,k,MeanPerson[m][k]);
        }
    }
    
    //判断某一个未知的人脸属于哪一个人（Recognition）
    
    char* chrec[]=
    {
        "1I.pgm","1J.pgm","2I.pgm","2J.pgm","3I.pgm","3J.pgm","4I.pgm","4J.pgm","5I.pgm","5J.pgm",
        "6I.pgm","6J.pgm","7I.pgm","7J.pgm","8I.pgm","8J.pgm","9I.pgm","9J.pgm","10I.pgm","10J.pgm",
        "11A.pgm",
        "11B.pgm",
        "11C.pgm",
        "11D.pgm",
        "11E.pgm",
        "11F.pgm",
        "11G.pgm",
        "11H.pgm",
        "11I.pgm",
        "11J.pgm",
        "12A.pgm",
        "12B.pgm",
        "12C.pgm",
        "12D.pgm",
        "12E.pgm",
        "12F.pgm",
        "12G.pgm",
        "12H.pgm",
        "12I.pgm",
        "12J.pgm",
        "13A.pgm",
        "13B.pgm",
        "13C.pgm",
        "13D.pgm",
        "13E.pgm",
        "13F.pgm",
        "13G.pgm",
        "13H.pgm",
        "13I.pgm",
        "13J.pgm",
        "14A.pgm",
        "14B.pgm",
        "14C.pgm",
        "14D.pgm",
        "14E.pgm",
        "14F.pgm",
        "14G.pgm",
        "14H.pgm",
        "14I.pgm",
        "14J.pgm",
        "15A.pgm",
        "15B.pgm",
        "15C.pgm",
        "15D.pgm",
        "15E.pgm",
        "15F.pgm",
        "15G.pgm",
        "15H.pgm",
        "15I.pgm",
        "15J.pgm",
        "16A.pgm",
        "16B.pgm",
        "16C.pgm",
        "16D.pgm",
        "16E.pgm",
        "16F.pgm",
        "16G.pgm",
        "16H.pgm",
        "16I.pgm",
        "16J.pgm",
        "17A.pgm",
        "17B.pgm",
        "17C.pgm",
        "17D.pgm",
        "17E.pgm",
        "17F.pgm",
        "17G.pgm",
        "17H.pgm",
        "17I.pgm",
        "17J.pgm",
        "18A.pgm",
        "18B.pgm",
        "18C.pgm",
        "18D.pgm",
        "18E.pgm",
        "18F.pgm",
        "18G.pgm",
        "18H.pgm",
        "18I.pgm",
        "18J.pgm",
        "19A.pgm",
        "19B.pgm",
        "19C.pgm",
        "19D.pgm",
        "19E.pgm",
        "19F.pgm",
        "19G.pgm",
        "19H.pgm",
        "19I.pgm",
        "19J.pgm",
        "20A.pgm",
        "20B.pgm",
        "20C.pgm",
        "20D.pgm",
        "20E.pgm",
        "20F.pgm",
        "20G.pgm",
        "20H.pgm",
        "20I.pgm",
        "20J.pgm"};
    char* chmeta[]=
    {
        "1I.pgm.meta","1J.pgm.meta","2I.pgm.meta","2J.pgm.meta","3I.pgm.meta","3J.pgm.meta","4I.pgm.meta","4J.pgm.meta","5I.pgm.meta","5J.pgm.meta","6I.pgm.meta","6J.pgm.meta","7I.pgm.meta","7J.pgm.meta","8I.pgm.meta","8J.pgm.meta","9I.pgm.meta","9J.pgm.meta","10I.pgm.meta","10J.pgm.meta",
        "11A.pgm.meta",
        "11B.pgm.meta",
        "11C.pgm.meta",
        "11D.pgm.meta",
        "11E.pgm.meta",
        "11F.pgm.meta",
        "11G.pgm.meta",
        "11H.pgm.meta",
        "11I.pgm.meta",
        "11J.pgm.meta",
        "12A.pgm.meta",
        "12B.pgm.meta",
        "12C.pgm.meta",
        "12D.pgm.meta",
        "12E.pgm.meta",
        "12F.pgm.meta",
        "12G.pgm.meta",
        "12H.pgm.meta",
        "12I.pgm.meta",
        "12J.pgm.meta",
        "13A.pgm.meta",
        "13B.pgm.meta",
        "13C.pgm.meta",
        "13D.pgm.meta",
        "13E.pgm.meta",
        "13F.pgm.meta",
        "13G.pgm.meta",
        "13H.pgm.meta",
        "13I.pgm.meta",
        "13J.pgm.meta",
        "14A.pgm.meta",
        "14B.pgm.meta",
        "14C.pgm.meta",
        "14D.pgm.meta",
        "14E.pgm.meta",
        "14F.pgm.meta",
        "14G.pgm.meta",
        "14H.pgm.meta",
        "14I.pgm.meta",
        "14J.pgm.meta",
        "15A.pgm.meta",
        "15B.pgm.meta",
        "15C.pgm.meta",
        "15D.pgm.meta",
        "15E.pgm.meta",
        "15F.pgm.meta",
        "15G.pgm.meta",
        "15H.pgm.meta",
        "15I.pgm.meta",
        "15J.pgm.meta",
        "16A.pgm.meta",
        "16B.pgm.meta",
        "16C.pgm.meta",
        "16D.pgm.meta",
        "16E.pgm.meta",
        "16F.pgm.meta",
        "16G.pgm.meta",
        "16H.pgm.meta",
        "16I.pgm.meta",
        "16J.pgm.meta",
        "17A.pgm.meta",
        "17B.pgm.meta",
        "17C.pgm.meta",
        "17D.pgm.meta",
        "17E.pgm.meta",
        "17F.pgm.meta",
        "17G.pgm.meta",
        "17H.pgm.meta",
        "17I.pgm.meta",
        "17J.pgm.meta",
        "18A.pgm.meta",
        "18B.pgm.meta",
        "18C.pgm.meta",
        "18D.pgm.meta",
        "18E.pgm.meta",
        "18F.pgm.meta",
        "18G.pgm.meta",
        "18H.pgm.meta",
        "18I.pgm.meta",
        "18J.pgm.meta",
        "19A.pgm.meta",
        "19B.pgm.meta",
        "19C.pgm.meta",
        "19D.pgm.meta",
        "19E.pgm.meta",
        "19F.pgm.meta",
        "19G.pgm.meta",
        "19H.pgm.meta",
        "19I.pgm.meta",
        "19J.pgm.meta",
        "20A.pgm.meta",
        "20B.pgm.meta",
        "20C.pgm.meta",
        "20D.pgm.meta",
        "20E.pgm.meta",
        "20F.pgm.meta",
        "20G.pgm.meta",
        "20H.pgm.meta",
        "20I.pgm.meta",
        "20J.pgm.meta"};
    ElementType rec[1][Height*Width];
    struct Matrix RecStore,R,RTrans,RMatrix;
    
    
    for ( j = 0; j < 120; j++)
    {
        //1.输入该人脸，并求它的20维权重
        fpout= fopen(chmeta[j],"w");
        fp= fopen(chrec[j],"rb");
        fgets(buf1,128,fp);
        fgets(buf2,128,fp);
        fgets(buf3,128,fp);
        for( i=0;i<=Height*Width-1;i++)
        {
            rec[0][i] = fgetc(fp);
            rec[0][i] -= MeanVector[i];
            //rec[0][i] = a[1][i]-MeanVector[i];
        }
        fclose(fp);
        CreateMatrix((ElementType *)rec,1,Height*Width,&RecStore);
        //StandradMatrixR(RecStore,&R);
        TransposeMatrix(RecStore,&RTrans);
        MultiplyMatrix(Result, RTrans, &RMatrix);
        
        //2.与每个人的平均权重值计算欧氏距离
        ElementType min=99999;
        int min_index=0;
        int k = 0;
        for ( m = 0; m < 10; m++)
        {
            sum=0;
            for ( k = 0; k < 20;k++)
            {
                sum=sum+(RMatrix.Data[k][0]-MeanPerson[m][k])*(RMatrix.Data[k][0]-MeanPerson[m][k]);
            }
            sum=sqrt(sum);
            if (sum<min)
            {
                min=sum;
                min_index=m;
            }
        }
        if (min<1956) {
            fprintf(fpout,"Is it anyone in the library:Yes\n");
            fprintf(fpout,"It seems to be:%d\n",min_index+1);
        }
        else fprintf(fpout,"Is it anyone in the library:No\n");
        fclose(fpout);
    }
    
    
    
    /*
    //输出相应的图片
    char* chout[]={
        "OUT1.pgm",
        "OUT2.pgm",
        "OUT3.pgm",
        "OUT4.pgm",
        "OUT5.pgm",
        "OUT6.pgm",
        "OUT7.pgm",
        "OUT8.pgm",
        "OUT9.pgm",
        "OUT10.pgm",
        "OUT11.pgm",
        "OUT12.pgm",
        "OUT13.pgm",
        "OUT14.pgm",
        "OUT15.pgm",
        "OUT16.pgm",
        "OUT17.pgm",
        "OUT18.pgm",
        "OUT19.pgm",
        "OUT20.pgm",
        "OUT21.pgm",
        "OUT22.pgm",
        "OUT23.pgm",
        "OUT24.pgm",
        "OUT25.pgm",
        "OUT26.pgm",
        "OUT27.pgm",
        "OUT28.pgm",
        "OUT29.pgm",
        "OUT30.pgm",
        "OUT31.pgm",
        "OUT32.pgm",
        "OUT33.pgm",
        "OUT34.pgm",
        "OUT35.pgm",
        "OUT36.pgm",
        "OUT37.pgm",
        "OUT38.pgm",
        "OUT39.pgm",
        "OUT40.pgm",
        "OUT41.pgm",
        "OUT42.pgm",
        "OUT43.pgm",
        "OUT44.pgm",
        "OUT45.pgm",
        "OUT46.pgm",
        "OUT47.pgm",
        "OUT48.pgm",
        "OUT49.pgm",
        "OUT50.pgm",
        "OUT51.pgm",
        "OUT52.pgm",
        "OUT53.pgm",
        "OUT54.pgm",
        "OUT55.pgm",
        "OUT56.pgm",
        "OUT57.pgm",
        "OUT58.pgm",
        "OUT59.pgm",
        "OUT60.pgm",
        "OUT61.pgm",
        "OUT62.pgm",
        "OUT63.pgm",
        "OUT64.pgm",
        "OUT65.pgm",
        "OUT66.pgm",
        "OUT67.pgm",
        "OUT68.pgm",
        "OUT69.pgm",
        "OUT70.pgm",
        "OUT71.pgm",
        "OUT72.pgm",
        "OUT73.pgm",
        "OUT74.pgm",
        "OUT75.pgm",
        "OUT76.pgm",
        "OUT77.pgm",
        "OUT78.pgm",
        "OUT79.pgm",
        "OUT80.pgm",
        "OUT81.pgm",
        "OUT82.pgm",
        "OUT83.pgm",
        "OUT84.pgm",
        "OUT85.pgm",
        "OUT86.pgm",
        "OUT87.pgm",
        "OUT88.pgm",
        "OUT89.pgm",
        "OUT90.pgm",
        "OUT91.pgm",
        "OUT92.pgm",
        "OUT93.pgm",
        "OUT94.pgm",
        "OUT95.pgm",
        "OUT96.pgm",
        "OUT97.pgm",
        "OUT98.pgm",
        "OUT99.pgm",
        "OUT100.pgm"
    };

    CopyMatrix(A, &B);

    //初始化近似矩阵的原数值
    for(int i = 0; i <= 99;i++)
    {
        for ( int j=0; j <= Width*Height-1;j++)
        {
            B.Data[i][j]=0;
            B.Data[i][j]=B.Data[i][j]+MeanVector[j];
        }
    }
    
    //计算近似矩阵
    for( int i = 0; i <= 99; i++)
    {
        for( int j = 0; j <= 19; j++)
        {
            for( int m = 0 ;m <= Height*Width-1;m++)
            {
                B.Data[i][m]=B.Data[i][m]+Result.Data[j][m]*CoMatrix.Data[j][i];
            }
        }
    }
    
    //将近似矩阵B中的图像逐个储存在文件中
    for( int i = 0 ; i <= 99; i++)
    {
        fp= fopen(chout[i],"wb");
        if (fp==NULL)
        {
            printf("error!!");
            exit(0);
        }
        fputs(buf1,fp);
        fputs(buf2,fp);
        fputs(buf3,fp);
        for(int j = 0; j<Height*Width; j++)
        {
            fputc((short)B.Data[i][j],fp);
        }
        fclose(fp);
    }*/

    return 1;
}
/********************************************************************/


void DisplayMatrix(struct Matrix A)
{
    int i,j;
    for(i = 0;i < A.row ; i++)
    {
        for(j = 0;j <A.column; j++)
        {
            //printf("%lf,",A.Data[i][j]);
        }
        //printf("\n");
    }
    
}
int CopyMatrix(struct Matrix A,struct Matrix *B)
{
    int i,j;
    B->row = A.row;
    B->column = A.column;
    B->Data = (ElementType **)malloc(sizeof(ElementType *) *A.row);//为要访问的数据创建空间
    for(i = 0; i < A.row; i ++)
    {
        B->Data[i] = (ElementType *)malloc(sizeof(ElementType) *A.column);//将二维数组行地址赋值到对应的一维指针上。
        for(j = 0;j <A.column ;j++)
            B->Data[i][j] = A.Data[i][j];
    }
    return 1;
}
int CreateMatrix(ElementType *a,int row,int column,struct Matrix *A)
{
    int i,j;
    A->row = row;
    A->column = column;
    ElementType **c =NULL;
    c = (ElementType **)malloc(sizeof(ElementType *) *row);
    for(i = 0;i<row ;i++)
    {
        c[i] = (ElementType *)malloc(sizeof(ElementType) *column);
        for(j = 0;j <column ;j++)
            c[i][j] = a[column*i+j];
    }
    
    A->Data = c;
    
    return 1;
}
int AddMatrix(struct Matrix A, struct Matrix B,struct Matrix *C)
{
    if((A.row == B.row)&&(A.column == B.column))
    {
        int i,j;
        C->row = A.row;
        C->column = A.column;
        C->Data = (ElementType **)malloc(sizeof(ElementType *) *A.row);//为要访问的数据创建空间
        for(i = 0; i < A.row; i ++)
        {
            C->Data[i] = (ElementType *)malloc(sizeof(ElementType) *A.column);//将二维数组行地址赋值到对应的一维指针上。
            for(j = 0;j <A.column ;j++)
                C->Data[i][j] = A.Data[i][j]+B.Data[i][j];
        }
        return 1;
    }
    else
        return 0;
    
}
int MinusMatrix(struct Matrix A, struct Matrix B,struct Matrix *C)
{
    if((A.row == B.row)&&(A.column == B.column))
    {
        int i,j;
        C->row = A.row;
        C->column = A.column;
        C->Data = (ElementType **)malloc(sizeof(ElementType *) *A.row);//为要访问的数据创建空间
        for(i = 0; i < A.row; i ++)
        {
            C->Data[i] = (ElementType *)malloc(sizeof(ElementType) *A.column);//将二维数组行地址赋值到对应的一维指针上。
            for(j = 0;j <A.column ;j++)
                C->Data[i][j] = A.Data[i][j]-B.Data[i][j];
        }
        return 1;
    }
    else
        return 0;
    
}
int MultiplyMatrix(struct Matrix A, struct Matrix B,struct Matrix *C)
{
    
    if(A.column == B.row)
    {
        int i,j,k;
        C->row = A.row;
        C->column = B.column;
        C->Data = (ElementType **)malloc(sizeof(ElementType *) *A.row);//为要访问的数据创建空间
        for(i = 0; i < C->row; i ++)
        {
            C->Data[i] = (ElementType *)malloc(sizeof(ElementType) *B.column);//将二维数组行地址赋值到对应的一维指针上。
            for(j = 0;j < C->column ;j++)
            {
                C->Data[i][j] = 0;
                for(k = 0; k < A.column; k++)
                    C->Data[i][j] = C->Data[i][j]+ A.Data[i][k]*B.Data[k][j];
            }
        }
        return 1;
    }
    else
        return 0;
    
}
int TransposeMatrix(struct Matrix A, struct Matrix *B)
{
    int i,j;
    B->row = A.column;
    B->column = A.row;
    B->Data = (ElementType **)malloc(sizeof(ElementType *) *B->row);//为要访问的数据创建空间
    for(i = 0; i < B->row; i ++)
    {
        B->Data[i] = (ElementType *)malloc(sizeof(ElementType) *B->column);//将二维数组行地址赋值到对应的一维指针上。
        for(j = 0;j <B->column ;j++)
            B->Data[i][j] = A.Data[j][i];
    }
    return 1;
}
int MergeMatrix(struct Matrix A, struct Matrix *B)
{
    int i,j;
    B->row = 1;
    B->column = A.row*A.column;
    B->Data = (ElementType **)malloc(sizeof(ElementType *) *1);//为要访问的数据创建空间
    B->Data[0] = (ElementType *)malloc(sizeof(ElementType) *B->row*B->column);//将二维数组行地址赋值到对应的一维指针上。
    for(i = 0; i < A.row; i ++)
    {
        for(j = 0;j <A.column ;j++)
            B->Data[0][i*A.column+j] = A.Data[i][j];
    }
    return 1;
}
int DeleteMatrix(struct Matrix *A)
{
    int i;
    for(i = 0;i < A->row ; i++)
    {
        free(A->Data[i]);
    }
    free(A->Data);
    A->Data = NULL;
    A->row = 0;
    A->column = 0;
    //		free(A);
    return 0;
}
int CreateIdentityMatrix(struct Matrix *A,int size)
{
    int i,j;
    if(A==NULL)               //检测指针是否为空
 		 {
             printf("The matrix pointer is NULL\n");
             return(0);
         }
    else
    {
        A->row = size;
        A->column = size;
        A->Data = (ElementType **)malloc(sizeof(ElementType *) *size);
        for(i = 0;i < size; i++)
        {
            A->Data[i] = (ElementType *)malloc(sizeof(ElementType ) *size);
            for( j = 0; j < size; j++)
            {
                if(i == j)
                    A->Data[i][j] = 1;
                else
                    A->Data[i][j] = 0;
            }
        }
        return(1);
    }
}
int JudgeSymmetry(struct Matrix A)
{
    int i,j;
    if(A.row == A.column)
    {
        for(i = 0;i < A.row; i++)
        {
            for(j = i+1;j < A.row; j++)
            {
                if((A.Data[i][j] - A.Data[j][i] > Inf1)||(A.Data[i][j] - A.Data[j][i] < -Inf1))
                    return 0;
            }
        }
        return 1;
    }
    else
        return 0;
}
int FindSMatrixElement(struct Matrix A,int *row,int *column)
{
    int i = 0,j = 0,ir = 0,jr = 0;
    ElementType temp;
    if(!JudgeSymmetry(A))
    {
        printf(" not a Symmetry Matrix\n");
        return 0;
    }
    else if((row == NULL)||(column == NULL))
    {
        printf(" a NULL pointer");
        return 0;
    }
    else
    {
        temp = fabs(A.Data[0][1]);
        ir = 0,jr = 1;
        for(i = 0;i < A.row; i++){
            for(j = i+1; j<A.row; j++)
            {
                if(A.Data[i][j]>temp)
                {
                    temp = A.Data[i][j];
                    ir = i;
                    jr = j;
                }
                if(A.Data[i][j]<-temp)
                {
                    temp = -A.Data[i][j];
                    ir = i;
                    jr = j;
                }
            }
        }
        *row = ir;
        *column = jr;
        return 1;
    }
}
int StandradMatrixR(struct Matrix A,struct Matrix *B)
{
    ElementType *temp;
    temp = (ElementType *)malloc(sizeof(ElementType)*A.column);
    CopyMatrix(A,B);
    int i,j;
    for(i = 0;i <A.column;i++)
    {
        temp[i] = 0;
        for(j = 0; j < A.row ; j++){
            temp[i] = temp[i]+A.Data[j][i];
        }
        temp[i] = temp[i]/A.row;
    }
    
    for(i = 0;i < A.row;i++)
    {
        for(j = 0; j < A.column ; j++){
            B->Data[i][j] = B->Data[i][j] - temp[j];
        }
    }
    return 1;
}
int StandradMatrixC(struct Matrix A,struct Matrix *B)
{
    ElementType *temp;
    temp = (ElementType *)malloc(sizeof(ElementType)*A.row);
    CopyMatrix(A,B);
    int i,j;
    for(i = 0;i <A.row;i++)
    {
        temp[i] = 0;
        for(j = 0; j < A.column; j++){
            temp[i] = temp[i]+A.Data[i][j];
        }
        temp[i] = temp[i]/A.column;
    }
    
    for(i = 0;i < A.column;i++)
    {
        for(j = 0; j < A.row ; j++){
            B->Data[j][i] = B->Data[j][i] - temp[j];
        }
    }
    return 1;
}
int SwapBuffer(struct Matrix A,struct Matrix *B)
{//把 A 的结果放在B中
    if((A.row == B->row)&&(A.column == B->column)&&(A.column != 0)&&(A.row != 0))
    {
        int i,j;
        for(i = 0; i < A.row; i ++)
        {
            for(j = 0;j <A.column ;j++)
                B->Data[i][j] = A.Data[i][j];
        }
        return 1;
    }
    else
        return 0;
}
int EigMatrix(struct Matrix A, struct Matrix *B, struct Matrix *C,int Nmax,double prec)
{//B为特征值，C为特征向量
    struct Matrix *temp = NULL,*swap = NULL,*tempC = NULL;
    struct Matrix MATa,MATb;
    temp = &MATa;
    swap = &MATb;
    int a,b;
    int count = 0;
    double phi1,phi2;
    if((B == NULL)||( C == NULL))
    {
        printf("The matrix pointer is NULL\n");
        return(0);
    }
    if(!JudgeSymmetry(A))
        return 0;
    if(CopyMatrix(A,B)){//把原矩阵复制
        
        //printf("\n");
        //printf("result is\n");
        //DisplayMatrix(*B);
        if((CreateIdentityMatrix(C,A.row))&&(CreateIdentityMatrix(temp,A.row))&&(CreateIdentityMatrix(swap,A.row)))
        {//新建特征向量矩阵
            if(!FindSMatrixElement(A,&a,&b))
                return 0;
            else
            {
                count =0;
                while(1)
                {
                    //printf("num %d\n",count);
                    count++ ;
                    FindSMatrixElement(*B,&a,&b);
                    //printf("%d , %d  max %lf\n",a , b , B->Data[a][b]);
                    
                    if((B->Data[a][b] < prec)&&(B->Data[a][b] > -prec))
                        break;
                    if(count > Nmax)
                        break;
                    phi1 = (atan((2*B->Data[a][b])/(B->Data[a][a] - B->Data[b][b])))/2;
                    temp->Data[a][b] = -sin(phi1);
                    temp->Data[b][a] = sin(phi1);
                    temp->Data[a][a] = temp->Data[b][b] = cos(phi1);
                    
                    MultiplyMatrix(*C,*temp,swap);
                    SwapBuffer(*swap,C);
                    MultiplyMatrix(*B,*temp,swap);
                    SwapBuffer(*swap,B);
                    
                    temp->Data[a][b] = sin(phi1);
                    temp->Data[b][a] = -sin(phi1);
                    MultiplyMatrix(*temp,*B,swap);
                    SwapBuffer(*swap,B);
                    
                    temp->Data[a][b] = 0;
                    temp->Data[b][a] = 0;
                    temp->Data[a][a] = temp->Data[b][b] = 1;
                    //printf("\n");
                    //printf("result is\n");
                    DisplayMatrix(*B);
                    //printf("\n");
                    //printf("result is\n");
                    DisplayMatrix(*C);
                }
                return 1;
            }
            
        }
    }
    else
        return 0;
    
    return 1;
}
int FindOrder(struct Matrix A,double *order)
{
    int i,j,k;
    ElementType *temp;
    ElementType tmp1,tmp2;
    if(A.column != A.row)
    {
        printf("can not find order!\n");
        return 0;
    }
    else
    {
        temp = (ElementType *)malloc(sizeof(ElementType)*A.row);
        for(i = 0; i < A.row ;i++){
            if(A.Data[i][i] == 0)
                return 0;
            temp[i] = A.Data[i][i];
        }
        for(i = 0; i < A.row ;i++)
        {
            tmp1  = temp[0];
            k = 0;
            for(j = 0; j < A.row ;j++)
            {
                if(temp[j] > tmp1){
                    k = j;
                    tmp1  = temp[j];
                }
                if(temp[j] < -tmp1){
                    k = j;
                    tmp1  = -temp[j];
                }
            }
            order[i] = k;
            temp[k] = 0; 
        }
    }
    return 1;
}


