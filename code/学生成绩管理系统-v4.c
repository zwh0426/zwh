#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_PASSWORD 30
#define MAX_USERS 50
#define MAX_USERNAME 30
#define MAX_COURSES 10
#define MAX_COURSE_NAME 30
#define ROLE_ADMIN 0
#define ROLE_TEACHER 1
#define ROLE_STUDENT 2
typedef struct{
    char name[MAX_COURSE_NAME];
    float score;
}Course;
typedef struct Student {
    int id;
    char name[MAX_NAME];
    Course courses[MAX_COURSES];
    int course_count;
    float average;
} Student;
typedef struct User{
    char username[MAX_USERNAME];
    unsigned long password_hash;
    int role;
    unsigned long security_key_hash;
}User;
User users[MAX_USERS];
int user_count = 0;
User *current_user = NULL;
Student students[MAX_STUDENTS];
int student_count = 0;
int session_add = 0;
int session_delete = 0;
int session_modify = 0;

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

void generateKey(char* key){
    const char chars[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for(int i=0;i<14;i++){
        if(i==4||i==9){
            key[i]='-';
        }
        else{
            key[i]=chars[rand()%36];
        }
    }
    key[14]='\0';
}//生成密钥

void clearBuffer(){
    while (getchar()!='\n');
}//清空输入缓冲区

int readInt(const char* prompt){
    int value;
    while(1){
        printf("%s",prompt);
        if(scanf("%d",&value)==1){
            clearBuffer();
            return value;
        }
        printf("输入无效，请输入数字！\n");
        clearBuffer();
    }
}//读入整型，防止程序崩溃

float readFloat(const char* prompt){
    float value;
    while(1){
        printf("%s",prompt);
        if(scanf("%f",&value)==1){
            clearBuffer();
            return value;
        }
        printf("输入无效，请输入有效数字！\n");
        clearBuffer();
    }
}//读入浮点型，防止程序崩溃

void pause(){
    printf("\n按任意键返回菜单...");
    getch();
}//退出函数

void writeLog(const char* action){
    FILE* fp = fopen("operation.log", "a");
    if (fp == NULL) return;
    
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    time_str[24] = '\0';//去掉换行
    
    fprintf(fp, "[%s] %s: %s\n", time_str, current_user->username, action);
    fclose(fp);
}//操作日志

void viewLog(){
    printf("\n====操作日志====\n\n");
    FILE* fp=fopen("operation.log","r");
    if(fp==NULL){
        printf("暂无日志记录。\n");
        pause();
        return;
    }
    char line[256];
    int count=0;
    while(fgets(line,sizeof(line),fp)!=NULL){
        printf("%s",line);
        count++;
    }
    fclose(fp);
    if(count==0){
        printf("暂无日志记录.\n");
    }
    pause();
}//查看日志

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

void updateAverage(Student* s){
    if(s->course_count==0){
        s->average=0;
        return;
    }
    float sum=0;
    for(int i=0;i<s->course_count;i++){
        sum+=s->courses[i].score;
    }
    s->average=sum/s->course_count;
}//更新平均分

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
    char key[15];
    generateKey(key);
    users[0].security_key_hash=hashPassword(key);
    printf("\n你的安全密钥是：%s\n",key);
    printf("请务必记下，可用它充当密码登录与修改密码凭证");
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
        if(strcmp(users[i].username,username)==0){
            unsigned long input_hash = hashPassword(password);
            if(users[i].password_hash==input_hash||users[i].security_key_hash==input_hash){
                current_user=&users[i];
                printf("登录成功！\n");
                return 1;
            }
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

void saveToFile();
int searchStudents(const char* keyword, int* indices);

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

    students[student_count].id = readInt("请输入学号：");
    for(int i = 0; i < student_count; i++) {
        if (students[i].id == students[student_count].id) {
            printf("学号已存在，请重新输入。\n");
            return;
        }
    }
    printf("请输入姓名：");
    scanf("%s", students[student_count].name);
    students[student_count].course_count = 0;

    printf("\n开始录入各科成绩（课程名输入 0 结束）\n");
    while (1) {
        char course_name[MAX_COURSE_NAME];
        printf("请输入课程名：");
        scanf("%s", course_name);
        if (strcmp(course_name, "0") == 0) break;

        if (students[student_count].course_count >= MAX_COURSES) {
            printf("已达最大科目数(%d)！\n", MAX_COURSES);
            break;
        }

        float score = readFloat("请输入成绩：");
        if (score < 0 || score > 100) {
            printf("成绩应在0-100之间！\n");
            continue;
        }

        int idx = students[student_count].course_count;
        strcpy(students[student_count].courses[idx].name, course_name);
        students[student_count].courses[idx].score = score;
        students[student_count].course_count++;
    }

    if (students[student_count].course_count == 0) {
        printf("未录入任何成绩，放弃添加该学生。\n");
        return;
    }

    updateAverage(&students[student_count]);
    student_count++;
    session_add++;
    printf("录入成功！共 %d 科成绩，均分 %.2f\n",
           students[student_count - 1].course_count,
           students[student_count - 1].average);
    char log_msg[100];
    sprintf(log_msg, "录入学生 %d %s", students[student_count-1].id, students[student_count-1].name);
    writeLog(log_msg);
    saveToFile();
    pause();
}//录入学生成绩/信息

void deleteStudent(){
    if(!isAdmin()){
        printf("权限不足！只有管理员可以删除学生信息。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        pause();
        return;
    }

    printf("请输入要删除的学生学号或姓名关键字：");
    char keyword[50];
    scanf("%s", keyword);

    int indices[MAX_STUDENTS];
    int count = searchStudents(keyword, indices);

    if(count == 0){
        printf("未找到匹配的学生！\n");
        pause();
        return;
    }

    printf("\n找到 %d 个匹配：\n", count);
    for(int k = 0; k < count; k++){
        int i = indices[k];
        printf("%d. 学号：%d  姓名：%s  均分：%.2f\n",
               k+1, students[i].id, students[i].name, students[i].average);
    }

    int sel;
    if(count == 1){
        sel = 1;
        printf("\n自动选中该学生。\n");
    } else {
        sel = readInt("请选择要删除的学生序号（0 取消）：");
        if(sel == 0) return;
        if(sel < 1 || sel > count){
            printf("无效序号！\n");
            pause();
            return;
        }
    }

    int idx = indices[sel - 1];
    printf("确定删除学生 %d %s 吗？（y/n）：",
           students[idx].id, students[idx].name);
    char confirm;
    scanf(" %c", &confirm);
    if(confirm != 'y' && confirm != 'Y'){
        printf("已取消删除。\n");
        pause();
        return;
    }

    int del_id = students[idx].id;
    for(int j = idx; j < student_count - 1; j++){
        students[j] = students[j + 1];
    }
    student_count--;
    session_delete++;
    printf("删除成功!\n");
    {char log_msg[50]; sprintf(log_msg, "删除了学生 %d", del_id); writeLog(log_msg);}
    saveToFile();
    pause();
}//删除学生

void modifyscore(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以修改学生成绩。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        pause();
        return;
    }

    printf("请输入要修改成绩的学生学号或姓名关键字：");
    char keyword[50];
    scanf("%s", keyword);

    int indices[MAX_STUDENTS];
    int count = searchStudents(keyword, indices);

    if(count == 0){
        printf("未找到匹配的学生！\n");
        pause();
        return;
    }

    printf("\n找到 %d 个匹配：\n", count);
    for(int k = 0; k < count; k++){
        int i = indices[k];
        printf("%d. 学号：%d  姓名：%s  均分：%.2f\n",
               k+1, students[i].id, students[i].name, students[i].average);
    }

    int sel;
    if(count == 1){
        sel = 1;
        printf("\n自动选中该学生。\n");
    } else {
        sel = readInt("请选择要修改的学生序号（0 取消）：");
        if(sel == 0) return;
        if(sel < 1 || sel > count){
            printf("无效序号！\n");
            pause();
            return;
        }
    }

    int idx = indices[sel - 1];
    if(students[idx].course_count == 0){
        printf("该学生暂无成绩记录。\n");
        pause();
        return;
    }

    printf("\n%s 的当前成绩：\n", students[idx].name);
    for(int j = 0; j < students[idx].course_count; j++){
        printf("  %d. %s：%.2f\n", j+1,
               students[idx].courses[j].name,
               students[idx].courses[j].score);
    }

    int course_idx = readInt("请选择要修改的科目序号：");
    if(course_idx < 1 || course_idx > students[idx].course_count){
        printf("无效序号！\n");
        pause();
        return;
    }
    course_idx--;

    float newscore = readFloat("请输入新的成绩：");
    if(newscore < 0 || newscore > 100){
        printf("成绩应该在0-100之间！\n");
        pause();
        return;
    }

    students[idx].courses[course_idx].score = newscore;
    updateAverage(&students[idx]);
    session_modify++;
    printf("成绩修改成功! 当前均分：%.2f\n", students[idx].average);
    {char log_msg[60]; sprintf(log_msg, "修改了学生 %d %s 科成绩为 %.2f",
        students[idx].id, students[idx].courses[course_idx].name, newscore);
        writeLog(log_msg);}
    saveToFile();
    pause();
}//修改学生成绩

int searchStudents(const char* keyword, int* indices) {
    int count = 0;
    char id_str[20];
    for (int i = 0; i < student_count; i++) {
        sprintf(id_str, "%d", students[i].id);
        if (strstr(id_str, keyword) || strstr(students[i].name, keyword)) {
            indices[count++] = i;
        }
    }
    return count;
}

void queryById(){
    printf("请输入学号或姓名关键字：");
    char keyword[50];
    scanf("%s", keyword);

    int indices[MAX_STUDENTS];
    int count = searchStudents(keyword, indices);

    if (count == 0) {
        printf("未找到匹配的学生！\n");
        pause();
        return;
    }

    printf("\n找到 %d 个匹配：\n", count);
    for (int k = 0; k < count; k++) {
        int i = indices[k];
        printf("\n学号：%d  姓名：%s  均分：%.2f\n",
               students[i].id, students[i].name, students[i].average);
        if (students[i].course_count > 0) {
            printf("各科成绩：\n");
            for (int j = 0; j < students[i].course_count; j++) {
                printf("  %-20s  %.2f\n",
                       students[i].courses[j].name,
                       students[i].courses[j].score);
            }
        }
    }
    pause();
}//按学号或姓名搜索

void displayAllStudents(){
    if(!isNotStudent()){
        printf("权限不足！只有管理员和教师可以查看所有学生信息。\n");
        return;
    }
    if(student_count==0){
        printf("暂无学生数据。\n");
        return;
    }
    printf("\n%-8s  %-16s  %-4s  %-6s\n", "学号", "姓名", "科数", "均分");
    printf("------------------------------------------\n");
    for(int i=0;i<student_count;i++){
        printf("%-8d  %-16s  %-4d  %-6.2f\n",
               students[i].id, students[i].name,
               students[i].course_count, students[i].average);
    }
    printf("------------------------------------------\n");
    pause();
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
            if(students[j].average<students[j+1].average){
                Student temp=students[j];
                students[j]=students[j+1];
                students[j+1]=temp;
            }
        }
    }
    printf("按均分排序成功!\n");
    pause();
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
    printf("按学号排序成功!请查看结果！\n");
    pause();
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
        sum+=students[i].average;
    }
    printf("全班均分：%.2f（共 %d 人）\n",sum/student_count, student_count);
    pause();
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
    fprintf(txt, "学号\t姓名\t科数\t均分\t各科详情\n");
    for (int i = 0; i < student_count; i++) {
        fprintf(txt, "%d\t%s\t%d\t%.2f",
                students[i].id, students[i].name,
                students[i].course_count, students[i].average);
        for(int j=0;j<students[i].course_count;j++){
            fprintf(txt, "\t%s:%.2f",
                    students[i].courses[j].name,
                    students[i].courses[j].score);
        }
        fprintf(txt, "\n");
    }
        fclose(txt);
}
}//保存到文件

/*==================================================
 *  用户管理
 *==================================================*/

int findUserByUsername(const char* username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

int searchUsers(const char* keyword, int* indices) {
    int count = 0;
    for (int i = 0; i < user_count; i++) {
        if (strstr(users[i].username, keyword)) {
            indices[count++] = i;
        }
    }
    return count;
}

int selectUser(const char* action) {
    printf("请输入要%s的用户名关键字：", action);
    char keyword[MAX_USERNAME];
    scanf("%s", keyword);

    int indices[MAX_USERS];
    int count = searchUsers(keyword, indices);

    if (count == 0) {
        printf("未找到匹配的用户！\n");
        return -1;
    }

    printf("\n找到 %d 个匹配：\n", count);
    for (int k = 0; k < count; k++) {
        printf("%d. %s（%s）\n", k + 1, users[indices[k]].username,
               users[indices[k]].role == ROLE_ADMIN   ? "管理员" :
               users[indices[k]].role == ROLE_TEACHER ? "教师"   : "学生");
    }

    if (count == 1) return indices[0];

    int sel = readInt("请选择序号（0 取消）：");
    if (sel == 0 || sel < 1 || sel > count) return -1;
    return indices[sel - 1];
}

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

    role = readInt("请选择角色（0-管理员，1-教师，2-学生）：");
    if(role<0||role>2){
        printf("无效角色选择。\n");
        return;
    }

    strcpy(users[user_count].username, username);
    users[user_count].password_hash = hashPassword(password1);
    users[user_count].role = role;

    char key[15];
    generateKey(key);
    users[user_count].security_key_hash = hashPassword(key);
    printf("\n该用户的安全密钥是：%s\n", key);
    printf("请告知用户妥善保管！\n");

    user_count++;
    saveUsers();
    printf("用户添加成功！\n");
    {char log_msg[60]; sprintf(log_msg, "添加了用户 %s", username); writeLog(log_msg);}
    pause();
}//添加用户

void deleteUser(){
    if(user_count==0){
        printf("暂无用户数据。\n");
        pause();
        return;
    }
    listUsers();

    int idx = selectUser("删除");
    if(idx == -1){ printf("已取消。\n"); pause(); return; }

    if(&users[idx]==current_user){
        printf("不能删除自己！\n");
        pause();
        return;
    }

    printf("确定删除用户 %s 吗？（y/n）：", users[idx].username);
    char confirm;
    scanf(" %c", &confirm);
    if(confirm!='y'&&confirm!='Y'){
        printf("已取消删除。\n");
        pause();
        return;
    }

    char deleted_name[MAX_USERNAME];
    strcpy(deleted_name, users[idx].username);
    for(int i=idx; i<user_count-1; i++){
        users[i]=users[i+1];
    }
    user_count--;
    saveUsers();
    printf("用户 %s 已删除！\n", deleted_name);
    {char log_msg[60]; sprintf(log_msg, "删除了用户 %s", deleted_name); writeLog(log_msg);}
    pause();
}//删除用户

void resetUserPassword() {
    if(user_count == 0){
        printf("暂无用户数据。\n");
        pause();
        return;
    }
    listUsers();

    int idx = selectUser("重置密码");
    if(idx == -1){ printf("已取消。\n"); pause(); return; }

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

    users[idx].password_hash = hashPassword(password1);
    saveUsers();
    printf("用户 %s 的密码已重置！\n", users[idx].username);
    {char log_msg[60]; sprintf(log_msg, "重置了用户 %s 的密码", users[idx].username); writeLog(log_msg);}
    pause();
}//管理员重置密码

void resetUserkey(){
    if(user_count == 0){
        printf("暂无用户数据。\n");
        pause();
        return;
    }
    listUsers();

    int idx = selectUser("重置密钥");
    if(idx == -1){ printf("已取消。\n"); pause(); return; }

    char key[15];
    generateKey(key);
    users[idx].security_key_hash = hashPassword(key);
    saveUsers();

    printf("用户 %s 的密钥已重置。\n", users[idx].username);
    printf("新安全密钥是：%s\n", key);
    printf("请告知用户妥善保管！\n");
    {char log_msg[60]; sprintf(log_msg, "重置了用户 %s 的密钥", users[idx].username); writeLog(log_msg);}
    pause();
}//重置密钥

void changeMyPassword(){
    char key[15];
    char password1[MAX_PASSWORD],password2[MAX_PASSWORD];

    printf("\n====修改密码====\n");

    printf("请输入安全密钥：");
    scanf("%s",key);

    if(current_user->security_key_hash!=hashPassword(key)){
        printf("安全密钥错误！\n");
        printf("请联系管理员重置密码和安全密钥。\n");
        pause();
        return;
    }
    do{
        printf("请输入新密码：");
        readPassword(password1,MAX_PASSWORD);
        printf("请再次输入新密码：");
        readPassword(password2, MAX_PASSWORD);
        if (strcmp(password1, password2) != 0) {
            printf("两次密码不一致，请重新输入。\n");
    }
    }while(strcmp(password1,password2)!=0);

    current_user->password_hash=hashPassword(password1);
    saveUsers();
    printf("密码修改成功！\n");
    pause();
}//修改密码


typedef void (*MenuFunc)();

typedef struct {
    char label[30];
    MenuFunc func;
    int needNotStudent;
    int needAdmin;
} MenuItem;//动态菜单结构体

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
        printf("5.重置用户密钥\n");
        printf("0.退出\n");
        choice = readInt("请选择：");
        if(choice<0||choice>5){
            printf("无效选择，请重新输入。\n");
            continue;
        }
        switch(choice){
            case 1: listUsers(); pause();   break;
            case 2: addUser();            break;
            case 3: deleteUser();         break;
            case 4: resetUserPassword();  break;
            case 5: resetUserkey();       break;
            case 0: return;
        }
    }
}//子菜单

int menu() {
    MenuItem items[] = {
        {"录入学生成绩",     addStudent,         1, 0},
        {"删除学生信息",     deleteStudent,      0, 1},
        {"修改学生成绩",     modifyscore,        1, 0},
        {"搜索学生",         queryById,          0, 0},
        {"查询所有学生成绩", displayAllStudents, 1, 0},
        {"按成绩排序",       sortByScore,        1, 0},
        {"按学号排序",       sortById,           1, 0},
        {"计算平均成绩",     calculateAverage,   1, 0},
        {"用户管理",         userManagement,     0, 1},
        {"修改密码",         changeMyPassword,   0, 0},
        {"查看操作日志",     viewLog,            0, 0},
    };
    int total = sizeof(items) / sizeof(items[0]);

    while (1) {
        printf("\n==== 学生成绩管理系统 ====\n");
        printf("当前用户：%s (角色：%s)\n", current_user->username,
               current_user->role == ROLE_ADMIN ? "管理员" :
               (current_user->role == ROLE_TEACHER ? "教师" : "学生"));
        printf("--------------------------------\n");

        int map[20];
        int count = 0;

        for (int i = 0; i < total; i++) {
            int visible = 1;
            if (items[i].needNotStudent && !isNotStudent()) visible = 0;
            if (items[i].needAdmin && !isAdmin()) visible = 0;
            if (visible) {
                map[count] = i;
                count++;
                printf("%d. %s\n", count, items[i].label);
            }
        }

        printf("0. 退出系统\n");

        char input[10];
        scanf("%s", input);
        int choice = atoi(input);

        if (choice == 0) {
            if (isNotStudent()) {
                saveToFile();
            }
            printf("\n==== 本次登录统计 ====\n");
            printf("录入学生：%d 人\n", session_add);
            printf("删除学生：%d 人\n", session_delete);
            printf("修改成绩：%d 次\n", session_modify);
            printf("======================\n\n");
            printf("感谢使用学生成绩管理系统！\n");
            return 0;
        }

        if (choice < 1 || choice > count) {
            printf("无效选择，请重新输入。\n");
            continue;
        }

        items[map[choice - 1]].func();
    }
}//主菜单

int main(){
    srand(time(NULL));
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
