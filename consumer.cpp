#include <iostream>
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>
using namespace std;
#define  PATH "/home/adhamelkazzaz59/Desktop/6713-7252-lab5/semkeys"
#define SHM_KEY 0x1234

typedef struct {
    char name[10];
    double price;
    double avg;
    int pricestat;
    int avgstat;
} commodity;

commodity prices[11][5];

int lasti(int i){
    if(i >0)
        return i-1;
    else
        return 4;
}
double avg(commodity arr[11][5],int x){
    double sum = 0;

    for(int i = 0; i < 5; i++)
    {
        sum = sum + arr[x][i].price;
    }
    return sum/5;
}
int al = 0, cop = 0, cot = 0, cru = 0, g = 0, l = 0, men = 0, na = 0, ni = 0, s = 0, z = 0;
double old_avg = 0, new_avg = 0;
enum comms {
    ALUMINIUM,
    COPPER,
    COTTON,
    CRUDEOIL,
    GOLD,
    LEAD,
    MENTHAOIL,
    NATURALGAS,
    NICKEL,
    SILVER,
    ZINC
};

void print_current(commodity arr[11][5], int i, int j)  {
    if(arr[i][j].pricestat == 0) {
        printf("\033[;36m %-7.2lf\033[0m", arr[i][j].price);
    }
    else if(arr[i][j].pricestat == 1) {
        printf("\033[;32m %-7.2lf↑\033[0m", arr[i][j].price);
    }
    else {
        printf("\033[;31m %-7.2lf↓\033[0m", arr[i][j].price);
    }
}

void print_avg(commodity arr[11][5], int i, int j)  {
    if(arr[i][j].avgstat == 0) {
        printf("\033[;36m %-7.2lf\033[0m", arr[i][j].avg);
    }
    else if(arr[i][j].pricestat == 1) {
        printf("\033[;32m %-7.2lf↑\033[0m", arr[i][j].avg);
    }
    else {
        printf("\033[;31m %-7.2lf↓\033[0m", arr[i][j].avg);
    }
}

void display(commodity arr[11][5],int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k){
    printf("\e[1;1H\e[2J");
    printf("+-------------------------------------+\n");
    printf("| Currency      |  Price   | AvgPrice |\n");
    printf("+-------------------------------------+\n");
    printf("| ALUMINIUM \033[4;17H|"); print_current(arr,0,a); printf("\033[4;28H|"); print_avg(arr, 0, a); printf("\033[4;39H|\n");
    printf("| COPPER \033[5;17H|"); print_current(arr,1,b); printf("\033[5;28H|"); print_avg(arr, 1, b); printf("\033[5;39H|\n");
    printf("| COTTON \033[6;17H|"); print_current(arr,2,c); printf("\033[6;28H|"); print_avg(arr, 2, c); printf("\033[6;39H|\n");
    printf("| CRUDEOIL \033[7;17H|"); print_current(arr,3,d); printf("\033[7;28H|"); print_avg(arr, 3, d); printf("\033[7;39H|\n");
    printf("| GOLD \033[8;17H|"); print_current(arr,4,e); printf("\033[8;28H|"); print_avg(arr, 4, e); printf("\033[8;39H|\n");
    printf("| LEAD \033[9;17H|"); print_current(arr,5,f); printf("\033[9;28H|"); print_avg(arr, 5, f); printf("\033[9;39H|\n");
    printf("| MENTHAOIL\033[10;17H|"); print_current(arr,6,g); printf("\033[10;28H|"); print_avg(arr, 6, g); printf("\033[10;39H|\n");
    printf("| NATURALGAS \033[11;17H|"); print_current(arr,7,h); printf("\033[11;28H|"); print_avg(arr, 7, h); printf("\033[11;39H|\n");
    printf("| NICKEL \033[12;17H|"); print_current(arr,8,i); printf("\033[12;28H|"); print_avg(arr, 8, i); printf("\033[12;39H|\n");
    printf("| SILVER \033[13;17H|"); print_current(arr,9,j); printf("\033[13;28H|"); print_avg(arr, 9, j); printf("\033[13;39H|\n");
    printf("| ZINC \033[14;17H|"); print_current(arr,10,k); printf("\033[14;28H|"); print_avg(arr, 10, k); printf("\033[14;39H|\n");
    printf("+-------------------------------------+\n");
}

void update(commodity x){
if (strcasecmp(x.name,"ALUMINIUM")==0)
    {
         old_avg = avg(prices,ALUMINIUM);
        prices[ALUMINIUM][al%5].price=x.price;
        new_avg = avg(prices,ALUMINIUM);
        prices[ALUMINIUM][al%5].avg = new_avg;
        if(x.price < prices[ALUMINIUM][lasti(al%5)].price){
            prices[ALUMINIUM][al%5].pricestat= -1;
        }
        else if(x.price > prices[ALUMINIUM][lasti(al%5)].price){
            prices[ALUMINIUM][al%5].pricestat= 1;
        }
        else{
            prices[ALUMINIUM][al%5].pricestat= 0;
        }
        if(new_avg<old_avg){
            prices[ALUMINIUM][al%5].avgstat= -1;
        }
        else if(new_avg>old_avg){
            prices[ALUMINIUM][al%5].avgstat= 1;
        }
        else{
            prices[ALUMINIUM][al%5].avgstat=0;
        }
        al++;
        display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
    }
else if(strcasecmp(x.name,"COPPER")==0){
    old_avg = avg(prices,COPPER);
    prices[COPPER][cop%5].price=x.price;
    new_avg = avg(prices,COPPER);
    prices[COPPER][cop%5].avg = new_avg;
    if(x.price < prices[COPPER][lasti(cop%5)].price){
        prices[COPPER][cop%5].pricestat= -1;
    }
    else if(x.price > prices[COPPER][lasti(cop%5)].price){
        prices[COPPER][cop%5].pricestat= 1;
    }
    else{
        prices[COPPER][cop%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[COPPER][cop%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[COPPER][cop%5].avgstat= 1;
    }
    else{
        prices[COPPER][cop%5].avgstat=0;
    }
    cop++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
    }
else if(strcasecmp(x.name,"COTTON")==0){
    old_avg = avg(prices,COTTON);
    prices[COTTON][cot%5].price=x.price;
    new_avg = avg(prices,COTTON);
    prices[COTTON][cot%5].avg = new_avg;
    if(x.price < prices[COTTON][lasti(cot%5)].price){
        prices[COTTON][cot%5].pricestat= -1;
    }
    else if(x.price > prices[COTTON][lasti(cot%5)].price){
        prices[COTTON][cot%5].pricestat= 1;
    }
    else{
        prices[COTTON][cot%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[COTTON][cot%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[COTTON][cot%5].avgstat= 1;
    }
    else{
        prices[COTTON][cot%5].avgstat=0;
    }
    cot++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"CRUDEOIL")==0){
    old_avg = avg(prices,CRUDEOIL);
    prices[CRUDEOIL][cru%5].price=x.price;
    new_avg = avg(prices,CRUDEOIL);
    prices[CRUDEOIL][cru%5].avg = new_avg;
    if(x.price < prices[CRUDEOIL][lasti(cru%5)].price){
        prices[CRUDEOIL][cru%5].pricestat= -1;
    }
    else if(x.price > prices[CRUDEOIL][lasti(cru%5)].price){
        prices[CRUDEOIL][cru%5].pricestat= 1;
    }
    else{
        prices[CRUDEOIL][cru%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[CRUDEOIL][cru%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[CRUDEOIL][cru%5].avgstat= 1;
    }
    else{
        prices[CRUDEOIL][cru%5].avgstat=0;
    }
    cru++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"GOLD")==0){
    old_avg = avg(prices,GOLD);
    prices[GOLD][g%5].price=x.price;
    new_avg = avg(prices,GOLD);
    prices[GOLD][g%5].avg = new_avg;
    if(x.price < prices[GOLD][lasti(g%5)].price){
        prices[GOLD][g%5].pricestat= -1;
    }
    else if(x.price > prices[GOLD][lasti(g%5)].price){
        prices[GOLD][g%5].pricestat= 1;
    }
    else{
        prices[GOLD][g%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[GOLD][g%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[GOLD][g%5].avgstat= 1;
    }
    else{
        prices[GOLD][g%5].avgstat=0;
    }
    g++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"LEAD")==0){
    old_avg = avg(prices,LEAD);
    prices[LEAD][l%5].price=x.price;
    new_avg = avg(prices,LEAD);
    prices[LEAD][l%5].avg = new_avg;
    if(x.price < prices[LEAD][lasti(l%5)].price){
        prices[LEAD][l%5].pricestat= -1;
    }
    else if(x.price > prices[LEAD][lasti(l%5)].price){
        prices[LEAD][l%5].pricestat= 1;
    }
    else{
        prices[LEAD][l%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[LEAD][l%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[LEAD][l%5].avgstat= 1;
    }
    else{
        prices[LEAD][l%5].avgstat=0;
    }
    l++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));

}
else if(strcasecmp(x.name,"MENTHAOIL")==0){
    old_avg = avg(prices,MENTHAOIL);
    prices[MENTHAOIL][men%5].price=x.price;
    new_avg = avg(prices,MENTHAOIL);
    prices[MENTHAOIL][men%5].avg = new_avg;
    if(x.price < prices[MENTHAOIL][lasti(men%5)].price){
        prices[MENTHAOIL][men%5].pricestat= -1;
    }
    else if(x.price > prices[MENTHAOIL][lasti(men%5)].price){
        prices[MENTHAOIL][men%5].pricestat= 1;
    }
    else{
        prices[MENTHAOIL][men%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[MENTHAOIL][men%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[MENTHAOIL][men%5].avgstat= 1;
    }
    else{
        prices[MENTHAOIL][men%5].avgstat=0;
    }
    men++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"NATURALGAS")==0){
    old_avg = avg(prices,NATURALGAS);
    prices[NATURALGAS][na%5].price=x.price;
    new_avg = avg(prices,NATURALGAS);
    prices[NATURALGAS][na%5].avg = new_avg;
    if(x.price < prices[NATURALGAS][lasti(na%5)].price){
        prices[NATURALGAS][na%5].pricestat= -1;
    }
    else if(x.price > prices[NATURALGAS][lasti(na%5)].price){
        prices[NATURALGAS][na%5].pricestat= 1;
    }
    else{
        prices[NATURALGAS][na%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[NATURALGAS][na%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[NATURALGAS][na%5].avgstat= 1;
    }
    else{
        prices[NATURALGAS][na%5].avgstat=0;
    }
    na++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"NICKEL")==0){
    old_avg = avg(prices,NICKEL);
    prices[NICKEL][ni%5].price=x.price;
    new_avg = avg(prices,NICKEL);
    prices[NICKEL][ni%5].avg = new_avg;
    if(x.price < prices[NICKEL][lasti(ni%5)].price){
        prices[NICKEL][ni%5].pricestat= -1;
    }
    else if(x.price > prices[NICKEL][lasti(ni%5)].price){
        prices[NICKEL][ni%5].pricestat= 1;
    }
    else{
        prices[NICKEL][ni%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[NICKEL][ni%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[NICKEL][ni%5].avgstat= 1;
    }
    else{
        prices[NICKEL][ni%5].avgstat=0;
    }
    ni++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"SILVER")==0){
    old_avg = avg(prices,SILVER);
    prices[SILVER][s%5].price=x.price;
    new_avg = avg(prices,SILVER);
    prices[SILVER][s%5].avg = new_avg;
    if(x.price < prices[SILVER][lasti(s%5)].price){
        prices[SILVER][s%5].pricestat= -1;
    }
    else if(x.price > prices[SILVER][lasti(s%5)].price){
        prices[SILVER][s%5].pricestat= 1;
    }
    else{
        prices[SILVER][s%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[SILVER][s%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[SILVER][s%5].avgstat= 1;
    }
    else{
        prices[SILVER][s%5].avgstat=0;
    }
    s++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}
else if(strcasecmp(x.name,"ZINC")==0){
    old_avg = avg(prices,ZINC);
    prices[ZINC][z%5].price=x.price;
    new_avg = avg(prices,ZINC);
    prices[ZINC][z%5].avg = new_avg;
    if(x.price < prices[ZINC][lasti(z%5)].price){
        prices[ZINC][z%5].pricestat= -1;
    }
    else if(x.price > prices[ZINC][lasti(z%5)].price){
        prices[ZINC][z%5].pricestat= 1;
    }
    else{
        prices[ZINC][z%5].pricestat= 0;
    }
    if(new_avg<old_avg){
        prices[ZINC][z%5].avgstat= -1;
    }
    else if(new_avg>old_avg){
        prices[ZINC][z%5].avgstat= 1;
    }
    else{
        prices[ZINC][z%5].avgstat=0;
    }
    z++;
    display(prices,lasti(al%5),lasti(cop%5),lasti(cot%5),lasti(cru%5),lasti(g%5),lasti(l%5),lasti(men%5),lasti(na%5),lasti(ni%5),lasti(s%5),lasti(z%5));
}


}


union semun
{
    int val;
    struct semid_ds *buf;
    ushort array [1];//*array!!
};

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
// ftok to generate unique key
    //key_t shmkey = ftok("/home/rafa/Desktop/lab5/etc ",65);
    //cout <<shmkey<<endl;
// shmget returns an identifier in shmid
    int shmid = shmget(SHM_KEY, N*sizeof(commodity) ,0666|IPC_CREAT);
    cout <<"shmkey: "<<SHM_KEY<<endl;
    //cout <<"shmid: "<<shmid<<endl;

    commodity *buffer = (commodity*) shmat(shmid,(void*)0,0);



    int shvarkey = shmget(0x1230,sizeof(int),0666|IPC_CREAT);
    cout<<"shvarkey: "<<shvarkey<<endl;
    int *ip = (int*) shmat(shvarkey,(void*)0,0);
    ip[0]=0;



    key_t key;
    int semid;


    union semun args;
    union semun argn;
    union semun arge;




    if ((key = ftok (PATH, 'x')) == -1) {
        perror ("ftok"); exit (1);
    }
    if ((semid = semget (key, 3, 0666| IPC_CREAT)) == -1) {
        perror ("semget"); exit (1);
    }
    cout<<"semid: "<<semid<<endl;
    // Giving initial value.
    args.val = 1; //s       // unlocked
    if (semctl (semid, 0, SETVAL, args) == -1) {
        perror ("semctl SETVAL"); exit (1);
    }
    argn.val = 0;//n
    if (semctl (semid, 1, SETVAL, argn) == -1) {
        perror ("semctl SETVAL"); exit (1);
    }
    arge.val = N;//e
    if (semctl (semid, 2, SETVAL, arge) == -1) {
        perror ("semctl SETVAL"); exit (1);
    }

    struct sembuf sbs = {0, 0, 0};
    struct sembuf sbn = {1, 0, 0};
    struct sembuf sbe = {2, 0, 0};
    int i=0;



        while (true) {

            sbn.sem_op = -1;
            if (semop(semid, &sbn, 1) == -1) {
                perror("semop: wait n");
                exit(1);
            }


            sbs.sem_op = -1;
            if (semop(semid, &sbs, 1) == -1) {
                perror("semop: mutex wait");
                exit(1);
            }

            // Critical section
            update(buffer[i%N]);
            //printf("Consumption #%d at pos %d:\n",i, i%N);
            //cout << "Commodity name: "<<buffer[i%N].name<<" price: "<<buffer[i%N].price<<endl;
            i++;

            //cout<<"WE ARE IN C.CRITICAL SECTION!!!"<<endl;
            //cout<<"the value of sem s must be 0 and we have it as: "<<semctl (semid, 0, GETVAL)<<endl;
            //cout<<"the value of sem n must be greater than 0 and we have it as: "<<semctl (semid, 1, GETVAL)<<endl;
            //cout<<"the value of sem e must be less than 20 we have it as: "<<semctl (semid, 2, GETVAL)<<endl;
            //cout<<"WE ARE outtt!!!"<<endl;

            sbs.sem_op = 1;
            if (semop(semid, &sbs, 1) == -1) {
                perror("semop: mutex signal");
                exit(1);
            }
            //cout<<"the value of sem s must be 1 and we have it as: "<<semctl (semid, 0, GETVAL)<<endl;
            sbe.sem_op = 1;
            if (semop(semid, &sbe, 1) == -1) {
                perror("semop: e signal");
                exit(1);
            }
            //sleep(2);

        }
    if (semctl (semid, 0, IPC_RMID) == -1) {
        perror ("semctl IPC_RMID"); exit (1);
    }
    if (semctl (semid, 1, IPC_RMID) == -1) {
        perror ("semctl IPC_RMID"); exit (1);
    }
    if (semctl (semid, 2, IPC_RMID) == -1) {
        perror ("semctl IPC_RMID"); exit (1);
    }
    shmdt(buffer);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
