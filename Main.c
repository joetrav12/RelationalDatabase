#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert_course_to_key(char c[5]) {
  char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int key = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 26; j++) {
      if (c[i] == alphabet[j]) {
        if (i == 0) {
          key += (j + 1) * 100000;
        }
        if (i == 1) {
          key += (j + 1) * 1000;
        }
      }
    }
  }

  key += atoi(&c[2]);

  return key;
}

struct CSG {
  char course[5];
  int student_id; //KEY
  char grade[2];
}; typedef struct CSG w;

struct SNAP {
  int student_id; //KEY
  char name[30];
  char address[50];
  char phone[8];
}; typedef struct SNAP x;

struct CP {
   char course[6]; //KEY
   char pre_req[5];
}; typedef struct CP y;

struct CDH {
  char course[6]; //KEY
  char day[2];
  char hour[4];
}; typedef struct CDH z;

struct CR {
  char course[6];
  char room[20];
}; typedef struct CR zz;

struct CSG_Node {
  w *csg;
  struct CSG_Node *next;
}; typedef struct CSG_Node csgn;

struct SNAP_Node {
  x *snap;
  struct SNAP_Node *next;
}; typedef struct SNAP_Node snapn;

struct CP_Node {
  y *cp;
  struct CP_Node *next;
}; typedef struct CP_Node cpn;

struct CDH_Node {
  z *cdh;
  struct CDH_Node *next;
}; typedef struct CDH_Node cdhn;

struct CR_Node {
  zz *cr;
  struct CR_Node *next;
}; typedef struct CR_Node crn;

struct CSG_Node *CSG_hashtable[1009];
struct SNAP_Node *SNAP_hashtable[1009];
struct CP_Node *CP_hashtable[1009];
struct CDH_Node *CDH_hashtable[1009];
struct CR_Node *CR_hashtable[1009];

//all the insert into linked list methods:
void CSG_insert_linked_list(char c[5], int sid, char g[2], struct CSG_Node **pL) {
  w *l = NULL;
  l = (w*)malloc(sizeof(w));
  strncpy(l->course, c, 5);
  l->student_id = sid;
  strncpy(l->grade, g, 2);

  if (*pL == NULL) {
    *pL = malloc(sizeof(struct CSG_Node *));
    (*pL)->csg = l;
    (*pL)->next = NULL;
  }
  else {
    CSG_insert_linked_list(c, sid, g, &((*pL)->next));
  }
}

void SNAP_insert_linked_list(int sid, char n[30], char a[50], char p[8], struct SNAP_Node **pL) {
  x *l = NULL;
  l = (x*)malloc(sizeof(x));
  l->student_id = sid;
  strncpy(l->name, n, 30);
  strncpy(l->address, a, 50);
  strncpy(l->phone, p, 8);

  if (*pL == NULL) {
    *pL = malloc(sizeof(struct SNAP_Node *));
    (*pL)->snap = l;
    (*pL)->next = NULL;
  }
  else {
    SNAP_insert_linked_list(sid, n, a, p, &((*pL)->next));
  }
}

void CP_insert_linked_list(char c[5], char pr[5], struct CP_Node **pL) {
  y *l = NULL;
  l = (y*)malloc(sizeof(y));
  strncpy(l->course, c, 5);
  strncpy(l->pre_req, pr, 5);

  if (*pL == NULL) {
    *pL = malloc(sizeof(struct CP_Node *));
    (*pL)->cp = l;
    (*pL)->next = NULL;
  }
  else {
    CP_insert_linked_list(c, pr, &((*pL)->next));
  }
}

void CDH_insert_linked_list(char c[5], char d[2], char h[4], struct CDH_Node **pL) {
  z *l = NULL;
  l = (z*)malloc(sizeof(z));
  strncpy(l->course, c, 5);
  strncpy(l->day, d, 2);
  strncpy(l->hour, h, 4);

  if (*pL == NULL) {
    *pL = malloc(sizeof(struct CDH_Node *));
    (*pL)->cdh = l;
    (*pL)->next = NULL;
  }
  else {
    CDH_insert_linked_list(c, d, h, &((*pL)->next));
  }
}

void CR_insert_linked_list(char c[5], char r[20], struct CR_Node **pL) {
  zz *l = NULL;
  l = (zz*)malloc(sizeof(zz));
  strncpy(l->course, c, 5);
  strncpy(l->room, r, 20);

  if (*pL == NULL) {
    *pL = malloc(sizeof(struct CR_Node *));
    (*pL)->cr = l;
    (*pL)->next = NULL;
  }
  else {
    CR_insert_linked_list(c, r, &((*pL)->next));
  }
}

//all the insert into hashtable methods:
void CSG_insert_hashtable(struct CSG_Node *pL) {
  CSG_hashtable[pL->csg->student_id % 1009] = pL;
}

void SNAP_insert_hashtable(struct SNAP_Node *pL) {
  SNAP_hashtable[pL->snap->student_id % 1009] = pL;
}

void CP_insert_hashtable(struct CP_Node *pL) {
  int key = convert_course_to_key(pL->cp->course);
  CP_hashtable[key % 1009] = pL;
}

void CDH_insert_hashtable(struct CDH_Node *pL) {
  int key = convert_course_to_key(pL->cdh->course);
  CDH_hashtable[key % 1009] = pL;
}

void CR_insert_hashtable(struct CR_Node *pL) {
  int key = convert_course_to_key(pL->cr->course);
  CR_hashtable[key % 1009] = pL;
}

void insert(char *tuple[4],  char relation[4]) {
  if (strcmp(relation, "CSG") == 0) {
    if (CSG_hashtable[atoi(tuple[1]) % 1009] == NULL) {
      struct CSG_Node *L = NULL;
      CSG_insert_linked_list(tuple[0], atoi(tuple[1]), tuple[2], &L);
      CSG_insert_hashtable(L);
    }
    else {
      CSG_insert_linked_list(tuple[0], atoi(tuple[1]), tuple[2], &CSG_hashtable[atoi(tuple[1]) % 1009]);
    }
  }
  if (strcmp(relation, "SNAP") == 0) {
    if (SNAP_hashtable[atoi(tuple[0]) % 1009] == NULL) {
      struct SNAP_Node *L = NULL;
      SNAP_insert_linked_list(atoi(tuple[0]), tuple[1], tuple[2], tuple[3], &L);
      SNAP_insert_hashtable(L);
    }
    else {
      SNAP_insert_linked_list(atoi(tuple[0]), tuple[1], tuple[2], tuple[3], &SNAP_hashtable[atoi(tuple[0]) % 1009]);
    }
  }
  if (strcmp(relation, "CP") == 0) {
    if (CP_hashtable[convert_course_to_key(tuple[0]) % 1009] == NULL) {
      struct CP_Node *L = NULL;
      CP_insert_linked_list(tuple[0], tuple[1], &L);
      CP_insert_hashtable(L);
    }
    else {
      CP_insert_linked_list(tuple[0], tuple[1], &CP_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
  }
  if (strcmp(relation, "CDH") == 0) {
    if (CDH_hashtable[convert_course_to_key(tuple[0]) % 1009] == NULL) {
      struct CDH_Node *L = NULL;
      CDH_insert_linked_list(tuple[0], tuple[1], tuple[2], &L);
      CDH_insert_hashtable(L);
    }
    else {
      CDH_insert_linked_list(tuple[0], tuple[1], tuple[2], &CDH_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
  }
  if (strcmp(relation, "CR") == 0) {
    if (CR_hashtable[convert_course_to_key(tuple[0]) % 1009] == NULL) {
      struct CR_Node *L = NULL;
      CR_insert_linked_list(tuple[0], tuple[1], &L);
      CR_insert_hashtable(L);
    }
    else {
      CR_insert_linked_list(tuple[0], tuple[1], &CR_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
  }
}

void CSG_read_from_file_and_insert() {
  FILE *fpointer;
  char *c = malloc(5); //dynamic allocation
  char *s = malloc(5);
  char *g = malloc(3);
  fpointer = fopen("dataBaseCSG.txt", "r");
  if (fpointer == NULL) {
    printf("Error, this file could not be opened.\n");
    exit(0);
  }

  while (!feof(fpointer)) {
    fscanf(fpointer, "%s %s %s ", c, s, g);
    char *csg1[3];
    csg1[0] = c;
    csg1[1] = s;
    csg1[2] = g;
    insert(csg1, "CSG");
  }

  fclose(fpointer);
}

void SNAP_read_from_file_and_insert() {
  FILE *fpointer;
  char *s = malloc(5);
  char *n = malloc(30);
  char *a = malloc(50);
  char *p = malloc(8);
  fpointer = fopen("dataBaseSNAP.txt", "r");
  if (fpointer == NULL) {
    printf("Error, this file could not be opened.\n");
    exit(0);
  }

  while (!feof(fpointer)) {
    fscanf(fpointer, "%s %s %s %s ", s, n, a, p);
    char *snap1[4];
    snap1[0] = s;
    snap1[1] = n;
    snap1[2] = a;
    snap1[3] = p;
    insert(snap1, "SNAP");
  }

  fclose(fpointer);
}

void CP_read_from_file_and_insert() {
  FILE *fpointer;
  char *c = malloc(5);
  char *pr = malloc(5);
  fpointer = fopen("dataBaseCP.txt", "r");
  if (fpointer == NULL) {
    printf("Error, this file could not be opened.\n");
    exit(0);
  }

  while (!feof(fpointer)) {
    fscanf(fpointer, "%s %s ", c, pr);
    char *cp1[2];
    cp1[0] = c;
    cp1[1] = pr;
    insert(cp1, "CP");
  }

  fclose(fpointer);
}

void CDH_read_from_file_and_insert() {
  FILE *fpointer;
  char *c = malloc(5);
  char *d = malloc(2);
  char *h = malloc(4);
  fpointer = fopen("dataBaseCDH.txt", "r");
  if (fpointer == NULL) {
    printf("Error, this file could not be opened.\n");
    exit(0);
  }

  while (!feof(fpointer)) {
    fscanf(fpointer, "%s %s %s ", c, d, h);
    char *cdh1[3];
    cdh1[0] = c;
    cdh1[1] = d;
    cdh1[2] = h;
    insert(cdh1, "CDH");
  }

  fclose(fpointer);
}

void CR_read_from_file_and_insert() {
  FILE *fpointer;
  char *c = malloc(5);
  char *r = malloc(20);
  fpointer = fopen("dataBaseCR.txt", "r");
  if (fpointer == NULL) {
    printf("Error, this file could not be opened.\n");
    exit(0);
  }

  while (!feof(fpointer)) {
    fscanf(fpointer, "%s %s ", c, r);
    char *cr1[2];
    cr1[0] = c;
    cr1[1] = r;
    insert(cr1, "CR");
  }

  fclose(fpointer);
}

void CSG_delete_helper(char *tuple[3], struct CSG_Node **L) {
  if (*L != NULL) {
    int target_count = 0;

    if (strcmp((*L)->csg->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if ((*L)->csg->student_id != atoi(tuple[1])) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->csg->grade, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 3) {
      *L = (*L)->next;
      CSG_delete_helper(tuple, &(*L));
    }
    else {
      CSG_delete_helper(tuple, &((*L)->next));
    }
  }
}

void SNAP_delete_helper(char *tuple[4], struct SNAP_Node **L) {
  if (*L != NULL) {
    int target_count = 0;

    if ((*L)->snap->student_id != atoi(tuple[0])) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->snap->name, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->snap->address, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->snap->phone, tuple[3]) != 0) {
      if (strcmp(tuple[3], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 4) {
      *L = (*L)->next;
      SNAP_delete_helper(tuple, &(*L));
    }
    else {
      SNAP_delete_helper(tuple, &((*L)->next));
    }
  }
}

void CP_delete_helper(char *tuple[2], struct CP_Node **L) {
  if (*L != NULL) {
    int target_count = 0;

    if (strcmp((*L)->cp->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->cp->pre_req, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 2) {
      *L =  (*L)->next;
      CP_delete_helper(tuple, &(*L));
    }
    else {
      CP_delete_helper(tuple, &((*L)->next));
    }
  }
}

void CDH_delete_helper(char *tuple[3], struct CDH_Node **L) {
  if (*L != NULL) {
    int target_count = 0;

    if (strcmp((*L)->cdh->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->cdh->day, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->cdh->hour, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 3) {
      *L =  (*L)->next;
      CDH_delete_helper(tuple, &(*L));
    }
    else {
      CDH_delete_helper(tuple, &((*L)->next));
    }
  }
}

void CR_delete_helper(char *tuple[2], struct CR_Node **L) {
  if (*L != NULL) {
    int target_count = 0;

    if (strcmp((*L)->cr->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp((*L)->cr->room, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 2) {
      *L =  (*L)->next;
      CR_delete_helper(tuple, &(*L));
    }
    else {
      CR_delete_helper(tuple, &((*L)->next));
    }
  }
}

void delete(char *tuple[4], char relation[4]) {
  if (strcmp(relation, "CSG") == 0) {
    if (strcmp(tuple[1], "*") != 0) {
      CSG_delete_helper(tuple, &CSG_hashtable[atoi(tuple[1]) % 1009]);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        if (CSG_hashtable[i] != NULL) {
          CSG_delete_helper(tuple, &CSG_hashtable[i]);
        }
      }
    }
  }
  if (strcmp(relation, "SNAP") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      SNAP_delete_helper(tuple, &SNAP_hashtable[atoi(tuple[0]) % 1009]);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        if (SNAP_hashtable[i] != NULL) {
          SNAP_delete_helper(tuple, &SNAP_hashtable[i]);
        }
      }
    }
  }
  if (strcmp(relation, "CP") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      CP_delete_helper(tuple, &CP_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        if (CP_hashtable[i] != NULL) {
          CP_delete_helper(tuple, &CP_hashtable[i]);
        }
      }
    }
  }
  if (strcmp(relation, "CDH") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      CDH_delete_helper(tuple, &CDH_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        if (CDH_hashtable[i] != NULL) {
          CDH_delete_helper(tuple, &CDH_hashtable[i]);
        }
      }
    }
  }
  if (strcmp(relation, "CR") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      CR_delete_helper(tuple, &CR_hashtable[convert_course_to_key(tuple[0]) % 1009]);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        if (CR_hashtable[i] != NULL) {
          CR_delete_helper(tuple, &CR_hashtable[i]);
        }
      }
    }
  }
}

void CSG_lookup_helper(char *tuple[3], struct CSG_Node *L) {
  while (L != NULL) {
    int target_count = 0;

    if (strcmp(L->csg->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (L->csg->student_id != atoi(tuple[1])) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->csg->grade, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 3) {
      printf("%s ", L->csg->course);
      printf("%d ", L->csg->student_id);
      printf("%s", L->csg->grade);
      printf("\n");
    }

    L = L->next;
  }
}

void SNAP_lookup_helper(char *tuple[4], struct SNAP_Node *L) {
  while (L != NULL) {
    int target_count = 0;

    if (L->snap->student_id != atoi(tuple[0])) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->snap->name, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->snap->address, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->snap->phone, tuple[3]) != 0) {
      if (strcmp(tuple[3], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 4) {
      printf("%d ", L->snap->student_id);
      printf("%s ", L->snap->name);
      printf("%s ", L->snap->address);
      printf("%s", L->snap->phone);
      printf("\n");
    }

    L = L->next;
  }
}

void CP_lookup_helper(char *tuple[2], struct CP_Node *L) {
  while (L != NULL) {
    int target_count = 0;

    if (strcmp(L->cp->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->cp->pre_req, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 2) {
      printf("%s ", L->cp->course);
      printf("%s ", L->cp->pre_req);
      printf("\n");
    }

    L = L->next;
  }
}

void CDH_lookup_helper(char *tuple[3], struct CDH_Node *L) {
  while (L != NULL) {
    int target_count = 0;

    if (strcmp(L->cdh->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->cdh->day, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->cdh->hour, tuple[2]) != 0) {
      if (strcmp(tuple[2], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 3) {
      printf("%s ", L->cdh->course);
      printf("%s ", L->cdh->day);
      printf("%s ", L->cdh->hour);
      printf("\n");
    }

    L = L->next;
  }
}

void CR_lookup_helper(char *tuple[2], struct CR_Node *L) {
  while (L != NULL) {
    int target_count = 0;

    if (strcmp(L->cr->course, tuple[0]) != 0) {
      if (strcmp(tuple[0], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (strcmp(L->cr->room, tuple[1]) != 0) {
      if (strcmp(tuple[1], "*") == 0) {
        target_count++;
      }
    }
    else {
      target_count++;
    }

    if (target_count == 2) {
      printf("%s ", L->cr->course);
      printf("%s ", L->cr->room);
      printf("\n");
    }

    L = L->next;
  }
}

void lookup(char *tuple[4], char relation[4]) {
  if (strcmp(relation, "CSG") == 0) {
    //Check if the primary index is given. If it is, then we need only check the linked list of a specific bucket:
    if (strcmp(tuple[1], "*") != 0) {
      struct CSG_Node *L = CSG_hashtable[atoi(tuple[1]) % 1009];
      CSG_lookup_helper(tuple, L);
    }
    //If primary index is not given, then we need to iterate through the hashtable and check the linked lists of each bucket:
    else {
      for (int i = 0; i < 1009; i++) {
        struct CSG_Node *L = CSG_hashtable[i];
        CSG_lookup_helper(tuple, L);
      }
    }
  }
  if (strcmp(relation, "SNAP") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      struct SNAP_Node *L = SNAP_hashtable[atoi(tuple[0]) % 1009];
      SNAP_lookup_helper(tuple, L);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        struct SNAP_Node *L = SNAP_hashtable[i];
        SNAP_lookup_helper(tuple, L);
      }
    }
  }
  if (strcmp(relation, "CP") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      struct CP_Node *L = CP_hashtable[convert_course_to_key(tuple[0]) % 1009];
      CP_lookup_helper(tuple, L);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        struct CP_Node *L = CP_hashtable[i];
        CP_lookup_helper(tuple, L);
      }
    }
  }
  if (strcmp(relation, "CDH") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      struct CDH_Node *L = CDH_hashtable[convert_course_to_key(tuple[0]) % 1009];
      CDH_lookup_helper(tuple, L);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        struct CDH_Node *L = CDH_hashtable[i];
        CDH_lookup_helper(tuple, L);
      }
    }
  }
  if (strcmp(relation, "CR") == 0) {
    if (strcmp(tuple[0], "*") != 0) {
      struct CR_Node *L = CR_hashtable[convert_course_to_key(tuple[0]) % 1009];
      CR_lookup_helper(tuple, L);
    }
    else {
      for (int i = 0; i < 1009; i++) {
        struct CR_Node *L = CR_hashtable[i];
        CR_lookup_helper(tuple, L);
      }
    }
  }
}

void CSG_print_list(struct CSG_Node *L) {
  printf("%s ", L->csg->course);
  printf("%d ", L->csg->student_id);
  printf("%s", L->csg->grade);

  if (L->next != NULL) {
    printf("%s", ", ");
    CSG_print_list(L->next);
  }
  else {
    printf("\n");
  }
}

void SNAP_print_list(struct SNAP_Node *L) {
  printf("%d ", L->snap->student_id);
  printf("%s ", L->snap->name);
  printf("%s ", L->snap->address);
  printf("%s", L->snap->phone);

  if (L->next != NULL) {
    printf("%s", ", ");
    SNAP_print_list(L->next);
  }
  else {
    printf("\n");
  }
}

void CP_print_list(struct CP_Node *L) {
  printf("%s ", L->cp->course);
  printf("%s", L->cp->pre_req);

  if (L->next != NULL) {
    printf("%s", ", ");
    CP_print_list(L->next);
  }
  else {
    printf("\n");
  }
}

void CDH_print_list(struct CDH_Node *L) {
  printf("%s ", L->cdh->course);
  printf("%s ", L->cdh->day);
  printf("%s", L->cdh->hour);

  if (L->next != NULL) {
    printf("%s", ", ");
    CDH_print_list(L->next);
  }
  else {
    printf("\n");
  }
}

void CR_print_list(struct CR_Node *L) {
  printf("%s ", L->cr->course);
  printf("%s", L->cr->room);

  if (L->next != NULL) {
    printf("%s", ", ");
    CR_print_list(L->next);
  }
  else {
    printf("\n");
  }
}

void CSG_print_hashtable(struct CSG_Node *hashtable[1009]) {
  printf("%s\n", "CSG:");
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      printf("%d ", i);
      CSG_print_list(hashtable[i]);
    }
  }
}

void SNAP_print_hashtable(struct SNAP_Node *hashtable[1009]) {
  printf("%s\n", "SNAP:");
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      printf("%d ", i);
      SNAP_print_list(hashtable[i]);
    }
  }
}

void CP_print_hashtable(struct CP_Node *hashtable[1009]) {
  printf("%s\n", "CP:");
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      printf("%d ", i);
      CP_print_list(hashtable[i]);
    }
  }
}

void CDH_print_hashtable(struct CDH_Node *hashtable[1009]) {
  printf("%s\n", "CDH:");
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      printf("%d ", i);
      CDH_print_list(hashtable[i]);
    }
  }
}

void CR_print_hashtable(struct CR_Node *hashtable[1009]) {
  printf("%s\n", "CR:");
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      printf("%d ", i);
      CR_print_list(hashtable[i]);
    }
  }
}

//Function to answer query: what grade did StudentName get in CourseName?
const char * query_1(char n[30], char c[5]) {
  int sid;
  int boolean = 0;
  const char *g;

  for (int i = 0; i < 1009; i++) {
    if (SNAP_hashtable[i] != NULL) {
      struct SNAP_Node *L = SNAP_hashtable[i];

      while (L != NULL) {
        if (strcmp(L->snap->name, n) == 0) {
          sid = L->snap->student_id;
          //there may be more than one person with name "n", but for the purpose of this project, let us get the first person in the hashtable whose name is "n":
          boolean = 1;
          break;
        }

        L = L->next;
      }

      if (boolean == 1) {
        break;
      }
    }
  }

  if (boolean == 0) {
    printf("%s\n", "There is no one in the database by that name.");
    return NULL;
  }

  struct CSG_Node *L = CSG_hashtable[sid % 1009];
  int boolean2 = 0;

  while (L != NULL) {
    if (strcmp(L->csg->course, c) == 0) {
      g = L->csg->grade;
      boolean2 = 1;
      break;
    }

    L = L->next;
  }

  if (boolean2 == 0) {
    printf("%s ", n);
    printf("%s\n", "did not take that course.");
    return NULL;
  }

  return g;
}

//Function to answer query: Where is StudentName at Time on Day?
const char * query_2(char n[30], char h[4], char d[2]) {
  int sid;
  const char *r;
  char *the_course;
  int boolean = 0;

  for (int i = 0; i < 1009; i++) {
    if (SNAP_hashtable[i] != NULL) {
      struct SNAP_Node *L = SNAP_hashtable[i];

      while (L != NULL) {
        if (strcmp(L->snap->name, n) == 0) {
          sid = L->snap->student_id;
          boolean = 1;
          break;
        }

        L = L->next;
      }

      if (boolean == 1) {
        break;
      }
    }
  }

  if (boolean == 0) {
    printf("%s\n", "There is no one in the database by that name.");
    return NULL;
  }

  struct CSG_Node *L = CSG_hashtable[sid % 1009];
  struct CSG_Node *new_L = NULL;

  while (L != NULL) {
    if (L->csg->student_id == sid) {
      CSG_insert_linked_list(L->csg->course, L->csg->student_id, L->csg->grade, &new_L);
    }

    L = L->next;
  }

  int boolean2 = 0;

  while (new_L != NULL) {
    struct CDH_Node *L = CDH_hashtable[convert_course_to_key(new_L->csg->course) % 1009];

    while (L != NULL) {
      if ((strcmp(L->cdh->day, d) == 0) && (strcmp(L->cdh->hour, h) == 0)) {
        the_course = L->cdh->course;
        boolean2 = 1;
        break;
      }

      L = L->next;
    }

    if (boolean2 == 1) {
      break;
    }

    new_L = new_L->next;
  }

  if (boolean2 == 0) {
    printf("%s ", n);
    printf("%s", "isn't in a class at");
    printf(" %s ", h);
    printf("%s", "on");
    printf(" %s", d);
    printf("%s\n", ".");
    return NULL;
  }

  struct CR_Node *L2 = CR_hashtable[convert_course_to_key(the_course) % 1009];

  while (L2 != NULL) {
    if (strcmp(L2->cr->course, the_course) == 0) {
      r = L2->cr->room;
      break;
    }

    L2 = L2->next;
  }

  return r;
}

//Selection and Projection:
void CSG_projection(char attribute[10], struct CSG_Node *hashtable[1009]) {
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      struct CSG_Node *L = hashtable[i];

      while (L != NULL) {
        if (strcmp(attribute, "course") == 0) {
          printf("%s\n", L->csg->course);
        }
        if (strcmp(attribute, "student_id") == 0) {
          printf("%d\n", L->csg->student_id);
        }
        if (strcmp(attribute, "grade") == 0) {
          printf("%s\n", L->csg->grade);
        }

        L = L->next;
      }
    }
  }
}

void SNAP_projection(char attribute[10], struct SNAP_Node *hashtable[1009]) {
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      struct SNAP_Node *L = hashtable[i];

      while (L != NULL) {
        if (strcmp(attribute, "student_id") == 0) {
          printf("%d\n", L->snap->student_id);
        }
        if (strcmp(attribute, "name") == 0) {
          printf("%s\n", L->snap->name);
        }
        if (strcmp(attribute, "address") == 0) {
          printf("%s\n", L->snap->address);
        }
        if (strcmp(attribute, "phone") == 0) {
          printf("%s\n", L->snap->phone);
        }

        L = L->next;
      }
    }
  }
}

void CP_projection(char attribute[6], struct CP_Node *hashtable[1009]) {
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      struct CP_Node *L = hashtable[i];

      while (L != NULL) {
        if (strcmp(attribute, "course") == 0) {
          printf("%s\n", L->cp->course);
        }
        if (strcmp(attribute, "pre_req") == 0) {
          printf("%s\n", L->cp->pre_req);
        }

        L = L->next;
      }
    }
  }
}

void CDH_projection(char attribute[6], struct CDH_Node *hashtable[1009]) {
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      struct CDH_Node *L = hashtable[i];

      while (L != NULL) {
        if (strcmp(attribute, "course") == 0) {
          printf("%s\n", L->cdh->course);
        }
        if (strcmp(attribute, "day") == 0) {
          printf("%s\n", L->cdh->day);
        }
        if (strcmp(attribute, "hour") == 0) {
          printf("%s\n", L->cdh->hour);
        }

        L = L->next;
      }
    }
  }
}

void CR_projection(char attribute[6], struct CR_Node *hashtable[1009]) {
  for (int i = 0; i < 1009; i++) {
    if (hashtable[i] != NULL) {
      struct CR_Node *L = hashtable[i];

      while (L != NULL) {
        if (strcmp(attribute, "course") == 0) {
          printf("%s\n", L->cr->course);
        }
        if (strcmp(attribute, "room") == 0) {
          printf("%s\n", L->cr->room);
        }

        L = L->next;
      }
    }
  }
}

struct CSG_Node **CSG_selection(char attribute[10], char attribute_target[5]) {
  static struct CSG_Node *new_hashtable[1009];

  //if the primary key is the given attribute:
  if (strcmp(attribute, "student_id") == 0) {
    struct CSG_Node *L = CSG_hashtable[atoi(attribute_target) % 1009];
    struct CSG_Node *new_L = NULL;

    while (L != NULL) {
      if (L->csg->student_id == atoi(attribute_target)) {
        CSG_insert_linked_list(L->csg->course, L->csg->student_id, L->csg->grade, &new_L);
      }

      L = L->next;
    }

    new_hashtable[atoi(attribute_target) % 1009] = new_L;
  }
  //if the primary key is NOT the given attribute:
  if (strcmp(attribute, "course") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CSG_hashtable[i] != NULL) {
        struct CSG_Node *L = CSG_hashtable[i];
        struct CSG_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->csg->course, attribute_target) == 0) {
            CSG_insert_linked_list(L->csg->course, L->csg->student_id, L->csg->grade, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }
  if (strcmp(attribute, "grade") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CSG_hashtable[i] != NULL) {
        struct CSG_Node *L = CSG_hashtable[i];
        struct CSG_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->csg->grade, attribute_target) == 0) {
            CSG_insert_linked_list(L->csg->course, L->csg->student_id, L->csg->grade, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }

  return new_hashtable;
}

struct SNAP_Node **SNAP_selection(char attribute[10], char attribute_target[50]) {
  static struct SNAP_Node *new_hashtable[1009];

  if (strcmp(attribute, "student_id") == 0) {
    struct SNAP_Node *L = SNAP_hashtable[atoi(attribute_target) % 1009];
    struct SNAP_Node *new_L = NULL;

    while (L != NULL) {
      if (L->snap->student_id == atoi(attribute_target)) {
        SNAP_insert_linked_list(L->snap->student_id, L->snap->name, L->snap->address, L->snap->phone, &new_L);
      }

      L = L->next;
    }

    new_hashtable[atoi(attribute_target) % 1009] = new_L;
  }
  if (strcmp(attribute, "name") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (SNAP_hashtable[i] != NULL) {
        struct SNAP_Node *L = SNAP_hashtable[i];
        struct SNAP_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->snap->name, attribute_target) == 0) {
            SNAP_insert_linked_list(L->snap->student_id, L->snap->name, L->snap->address, L->snap->phone, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }
  if (strcmp(attribute, "address") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (SNAP_hashtable[i] != NULL) {
        struct SNAP_Node *L = SNAP_hashtable[i];
        struct SNAP_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->snap->address, attribute_target) == 0) {
            SNAP_insert_linked_list(L->snap->student_id, L->snap->name, L->snap->address, L->snap->phone, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }
  if (strcmp(attribute, "phone") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (SNAP_hashtable[i] != NULL) {
        struct SNAP_Node *L = SNAP_hashtable[i];
        struct SNAP_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->snap->phone, attribute_target) == 0) {
            SNAP_insert_linked_list(L->snap->student_id, L->snap->name, L->snap->address, L->snap->phone, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }

  return new_hashtable;
}

struct CP_Node **CP_selection(char attribute[7], char attribute_target[5]) {
  static struct CP_Node *new_hashtable[1009];

  if (strcmp(attribute, "course") == 0) {
    struct CP_Node *L = CP_hashtable[convert_course_to_key(attribute_target) % 1009];
    struct CP_Node *new_L = NULL;

    while (L != NULL) {
      if (strcmp(L->cp->course, attribute_target) == 0) {
        CP_insert_linked_list(L->cp->course, L->cp->pre_req, &new_L);
      }

      L = L->next;
    }

    new_hashtable[convert_course_to_key(attribute_target) % 1009] = new_L;
  }
  if (strcmp(attribute, "pre_req") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CP_hashtable[i] != NULL) {
        struct CP_Node *L = CP_hashtable[i];
        struct CP_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->cp->pre_req, attribute_target) == 0) {
            CP_insert_linked_list(L->cp->course, L->cp->pre_req, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }

  return new_hashtable;
}

struct CDH_Node **CDH_selection(char attribute[6], char attribute_target[5]) {
  static struct CDH_Node *new_hashtable[1009];

  if (strcmp(attribute, "course") == 0) {
    struct CDH_Node *L = CDH_hashtable[convert_course_to_key(attribute_target) % 1009];
    struct CDH_Node *new_L = NULL;

    while (L != NULL) {
      if (strcmp(L->cdh->course, attribute_target) == 0) {
        CDH_insert_linked_list(L->cdh->course, L->cdh->day, L->cdh->hour, &new_L);
      }

      L = L->next;
    }

    new_hashtable[convert_course_to_key(attribute_target) % 1009] = new_L;
  }
  if (strcmp(attribute, "day") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CDH_hashtable[i] != NULL) {
        struct CDH_Node *L = CDH_hashtable[i];
        struct CDH_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->cdh->day, attribute_target) == 0) {
            CDH_insert_linked_list(L->cdh->course, L->cdh->day, L->cdh->hour, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }
  if (strcmp(attribute, "hour") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CDH_hashtable[i] != NULL) {
        struct CDH_Node *L = CDH_hashtable[i];
        struct CDH_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->cdh->hour, attribute_target) == 0) {
            CDH_insert_linked_list(L->cdh->course, L->cdh->day, L->cdh->hour, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }

  return new_hashtable;
}

struct CR_Node **CR_selection(char attribute[6], char attribute_target[20]) {
  static struct CR_Node *new_hashtable[1009];

  if (strcmp(attribute, "course") == 0) {
    struct CR_Node *L = CR_hashtable[convert_course_to_key(attribute_target) % 1009];
    struct CR_Node *new_L = NULL;

    while (L != NULL) {
      if (strcmp(L->cr->course, attribute_target) == 0) {
        CR_insert_linked_list(L->cr->course, L->cr->room, &new_L);
      }

      L = L->next;
    }

    new_hashtable[convert_course_to_key(attribute_target) % 1009] = new_L;
  }
  if (strcmp(attribute, "room") == 0) {
    for (int i = 0; i < 1009; i++) {
      if (CR_hashtable[i] != NULL) {
        struct CR_Node *L = CR_hashtable[i];
        struct CR_Node *new_L = NULL;

        while (L != NULL) {
          if (strcmp(L->cr->room, attribute_target) == 0) {
            CR_insert_linked_list(L->cr->course, L->cr->room, &new_L);
          }

          L = L->next;
        }

        new_hashtable[i] = new_L;
      }
    }
  }

  return new_hashtable;
}

int main() {
  //Here, I am reading from the various txt files and inserting the tuples listed in them into their respective hashtables:
  CSG_read_from_file_and_insert();
  SNAP_read_from_file_and_insert();
  CP_read_from_file_and_insert();
  CDH_read_from_file_and_insert();
  CR_read_from_file_and_insert();
  //Note: the text files represent the relations from Chapter 8 of FOCS.
  //Another note: we will write the relations onto files later.

  //Now we have a database of 5 relations. Let us manually insert some other tuples, for the sake of more examples:
  //this is a good example because the student_id is not 12345, BUT 12345 % 1009 = 66831 % 1009. So the student with this student_id will be in the same bucket as the students with the student_id 12345.
  char *csg1[3];
  csg1[0] = "MT150";
  csg1[1] = "66831";
  csg1[2] = "B-";
  insert(csg1, "CSG");

  //another good example, for the same reason:
  char *snap1[4];
  snap1[0] = "45429";
  snap1[1] = "Raekwon";
  snap1[2] = "Shaolin";
  snap1[3] = "hitmylin";
  insert(snap1, "SNAP");

  //We will print the hashtables out later.
  //Also, we will not test the delete function now; it is more prudent to test the other parts of the project that do NOT affect the hashtables and then implement delete later.

  //Let us implement the lookup function for each hashtable:
  //This checks if there are tuples in CSG with grade C, and then prints out the tuples:
  char *csg_lookup_1[3];
  csg_lookup_1[0] = "*";
  csg_lookup_1[1] = "*";
  csg_lookup_1[2] = "C";
  lookup(csg_lookup_1, "CSG");
  printf("\n");

  //This checks if there is are tuples in SNAP with student_id 22222, and then prints out the tuples:
  char *snap_lookup_1[4];
  snap_lookup_1[0] = "22222";
  snap_lookup_1[1] = "*";
  snap_lookup_1[2] = "*";
  snap_lookup_1[3] = "*";
  lookup(snap_lookup_1, "SNAP");
  printf("\n");

  //This checks if there are tuples in CP with course CS101 and pre_req CS120, and then prints out the tuples (so it will print out nothing):
  char *cp_lookup_1[2];
  cp_lookup_1[0] = "CS101";
  cp_lookup_1[1] = "CS120";
  lookup(cp_lookup_1, "CP");

  //This checks if there are tuples in CDH with course EE200 and time 10AM, and then prints out the tuples:
  char *cdh_lookup_1[3];
  cdh_lookup_1[0] = "EE200";
  cdh_lookup_1[1] = "*";
  cdh_lookup_1[2] = "10AM";
  lookup(cdh_lookup_1, "CDH");
  printf("\n");

  //This prints out all the tuples in CR:
  char *cr_lookup_1[2];
  cr_lookup_1[0] = "*";
  cr_lookup_1[1] = "*";
  lookup(cr_lookup_1, "CR");
  printf("\n");
  printf("\n");

  //This function will answer the query: "What grade did C.Brown get in CS101?":
  printf("%s\n", "What grade did C.Brown get in CS101?");
  const char *question1 = query_1("C.Brown", "CS101");
  if (question1 != NULL) {
    printf("%s\n", question1);
  }
  printf("\n");

  //This function will answer the query: "Where is C.Brown at 9AM on M?":
  printf("%s\n", "Where is C.Brown at 9AM on M?");
  const char *question2 = query_2("C.Brown", "9AM", "M");
  if (question2 != NULL) {
    printf("%s\n", question2);
  }
  printf("\n");
  printf("\n");

  //These next examples will demonstrate relation algebra.
  //EXAMPLE 1: (select(course = "CS101") from CSG):
  printf("%s\n", "EXAMPLE 1:");
  struct CSG_Node **x = CSG_selection("course", "CS101");
  CSG_print_hashtable(x);
  printf("\n");

  //EXAMPLE 2: (project(student_id) from x):
  //I use x here because x is equal to select(course = "CS101") from CSG.
  printf("%s\n", "EXAMPLE 2:");
  CSG_projection("student_id", x);
  printf("\n");
  printf("\n");

  //Let us now print out all the hashtables:
  //Keep in mind that the number on the far left is the index of the hashtable. It is not another attribute in the tuples.
  //Furthemore, commas separate tuples that are in the same bucket.
  printf("%s\n", "HASHTABLES, ROUND 1:");
  CSG_print_hashtable(CSG_hashtable);
  printf("\n");
  SNAP_print_hashtable(SNAP_hashtable);
  printf("\n");
  CP_print_hashtable(CP_hashtable);
  printf("\n");
  CDH_print_hashtable(CDH_hashtable);
  printf("\n");
  CR_print_hashtable(CR_hashtable);
  printf("\n");

  //Let us now implement the delete function for each hashtable:
  //This will delete all the tuples in CSG with student_id 12345:
  char *csg_delete_1[3];
  csg_delete_1[0] = "*";
  csg_delete_1[1] = "12345";
  csg_delete_1[2] = "*";
  delete(csg_delete_1, "CSG");

  //This will delete all the tuples in SNAP with phone 555-1234:
  char *snap_delete_1[4];
  snap_delete_1[0] = "*";
  snap_delete_1[1] = "*";
  snap_delete_1[2] = "*";
  snap_delete_1[3] = "555-1234";
  delete(snap_delete_1, "SNAP");

  //This will delete all the tuples in CP with course CS205 and pre_req CS101:
  char *cp_delete_1[2];
  cp_delete_1[0] = "CS205";
  cp_delete_1[1] = "CS101";
  delete(cp_delete_1, "CP");

  //This will delete all the tuples in CDH with course CS101 and hour 9AM:
  char *cdh_delete_1[3];
  cdh_delete_1[0] = "CS101";
  cdh_delete_1[1] = "*";
  cdh_delete_1[2] = "9AM";
  delete(cdh_delete_1, "CDH");

  //This is delete all the tuples in CR with name CS101 and room Hoyt (so it won't delete any):
  char *cr_delete_1[2];
  cr_delete_1[0] = "CS101";
  cr_delete_1[1] = "Hoyt";
  delete(cr_delete_1, "CR");

  //Let us print out all the hashtables again:
  printf("%s\n", "HASHTABLES, ROUND 2:");
  CSG_print_hashtable(CSG_hashtable);
  printf("\n");
  SNAP_print_hashtable(SNAP_hashtable);
  printf("\n");
  CP_print_hashtable(CP_hashtable);
  printf("\n");
  CDH_print_hashtable(CDH_hashtable);
  printf("\n");
  CR_print_hashtable(CR_hashtable);
}
