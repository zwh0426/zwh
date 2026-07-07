#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_PASSWORD 30
#define MAX_USERS 50
#define MAX_USERNAME 30
#define ROLE_ADMIN 0
#define ROLE_TEACHER 1
#define ROLE_STUDENT 2
typedef struct Student {
    int id;
    char name[MAX_NAME];
    float score;
} Student;
typedef struct User{
    char username[MAX_USERNAME];
    unsigned long password_hash;
    int role;
}User;
User users[MAX_USERS];
int user_count = 0;
User *current_user = NULL;
Student students[MAX_STUDENTS];
int student_count = 0;

/*==================================================
 *  工具函数
 *==================================================*/

unsigned long hashPassword(const char *password) {
    unsigned long hash = 5381;
    int c;
    while ((c = *password++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}//利用哈希加密存储密码

void readPassword(char *buffer,int max_len){
    int index=0;
    char ch;
    while(1){
        ch=getch();
        if(ch=='\r'||ch=='\n'){
            buffer[index]='\0';
            printf("\n");
            break;
        }
        else if(ch=='\b'||ch==127){
            if(index>0){
                index--;
                printf("\b \b");
            }
        }
        else if(index<max_len-1&&ch>=32&&ch<=126){
            buffer[index++]=ch;
            printf("*");
        }
    }
}//隐藏输入密码

/*==================================================
 *  数据读写（不依赖权限）
 *==================================================*/

void saveUsers(){
    FILE *fp=fopen("users.dat","wb");
    if(fp==NULL){
        printf("文件打开失败！\n");
        return;
    }
    fwrite(&user_count,sizeof(int),1,fp);
    fwrite(users,sizeof(User),user_count,fp);
    fclose(fp);
    FILE* txt = fopen("users.txt", "w");
    if (txt != NULL) {
    for (int i = 0; i < user_count; i++) {
        fprintf(txt, "%s %s\n", users[i].username,
            users[i].role == ROLE_ADMIN   ? "管理员" :
            users[i].role == ROLE_TEACHER ? "教师"   : "学生");
    }
        fclose(txt);
}
}//保存用户数据到文件

void loadUsers(){
    FILE *fp=fopen("users.dat","rb");
    if(fp==NULL){
        user_count=0;
        return;
    }
    fread(&user_count,sizeof(int),1,fp);
    fread(users,sizeof(User),user_count,fp);
    fclose(fp);
}//从文件读取用户数据

void loadFromFile(){
    FILE *fp=fopen("students.dat","rb");
    if(fp==NULL){
        printf("文件打开失败！\n");
        return;
    }
    fread(&student_count,sizeof(int),1,fp);
    fread(students,sizeof(Student),student_count,fp);
    fclose(fp);
}//从文件读取数据

/*==================================================
 *  认证与权限
 *==================================================*/

void firstTimeSetup(){
    char password1[MAX_PASSWORD];
    char password2[MAX_PASSWORD];
    printf("\n===== 首次使用，请设置管理员账号 =====\n");
    printf("请输入管理员用户名：");
    scanf("%s", users[0].username);
    do{
        printf("请输入管理员密码：");
        readPassword(password1, MAX_PASSWORD);
        printf("请再次输入管理员密码：");
        readPassword(password2, MAX_PASSWORD);
        if(strcmp(password1,password2)!=0){
            printf("两次输入的密码不一致，请重新输入。\n");
        }
    }while(strcmp(password1,password2)!=0);
    users[0].password_hash=hashPassword(password1);
    users[0].role=ROLE_ADMIN;
    user_count=1;
    saveUsers();
    printf("管理员账号设置成功！请重新启动程序。\n");
    printf("按任意键退出...\n");
    getch();
    exit(0);
}//首次使用设置管理员账号

int login(){
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int attempts=3;

    printf("\n===== 学生成绩管理系统登录 =====\n");

    while(attempts>0){
    printf("\n请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    readPassword(password, MAX_PASSWORD);
    for(int i=0;i<user_count;i++){
        if(strcmp(users[i].username,username)==0&&users[i].password_hash==hashPassword(password)){
            current_user=&users[i];
            printf("登录成功！\n");
            return 1;
        }
    }
    attempts--;
    printf("用户名或密码错误！还剩%d次机会。\n", attempts);
}
    printf("登录失败次数过多，程序将退出。\n");
    return 0;
}//用户登录

int isNotStudent(){
    return current_user->role==ROLE_ADMIN||current_user->role==ROLE_TEACHER;
}//判断当前用户是否为学生

int isAdmin(){
    return current_user->role==ROLE_ADMIN;
}//判断当前用户是否是管理员

/*==================================================
 *  学生操作
 *==================================================*/

void addStudent(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以录入学生信息。\n");
        return;
    }

    if(student_count >= MAX_STUDENTS){
        printf("学生数量已达上限，无法添加更多学生。\n");
        return;
    }

    printf("请输入学号：");
    scanf("%d", &students[student_count].id);
    for(int i = 0; i < student_count; i++) {
        if (students[i].id == students[student_count].id) {
            printf("学号已存在，请重新输入。\n");
            return;
        }
    }
    printf("请输入姓名：");
    scanf("%s",students[student_count].name);
    printf("请输入成绩：");
    scanf("%f", &students[student_count].score);
    if(students[student_count].score<0||students[student_count].score>100){
        printf("成绩应该在0-100之间！\n");
        return;
    }
    student_count++;
    printf("录入成功!\n");
}//录入学生成绩/信息

void deleteStudent(){
    if(!isAdmin()){
        printf("权限不足！只有管理员可以删除学生信息。\n");
        return;
    }
    int targetid,i,j;
    int found = 0;
    printf("请输入要删除的学生学号：");
    scanf("%d", &targetid);
    for(i = 0; i < student_count; i++){
        if(students[i].id == targetid){
            for(j = i; j < student_count - 1; j++){
                students[j] = students[j + 1];
            }
            student_count--;
            found = 1;
            printf("删除成功!\n");
            break;
        }
    }
    if(!found){
        printf("未找到该学号的学生。\n");
    }
}//删除学生

void modifyscore(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以修改学生成绩。\n");
        return;
    }
    int targetid;
    float newscore;
    int found = 0;
    printf("请输入要修改成绩的学生学号：");
    scanf("%d", &targetid);
    for(int i=0;i<student_count;i++){
        if(students[i].id==targetid){
            printf("当前成绩：%0.2f\n",students[i].score);
            printf("请输入新的成绩：");
            scanf("%f",&newscore);
            students[i].score=newscore;
            found=1;
            printf("成绩修改成功!\n");
            break;
        }
    }
    if(!found){
        printf("未找到该学号的学生。\n");
    }
}//修改学生成绩

void queryById(){
    int targetid;
    printf("请输入查询学号：");
    scanf("%d", &targetid);
    for(int i=0;i<student_count;i++){
        if(students[i].id==targetid){
            printf("学号：%d\n姓名：%s\n成绩：%.2f\n",students[i].id,students[i].name,students[i].score);
            return;
        }
    }
    printf("未找到该学生！\n");
}//按学号查询

void displayAllStudents(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以查看所有学生信息。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        return;
    }
    printf("\n%-8s %-20s %-10s\n", "学号", "姓名", "成绩");
    printf("----------------------------------------\n");
    for(int i=0;i<student_count;i++){
        printf("%-8d %-20s %-10.2f\n", students[i].id, students[i].name, students[i].score);
    }
    printf("----------------------------------------\n");
}//查询所有学生成绩/信息

void sortByScore(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以按成绩排序。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        return;
    }
    for(int i=0;i<student_count-1;i++){
        for(int j=0;j<student_count-i-1;j++){
            if(students[j].score<students[j+1].score){
                Student temp=students[j];
                students[j]=students[j+1];
                students[j+1]=temp;
            }
        }
    }
    printf("按成绩排序成功!\n");
}//按成绩排序

void sortById(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以按学号排序。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        return;
    }
    for(int i=0;i<student_count-1;i++){
        for(int j=0;j<student_count-i-1;j++){
            if(students[j].id>students[j+1].id){
                Student temp=students[j];
                students[j]=students[j+1];
                students[j+1]=temp;
            }
        }
    }
    printf("按学号排序成功!\n");
}//按学号排序

void calculateAverage(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以计算平均成绩。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        return;
    }
    float sum=0.0f;
    for(int i=0;i<student_count;i++){
        sum+=students[i].score;
    }
    printf("平均成绩：%.2f\n",sum/student_count);
}//计算平均成绩

void saveToFile(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以保存数据到文件。\n");
        return;
    }
    FILE *fp=fopen("students.dat","wb");
    if(fp==NULL){
        printf("文件打开失败！\n");
        return;
    }
    fwrite(&student_count,sizeof(int),1,fp);
    fwrite(students,sizeof(Student),student_count,fp);
    fclose(fp);
    printf("数据已保存到文件。\n");
    FILE* txt = fopen("students.txt", "w");
    if (txt != NULL) {
    fprintf(txt, "学号\t姓名\t成绩\n");
    for (int i = 0; i < student_count; i++) {
        fprintf(txt, "%d %s %.2f\n",
                students[i].id, students[i].name, students[i].score);
    }
        fclose(txt);
}
}//保存到文件

/*==================================================
 *  用户管理
 *==================================================*/

void listUsers(){
    if(!isAdmin()){
        printf("权限不足！只有管理员可以查看所有用户。\n");
        return;
    }
    if(user_count==0){
        printf("暂无用户数据。\n");
        return;
    }
    printf("\n%-20s %-10s\n", "用户名", "角色");
    printf("------------------------------\n");
    for(int i=0;i<user_count;i++){
        printf("%-20s %-10s\n", users[i].username,
               users[i].role == ROLE_ADMIN ? "管理员" :
               (users[i].role == ROLE_TEACHER ? "教师" : "学生"));
    }
    printf("------------------------------\n");
}//查看所有用户

void addUser(){
    if(!isAdmin()){
        printf("权限不足！只有管理员可以添加用户。\n");
        return;
    }
    if(user_count >= MAX_USERS){
        printf("用户数量已达上限，无法添加更多用户。\n");
        return;
    }
    char username[MAX_USERNAME];
    char password1[MAX_PASSWORD];
    char password2[MAX_PASSWORD];
    int role;

    printf("请输入新用户名：");
    scanf("%s", username);

    for(int i=0;i<user_count;i++){
        if(strcmp(users[i].username,username)==0){
            printf("用户名已存在，请重新输入。\n");
            return;
        }
    }
    do{
        printf("请输入密码：");
        readPassword(password1, MAX_PASSWORD);
        printf("请再次输入密码：");
        readPassword(password2, MAX_PASSWORD);
        if(strcmp(password1,password2)!=0){
            printf("两次输入的密码不一致，请重新输入。\n");
        }
    }while(strcmp(password1,password2)!=0);

    printf("请选择角色（0-管理员，1-教师，2-学生）：");
    scanf("%d", &role);
    if(role<0||role>2){
        printf("无效角色选择。\n");
        return;
    }

    strcpy(users[user_count].username, username);
    users[user_count].password_hash = hashPassword(password1);
    users[user_count].role = role;
    user_count++;
    saveUsers();
    printf("用户添加成功！\n");
}//添加用户

void deleteUser(){
    listUsers();
    if(user_count==0) return;

    int index;
    printf("请输入要删除的用户序号：");
    scanf("%d",&index);

    if(index<1||index>user_count){
        printf("无效的序号！\n");
        return;
    }

    if(&users[index-1]==current_user){
        printf("不能删除自己！");
        return;
    }

    printf("确定删除该用户%s吗?（y/n）：",users[index-1].username);
    char confirm;
    scanf(" %c",&confirm);
    if(confirm!='y'&&confirm!='Y'){
        printf("已取消删除。\n");
        return;
    }

    for(int i=index-1;i<user_count-1;i++){
        users[i]=users[i+1];
    }
    user_count--;
    saveUsers();
    printf("用户删除成功！\n");
}

void resetUserPassword() {
    listUsers();
    if (user_count == 0) return;

    int index;
    printf("请输入要重置密码的用户序号：");
    scanf("%d", &index);

    if (index < 1 || index > user_count) {
        printf("无效的序号！\n");
        return;
    }

    char password1[MAX_PASSWORD], password2[MAX_PASSWORD];
    do {
        printf("请输入新密码：");
        readPassword(password1, MAX_PASSWORD);
        printf("请再次输入新密码：");
        readPassword(password2, MAX_PASSWORD);
        if (strcmp(password1, password2) != 0) {
            printf("两次密码不一致，请重新输入。\n");
        }
    } while (strcmp(password1, password2) != 0);

    users[index - 1].password_hash = hashPassword(password1);
    saveUsers();
    printf("密码重置成功！\n");
}

/*==================================================
 *  菜单与入口
 *==================================================*/

void userManagement(){
    int choice;

    while(1){
        printf("\n==== 用户管理 ====\n");
        printf("1.查看所有用户\n");
        printf("2.添加用户\n");
        printf("3.删除用户\n");
        printf("4.重置用户密码\n");
        printf("0.退出\n");
        scanf("%d", &choice);
        if(choice<0||choice>4){
            printf("无效选择，请重新输入。\n");
            continue;
        }
        switch(choice){
            case 1: listUsers();          break;
            case 2: addUser();            break;
            case 3: deleteUser();         break;
            case 4: resetUserPassword();  break;
            case 0: return;
        }
    }
}//子菜单

int menu(){
    char input[10];
    int choice;

        while(1) {
        printf("\n==== 学生成绩管理系统 ====\n");
        printf("当前用户：%s (角色：%s)\n", current_user->username,
               current_user->role == ROLE_ADMIN ? "管理员" :
               (current_user->role == ROLE_TEACHER ? "教师" : "学生"));
        printf("--------------------------------\n");

        if(isNotStudent()) {
            printf("1. 录入学生成绩\n");
            printf("2. 删除学生信息\n");
            printf("3. 修改学生成绩\n");
            printf("5. 查询所有学生成绩\n");
            printf("6. 按成绩排序\n");
            printf("7. 按学号排序\n");
            printf("8. 计算平均成绩\n");
            printf("9. 保存数据到文件\n");
        }
        printf("4. 按学号查询\n");
        if(isAdmin()) {
            printf("10. 用户设置\n");
        }
        printf("0. 退出系统\n");
        scanf("%s", input);
        choice = atoi(input);
        if(!isNotStudent()&&choice!=4&&choice!=0){
            printf("权限不足！请重新选择。\n");
            continue;
        }
        switch(choice){
            case 1:  addStudent();         break;
            case 2:  deleteStudent();      break;
            case 3:  modifyscore();        break;
            case 4:  queryById();          break;
            case 5:  displayAllStudents(); break;
            case 6:  sortByScore();        break;
            case 7:  sortById();           break;
            case 8:  calculateAverage();   break;
            case 9:  saveToFile();         break;
            case 10: userManagement();     break;
            case 0:
                if(isNotStudent()){
                    saveToFile();
                    printf("数据已自动保存。\n");
                }
                printf("感谢使用学生成绩管理系统！\n");
                return 0;//如果不是学生退出自动保存数据
            default:
                printf("无效选择，请重新输入。\n");
        }
    }
}//主菜单

int main(){
    loadUsers();
    if(user_count==0){
        firstTimeSetup();
    }
    if(!login()){
        return 0;
    }
    loadFromFile();
    menu();
    return 0;
}
