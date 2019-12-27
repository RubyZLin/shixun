#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"llist.h"
#include"student.h"

typedef struct {
    int id;
    char name[20];
    int score;
}STUDENT;
typedef struct {
    int id;
    char name[20];
    int num;
    LLIST *studentlist;
}CLASS;

LLIST *classlist = NULL;

int main() {
    classlist_creat();
    menu_main();
    return 0;
}

int student_id_cmp(void *data, void *record) {
    STUDENT *t1 = (STUDENT *) data;
    int *t2 = (int *) record;
    if(t1->id == (*t2)) return 1;
    else return 0;
}
int student_name_cmp(void *data, void *record) {
    STUDENT *t1 = (STUDENT *) data;
    char *t2 = (char *) record;
    if(strcmp(t1->name, t2) == 0) return 1;
    else return 0;
}
int student_score_cmp(void *data, void *record) {
    STUDENT *t1 = (STUDENT *) data;
    int *t2 = (int *) record;
    if(t1->id == (*t2)) return 1;
    else return 0;
}
void student_print(void *data) {
    STUDENT *st = (STUDENT *) data;
    printf("学号：%d\t\t姓名：%s\t\t成绩：%d\n", st->id, st->name, st->score);
}
int class_id_cmp(void *data, void *record) {
    CLASS *t1 = (CLASS *) data;
    int *t2 = (int *) record;
    if(t1->id == (*t2)) return 1;
    else return 0;
}
int class_name_cmp(void *data, void *record) {
    CLASS *t1 = (CLASS *) data;
    char *t2 = (char *) record;
    if(strcmp(t1->name, t2) == 0) return 1;
    else return 0;
}
void class_print(void *data) {
    CLASS *cl = (CLASS *) data;
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("班级编号：%d\n", cl->id);
    printf("班级名称：%s\n", cl->name);
    printf("班级人数：%d\n", cl->num);
    llist_print_all(cl->studentlist, student_print);
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}
void class_add() {
    CLASS newclass;
    printf("请输入班级编号：");
    scanf("%d", &newclass.id);
    printf("请输入班级名称：");
    scanf("%s", newclass.name);
    system("clear");
    newclass.num = 0;
    newclass.studentlist = llist_creat(sizeof(STUDENT));
    while(1) {
        STUDENT newstudent;
        printf("请输入学生编号：(输入-1结束)");
        scanf("%d", &newstudent.id);
        if(newstudent.id == -1) break;
        printf("请输入学生姓名：");
        scanf("%s", newstudent.name);
        printf("请输入学生成绩：");
        scanf("%d", &newstudent.score);
        system("clear");
        llist_insert_back(newclass.studentlist, &newstudent);
        newclass.num++;
    }
    llist_insert_back(classlist, &newclass);
}
void class_delete() {
    while(1) {
        printf("1.按班级编号删除\n");
        printf("2.按班级名称删除\n");
        printf("0.返回上一级\n");
        int op;
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 2) continue;
        if(op == 0) break;
        int flag;
        switch(op) {
            case 1: {
                int id;
                printf("请输入班级编号：");
                scanf("%d", &id);
                flag = llist_delete(classlist, &id, class_id_cmp);
            } break;
            case 2: {
                char name[20];
                printf("请输入班级名称：");
                scanf("%s", name);
                flag = llist_delete(classlist, name, class_name_cmp);
            } break;
        }
        if(flag == 0) printf("没有该班级信息！\n");
        else printf("删除成功！\n");
    }
}
void class_updata() {
    while(1) {
        CLASS *nowclass = class_find();
        if(nowclass == NULL) break;
        printf("请输入新的班级编号：");
        scanf("%d", &nowclass->id);
        printf("请输入新的班级名称：");
        scanf("%s", nowclass->name);
        system("clear");
    }
}
void *class_find() {
    while(1) {
        printf("1.按班级编号查找\n");
        printf("2.按班级名称查找\n");
        printf("0.返回上一级\n");
        int op;
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 2) continue;
        if(op == 0) return NULL;
        CLASS *nowclass;
        switch(op) {
            case 1: {
                printf("请输入班级编号：");
                int id;
                scanf("%d", &id);
                nowclass = llist_find(classlist, &id, class_id_cmp);
            } break;
            case 2: {
                printf("请输入班级名称：");
                char name[20];
                scanf("%s", name);
                nowclass = llist_find(classlist, name, class_name_cmp);
            } break;
        }
        if(nowclass == NULL) {
            printf("没有该班级信息！\n");
            continue;
        }
        return nowclass;
    }
}
void class_query() {
    while(1) {
        CLASS *nowclass = class_find();
        if(nowclass == NULL) break;
        printf("************************\n");
        class_print(nowclass);
        printf("************************\n");
    }
}
void classlist_creat() {
    classlist = llist_creat(sizeof(CLASS));
}
void student_add(void *ptr) {
    CLASS *nowclass = (CLASS *) ptr;
    STUDENT newstudent;
    printf("请输入学生学号：");
    scanf("%d", &newstudent.id);
    printf("请输入学生姓名：");
    scanf("%s", newstudent.name);
    printf("请输入学生成绩：");
    scanf("%d", &newstudent.score);
    nowclass->num++;
    llist_insert_back(nowclass->studentlist, &newstudent);
}
void *student_find(void *ptr) {
    CLASS *nowclass = (CLASS *) ptr;
    while(1) {
        printf("1.按学生学号查找\n");
        printf("2.按学生姓名查找\n");
        printf("0.返回上一级\n");
        int op;
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 2) continue;
        if(op == 0) return NULL;
        STUDENT *nowstudent;
        switch(op) {
            case 1: {
                printf("请输入学生学号：");
                int id;
                scanf("%d", &id);
                nowstudent = llist_find(nowclass->studentlist, &id, student_id_cmp);
            } break;
            case 2: {
                printf("请输入学生姓名：");
                char name[20];
                scanf("%s", name);
                nowstudent = llist_find(nowclass->studentlist, name, student_name_cmp);
            } break;
        }
        if(nowstudent == NULL) {
            printf("没有该学生信息！\n");
            continue;
        }
        return nowstudent;
    }
}
void student_delete(void *ptr) {
    CLASS *nowclass = (CLASS *) ptr;
    while(1) {
        printf("1.按学生学号删除\n");
        printf("2.按学生姓名删除\n");
        printf("0.返回上一级\n");
        int op;
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 2) continue;
        if(op == 0) return;
        STUDENT *nowstudent;
        int flag;
        switch(op) {
            case 1: {
                printf("请输入要查询的学生学号：");
                int id;
                scanf("%d", &id);
                flag = llist_delete(nowclass->studentlist, &id, student_id_cmp);
            } break;
            case 2: {
                printf("请输入要查询的学生姓名：");
                char name[20];
                scanf("%s", name);
                flag = llist_delete(nowclass->studentlist, name, student_name_cmp);
            } break;
        }
        if(flag == 0) printf("没有该学生信息！\n");
        else printf("删除成功！\n");
    }
}
void student_query(void *ptr) {
    CLASS *nowclass = (CLASS *) ptr;
    while(1) {
        STUDENT *nowstudent = student_find(nowclass);
        if(nowstudent == NULL) break;
        printf("************************\n");
        student_print(nowstudent);
        printf("************************\n");
    }
}
void student_updata(void *ptr) {
    CLASS *nowclass = (CLASS *) ptr;
    while(1) {
        STUDENT *nowstudent = student_find(nowclass);
        if(nowstudent == NULL) break;
        printf("请输入新的学生学号：");
        scanf("%d", &nowstudent->id);
        printf("请输入新的学生姓名：");
        scanf("%s", nowstudent->name);
        printf("请输入新的学生成绩：");
        scanf("%d", &nowstudent->score);
        system("clear");
    }
}
void menu_student() {
    printf("请输入学生所在班级编号：");
    int id;
    scanf("%d", &id);
    system("clear");
    CLASS *nowclass = llist_find(classlist, &id, class_id_cmp);
    if(nowclass == NULL) {
        printf("没有该班级！\n");
        return;
    }
    int op;
    while(1) {
        printf("************************\n");
        printf("|    1.添加学生信息    |\n");
        printf("|    2.删除学生信息    |\n");
        printf("|    3.查询学生信息    |\n");
        printf("|    4.修改学生信息    |\n");
        printf("|    0.返回上一级      |\n");
        printf("************************\n");
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 4) {
            printf("输入错误!\n");
            continue;
        }
        if(op == 0) break;
        switch(op) {
            case 1: student_add(nowclass); break;
            case 2: student_delete(nowclass); break;
            case 3: student_query(nowclass); break;
            case 4: student_updata(nowclass); break;
        }
    }
}
void menu_class() {
    int op;
    while(1) {
        printf("************************\n");
        printf("|    1.添加新的班级    |\n");
        printf("|    2.删除班级信息    |\n");
        printf("|    3.修改班级信息    |\n");
        printf("|    4.查询班级信息    |\n");
        printf("|    0.返回上一级      |\n");
        printf("************************\n");
        printf("请输入需要进行的操作: ");
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 4) {
            printf("输入错误!\n");
            continue;
        }
        if(op == 0) break;
        switch(op) {
            case 1: class_add(); break;
            case 2: class_delete(); break;
            case 3: class_updata(); break;
            case 4: class_query(); break;
        }
    }
}
void list_clear() {
    list_node *p = classlist->head.next;
    CLASS *t;
    while(p != &classlist->head) {
        t = (CLASS *) p->data;
        llist_clear(t->studentlist);
        p = p->next;
    }
    llist_clear(classlist);
    classlist_creat();
}
void menu_main() {
    printf("欢迎来到学生管理系统！\n\n");
    while(1) {
        printf("************************\n");
        printf("|    1.操作学生信息    |\n");
        printf("|    2.操作班级信息    |\n");
        printf("|    3.输出全部信息    |\n");
        printf("|    4.初始化          |\n");
        printf("|    0.退出            |\n");
        printf("************************\n");
        printf("请输入需要进行的操作: ");
        int op;
        scanf("%d", &op);
        system("clear");
        if(op < 0 || op > 4) {
            printf("输入错误!\n");
            continue;
        }
        if(op == 0) break;
        switch(op) {
            case 1: menu_student(); break;
            case 2: menu_class(); break;
            case 3: llist_print_all(classlist, class_print); break;
            case 4: list_clear(); break;
        }
    }
}


