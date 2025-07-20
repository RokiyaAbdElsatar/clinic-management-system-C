#include "strHeader.h"

Patient patients[maxPatient];
int patientCount = 0;
int slotReserved[maxSlots] = {0};

int findByID(int id){
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int addPatient(Patient newPatient){
    if (findByID(newPatient.id)!=-1)
    {
        return 0;
    }
    if (patientCount >= maxPatient) // check memory full
    {
        return -1;
    }
    newPatient.reservedSlot = -1;
    patients[patientCount++] = newPatient;
    return 1;
}