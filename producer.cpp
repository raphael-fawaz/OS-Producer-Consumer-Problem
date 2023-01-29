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
#include <random>
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

union semun
{
    int val;
    struct semid_ds *buf;
    ushort array [1];//*array!!
};

void formatted_time() {
    struct timespec spec;
    time_t now = time(NULL);
    struct tm s_now;
    localtime_r(&now, &s_now);
    clock_gettime(CLOCK_REALTIME, & spec);
    char timestamp[100];
    strftime(timestamp, 100, "%m/%d/%Y %H:%M:%S.", &s_now);
    std::cerr <<"["<<timestamp;
    fprintf(stderr,"%ld] ", (spec.tv_nsec));
}


int main(int argc, char* argv[])
{
    //read command line arguments
    string str_cname = argv[1];
    int str_cname_length = str_cname.length();
    char char_cname[str_cname_length +1];
    strcpy(char_cname,str_cname.c_str());
    double mean = stod(argv[2]);
    double stdev = stod(argv[3]);
    int sleep_interval = atoi(argv[4]);
    int N = atoi(argv[5]);
    //cout<<char_cname<<endl;
    //cout<<mean<<endl;
    //cout<<stdev<<endl;
    //cout<<sleep_interval<<endl;
    //cout<<N<<endl;

    //random number generation using normal distribution
    default_random_engine generator;
    normal_distribution<double> distribution(mean,stdev);
    double number;
    

    // shmget returns an identifier in shmid
    int shmid = shmget(SHM_KEY,N* sizeof(commodity),0666|IPC_CREAT);
    cout <<"shmkey: "<<SHM_KEY<<endl;
    cout <<"shmid: "<<shmid<<endl;


//shared variable

int shvarkey = shmget(0x1230,sizeof(int),0666|IPC_CREAT);
cout<<"shvarkey: "<<shvarkey<<endl;
int *i = (int*) shmat(shvarkey,(void*)0,0);





    key_t key;
    int semid;


    union semun args;
    union semun argn;
    union semun arge;



    if ((key = ftok (PATH, 'x')) == -1) {
        perror ("ftok"); exit (1);
    }
    if ((semid = semget (key, 3, 0666)) == -1) {//no ipc create
        perror ("semget"); exit (1);
    }
    cout <<"semid: "<<semid<<endl;

    struct sembuf sbs = {0, 0, 0};
    struct sembuf sbn = {1, 0, 0};
    struct sembuf sbe = {2, 0, 0};
    commodity *buffer = (commodity*) shmat(shmid,(void*)0,0);


        while (true) {

            number = distribution(generator);
            formatted_time();
            std::cerr<<char_cname<<": generating a new value "<<number<<endl;
            sbe.sem_op = -1;
            if (semop(semid, &sbe, 1) == -1) {
                perror("semop: e");
                exit(1);
            }
            formatted_time();
            std::cerr<<char_cname<<": trying to get mutex on shared buffer"<<endl;
            sbs.sem_op = -1;
            if (semop(semid, &sbs, 1) == -1) {
                perror("semop: s");
                exit(1);
            }

            // Critical section
            strcpy(buffer[i[0] % N].name,char_cname);
            buffer[i[0] % N].price = number;
            formatted_time();
            std::cerr<<char_cname<<": placing "<<number<<" on shared buffer"<<endl;
            //printf("Production no. %d in position %d\n",i[0],i[0]%N);
            //cout << "Commodity name: "<<buffer[i[0]%N].name<<" price: "<<buffer[i[0]%N].price<<endl;
            i[0]+=1;
            //cout<<"WE ARE IN P.CRITICAL SECTION!!!"<<endl;
            //cout<<"the value of sem s must be 0 and we have it as: "<<semctl (semid, 0, GETVAL)<<endl;
            //cout<<"the value of sem n must be less than 20 and we have it as: "<<semctl (semid, 1, GETVAL)<<endl;
            //cout<<"the value of sem e must be greater than 0 we have it as: "<<semctl (semid, 2, GETVAL)<<endl;
            //cout<<"WE ARE outtt!!!"<<endl;
            sbs.sem_op = 1;
            if (semop(semid, &sbs, 1) == -1) {
                perror("semop: s");
                exit(1);
            }
            //cout<<"the value of sem s must be 1 and we have it as: "<<semctl (semid, 0, GETVAL)<<endl;


            sbn.sem_op = 1;
            if (semop(semid, &sbn, 1) == -1) {
                perror("semop: n");
                exit(1);
            }

            // Take a nap
            float nap;
            nap=sleep_interval/(float)1000;
            //cout<<nap<<endl;
            sleep(nap);
            formatted_time();
            std::cerr<<char_cname<<": sleeping for "<<sleep_interval<<" ms"<<endl;

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
