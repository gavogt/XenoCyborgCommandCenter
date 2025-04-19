typedef enum { SCOUT, WARRIOR, ENGINEER, MEDIC } CyborgRole;

typedef struct {
	int id;
	char name[50];
	int age;
	CyborgRole role;
} AlienCyborg;