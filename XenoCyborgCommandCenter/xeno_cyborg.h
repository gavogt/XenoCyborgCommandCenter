#ifndef XENO_CYBORG_H
#define XENO_CYBORG_H

typedef enum { SCOUT, WARRIOR, ENGINEER, MEDIC } CyborgRole;

const char* CyborgRoleToString(CyborgRole role);

typedef struct {
	int id;
	char name[50];
	int age;
	CyborgRole role;
} AlienCyborg;

int GetUserChoice();

void ListXenoCyborgs(const AlienCyborg* cyborgs, int count);

void MenuSwitch(int choice, AlienCyborg** cyborgs, int *capacity, int *count);

AlienCyborg AddXenoCyborg(void);

#endif // XENO_CYBORG_H