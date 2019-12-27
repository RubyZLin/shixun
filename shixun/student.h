#ifndef STUDENT_H
#define STUDENT_H

extern LLIST *classlist;
int student_id_cmp(void *data, void *record); //按学生学号比较
int student_name_cmp(void *data, void *record); //按学生姓名比较
int student_score_cmp(void *data, void *record); //按学生成绩比较
void student_print(void *data); //输出学生信息
void class_print(void *data); //输出班级信息
int class_id_cmp(void *data, void *record); //按班级编号比较
int class_name_cmp(void *data, void *record); //按班级名称比较
void class_add(); //添加新的班级
void class_delete(); //删除班级信息
void class_updata(); //修改班级信息
void *class_find(); //查找班级位置
void class_query(); //查询班级信息
void *student_find(void *ptr); //查找学生位置
void student_add(void *ptr); //添加学生信息
void student_delete(void *ptr); //删除学生信息
void student_query(void *ptr); //查询学生信息
void student_updata(void *ptr); //更新学生信息
void classlist_creat(); //创建新的班级头节点
void list_clear(); //初始化所有信息
void menu_main(); //主页面
void menu_student(); //学生操作页面
void menu_class(); //班级操作页面

#endif