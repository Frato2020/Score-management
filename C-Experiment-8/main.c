/**************************
***�ɼ�����ϵͳ
***V4.0
***�ṹ�����������
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�궨�峣��
//N����ѧ������,X����������ռ�ַ���,C������������
#define N 30
#define X 22
#define S 6

typedef struct student
{
    long number;
    float score[S];
    char name[X];
    float sum;
} STU;
/**************************
***����Input
***����ѧ��������ѧ�ż��ɼ�
***����n��������,ret������ⷵ��ֵ,i,j��������
***����ѧ������
**************************/
int Input(STU student[],int *pcourse)
{
    int n,ret,i,j;
    /*����ѧ��������������������ָ�봫�ݿ���������*/
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
    /*����ѧ����Ϣ*/
    printf("Input numbers,names and scores in order.(seperated by Enter)\n");
    for(i=0; i<n; i++)
    {
        do
        {
            printf("Student %d:\n",i+1);
            printf("Number:");
            if((ret=(scanf("%ld",&(student[i].number))!=1)))
            {
                printf("Invalid input.\n");
                while(getchar()!='\n');
            }
            for(j=0; j<i; j++)
            {
                if((student[i].number)==(student[j].number))
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
            fgets((student[i].name),X,stdin);
            if((student[i].name[strlen(student[i].name)-1])!='\n')
            {
                printf("The name you input may cause wrong output.\n");
                while(getchar()!='\n');
            }
        }
        while((student[i].name[strlen(student[i].name)-1])!='\n');

        for(j=0; j<*pcourse; j++)
        {
            printf("Score[%d]:",j+1);
            if(scanf("%f",&student[i].score[j])!=1)
            {
                printf("Invalid input.\n");
                while(getchar()!='\n');
                j--;
                continue;
            }
            else if(student[i].score[j]>100||student[i].score[j]<0)
            {
                printf("Please check the score you input(0~100 expected).\n");
                j--;
                continue;
            }
        }
    }

    for(i=0; i<n; i++)
    {
        (student[i].name[strlen(student[i].name)-1])='\0';
    }

    return n;
}

/*****************************
***����SumAndAver
***����ÿ�ſγ̵��ֺܷ�ƽ����
***����i,j��������,sum�����ܷ�
***����ֺܷ�ƽ����
*****************************/
void SumAndAver(STU student[],int course,int n)
{
    int i,j;
    float sum;
    printf("            Sum     Average\n");
    for(j=0; j<course; j++)
    {
        sum=0;
        for(i=0; i<n; i++)
        {
            sum+=(student[i].score[j]);
        }
        printf("Course[%d]   %-7.1f %f\n",j+1,sum,sum/n);
    }
}

/******************************
***����SumAndAverStu
***����ÿ��ѧ�����ܷ���ƽ����
******************************/
void SumAndAverStu(STU student[],STU cpystu[],int course,int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        (student[i].sum)=0;
        for(j=0; j<course; j++)
        {
            student[i].sum+=student[i].score[j];
        }
    }

    for(i=0; i<n; i++)
    {
        cpystu[i]=student[i];
    }
}

/********************************
***����SortByScore
***����ѧ�š��ɼ��������뺯��ָ��
***����i,j��������,k������¼��ֵ
***������ɼ������ѧ����ɼ�
********************************/
void SortByScore(STU student[],int n,int (*f)(STU *,int,int))
{
    int i,j,k;
    STU stu;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if((*f)(student,k,j))
                k=j;
        }
        stu=student[k];
        student[k]=student[i];
        student[i]=stu;
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,(student[i].number),(student[i].name),(student[i].sum));
    }
}

/***************
***����Ascend
***�����������1
***************/
int Ascend(STU student[],int k,int j)
{
    return (student[k].score)>(student[j].score);
}

/***************
***����Descend
***�����������1
***************/
int Descend(STU student[],int k,int j)
{
    return (student[k].score)<(student[j].score);
}

/****************************
***����SortByNumber
***����ѧ�š��ɼ�������
***����i,j��������,k������¼��ֵ
***�����ѧ�������ѧ����ɼ�
****************************/
void SortByNumber(STU student[],int n)
{
    int i,j,k;
    STU stu;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if((student[j].number)<(student[k].number))
                k=j;
        }
        stu=student[k];
        student[k]=student[i];
        student[i]=stu;
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,(student[i].number),(student[i].name),(student[i].sum));
    }
}

/*****************
***����SortByName
***����������
*****************/
void SortByName(STU student[],int n)
{
    int i,j,k;
    STU stu;
    printf("      Number     Name                Score\n");
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if(strcmp((student[k].name),(student[j].name))>=0)
            {
                k=j;
            }
        }
        stu=student[k];
        student[k]=student[i];
        student[i]=stu;
        printf("No.%-3d%-10ld %-20s%.1f\n",i+1,(student[i].number),(student[i].name),(student[i].sum));
    }
}

/*************************
***����Rank
***��ȡָ��ѧ�ŵ�����
***����r������¼����,k��������
*************************/
int Rank(float sco,STU student[],int n)
{
    int k,r=1;
    for(k=0; k<n; k++)
    {
        if((student[k].sum)>sco)
            r++;
    }
    return r;
}

/****************
***����Search
***����ѧ��num
***����i,j��������
***���������ɼ�
****************/
void Search(STU student[],int n,int course)
{
    int i,j;
    long num;
    printf("Please input the number:\n");
    scanf("%ld",&num);
    for(i=0; i<n; i++)
    {
        if((student[i].number)==num)
        {
            printf("Rank ");
            for(j=0; j<course; j++)
            {
                printf("Score[%-1d] ",j+1);
            }
            putchar('\n');

            printf("%-5d",Rank((student[i].sum),student,n));
            for(j=0; j<course; j++)
            {
                printf("%-9.1f",(student[i].score[j]));
            }
            putchar('\n');
            i++;
            break;
        }
    }
    if((student[i-1].number)!=num)
        printf("No result,please check the data.\n");
}

/******************
***����SearchByName
***����������
***����i,j��������,flag��������Ƿ��ҵ�����
*******************/
void SearchByName(STU student[],int n,int course)
{
    int i,j,flag=0;
    char nam[X];

    printf("Please input the name:\n");
    while(getchar()!='\n');
    fgets(nam,X,stdin);
    nam[strlen(nam)-1]='\0';

    for(i=0; i<n; i++)
    {
        if(strcmp(nam,(student[i].name))==0)
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

            printf("%-10ld %-3d  ",(student[i].number),Rank((student[i].sum),student,n));
            for(j=0; j<course; j++)
                printf("%-9.1f",(student[i].score[j]));
            putchar('\n');
            flag++;
        }
    }
    if(flag==0)
        printf("No result,please check the data.\n");
    printf("Press Enter to continue.\n");
}

/*****************************
***����Analysis
***ͳ�Ƹ�����������������
***����A,B,C,D,E����������������,i,j��������
*****************************/
void Analysis(STU student[],int n,int course)
{
    int i,j,A,B,C,D,E;
    printf("           90~100      80~90       70~80       60~70       0~60\n");
    for(j=0; j<course; j++)
    {
        A=B=C=D=E=0;
        for(i=0; i<n; i++)
        {
            if((student[i].score[j])<=100&&(student[i].score[j])>=90)
                A++;
            else if((student[i].score[j])<90&&(student[i].score[j])>=80)
                B++;
            else if((student[i].score[j])<80&&(student[i].score[j])>=70)
                C++;
            else if((student[i].score[j])<70&&(student[i].score[j])>=60)
                D++;
            else
                E++;
        }

        printf("Course[%-1d]||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%||%-3d%-6.2f%%\n",
               j+1,A,(float)A*100/n,B,(float)B*100/n,C,(float)C*100/n,D,(float)D*100/n,E,(float)E*100/n);
    }
}

/****************************
***����Output
***�������˳�����ѧ����ɼ�
***����i,j��������
****************************/
void Output(STU cpystu[],int n,int course)
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
        printf("%-10ld  %-20s  ",(cpystu[i].number),(cpystu[i].name));
        for(j=0; j<course; j++)
            printf("%-8.1f ",(cpystu[i].score[j]));
        printf("%.1f   %f\n",(cpystu[i].sum),(cpystu[i].sum)/course);
    }
}

/*************************************************************
***������main
***ѡ���Ӻ���
***����choice�����û���ѡ��,n����������,course�����γ���,i��������,flag��������û��Ƿ���������
***����number,score,name,sum����ѧ��,����,����,�����ܷ�,cpynum,cpysco,cpynam������������
*************************************************************/
int main()
{
    /*ѧ������Ŀ���*/
    printf("Number:200210522\nsubject No.8\n\n");
    /*�û��˵�*/
    STU student[N],cpystu[N];
    int choice,n,course,i,flag=0;
    int *pcourse=&course;
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
            n=Input(student,pcourse);
            SumAndAverStu(student,cpystu,course,n);
            break;
        case 2:
            SumAndAver(student,course,n);
            break;
        case 3:
            printf("Number    Name                Sum     Average\n");
            for(i=0; i<n; i++)
            {
                printf("%-10ld%-20s%-7.1f %f\n",(student[i].number),(student[i].name),(student[i].sum),(student[i].sum)/course);
            }
            break;
        case 4:
            SortByScore(student,n,Descend);
            break;
        case 5:
            SortByScore(student,n,Ascend);
            break;
        case 6:
            SortByNumber(student,n);
            break;
        case 7:
            SortByName(student,n);
            break;
        case 8:
            Search(student,n,course);
            break;
        case 9:
            SearchByName(student,n,course);
            break;
        case 10:
            Analysis(student,n,course);
            break;
        case 11:
            Output(cpystu,n,course);
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
