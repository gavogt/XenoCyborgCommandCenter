#ifndef XENO_CYBORG_H
#define XENO_CYBORG_H

typedef enum { SCOUT, WARRIOR, ENGINEER, MEDIC } CyborgRole;

CyborgRole StringToCyborgRole(const char* str);
const char* CyborgRoleToString(CyborgRole role);

typedef struct {
	int id;
	char name[50];
	int age;
	CyborgRole role;
} AlienCyborg;

int GetUserChoice();

void ListXenoCyborgs(const AlienCyborg* cyborgs, int count);
void MenuSwitch(int choice, AlienCyborg** cyborgs, int* capacity, int* count, const char* save_fname, int save_mode);
void SortCyborgsByID(AlienCyborg* cyborgs, int count);
void SortCyborgsByName(AlienCyborg* cyborgs, int count);
void SearchCyborgsByName(const AlienCyborg* cyborgs, int count);
void DetermineAge(AlienCyborg *cyborgs);
void SearchCyborgsByRole(const AlienCyborg* cyborgs, int count);
void Cleanup(AlienCyborg* cyborgs);

AlienCyborg AddXenoCyborg(void);

#endif // XENO_CYBORG_H