#ifndef XENO_CYBORG_H
#define XENO_CYBORG_H

typedef enum { SCOUT, WARRIOR, ENGINEER, MEDIC } CyborgRole;

typedef struct {
	int id;
	char name[50];
	int age;
	CyborgRole role;
} AlienCyborg;

int GetUserChoice();

AlienCyborg MenuSwitch(int choice);

AlienCyborg AddXenoCyborg(void);

#endif // XENO_CYBORG_H