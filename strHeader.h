#define Length 50
#define maxPatient 5
#define maxSlots 5

typedef struct 
{
    char name[Length],gender;
    int age , id ,reservedSlot ;

}Patient;

int addPatient(Patient newPatient);
int findByID(int id);