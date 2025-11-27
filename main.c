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