
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define CAPACITY 1000       //  MAX Capacity of Hospital
#define RANDOM 163      // Used to assign Patient Number
#define NUM_Doc 6       // Number of doctors in hospital
typedef struct 
{
    char TotalCharge [15];
    char TotalDeposited [15];
    char TotalReturn [15];
    int check_return ;          // Variable which checks whether amount is to be returned or not
}charges;
typedef struct
{
    char name[20];
    int job;
    // job = 0  means treat only OPD Patients
    // job = 1 means treat only Emergency patients 
    // job = 2 means both OPD and Emergency Patients
}doctors;
// List Of All Doctors working in Otaku Hospital        
doctors arr[NUM_Doc] = {
                    {"ABC",0},
                    {"DEF",0},
                    {"GHI",1},
                    {"JKL",1},
                    {"MNO",2},
                    {"PQRS",2},
};
typedef struct 
{
    int PatientNumber;
    int age;
    char gender;
    char FirstName [20];
    char LastName [20];
    char PhoneNumber [10];
    char ResidentialCity [15];
    char Email [30];
    char Doctor [20];
    char Problem [30];
    int ServiceType;
    charges ch;
}patient;
patient p[CAPACITY];
int num = 0;            // Total Number of patients seeking treatment
int COUNT_OPD = 0 , COUNT_EMER = 0;
void add_record(int service)        // Required Function for Q1
{
    patient x;
    x.PatientNumber = RANDOM+num+1;
    printf("Enter patient Age\n");
    scanf("%d",&x.age);
    fflush(stdin);
    printf("Enter gender\n");
    scanf("%c",&x.gender);
    fflush(stdin);
    printf("Enter First Name of Patient\n");
    scanf("%s",x.FirstName);
    fflush(stdin);
    printf("Enter Last Name of Patient\n");
    scanf("%s",x.LastName);
    fflush(stdin);
    printf("Enter phone Number\n");
    scanf("%s",x.PhoneNumber);
    fflush(stdin);
    printf("Enter Address\n");
    scanf("%s",x.ResidentialCity);
    printf("Enter Email Address\n");
    scanf("%s",x.Email);
    fflush(stdin);
    printf("Enter your problem in short\n");
    scanf("%s",x.Problem);
    fflush(stdin);
    x.ServiceType = service;
    int pay = (x.PatientNumber)*100;   // Just a way to initialise total charge Does Not Happens in Real Life
    printf("Pay = %d\n",pay);
    sprintf(x.ch.TotalCharge,"%d",pay);
    printf("Total Charge = %s\n",x.ch.TotalCharge);
    printf("Enter Total Charges DEposited\n");
    scanf("%s",x.ch.TotalDeposited);
    fflush(stdin);
    int x1,x2;
    sscanf(x.ch.TotalCharge,"%d",&x1);
    sscanf(x.ch.TotalDeposited,"%d",&x2);
    if(x1 > x2)
    x.ch.check_return = 0;
    else
    x.ch.check_return = 1;
    sprintf(x.ch.TotalReturn,"%d",abs(x1-x2));
    if(service == 1)
    {
        if(x.PatientNumber % 4 == 0)
        strcpy(x.Doctor,"ABC");
        else if(x.PatientNumber % 4 == 1)
        strcpy(x.Doctor,"DEF");
        else if(x.PatientNumber % 4 == 2)
        strcpy(x.Doctor,"MNO");
        else
        strcpy(x.Doctor,"PQRS");
        p[num] = x;
        COUNT_OPD++;
        num++;
    }
    else
    {
        if(num != COUNT_EMER)
        {
            for(int i = num+1 ; i > COUNT_EMER ; i--)
            p[i]=p[i-1];
        }
        if(x.PatientNumber % 4 == 0)
        strcpy(x.Doctor,"GHI");
        else if(x.PatientNumber % 4 == 1)
        strcpy(x.Doctor,"JKL");
        else if(x.PatientNumber % 4 == 2)
        strcpy(x.Doctor,"MNO");
        else
        strcpy(x.Doctor,"PQRS");
        p[COUNT_EMER] = x;
        COUNT_EMER++;
        num++;
    }
    printf("Your record has been created successfully\n");
    printf("Patient NUmber %d\n",x.PatientNumber); 
}
void printDetails(int i,patient p[])        // Function for printing all details of patients
{
    printf("Patient Number %d\n",p[i].PatientNumber);
    printf("Name of the patient is %s %s\n",p[i].FirstName,p[i].LastName);
    printf("Age %d\n",p[i].age);
    if(p[i].gender == 'F')
    printf("Gender FeMale\n");
    else if(p[i].gender == 'M')
    printf("Gender Male\n");
    else
    printf("Gender Others\n");
    printf("City %s\n",p[i].ResidentialCity);
    printf("Phone Number %.10s\n",p[i].PhoneNumber);
    printf("Email Address %s\n",p[i].Email);
    printf("Disease %s\n",p[i].Problem);
    if(p[i].ServiceType == 0)
    printf("Emergency Patient\n");
    else
    printf("OPD Patient\n");
    printf("Looked after by Dr %s\n",p[i].Doctor);
    printf("Total Bill = %s\n",p[i].ch.TotalCharge);
    printf("Total Cash Deposited = %s\n",p[i].ch.TotalDeposited);
    int refund;
    sscanf(p[i].ch.TotalReturn,"%d",&refund);
    if(refund != 0)
    {
        if(p[i].ch.check_return == 0)
        printf("Pay your remaining amount of %s\n",p[i].ch.TotalReturn);
        else
        printf("Yours remaining amount of %s will be refunded soon\n",p[i].ch.TotalReturn);
    }
    printf("\n\n\n\n\n");
}
int search_by_number(int x)     // Required Function for Q2 
{
    if(num == 0)
    return -1;
    // Using Binary Search as Patient Numbers are in increasing order for both OPD and Emergency patient 
    int l = 0 , r = COUNT_EMER-1;
    while(l <= r)
    {
        int mid = (l+r)/2;
        // printf("mid = %d\n",p[mid].PatientNumber);
        if(p[mid].PatientNumber == x)
        return mid;
        else if(x > p[mid].PatientNumber)
        l = mid+1;
        else
        r = mid-1;
    }
    l = COUNT_EMER;
    r = num-1;
    while(l <= r)
    {
        int mid = (l+r)/2;
        // printf("mid = %d\n",p[mid].PatientNumber);
        if(p[mid].PatientNumber == x)
        return mid;
        else if(p[mid].PatientNumber < x)
        l = mid+1;
        else
        r = mid-1;
    }
    return -1;
}
int search_by_name(char first[],char last[])        // Required function for Q2
{
    if(num == 0)
    return -1;
    for(int i = 0 ; i < num ; i++)
    {
        if(strcmp(p[i].FirstName,first) == 0 && strcmp(p[i].LastName,last) == 0)
        return i;
    }
    return -1;
}
void edit_details(int i)                // Required function for Editing Info about Patient
{
        int y;                      
        printf("Press 1 to edit Age else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter new Age\n");
            scanf("%d",&p[i].age);
        }
        printf("Press 1 to Edit Full Name else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Name\n");
            scanf("%s %s",p[i].FirstName,p[i].LastName);
        }
        printf("Press 1 to edit Gender else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Gender\n");
            scanf("%c",&p[i].gender);
        }
        printf("Press 1 to edit Phone Number else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Phone Number\n");
            scanf("%s",&p[i].PhoneNumber);
        }
        printf("Press 1 to edit Residential City else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Residential City\n");
            scanf("%s",&p[i].ResidentialCity);
        }
        printf("Press 1 to edit Email Address else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Email ID\n");
            scanf("%s",&p[i].Email);
        }
        printf("Press 1 to edit Problem else 0\n");
        scanf("%d",&y);
        if(y == 1)
        {
            fflush(stdin);
            printf("Enter New Problem\n");
            scanf("%s",&p[i].Problem);
        }
        printf("New Details of Patient No %d are\n\n",p[i].PatientNumber);
        printDetails(i,p);
}
void edit_by_number(int x)          // Required function for Q3
{
    int i = search_by_number(x);
    if(i == -1)
    printf("No such records found\n");
    else
    {
        printDetails(i,p);
        edit_details(i);
    }
}
void edit_by_name(char first[],char last[])         // Required function for Q3
{
    int i = search_by_name(first,last);
    if(i == -1)
    printf("No such records found\n");
    else
    {
        printDetails(i,p);
        edit_details(i);
    }
}
void merge_func(patient A[], int low, int mid, int high)       // Merge Func for merge_sort 
{
 int i = low;
 int j = mid+1;
 int k = low;
 patient B[num];
 while (i<= mid && j <= high)
 {
    if(strcmp(A[i].FirstName,A[j].FirstName) > 0)
    {
        B[k]=A[j];
        j++;
        k++;
    }
    else if(strcmp(A[i].FirstName,A[j].FirstName) < 0)
    {
        B[k]=A[i];
        i++;
        k++;
    }
    else
    {
        if(strcmp(A[i].LastName,A[j].LastName) > 0)
        {
            B[k]=A[j];
            j++;
            k++;
        }
        else
        {
            B[k]=A[i];
            i++;
            k++;
        }
    }
 }
    while (i<=mid)
    {
        B[k]=A[i];
        i++;
        k++;
   }
    while (j<=high)
    {
        B[k]=A[j];
        j++;
        k++;
    }
    for (int i = 0; i <= high; i++)
    {
        A[i]=B[i];
    }
}
void merge_sort(patient arr[],int l,int r)      // // Required function for Q4 part a
{
    int mid = (l+r)/2;
    if(l<r)
    {
        merge_sort(arr,l,mid);
        merge_sort(arr,mid+1,r);
        merge_func(arr,l,mid,r);
    }
}
void delete_record(int x)               // Required function for Q5//
{
    int pos = search_by_number(x);
    if(pos == -1)
    printf("No such records found\n");
    else
    {
        printDetails(pos,p);
        printf("Above mentoned recod has been deleted\n");
        for(int i = pos ; i < num-1 ; i++)
        p[i]=p[i+1];
        num --;
    }
}
void outside_patients()         // Required function for Q6
{
    for(int i = 0 ; i < num ; i++)
    {
        if(strcmp(p[i].ResidentialCity,"Nagpur"))
        printDetails(i,p);
    }
}       
void print_maximum()    // Required function for Q7
{
    int MAX = -1,x;
    for(int i = 0 ; i < num; i++)
    {
        sscanf(p[i].ch.TotalCharge,"%d",&x);
        if(x > MAX)
        MAX = x;
    }
    for(int i = 0 ; i < num ; i++)
    {
        sscanf(p[i].ch.TotalCharge,"%d",&x);
        if(x == MAX)
        printDetails(i,p);
    }
}       
void print_minimum()            // Required function for Q7
{
    int x , MIN ;
    sscanf(p[0].ch.TotalCharge,"d",&MIN);
    for(int i = 1 ; i < num; i++)
    {
        sscanf(p[i].ch.TotalCharge,"%d",&x);
        if(x < MIN)
        MIN= x;
    }
    for(int i = 0 ; i < num ; i++)
    {
        sscanf(p[i].ch.TotalCharge,"%d",&x);
        if(x == MIN)
        printDetails(i,p);
    }
}
void age_grp(int Min,int Max)
{
    for(int i = 0 ; i < COUNT_EMER ; i++)
    if(p[i].age >= Min && p[i].age <= Max)
    printDetails(i,p);
}
void search_doctor(char Name[])     //Required Function for Q10
{
    int status = 0;
    for(int i = 0 ; i < NUM_Doc && status == 0; i++)
    {
        if(strcmp(Name,arr[i].name) == 0)
        status = 1;
    }
    if(status == 0)
    printf("No such doctor found\n");
    else
    {
        int count = 0;
        for(int i = 0 ; i < num ; i++)
        if(strcmp(p[i].Doctor,Name) == 0)
        count++;
        if(count == 0)
        printf("Currently Dr %s is on a leave\n",Name);
        else{
        printf("Names of Patients looked after by Dr %s are\n",Name);
        for(int i = 0 ; i < num ; i++)
        if(strcmp(p[i].Doctor,Name) == 0)
        printf("%s %s\n",p[i].FirstName,p[i].LastName);
        }
    }
}
void view_doctors(int x)        // Required Function for Q11
{
    if(x == 1)
    {
        printf("Doctors treating only OPD Patients are\n");
        for(int i = 0 ; i < 2 ; i++)
        printf("%s\n",arr[i].name);
    }
    else if(x == 2)
    {
        printf("Doctors treating only Emergency Patients are\n");
        for(int i = 2 ; i < 4 ; i++)
        printf("%s\n",arr[i].name);
    }
    else if(x == 3)
    {
        printf("Doctors treating both OPD and Emergency patients are\n");
        for(int i = 4 ; i < 6 ; i++)
        printf("%s\n",arr[i].name);
    }
}
void view_refund()          // Required Function for Q8
{
    for(int i = 0 ; i < num ; i++)
    {
        int ref;
        sscanf(p[i].ch.TotalReturn,"%d",&ref);
        if(ref != 0 && p[i].ch.check_return == 1)
        printf("%s %s Refund Amount %s\n",p[i].FirstName,p[i].LastName,p[i].ch.TotalReturn);
    }
}
int main()
{
    int service;
    char first[10],last[10];
    int x;
    printf("WELCOME TO OTAKU HOSPITAL\n");
    int choice;
   // Q1)         Add Record 
   do
    {
    printf("Press 1 to add record\n");
    printf("Press 2 to search record\n");
    printf("Press 3 to edit record\n");
    printf("Press 4 to view list of record\n");
    printf("Press 5 to delete record\n");
    printf("Press 6 to view list of outsider patients\n");
    printf("Press 7 to view of highest and lowest charges record\n");
    printf("Press 8 to view list of refund patients\n");
    printf("Press 9 to agewise search of patients in Emergency Ward\n");
    printf("Press 10 to view list of patients treated by a particular doctor\n");
    printf("Press 11 to view List Of Doctors\n");
    printf("Press -1 To Exit\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        printf("Enter 0 for Emergency 1 for OPD\n");
        scanf("%d",&service);
        add_record(service);
    }
    else if(choice == 2)
    {
    printf("Press 1 to search by name\n2 to search by Patient Number\n");
    scanf("%d",&service);
    if(service == 1)
    {
        printf("Enter full Name of Patient\n");
        scanf("%s %s",first,last);
        int i = search_by_name(first,last);
        if(i == -1)
        printf("No such records found\n");
        else
        printDetails(i,p);
    }
    else if(service == 2)
    {
        printf("Enter Patient Number\n");
        scanf("%d",&x);
        int i = search_by_number(x);
        if(i == -1)
        printf("No such records found\n");
        else
        printDetails(i,p);
    }
    }
    else if(choice == 3)
    {
    printf("Enter 1 to Edit Record By Number\n2 to Edit REcord Record by Full Name\n");
    scanf("%d",&service);
    if(service == 1)
    {
        printf("Enter Patient Number\n");
        scanf("%d",&x);
        edit_by_number(x);
    }
    else if(service == 2)
    {
        printf("Enter Full Name\n");
        scanf("%s %s",first,last);
        edit_by_name(first,last);
    }
    }
    else if(choice == 4)
    {
        printf("Enter 1 for alphabetcal list\nEnter 2 for OPD List\nEnter 3 for Emergency List\n");
    scanf("%d",&service);
    if(service == 3)
    {
        for(int i = 0 ; i < COUNT_EMER ; i++)
        printDetails(i,p);
    }
    else if(service == 2)
    {
        for(int i = COUNT_EMER ; i < num ; i++)
        printDetails(i,p);
    }
    else
    {
        patient temp[CAPACITY];
        for(int i = 0 ; i < num ; i++)
        temp[i] = p[i];
        merge_sort(temp,0,num-1);
        for(int i = 0 ; i < num ; i++)
        printDetails(i,temp);
    }
    }
    else if(choice == 5)
    {
        printf("Enter Patient Number of record to be deleted\n");
        scanf("%d",&x);
        delete_record(x);
    }
    else if(choice == 6)
    outside_patients();
    else if(choice == 7)
    {printf("press 1 to see maximum charge of treatment records\n");
    printf("press 2 to see minimum charge of treatment records\n");
    scanf("%d",&service);
    if(service == 1)
    print_maximum();
    else if(service == 2)
    print_minimum();
    }
    else if(choice == 8)
    view_refund();
    else if(choice == 9)
    {
    printf("Enter 1 for 25 to 40 Age Group \n2 For 40 + Age Group\n");
    scanf("%d",&service);
    if(service == 1)
    age_grp(25,40);
    else if(service == 2)
    age_grp(41,200);
    }
    else if(choice == 10)
    {
    char Name [10];
    printf("Enter Doctors Name\n");
    scanf("%s",Name);
    search_doctor(Name);
    }
    else if(choice == 11)
    {
    printf("Enter 1 to View only OPD Doctors\n2 for Only Emergency Doctors\n3 for Both\n");
    scanf("%d",&service);
    view_doctors(service);
    }
   
    }while(choice != -1);
   
}