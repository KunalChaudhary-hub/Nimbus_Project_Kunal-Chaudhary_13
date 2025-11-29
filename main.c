#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct{
    int slotNumber;
    char patientName[64];
}Appointment;

typedef struct{
    int id;
    char name[64];
    char field[64]; 
    int capacity;
    Appointment *schedule;
    int bookedCount;
}Doctor;

Doctor *docList = Null;
int docCount = 0;

void addDoctor(int id,const char *name,const char*field,int slots){
    docList = realloc(docList,sizeof(Doctor)*(docCount + 1));
    Doctor *d = &docList[docCount];

    d->id = id;
    strcpy(d->name,name);
    strcpy(d->field,field);
    d->capacity = slots;
    d->bookedCount = 0;
    d->schedule = malloc(sizeof(Appointment)*slots);
    for(int i=0;i<slots;i++){
        d->schedule[i].slotNumber = i+1;
        strcpy(d->schedule[i].patientName,"");
    }
    docCount++;
}
void listDoctors(){
    printf("\n------Doctor Directory------\n");
    for(int i=0;i<docCount;i++){
        printf("%d) %s [%s] Slots:%d\n",
                docList[i].id,docList[i].name,
                docList[i].field, docList[i].capacity);
    }
}

Doctor* findDoctor(int id) {
    for(int i=0;i<docCount;i++)
        if(docList[i].id==id) return &docList[i];
        return NULL;
}

void bookSlot(){
    listDoctors();
    int did,slot;
    char pname[64];

    printf("\nSelect Doctor id: ");
    scanf("%d",&did);
    getchar();

    Doctor *d = findDoctor(did);
    if(!d){
        printf("Invalid doctor. \n");
        return;
    }
    printf("\n-----SLOTS-----\n");
    for(int i=0;i<d->capacity;i++){
        printf("Slot %d : %s\n",d->schedule[i].slotNumber,
                strlen(d->schedule[i].patientName)==0 ? "Available"
                                                       : d->schedule[i].patientName);                                                       
    }
    printf("Choose slot: ");
    scanf("%d",&slot);
    getchar();

    if(slot<1 || slot>d->capacity){
        printf("Invalid slot\n");
        return;
    }
    if(strlen(d->schedule[slot-1].patientName)!=0){
        printf("Slot already taken\n");
        return;
    }

    printf("Enter the patient's name: ");
    fgets(pname,64,stdin);
    pname[strcspn(pname,"\n")]=0;

    strcpy(d->schedule[slot-1].patientName,pname);
    d->bookedCount++;

    printf("Appointment booked:\n");
}
void cancelSlot(){
    listDoctors();
    int did,slot;

    printf("\nDoctor id: ");
    scanf("%d",&did);
    getchar();

    Doctor *d = findDoctor(did);
    if(!d){
        printf("Invalid doctor\n");
        return;
    }
    printf("Slot to cancel: ");
    scanf("%d",&slot);
    getchar();

    if(slot<1 || slot>d->capacity){
        printf("Invalid slot\n");
        return;
    }
    
    if(strlen(d->schedule[slot-1].patientName)==0){
        printf("Slot already emppty");
        return;
    }

    strcpy(d->schedule[slot-1].patientName,"");
    d->bookedCount--;
    
    printf("Appointmentt removed.\n");
}

typedef struct{
int id;
char name[64];
char symptoms[120];
int priority;
time_t arrivalTime;
}Walkin;

Walkin *pq = NULL;
int pqSize = 0;

void swapWalkin(Walkin *a,Walkin *b)
{
    Walkin temp;
*a=*b;
*b=temp;
}

void pushWalkin(const char *name,const char *sym,int pr)
{
    pq = realloc(pq,sizeof(Walkin)*(pqSize+1));
Walkin *w =&pq[pqSize];
w->id=rand()%900 + 100;
strcpy(w->name,name);
strcpy(w->symptoms,sym);
w->priority =pr;
w->arrivalTime = time(NULL);

//simple min-heap bubble-up
int idx =pqSize;
while(idx>0)
{
int parent =(idx-1)/2;
if(pq[parent].priority<=pq[idx].priority)
    break;
swapWalkin(&pq[parent],&pq[idx]);
idx = parent;
}

pqSize++;
printf("Walk-ins registered.\n");
}

void serveWalkin()
{
    if(pqSize==0){
printf("No Walk-ins present.\n");
return;
    }

Walkin top=pq[0];

pq[0] = pq[pqSize-1];
pqSize--;
pq = realloc(pq,sizeof(Walkin)*pqSize);

int idx=0;
while(1)
{
int left=2*idx+1,right=2*idx+2;
int smallest =idx;

if(left<pqSize && pq[left].priority<pq[smallest].priority)
    smallest=left;
if(right<pqSize && pq[right].priority<pq[smallest].priority)
    smallest=right;
if(smallest==idx)
    break;

swapWalkin(&pq[idx],&pq[smallest]);
idx=smallest;
}

time_t now =time(NULL);
double wait = difftime(now,top.arrivalTime);

printf("\n--NOW SERVING WALK-IN--\n");
printf("NAme:%s|ID:%d\n",top.name,top.id);
printf("Wait Time : %0f sec\n",wait);
}
int totalBooked =0;
int totalCnacelled=0;
int walkinServed =0;
double accumulatedWait=0;

void recordBooked(){totalBooked++;}
void recordCancelled(
{totalCancelled++;}

void printReport(){
    printf("\n==========DAILY REPORT==========\n");
for(int i=0;i<docCount;i++)
{
Doctor*d=&docList[i];
printf("\nDoctor;%s\n",d->name);
printf("Total slots: %dd\n", d->capacity);
printf("Book: %d | Free": %d\n", d->bookedCount,d-capacity-d->bookedCount);
}
printf("\n----Walked-in Queue----\n");
if(pqSize==0)
    printf("Pending Walk-ins: 0\n");
else
    printf("Pending Walk-ins: %d\n",pqSize);

printf("\nAppointments Books:%d\n",totalBooked);
printf("Appointments Cancelled%d\n",totalCancelled);
}
int main()
{
    srand(time(NULL));

addDoctor(1, "Dr.Kunal","Heart Specialist",5);
addDoctor(2, "Dr.Dhruv","Skin clinic",4);
addDoctor(3,"Dr.Abhinav","General Medicine",6);
int op;
do{
printf("\n======CLINIC CONTROL SYSYTEM=======\n");
    printf("1.Book Appointment\n");
 printf("1.Book Appointment\n");
 printf("2.Cancelled Appointment\n");
 printf("3.Register walk-in\n");
 printf("4.Server Walk-in\n");
 printf("5.view Doctors\n");
 printf("6.Daily report\n");
 printf("0.Exit\n");
 printf("Choose\n");

scanf("%d",&op);
getchar();

if(op==1) {bookSlot();recordBooked();}
else if(op==2){cancelSlot();recordCancelled();}
else if(op==3){
char n[64],s[120];
int p;
printf("Name:");
fgets(n,64,stdin);n[strcspn(n,"\n)]=0;
printf("Symptoms:");
fgets(s,120,stdin);s[strcspn(s,"\n)]=0;
printf("priorty(1=High,2=Medium,3=Low):");
pushWalkin(n,s,p);
}
else if(op==4) serveWalkIn();
else if(op==5) listDoctors();
else if(op==6)printfReport();
}
while(op!=0);
return 0;
}







