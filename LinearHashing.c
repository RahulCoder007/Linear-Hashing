#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#define capacity 5
#define set 15
#define file "demo.txt"


//dataset

struct Data{
 int id;
 int amt;
 char name[4];
 int cat;
};

int TotalFileCounter=0;

int hashm2(int key,int raiseToPower, int modPow){

    double index;
    int index1,var;

    index=pow(modPow,raiseToPower);
    var=modPow*(int)index;
    index1=key% var;
    return index1;
}

int readFile(int fileNo,int key){

FILE *fp;
 char fn[20];
 char fName[20];
 itoa(fileNo,fn,10);
 strcpy(fName,fn);
 int i=0;
 struct Data data[set];
 fp=fopen(strcat(fName,".txt"),"r");
   if(fp==NULL)
   {
       //printf("file not found");
       return 0;
   }
   else{
    while(fscanf(fp,"%d%d%s%d",&data[i].id,&data[i].amt,&data[i].name,&data[i].cat)!=EOF)
     {
         if(data[i].id==key){
                printf("Record %d Found at line# : %d",key,i+1);
                fclose(fp);
            return 1;
         }

         i++;
     }
   }

   fclose(fp);
   return 0;

}
void search()
{

 int key,index,i,flag=0,hkey;
 int modPow=2;
 int raiseToPower=0;
 int nextToSplit=0;
 int splitdecrement= modPow* ((int)(pow(modPow,raiseToPower)));
 int dataFound=0;
 printf("\nenter search record\n");
 scanf("%d",&key);
 int j;
 for(j=0;j<set;j++){
                // initial hashing mod 2  12%2
          index= hashm2(key,raiseToPower,modPow); // actual raise to power should be 0 always mod 2
           if(index<nextToSplit){
                index=hashm2(key,raiseToPower+1,modPow); //12%4

            }

            nextToSplit++; //bucket file //1
                splitdecrement--; //to check reset  1



                dataFound=readFile(index,key);
                if(dataFound==1)
                {
                  printf(" in %d.txt File\n",index);
                  break;
                }
                if(splitdecrement==0)
             {
                 nextToSplit=0;
                 raiseToPower++;
                 splitdecrement= modPow* ((int)(pow(modPow,raiseToPower)));
             }

     }

  if(j == set)
    printf("\n value is not found\n");

}

void generateData(){

struct Data data[set];
   //int id[set],amt[set],cat[set];
   char name[set][4];
   int i,j,k,min=1;

    srand(time(0));

     const char pool[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      int poolsize=sizeof(pool)-1;
      for (i=0;i<set;i++)
      {
        for(j=0;j<4;j++)
        {
           if(j<=2)
            name[i][j]=pool[(rand()%poolsize+0)]; // assign random chars
           else
            name[i][j]='\0';

        }
        strcpy(data[i].name,name[i]);
      }


    for(i=0;i<set;i++)
        data[i].id=i+min;
    for(i=0;i<set;i++)
        data[i].amt=rand()%80000+min;
    for(i=0;i<set;i++)
        data[i].cat=rand()%1500+min;

        FILE *fp;
        fp=fopen(file,"w+");
       for(i=0;i<set;i++){
        fprintf(fp,"%d\t%d\t%s\t%d\n",data[i].id,data[i].amt,data[i].name,data[i].cat);
       }
       printf("\nDataset successfully created\n");
        fclose(fp);
    }


int checkFile(int nextToSplit){
 FILE *fp;
 char fn[20];
 char fName[20];
 itoa(nextToSplit,fn,10);
 strcpy(fName,fn);
 fp=fopen(strcat(fName,".txt"),"r");
   if(fp!=NULL)
    {
     fclose(fp);
     return 1;

    }
    else
        fclose(fp);
     return 0;
}

void overflow(int index,struct Data data[],int ind){

        char f[20];
        itoa(index,f,10);
        FILE *f2write=fopen(strcat(f,"OF.txt"),"a+");
        fprintf(f2write,"%d\t%d\t%s\t%d\n",data[ind].id,data[ind].amt,data[ind].name,data[ind].cat);
        fclose(f2write);

}



int splitFile(int nextTosplit, int modPow, int c[], int sz , char arr[10], int raiseTopower){

    struct Data data[capacity];
    int i=0;
    int j;
    int index;
    char fn[20];
    char fName[20];
    itoa(nextTosplit,fn,10);
    strcpy(fName,fn);

     FILE *fp, *temp;

     fp=fopen(strcat(fName,".txt"),"r");
     char fname[20];
     char tempFile[20]="temp.txt";
while(fscanf(fp,"%d%d%s%d",&data[i].id,&data[i].amt,&data[i].name,&data[i].cat)!=EOF)
     {

         i++;
     }
     fclose(fp);
     raiseTopower++;

     int ct=0;
    for(j=0;j<i;j++){


        index=hashm2(data[j].id,raiseTopower,modPow);

         if(ct==0)
         {
            if(checkFile(index)==0) //file doesn't exist
            {
                ct++;
             itoa(index,fname,10);
                fp=fopen(strcat(fname,".txt"),"a+");//2.txt
                fprintf(fp,"%d\t%d\t%s\t%d\n",data[j].id,data[j].amt,data[j].name,data[j].cat);
                c[index]=c[index]+1;
                 c[nextTosplit]=c[nextTosplit] - 1;
                     fclose(fp);
            }else{

             temp=fopen("temp.txt","a+");
             fprintf(temp,"%d\t%d\t%s\t%d\n",data[j].id,data[j].amt,data[j].name,data[j].cat);
              fclose(temp);

            }


        }
        else if(ct>0 && nextTosplit!=index)
        {

         itoa(index,fname,10);
                fp=fopen(strcat(fname,".txt"),"a+");//2.txt
                fprintf(fp,"%d\t%d\t%s\t%d\n",data[j].id,data[j].amt,data[j].name,data[j].cat);
                c[index]=c[index]+1;
                 c[nextTosplit]=c[nextTosplit] - 1;
                    fclose(fp);
        }
        else{

             temp=fopen("temp.txt","a+");
             fprintf(temp,"%d\t%d\t%s\t%d\n",data[j].id,data[j].amt,data[j].name,data[j].cat);
             fclose(temp);

        }

    }


     strcpy(arr,tempFile);

    return nextTosplit;

}
int checkOverFlow(int nextToSplit){
 FILE *fp;
 char fn[20];
 char fName[20];
 itoa(nextToSplit,fn,10);
 strcpy(fName,fn);
 fp=fopen(strcat(fName,"OF.txt"),"r");
   if(fp!=NULL)
    {
     fclose(fp);
     return 1;

    }
    else
        fclose(fp);
     return 0;
}

void splitOverFlow(int nextTosplit, int modPow, int c[], int sz , char arr[10], int raiseTopower){

struct Data data[capacity];
    int i=0;
    int j;
    int index;
    char fn[20];
    char fName[20];
    itoa(nextTosplit,fn,10);
    strcpy(fName,fn);

     FILE *fp,*temp;

     fp=fopen(strcat(fName,"OF.txt"),"r");
     char fname[20];

     while(fscanf(fp,"%d%d%s%d",&data[i].id,&data[i].amt,&data[i].name,&data[i].cat)!=EOF)
     {

         i++;
     }
     fclose(fp);
    raiseTopower++;
    for(j=0;j<i;j++){

        index=hashm2(data[j].id,raiseTopower,modPow);

            if(checkFile(index)==1)
            {
             itoa(index,fname,10);
                fp=fopen(strcat(fname,".txt"),"a+");
                fprintf(fp,"%d\t%d\t%s\t%d\n",data[j].id,data[j].amt,data[j].name,data[j].cat);
                 printf(" Data %d is inserted in %s \n",data[j].id,fname);
                c[index]=c[index]+1;
                     fclose(fp);
            }
    }


     remove(fName);
    }

void writeToFile(int index,struct Data data[], int ind){

           FILE *fp;
           char fname[20];
           itoa(index,fname,10);
           fp=fopen(strcat(fname,".txt"),"a+");
           fprintf(fp,"%d\t%d\t%s\t%d\n",data[ind].id,data[ind].amt,data[ind].name,data[ind].cat);

           fclose(fp);
}


int main()
{
    generateData();

   //****** File to Read Data ***********
   FILE *fp;
   fp=fopen(file,"r"); // open demo1.txt
   if(fp==NULL)
   {
       printf("file not found");
       exit(1);
   }

    struct Data data[set];
    int i=0;
      //read data from file
    while(fscanf(fp,"%d%d%s%d",&data[i].id,&data[i].amt,&data[i].name,&data[i].cat)!=EOF)
     {
         i++;
     }
     fclose(fp); // close demo1.txt

//*****END OF READING DATA **********




       int j;
        int raiseToPower=0;
       int counter[set]={0};
       int modPow=2;
        int nextToSplit=0;
        int index;
        int splitdecrement= modPow* ((int)(pow(modPow,raiseToPower)));

       for(j=0;j<set;j++){
                // initial hashing mod 2
          index= hashm2(data[j].id,raiseToPower,modPow); // actual raise to power should be 0 always mod 2
           if(index<nextToSplit){
                index=hashm2(data[j].id,raiseToPower+1,modPow);
            }

          if(counter[index]<capacity){

             writeToFile(index,data,j);
              printf(" Data %d is inserted in %d.txt \n",data[j].id,index);
             counter[index]=counter[index]+1;
         }
         else{

               char tempfn[20];
                overflow(index,data,j);
                int ind=splitFile(nextToSplit,modPow,counter,set,tempfn,raiseToPower);
                 char a[20];
                 itoa(ind,a,10);

                 strcat(a,".txt");
                 remove(a);
                 rename(tempfn,a);
                  printf(" Data %d is inserted in %s \n",data[j].id,a);
                 if(checkOverFlow(nextToSplit))
                {
                    splitOverFlow(nextToSplit,modPow,counter,10,tempfn,raiseToPower);

                }

                nextToSplit++; //bucket file //2
                splitdecrement--; //to check reset 0

             }

              if(splitdecrement==0)
             {
                 nextToSplit=0;
                 raiseToPower++;
                 splitdecrement= modPow* ((int)(pow(modPow,raiseToPower)));
             }


     }
search();
return 0;
}
