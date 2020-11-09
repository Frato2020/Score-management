/**************************
***成绩管理系统
***V3.0
***二维字符数组的运用
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//宏定义常量
//N——学生人数,X——姓名所占字符数,C——考试门数
#define N 30
#define X 22
#define S 6

/**************************
***函数Input
***输入学生人数、学号及成绩
***变量n——人数,ret——检测返回值,i,j——计数
***返回学生人数
**************************/
int Input(long number[],float score[][S],long cpynum[],float cpysco[][S],char name[][X],char cpynam[][X],int *pcourse)
{
    int n,ret,i,j;
    /*输入学生人数及考试门数（用指针传递考试门数）*/
    do
    {
        printf("How many students?(not higher than 30)\n");
        ret=scanf("%d",&n);
        if(ret!=1)
        {
            printf("Wrong input format,please try again.\n\n");
            while(getchar()!='\n');
        }
        else if(n<=0||n>30)
            printf("The number you input is not permitted.\n\n");
    }
    while(n<=0||n>30||ret!=1);

    do
    {
        printf("How many courses?(not higher than 6)\n");
        ret=scanf("%d",pcourse);
        if(ret!=1)
        {
            printf("Wrong input format,please try again.\n\n");
            while(getchar()!='\n');
        }
        else if(*pcourse<=0||*pcourse>6)
            printf("The number you input is not permitted.\n\n");
    }
    while(ret!=1||*pcourse<=0||*pcourse>6);
    /*输入学生信息*/
    printf("Input numbers,names and scores in order.(seperated by Enter)\n");
    for(i=0; i<n; i++)
    {
        do
        {
            printf("Student %d:\n",i+1);
            printf("Number:");
            if((ret=(scanf("%ld",&number[i])!=1)))
            {
                printf("Invalid input.\n");
                while(getchar()!='\n');
            }
            for(j=0;j<i;j++)
            {
                if(number[i]==number[j])
                {
                    printf("Input repeatedly.\n");
                    ret=1;
                    break;
                }
            }
        }
        while(ret==1);
        while(getchar()!='\n');

        do
        {
            printf("Name(1~20 characters supposed):\n");
            fgets(name[i],X,stdin);
            if(name[i][strlen(name[i])-1]!='\n')
            {
                printf("The name you input may cause wrong output.\n");
                while(getchar()!='\n');
            }
        }
        while(name[i][strlen(name[i])-1]!='\n');

        for(j=0; j<*pcourse; j++)
        {
            printf("Score[%d]:",j+1);
            if(scanf("%f",&score[i][j])!=1)
            {
                printf("Invalid input.\n");
                while(getchar()!='\n');
                j--;
                continue;
            }
            else if(score[i][j]>100||score[i][j]<0)
            {
                printf("Please check the score you input(0~100 expected).\n");
                j--;
                continue;
            }
        }
    }

    for(i=0; i<n; i++)
    {
        name[i][strlen(name[i])-1]='\0';
    }
    memcpy(cpynum,number,N*sizeof(long));
    memcpy(cpysco,score,N*S*sizeof(float));
    for(i=0; i<n; i++)
    {
        strcpy(cpynam[i],name[i]);
    }
    return n;
}

/*****************************
***函数SumAndAver
***计算每门课程的总分和平均分
***变量i,j——计数,sum——总分
***输出总分和平均分
*****************************/
void SumAndAver(float score[][S],int course,int n)
{
    int i,j;
    float sum;
    printf("            Sum     Average\n");
    for(j=0; j<course; j++)
    {
        sum=0;
        for(i=0; i<n; i++)
        {
            sum+=score[i][j];
        }
        printf("Course[%d]   %-7.1f %f\n",j+1,sum,sum/n);
    }
}

/******************************
***函数SumAndAverStu
***计算每个学生的总分与平均分
******************************/
void SumAndAverStu(long number[],float score[][S],char name[][X],float sum[],int course,int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<course; j++)
        {
            sum[i]+=score[i][j];
        }
    }
}

/***************************
***函数Temp
***交换数组中的元素
***变量temp1,temp2——用于交换
***************************/
void Temp(long number[],float score[][S],char name[][X],float sum[],int i,int k)
{
    long temp1;
    float temp2,temp4[S];
    char temp3[X];
    temp1=number[i];
    number[i]=number[k];
    number[k]=temp1;
    temp2=sum[i];
    sum[i]=sum[k];
    sum[k]=temp2;
    strcpy(temp3,name[i]);
    strcpy(name[i],name[k]);
    strcpy(name[k],temp3);
    memcpy(temp4,score[i],S*sizeof(float));
    memcpy(score[i],score[k],S*sizeof(float));
    memcpy(score[k],temp4,S*sizeof(float));
}

/********************************
***函数SortByScore
***输入学号、成绩、人数与函数指针
***变量i,j——计数,k——记录最值
***输出按成绩排序的学号与成绩
********************************/
void SortByScore(long number[],float score[][S],char name[][X],float sum[],int n,int (*f)(float *,int,int))
{
    int i,j,k;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if((*f)(sum,k,j))
                k=j;
        }
        Temp(number,score,name,sum,i,k);
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,number[i],name[i],sum[i]);
    }
}

/***************
***函数Ascend
***升序排列输出1
***************/
int Ascend(float score[],int k,int j)
{
    return score[k]>score[j];
}

/***************
***函数Descend
***降序排列输出1
***************/
int Descend(float score[],int k,int j)
{
    return score[k]<score[j];
}

/****************************
***函数SortByNumber
***输入学号、成绩与人数
***变量i,j——计数,k——记录最值
***输出按学号排序的学号与成绩
****************************/
void SortByNumber(long number[],float score[][S],char name[][X],float sum[],int n)
{
    int i,j,k;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if(number[j]<number[k])
                k=j;
        }
        Temp(number,score,name,sum,i,k);
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,number[i],name[i],sum[i]);
    }
}

/*****************
***函数SortByName
***按姓名排名
*****************/
void SortByName(long number[],float score[][S],char name[][X],float sum[],int n)
{
    int i,j,k;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if(strcmp(name[k],name[j])>=0)
            {
                k=j;
            }
        }
        Temp(number,score,name,sum,i,k);
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,number[i],name[i],sum[i]);
    }
}

/*************************
***函数Rank
***获取指定学号的排名
***变量r——记录排名,k——计数
*************************/
int Rank(float sco,float sum[],int n)
{
    int k,r=1;
    for(k=0; k<n; k++)
    {
        if(sum[k]>sco)
            r++;
    }
    return r;
}

/****************
***函数Search
***输入学号num
***变量i,j——计数
***输出排名与成绩
****************/
void Search(long number[],float score[][S],float sum[],int n,int course)
{
    int i,j;
    long num;
    printf("Please input the number:\n");
    scanf("%ld",&num);
    for(i=0; i<n; i++)
    {
        if(number[i]==num)
        {
            printf("Rank ");
            for(j=0; j<course; j++)
            {
                printf("Score[%-1d] ",j+1);
            }
            putchar('\n');

            printf("%-5d",Rank(sum[i],sum,n));
            for(j=0; j<course; j++)
            {
                printf("%-9.1f",score[i][j]);
            }
            putchar('\n');
            i++;
            break;
        }
    }
    if(number[i-1]!=num)
        printf("No result,please check the data.\n");
}

/******************
***函数SearchByName
***按姓名查找
***变量i,j——计数,flag——标记是否找到数据
*******************/
void SearchByName(long number[],float score[][S],char name[][X],float sum[],int n,int course)
{
    int i,j,flag=0;
    char nam[X];

    printf("Please input the name:\n");
    while(getchar()!='\n');
    fgets(nam,X,stdin);
    nam[strlen(nam)-1]='\0';

    for(i=0; i<n; i++)
    {
        if(strcmp(nam,name[i])==0)
        {

            if(flag==0)
            {
                printf("Number     Rank ");
                for(j=0; j<course; j++)
                {
                    printf("Score[%-1d] ",j+1);
                }
                putchar('\n');
            }

            printf("%-10ld %-3d  ",number[i],Rank(sum[i],sum,n));
            for(j=0; j<course; j++)
                printf("%-9.1f",score[i][j]);
            putchar('\n');
            flag++;
        }
    }
    if(flag==0)
        printf("No result,please check the data.\n");
    printf("Press Enter to continue.\n");
}

/*****************************
***函数Analysis
***统计各分数段人数及比例
***变量A,B,C,D,E——各分数段人数,i,j——计数
*****************************/
void Analysis(float score[][S],int n,int course)
{
    int i,j,A,B,C,D,E;
    printf("           90~100      80~90       70~80       60~70       0~60\n");
    for(j=0; j<course; j++)
    {
        A=B=C=D=E=0;
        for(i=0; i<n; i++)
        {
            if(score[i][j]<=100&&score[i][j]>=90)
                A++;
            else if(score[i][j]<90&&score[i][j]>=80)
                B++;
            else if(score[i][j]<80&&score[i][j]>=70)
                C++;
            else if(score[i][j]<70&&score[i][j]>=60)
                D++;
            else
                E++;
        }

        printf("Course[%-1d]||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%\n",
               j+1,A,(float)A*100/n,B,(float)B*100/n,C,(float)C*100/n,D,(float)D*100/n,E,(float)E*100/n);
    }
}

/****************************
***函数Output
***按输入的顺序输出学号与成绩
***变量i,j——计数
****************************/
void Output(long number[],float score[][S],char name[][X],float sum[],int n,int course)
{
    int i,j;
    printf("Number      Name                  ");
    for(j=0; j<course; j++)
    {
        printf("Score[%-1d] ",j+1);
    }
    printf("Sum      Average");
    putchar('\n');

    for(i=0; i<n; i++)
    {
        printf("%-10ld  %-20s  ",number[i],name[i]);
        for(j=0; j<course; j++)
            printf("%-8.1f ",score[i][j]);
        printf("%.1f   %f\n",sum[i],sum[i]/course);
    }
}

/*************************************************************
***主函数main
***选择子函数
***变量choice——用户的选择,n——总人数,course——课程数,i——计数,flag——标记用户是否输入数据
***数组number,score,name,sum——学号,分数,名字,个人总分,cpynum,cpysco,cpynam——备份数据
*************************************************************/
int main()
{
    /*学号与项目编号*/
    printf("Number:200210522\nsubject No.7\n\n");
    /*用户菜单*/
    int choice,n,course,i,flag=0;
    int *pcourse=&course;
    long number[N]={0},cpynum[N];
    float score[N][S]= {0},cpysco[N][S]= {0},sum[N]= {0};
    char name[N][X],cpynam[N][X];
    do
    {
        printf("1. Input record.\n");
        printf("2. Calculate total and average score of every course.\n");
        printf("3. Calculate total and average score of every student.\n");
        printf("4. Sort in descending order by total score of every student.\n");
        printf("5. Sort in ascending order by total score of every student.\n");
        printf("6. Sort in ascending order by number.\n");
        printf("7. Sort in dictionary order by name.\n");
        printf("8. Search by number.\n");
        printf("9. Search by name.\n");
        printf("10. Statistic analysis for every course.\n");
        printf("11.List record.\n");
        printf("0 .Exit.\n");
        printf("Please enter your choice:");
        if(scanf("%d",&choice)!=1||choice<0||choice>11)
        {
            printf("Invalid input.\n");
            while(getchar()!='\n');
            continue;
        }
        if(choice==1||choice==0)
            flag=1;
        else if(flag!=1)
        {
            printf("There is no data input,please try again.\n\n");
            continue;
        }
        switch(choice)
        {
        case 1:
            n=Input(number,score,cpynum,cpysco,name,cpynam,pcourse);
            SumAndAverStu(number,score,name,sum,course,n);
            break;
        case 2:
            SumAndAver(score,course,n);
            break;
        case 3:
            printf("Number    Name                Sum     Average\n");
            for(i=0; i<n; i++)
            {
                printf("%-10ld%-20s%-7.1f %f\n",number[i],name[i],sum[i],sum[i]/course);
            }
            break;
        case 4:
            SortByScore(number,score,name,sum,n,Descend);
            break;
        case 5:
            SortByScore(number,score,name,sum,n,Ascend);
            break;
        case 6:
            SortByNumber(number,score,name,sum,n);
            break;
        case 7:
            SortByName(number,score,name,sum,n);
            break;
        case 8:
            Search(number,score,sum,n,course);
            break;
        case 9:
            SearchByName(number,score,name,sum,n,course);
            break;
        case 10:
            Analysis(score,n,course);
            break;
        case 11:
            Output(cpynum,cpysco,cpynam,sum,n,course);
            break;
        case 0:
            break;
        default:
            printf("Invalid input.\n");
            break;
        }
        while(getchar()!='\n');
        printf("__________________________________________________\n");
    }
    while(choice!=0);
    return 0;
}

