/** 
  C语言课程设计题目源程序: 成绩管理系统

  系统要求: 包含三类用户,管理员,教师,学生
		管理员功能:			
				(1)自身密码修改
				(2)教师信息管理:添加,修改,查询,删除
				(3)学生信息管理:添加,修改,查询,删除
				(4)成绩信息管理:添加,修改,查询,删除
				(5)课程信息管理:添加,修改,查询,删除
				(6)授课信息管理:添加,修改,查询,删除
				(7)退出登陆系统
		教师功能: 
				(1)个人信息修改
				(2)学生信息管理: 只能查看学生的信息
				(3)成绩信息管理: 添加,修改,删除(只限该老师所授课程),查询(所有学生成绩)
				(4)退出登陆系统
		学生功能:
				(1)个人信息修改
				(2)成绩信息管理: 只能查询自己的成绩
				(3)退出登陆系统
**************************************************
	程序作者: 双鱼林  作者真实姓名:  汪建林
	生日: 1985年2月26日 星座: 双鱼座
	血型: 0  家乡: 四川达州
	QQ: 287307421 手机:13558690869
	淘宝店: http://shop34864101.taobao.com
	程序制作时间: 2008年中秋佳节 请朋友们随便传播,但不要把作者信息删除
***************************************************
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USER_TYPE 1
#define TEACHER_USER_TYPE 2
#define STUDENT_USER_TYPE 3


#define FUNCTION_FAILED -1
#define FUNCTION_SUCCESS 0

/** 管理员身份信息表 **/
typedef struct AdminInfo {
    char adminName[20];                    //管理员帐号,主键
    char password[20];                    //管理员密码
    struct AdminInfo *next;                //指向下一个管理员信息
} AdminInfo;


/** 教师信息表  **/
typedef struct TeacherInfo {
    char teacherId[20];                    //教工号,主键
    char teacherPassword[20];            //教师登陆密码
    char teacherName[20];                //教师姓名
    char teacherSex[4];                    //教师性别
    char teacherBirthTime[15];            //教师生日
    char teacherAddress[50];            //教师居住地址
    struct TeacherInfo *next;            //指向下一个教师的信息
} TeacherInfo;


/** 学生信息 **/
typedef struct StudentInfo {
    char studentNumber[20];                //学号,主键
    char studentName[10];                //姓名
    char studentPassword[20];            //学生登陆密码
    char studentSex[4];                    //学生性别
    char studentBirthTime[15];            //学生生日
    char studentAddress[50];            //学生居住地址
    struct StudentInfo *next;            //指向下一个学生的信息
} StudentInfo;


/** 课程信息 **/
typedef struct CourseInfo {
    int courseId;                        //课程编号,主键
    char courseName[20];                //课程名称
    char courseClassroom[20];            //上课所在教室
    char courseTime[20];                //上课时间
    struct CourseInfo *next;            //指向下一门课程的信息
} CourseInfo;

/** 授课信息 **/
typedef struct CourseTeachInfo {
    int courseId;                        //课程编号
    char teacherId[20];                    //教师编号
    struct CourseTeachInfo *next;        //指向下一条教师授课信息
} CourseTeachInfo;


/** 学生成绩信息 **/
typedef struct ScoreInfo {
    char studentNumber[20];                //学生学号
    int courseId;                        //课程编号
    float score;                        //课程成绩
    struct ScoreInfo *next;                //指向下一条成绩信息
} ScoreInfo;


static AdminInfo *pAdminInfoHead = NULL;                //指向系统管理员信息记录的头指针
static CourseInfo *pCourseInfoHead = NULL;                //指向课程信息记录的头指针
static CourseTeachInfo *pCourseTeachInfoHead = NULL;    //指向教师授课信息记录的头指针
static ScoreInfo *pScoreInfoHead = NULL;                //指向成绩记录信息的头指针
static StudentInfo *pStudentInfoHead = NULL;            //指向学生信息记录的头指针
static TeacherInfo *pTeacherInfoHead = NULL;            //指向教师信息记录的头指针

static char currentUserName[20];                    /*保存登陆系统的当前帐号*/
static char currentUserType[20];                    /*保存登陆系统的身份*/

void InitSystem();                            /*初始化系统函数,向各种信息链表中加入测试数据*/
int AddAdminInfo(AdminInfo *);                /*向管理员信息链表中加入一条管理员信息*/
int AddOneCourseInfo(CourseInfo *);            /*向课程信息链表中加入一条课程信息*/
int AddOneTeacherInfo(TeacherInfo *);        /*向教师信息链表中加入一条教师信息*/
int AddOneStudentInfo(StudentInfo *);        /*向学生信息链表中加入一条学生信息*/
int AddOneCourseTeachInfo(CourseTeachInfo *);/*向授课信息链表中加入一条授课信息*/
int AddOneScoreInfo(ScoreInfo *);            /*向成绩链表中加入一条成绩信息*/
void GetStudentName(char *, char *);            /*得到某个学号的学生姓名*/
void GetCourseName(int, char *);                /*得到某门课程编号的名称*/
void GetTeacherName(char *, char *);            /*根据教师编号得到教师姓名*/
bool IsHavingStudentNumber(char *);            /*判断是否存在某个学号的学生信息*/
bool IsHavingCourseId(int);                /*判断是否存在某门课程的信息*/
bool IsHavingTeacherId(char *);                /*判断是否存在某个教师信息*/
bool CanTeacherOpeScore(int, char *);        /*判断某个老师是否有添加某门课程成绩的权限*/
bool IsCourseInTeachInfo(int);                /*判断某门课程是否在授课信息中存在*/
bool IsCourseInScoreInfo(int);                /*判断某门课程是否在成绩信息中存在*/
void ShowWelcomeMenu();                        /*显示系统欢迎菜单*/
int AdminLogin();                            /*管理员身份登陆系统*/
int TeacherLogin();                            /*教师身份登陆系统*/
int StudentLogin();                            /*学生身份登陆系统*/
void SelectLoginType();                        /*选择登陆系统的身份*/
void ShowAdminMenu();                        /*显示管理员操作菜单*/
void AdminPasswordModify();                /*管理员修改自己的密码*/
void TeacherInfoManage();                    /*教师信息管理*/
void TeacherInfoView();                    /*教师信息查看*/
void TeacherInfoAdd();                    /*教师信息添加*/
void TeacherInfoModify();                /*教师信息修改*/
void TeacherInfoDelete();                /*教师信息删除*/
void StudentInfoManage();                    /*学生信息管理*/
/*学生信息查看功能同教师身份登陆时的学生信息查看一样*/
void StudentInfoAdd();                    /*学生信息添加*/
void StudentInfoModify();                /*学生信息修改*/
void StudentInfoDelete();                /*学生信息删除*/
void Admin_ScoreInfoManage();                /*管理员对成绩信息管理*/
void ScoreInfoView();                    /*成绩信息查看*/
void ScoreInfoAdd();                    /*成绩信息添加*/
void ScoreInfoModify();                    /*成绩信息修改*/
void ScoreInfoDelete();                    /*成绩信息删除*/
void CourseInfoManage();                    /*课程信息管理*/
void CourseInfoView();                    /*课程信息查看*/
void CourseInfoAdd();                    /*课程信息添加*/
void CourseInfoModify();                /*课程信息修改*/
void CourseInfoDelete();                /*课程信息删除*/
void CourseTeachInfoManage();                /*授课信息管理*/
void CourseTeachInfoView();                /*授课信息查看*/
void CourseTeachInfoAdd();                /*授课信息添加*/
void CourseTeachInfoModify();            /*授课信息修改*/
void CourseTeachInfoDelete();            /*授课信息删除*/
void ShowTeacherMenu();                        /*显示教师身份操作菜单*/
void TeacherSelfInfoModify();                /*教师信息修改*/
void StudentInfoView();                    /*学生信息查看*/
void Teacher_ScoreInfoManage();            /*教师对成绩信息管理*/
void ScoreInfoView();                    /*成绩信息查看*/
void ScoreInfoAdd();                    /*成绩信息添加*/
void ScoreInfoModify();                    /*成绩信息修改*/
void ScoreInfoDelete();                    /*成绩信息删除*/
void ShowStudentMenu();                        /*显示学生身份操作菜单*/
void StudentSelfInfoModify();            /*学生个人信息修改*/
void Student_ScoreInfoView();            /*学生本人成绩查询*/
void InitSystem() {                /*初始化系统函数,向各种信息链表中加入测试数据*/
    AdminInfo adminInfo;        /*初始化一个管理员信息*/
    strcpy(adminInfo.adminName, "admin");
    strcpy(adminInfo.password, "admin");
    adminInfo.next = NULL;
    AddAdminInfo(&adminInfo);    /*将这个管理员信息加入到管理员信息链表中*/

    CourseInfo courseInfo[3];    /*初始化三门课程信息*/
    strcpy(courseInfo[0].courseClassroom, "6A-101");
    strcpy(courseInfo[1].courseClassroom, "6A-102");
    strcpy(courseInfo[2].courseClassroom, "6A-103");
    strcpy(courseInfo[0].courseName, "计算机网络");
    strcpy(courseInfo[1].courseName, "毛泽东思想");
    strcpy(courseInfo[2].courseName, "C语言程序设计");
    strcpy(courseInfo[0].courseTime, "星期一上午一二节课");
    strcpy(courseInfo[1].courseTime, "星期五下午三四节课");
    strcpy(courseInfo[2].courseTime, "星期三晚上三节课");
    courseInfo[0].next = courseInfo[1].next = courseInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneCourseInfo(&courseInfo[i]);

    TeacherInfo teacherInfo[3]; /*初始化三个教师信息*/
    strcpy(teacherInfo[0].teacherId, "TH001");
    strcpy(teacherInfo[1].teacherId, "TH002");
    strcpy(teacherInfo[2].teacherId, "TH003");
    strcpy(teacherInfo[0].teacherName, "汪老师");
    strcpy(teacherInfo[1].teacherName, "梁老师");
    strcpy(teacherInfo[2].teacherName, "李老师");
    strcpy(teacherInfo[0].teacherPassword, "TH001");
    strcpy(teacherInfo[1].teacherPassword, "TH002");
    strcpy(teacherInfo[2].teacherPassword, "TH003");
    strcpy(teacherInfo[0].teacherSex, "男");
    strcpy(teacherInfo[1].teacherSex, "女");
    strcpy(teacherInfo[2].teacherSex, "男");
    strcpy(teacherInfo[0].teacherBirthTime, "1975年3月12日");
    strcpy(teacherInfo[1].teacherBirthTime, "1980年7月5日");
    strcpy(teacherInfo[2].teacherBirthTime, "1978年1月17日");
    strcpy(teacherInfo[0].teacherAddress, "四川成都");
    strcpy(teacherInfo[1].teacherAddress, "湖南长沙");
    strcpy(teacherInfo[2].teacherAddress, "云南昆明");
    teacherInfo[0].next = teacherInfo[1].next = teacherInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneTeacherInfo(&teacherInfo[i]);

    StudentInfo studentInfo[3];    /*初始化三个学生信息*/
    strcpy(studentInfo[0].studentAddress, "湖北武汉");
    strcpy(studentInfo[1].studentAddress, "上海");
    strcpy(studentInfo[2].studentAddress, "四川达州");
    strcpy(studentInfo[0].studentBirthTime, "1987年3月18日");
    strcpy(studentInfo[1].studentBirthTime, "1989年9月19日");
    strcpy(studentInfo[2].studentBirthTime, "1988年6月15日");
    strcpy(studentInfo[0].studentName, "汪建林");
    strcpy(studentInfo[1].studentName, "张高铅");
    strcpy(studentInfo[2].studentName, "蒋介石");
    strcpy(studentInfo[0].studentNumber, "200305030317");
    strcpy(studentInfo[1].studentNumber, "200305030318");
    strcpy(studentInfo[2].studentNumber, "200305030320");
    strcpy(studentInfo[0].studentPassword, "1234");
    strcpy(studentInfo[1].studentPassword, "1234");
    strcpy(studentInfo[2].studentPassword, "1234");
    strcpy(studentInfo[0].studentSex, "男");
    strcpy(studentInfo[1].studentSex, "女");
    strcpy(studentInfo[2].studentSex, "男");
    studentInfo[0].next = studentInfo[1].next = studentInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneStudentInfo(&studentInfo[i]);

    CourseTeachInfo courseTeachInfo[3]; /*初始化三个教师授课信息*/
    courseTeachInfo[0].courseId = 1;
    courseTeachInfo[1].courseId = 2;
    courseTeachInfo[2].courseId = 3;
    strcpy(courseTeachInfo[0].teacherId, "TH001");
    strcpy(courseTeachInfo[1].teacherId, "TH002");
    strcpy(courseTeachInfo[2].teacherId, "TH003");
    courseTeachInfo[0].next = NULL;
    courseTeachInfo[1].next = NULL;
    courseTeachInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneCourseTeachInfo(&courseTeachInfo[i]);
}

int AddAdminInfo(AdminInfo *pAdminInfo) {
    /* 分配堆空间内存 */
    AdminInfo *pAdminInfoTmp = (AdminInfo *) malloc(sizeof(AdminInfo));
    if (NULL == pAdminInfoTmp) {
        printf("对不起，添加管理员信息时,堆内存分配失败!");
        return FUNCTION_FAILED;
    }
    /* 复制管理员信息 */
    strcpy(pAdminInfoTmp->adminName, pAdminInfo->adminName);
    strcpy(pAdminInfoTmp->password, pAdminInfo->password);
    /* 直接将堆空间的该记录的下一条记录指针指向头指针 */
    pAdminInfoTmp->next = pAdminInfoHead;
    /* 再将头指针重新指向该条记录 */
    pAdminInfoHead = pAdminInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneCourseInfo(CourseInfo *pCourseInfo) {
    int courseId;            //程序自动生成课程编号
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    if (NULL == pCourseInfoHead)
        courseId = 1;
    else {
        while (NULL != tmpCourseInfo->next)
            tmpCourseInfo = tmpCourseInfo->next;
        courseId = tmpCourseInfo->courseId + 1;
    }

    CourseInfo *pCourseInfoTmp = (CourseInfo *) malloc(sizeof(CourseInfo));
    if (NULL == pCourseInfoTmp) {
        printf("对不起,添加课程信息时,堆内存分配失败!");
        return FUNCTION_FAILED;
    }
    strcpy(pCourseInfoTmp->courseClassroom, pCourseInfo->courseClassroom);
    pCourseInfoTmp->courseId = courseId;
    strcpy(pCourseInfoTmp->courseName, pCourseInfo->courseName);
    strcpy(pCourseInfoTmp->courseTime, pCourseInfo->courseTime);
    pCourseInfoTmp->next = pCourseInfo->next;

    if (NULL == pCourseInfoHead)
        pCourseInfoHead = pCourseInfoTmp;
    else
        tmpCourseInfo->next = pCourseInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneTeacherInfo(TeacherInfo *pTeacherInfo) {
    /* 分配堆空间内存 */
    TeacherInfo *pTeacherInfoTmp = (TeacherInfo *) malloc(sizeof(TeacherInfo));
    if (NULL == pTeacherInfoTmp) {
        printf("对不起，添加教师信息时,堆内存分配失败!");
        return FUNCTION_FAILED;
    }
    /* 复制教师信息 */
    strcpy(pTeacherInfoTmp->teacherAddress, pTeacherInfo->teacherAddress);
    strcpy(pTeacherInfoTmp->teacherBirthTime, pTeacherInfo->teacherBirthTime);
    strcpy(pTeacherInfoTmp->teacherId, pTeacherInfo->teacherId);
    strcpy(pTeacherInfoTmp->teacherName, pTeacherInfo->teacherName);
    strcpy(pTeacherInfoTmp->teacherPassword, pTeacherInfo->teacherPassword);
    strcpy(pTeacherInfoTmp->teacherSex, pTeacherInfo->teacherSex);
    /* 直接将堆空间的该记录的下一条记录指针指向头指针 */
    pTeacherInfoTmp->next = pTeacherInfoHead;
    /* 再将头指针重新指向该条记录 */
    pTeacherInfoHead = pTeacherInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneStudentInfo(StudentInfo *pStudentInfo) {
    /* 分配堆空间内存 */
    StudentInfo *pStudentInfoTmp = (StudentInfo *) malloc(sizeof(StudentInfo));
    if (NULL == pStudentInfoTmp) {
        printf("对不起，添加学生信息时,堆内存分配失败!");
        return FUNCTION_FAILED;
    }
    /* 复制学生信息 */
    strcpy(pStudentInfoTmp->studentAddress, pStudentInfo->studentAddress);
    strcpy(pStudentInfoTmp->studentBirthTime, pStudentInfo->studentBirthTime);
    strcpy(pStudentInfoTmp->studentName, pStudentInfo->studentName);
    strcpy(pStudentInfoTmp->studentNumber, pStudentInfo->studentNumber);
    strcpy(pStudentInfoTmp->studentPassword, pStudentInfo->studentPassword);
    strcpy(pStudentInfoTmp->studentSex, pStudentInfo->studentSex);

    /* 直接将堆空间的该记录的下一条记录指针指向头指针 */
    pStudentInfoTmp->next = pStudentInfoHead;
    /* 再将头指针重新指向该条记录 */
    pStudentInfoHead = pStudentInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneCourseTeachInfo(CourseTeachInfo *pCourseTeachInfo) {
    /* 分配堆空间 */
    CourseTeachInfo *pCourseTeachInfoTmp = (CourseTeachInfo *) malloc(sizeof(CourseTeachInfo));
    if (NULL == pCourseTeachInfoTmp) {
        printf("对不起,添加授课信息时堆内存分配失败!");
        return FUNCTION_FAILED;
    }
    /* 复制授课信息 */
    strcpy(pCourseTeachInfoTmp->teacherId, pCourseTeachInfo->teacherId);
    pCourseTeachInfoTmp->courseId = pCourseTeachInfo->courseId;
    /* 直接将堆空间的该记录的下一条记录指针指向头指针 */
    pCourseTeachInfoTmp->next = pCourseTeachInfoHead;
    /* 再将头指针重新指向该条记录 */
    pCourseTeachInfoHead = pCourseTeachInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneScoreInfo(ScoreInfo *pScoreInfo) {            /*向成绩链表中加入一条成绩信息*/
    /* 分配堆内存空间 */
    ScoreInfo *pScoreInfoTmp = (ScoreInfo *) malloc(sizeof(ScoreInfo));
    if (NULL == pScoreInfoTmp) {
        printf("对不起,添加成绩信息时堆内存空间分配失败!");
        return FUNCTION_FAILED;
    }
    /* 复制成绩信息 */
    pScoreInfoTmp->courseId = pScoreInfo->courseId;
    strcpy(pScoreInfoTmp->studentNumber, pScoreInfo->studentNumber);
    pScoreInfoTmp->score = pScoreInfo->score;
    /* 直接将堆空间的该记录的下一条记录指针指向头指针 */
    pScoreInfoTmp->next = pScoreInfoHead;
    /* 再将头指针重新指向该条记录 */
    pScoreInfoHead = pScoreInfoTmp;
    return FUNCTION_SUCCESS;
}

void ShowWelcomeMenu() {
    printf("********************************************************************************");
    printf("                 C语言课程设计题目: 成绩管理系统                 \n");
    printf("                                          程序设计by:双鱼林  QQ:287307421\n");
    printf("管理员功能:\n");
    printf("  (1)自身密码修改\n");
    printf("  (2)教师信息管理:添加,修改,查询,删除\n");
    printf("  (3)学生信息管理:添加,修改,查询,删除\n");
    printf("  (4)成绩信息管理:添加,修改,查询,删除\n");
    printf("  (5)课程信息管理:添加,修改,查询,删除\n");
    printf("  (6)授课信息管理:添加,修改,查询,删除\n");
    printf("  (7)退出登陆系统\n");
    printf("教师功能:\n");
    printf("  (1)个人信息修改\n");
    printf("  (2)学生信息管理: 只能查看学生的信息\n");
    printf("  (3)成绩信息管理: 添加,修改,删除(只限该老师所授课程),查询(所有学生成绩)\n");
    printf("  (4)退出登陆系统\n");
    printf("学生功能:\n");
    printf("  (1)个人信息修改\n");
    printf("  (2)成绩信息管理:只能查看自己的成绩\n");
    printf("  (3)退出登陆系统\n");
    printf("********************************************************************************");
}

int AdminLogin() {
    char adminName[20], password[20];
    bool haveAdminUser = false;        /*系统是否存在该帐号标志*/
    AdminInfo *tmpAdminInfo;
    printf("你好,你现在选择的是管理员身份登陆系统,请输入你的登陆帐号和密码\n");
    printf("登陆帐号:");
    scanf("%s", adminName);
    printf("密码:");
    scanf("%s", password);
    tmpAdminInfo = pAdminInfoHead;
    if (NULL == tmpAdminInfo) return FUNCTION_FAILED;
    while (NULL != tmpAdminInfo) {
        if (0 == strcmp(adminName, tmpAdminInfo->adminName)) {    /*找到该帐号信息*/
            haveAdminUser = true;                                /*设置存在标志*/
            if (0 == strcmp(password, tmpAdminInfo->password)) {    /*密码输入也正确*/
                strcpy(currentUserName, adminName);                /*保存当前帐号*/
                strcpy(currentUserType, "admin");                /*设置当前身份为管理员*/
                ShowAdminMenu();                                /*显示管理员操作菜单*/
                return FUNCTION_SUCCESS;
            } else {
                printf("对不起,你输入的密码错误!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpAdminInfo = tmpAdminInfo->next;
        }
    }
    if (false == haveAdminUser) {
        printf("对不起,你输入的管理员帐号不存在!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;

}

int TeacherLogin() {
    char teacherId[20], teacherPassword[20];
    bool haveTeacherInfo = false;        /*系统是否存在该帐号标志*/
    TeacherInfo *tmpTeacherInfo;
    printf("你好,你现在选择的是教师身份登陆系统,请输入你的登陆帐号和密码\n");
    printf("登陆帐号(教师编号):");
    scanf("%s", teacherId);
    printf("密码:");
    scanf("%s", teacherPassword);
    tmpTeacherInfo = pTeacherInfoHead;
    if (NULL == tmpTeacherInfo) return FUNCTION_FAILED;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(teacherId, tmpTeacherInfo->teacherId)) {                    /*找到该帐号信息*/
            haveTeacherInfo = true;                                                /*设置存在标志*/
            if (0 == strcmp(teacherPassword, tmpTeacherInfo->teacherPassword)) {    /*密码输入也正确*/
                strcpy(currentUserName, teacherId);                                /*保存当前帐号*/
                strcpy(currentUserType, "teacher");                                /*设置当前身份为管理员*/
                ShowTeacherMenu();                                                /*显示教师操作操作菜单*/
                return FUNCTION_SUCCESS;
            } else {
                printf("对不起,你输入的密码错误!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpTeacherInfo = tmpTeacherInfo->next;
        }
    }
    if (false == haveTeacherInfo) {
        printf("对不起,你输入的教师编号不存在!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;
}

int StudentLogin() {
    char studentNumber[20], studentPassword[20];
    bool haveStudentInfo = false;        /*系统是否存在该帐号标志*/
    StudentInfo *tmpStudentInfo;
    printf("你好,你现在选择的是学生身份登陆系统,请输入你的登陆帐号和密码\n");
    printf("登陆帐号(学号):");
    scanf("%s", studentNumber);
    printf("密码:");
    scanf("%s", studentPassword);
    tmpStudentInfo = pStudentInfoHead;
    if (NULL == tmpStudentInfo) return FUNCTION_FAILED;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(studentNumber, tmpStudentInfo->studentNumber)) {            /*找到该帐号信息*/
            haveStudentInfo = true;                                                /*设置存在标志*/
            if (0 == strcmp(studentPassword, tmpStudentInfo->studentPassword)) {    /*密码输入也正确*/
                strcpy(currentUserName, studentNumber);                            /*保存当前帐号*/
                strcpy(currentUserType, "student");                                /*设置当前身份为管理员*/
                ShowStudentMenu();                                                /*显示教师操作操作菜单*/
                return FUNCTION_SUCCESS;
            } else {
                printf("对不起,你输入的密码错误!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpStudentInfo = tmpStudentInfo->next;
        }
    }
    if (false == haveStudentInfo) {
        printf("对不起,你输入的学号不存在!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;
}

void ShowAdminMenu() {
    int select = 0;
    while (7 != select) {
        printf("你好,管理员,你拥有下面的这些功能,请通过选择相应的序号进入\n");
        printf("1--自身密码修改\n");
        printf("2--教师信息管理\n");
        printf("3--学生信息管理\n");
        printf("4--成绩信息管理\n");
        printf("5--课程信息管理\n");
        printf("6--授课信息管理\n");
        printf("7--退出登陆系统\n");
        scanf("%d", &select);
        switch (select) {
            case 1:
                AdminPasswordModify();
                continue;
            case 2:
                TeacherInfoManage();
                continue;
            case 3:
                StudentInfoManage();
                continue;
            case 4:
                Admin_ScoreInfoManage();
                continue;
            case 5:
                CourseInfoManage();
                continue;
            case 6:
                CourseTeachInfoManage();
                continue;
            default:
                continue;
        }
    }
    SelectLoginType();
}

void AdminPasswordModify() {            /*管理员修改自己的密码*/
    char oldPassword[20], newPassword[20], newPassword2[20];
    printf("请输入当前的密码:\n");
    scanf("%s", oldPassword);
    AdminInfo *tmpAdminInfo = pAdminInfoHead;
    while (NULL != tmpAdminInfo) {
        if (0 == strcmp(currentUserName, tmpAdminInfo->adminName)) {    /*首先找到要修改的记录*/
            if (0 == strcmp(oldPassword, tmpAdminInfo->password)) {    /*如果密码输入正确*/
                printf("请输入新的密码:\n");
                scanf("%s", newPassword);
                printf("请再次确认新密码:\n");
                scanf("%s", newPassword2);
                if (0 == strcmp(newPassword, newPassword2)) {            /*如果两次新的密码一致*/
                    strcpy(tmpAdminInfo->password, newPassword);
                    printf("密码修改成功!\n");
                } else
                    printf("对不起,你两次输入的新密码不一致!\n");
            } else {
                printf("对不起,你的旧密码输入不正确!\n");
            }
            break;
        } else {
            tmpAdminInfo = tmpAdminInfo->next;
        }
    }

}

void TeacherInfoManage() {                /*教师信息管理*/
    int select = 0;
    while (5 != select) {
        printf("你好,管理员,你现在进入的是教师信息管理功能模块,拥有下面的功能\n");
        printf("1--教师信息查看  2--教师信息添加  3--教师信息修改  4--教师信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                TeacherInfoView();
                continue;
            case 2:
                TeacherInfoAdd();
                continue;
            case 3:
                TeacherInfoModify();
                continue;
            case 4:
                TeacherInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void TeacherInfoView() {
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    printf("教师编号 姓名   性别    出生日期       登陆密码 居住地址\n");
    if (NULL == tmpTeacherInfo) printf("对不起,目前还不存在任何教师信息!\n");
    while (NULL != tmpTeacherInfo) {
        printf("%s\t", tmpTeacherInfo->teacherId);
        printf("%s\t", tmpTeacherInfo->teacherName);
        printf("%s\t", tmpTeacherInfo->teacherSex);
        printf("%s\t", tmpTeacherInfo->teacherBirthTime);
        printf("%s\t", tmpTeacherInfo->teacherPassword);
        printf("%s\n", tmpTeacherInfo->teacherAddress);

        tmpTeacherInfo = tmpTeacherInfo->next;
    }

}

void TeacherInfoAdd() {
    TeacherInfo teacherInfo;
    printf("请输入教师编号:");
    scanf("%s", teacherInfo.teacherId);
    printf("请输入教师姓名:");
    scanf("%s", teacherInfo.teacherName);
    printf("请输入教师性别:");
    scanf("%s", teacherInfo.teacherSex);
    printf("请输入教师出生日期:");
    scanf("%s", teacherInfo.teacherBirthTime);
    printf("请输入教师登陆密码:");
    scanf("%s", teacherInfo.teacherPassword);
    printf("请输入教师居住地址:");
    scanf("%s", teacherInfo.teacherAddress);
    teacherInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneTeacherInfo(&teacherInfo))
        printf("教师信息添加成功!\n");
}

void TeacherInfoModify() {
    char teacherId[20];
    bool haveTeacherId = false;
    TeacherInfo *tmpTeacherInfo;
    printf("请输入要修改的教师编号:");
    scanf("%s", teacherId);
    tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(tmpTeacherInfo->teacherId, teacherId)) {  /*找到要修改的教师信息记录*/
            haveTeacherId = true;                                /*修改教师编号存在标志*/
            printf("教师编号为%s的信息如下:\n", teacherId);        /*显示该教师的原来信息*/
            printf("教师姓名: %s\n", tmpTeacherInfo->teacherName);
            printf("教师性别: %s\n", tmpTeacherInfo->teacherSex);
            printf("教师密码: %s\n", tmpTeacherInfo->teacherPassword);
            printf("教师生日: %s\n", tmpTeacherInfo->teacherBirthTime);
            printf("教师居住地址: %s\n", tmpTeacherInfo->teacherAddress);
            printf("请输入该教师的新信息:\n");                    /*下面输入该老师的新信息*/
            printf("教师姓名:");
            scanf("%s", tmpTeacherInfo->teacherName);
            printf("教师性别:");
            scanf("%s", tmpTeacherInfo->teacherSex);
            printf("教师密码:");
            scanf("%s", tmpTeacherInfo->teacherPassword);
            printf("教师生日:");
            scanf("%s", tmpTeacherInfo->teacherBirthTime);
            printf("教师居住地址:");
            scanf("%s", tmpTeacherInfo->teacherAddress);
            printf("教师信息修改成功!");
            break;
        } else {
            tmpTeacherInfo = tmpTeacherInfo->next;
        }
    }
    if (false == haveTeacherId)
        printf("对不起,你存在你要修改的教师编号!\n");
}

void TeacherInfoDelete() {
    char teacherId[20];                            /*待删除的教师编号*/
    printf("请输入你要删除的教师编号:");
    scanf("%s", teacherId);
    TeacherInfo *tmpTeacherInfoA, *tmpTeacherInfoB;
    tmpTeacherInfoA = tmpTeacherInfoB = pTeacherInfoHead;    /*tmpTeacherInfoB指向要删除的记录，tmpTeacherInfoA指向前一条记录*/
    if (NULL == tmpTeacherInfoB) return;
    while (NULL != tmpTeacherInfoB) {
        if (0 == strcmp(tmpTeacherInfoB->teacherId, teacherId)) {
            if (tmpTeacherInfoB == pTeacherInfoHead && tmpTeacherInfoB->next == NULL) {    //如果系统只有一条教师信息
                free(pTeacherInfoHead);
                pTeacherInfoHead = NULL;
                printf("教师信息删除成功!\n");
                /*此处最好再加入删除该老师授课的信息*/
                return;
            }
            tmpTeacherInfoA->next = tmpTeacherInfoB->next;
            if (pTeacherInfoHead == tmpTeacherInfoB)
                pTeacherInfoHead = tmpTeacherInfoB->next;
            free(tmpTeacherInfoB);
            printf("教师信息删除成功!\n");
            /*此处最好再加入删除该老师授课的信息*/
            return;
        } else {
            tmpTeacherInfoA = tmpTeacherInfoB;
            tmpTeacherInfoB = tmpTeacherInfoB->next;
        }
    }
    printf("对不起，不存在该教师编号的信息!\n");
}

void StudentInfoManage() {                /*学生信息管理*/
    int select = 0;
    while (5 != select) {
        printf("你好,管理员,你现在进入的是学生信息管理功能模块,拥有下面的功能\n");
        printf("1--学生信息查看  2--学生信息添加  3--学生信息修改  4--学生信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                StudentInfoView();
                continue;
            case 2:
                StudentInfoAdd();
                continue;
            case 3:
                StudentInfoModify();
                continue;
            case 4:
                StudentInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void StudentInfoAdd() {    /*学生信息添加*/
    StudentInfo studentInfo;
    printf("请输入学号:");
    scanf("%s", studentInfo.studentNumber);
    printf("请输入姓名:");
    scanf("%s", studentInfo.studentName);
    printf("请输入性别:");
    scanf("%s", studentInfo.studentSex);
    printf("请输入出生日期:");
    scanf("%s", studentInfo.studentBirthTime);
    printf("请输入学生登陆密码:");
    scanf("%s", studentInfo.studentPassword);
    printf("请输入学生居住地址:");
    scanf("%s", studentInfo.studentAddress);
    studentInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneStudentInfo(&studentInfo))
        printf("学生信息添加成功!\n");
}

void StudentInfoModify() { /*学生信息修改*/
    char studentNumber[20];
    bool haveStudentNumber = false;    /*是否存在该学号学生标志变量*/
    StudentInfo *tmpStudentInfo;
    printf("请输入要修改的学生学号:");
    scanf("%s", studentNumber);
    tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(tmpStudentInfo->studentNumber, studentNumber)) {  /*找到要修改的学生信息记录*/
            haveStudentNumber = true;                            /*修改学号存在标志*/
            printf("学号为%s的信息如下:\n", studentNumber);        /*显示该学生的原来信息*/
            printf("学生姓名: %s\n", tmpStudentInfo->studentName);
            printf("学生性别: %s\n", tmpStudentInfo->studentSex);
            printf("学生密码: %s\n", tmpStudentInfo->studentPassword);
            printf("学生生日: %s\n", tmpStudentInfo->studentBirthTime);
            printf("学生居住地址: %s\n", tmpStudentInfo->studentAddress);
            printf("请输入该学生的新信息:\n");                    /*下面输入该老师的新信息*/
            printf("学生姓名:");
            scanf("%s", tmpStudentInfo->studentName);
            printf("学生性别:");
            scanf("%s", tmpStudentInfo->studentSex);
            printf("学生密码:");
            scanf("%s", tmpStudentInfo->studentPassword);
            printf("学生生日:");
            scanf("%s", tmpStudentInfo->studentBirthTime);
            printf("学生居住地址:");
            scanf("%s", tmpStudentInfo->studentAddress);
            printf("学生信息修改成功!\n");
            break;
        } else {
            tmpStudentInfo = tmpStudentInfo->next;
        }
    }
    if (false == haveStudentNumber)
        printf("对不起,你存在你要修改的学号!\n");
}

void StudentInfoDelete() { /*学生信息删除*/
    char studentNumber[20];            /*待删除的学生学号*/
    printf("请输入你要删除的学生学号:");
    scanf("%s", studentNumber);
    StudentInfo *tmpStudentInfoA, *tmpStudentInfoB;
    tmpStudentInfoA = tmpStudentInfoB = pStudentInfoHead;    /*tmpStudentInfoB指向要删除的记录，tmpStudentInfoA指向前一条记录*/
    if (NULL == tmpStudentInfoB) return;
    while (NULL != tmpStudentInfoB) {
        if (0 == strcmp(tmpStudentInfoB->studentNumber, studentNumber)) {
            if (tmpStudentInfoB == pStudentInfoHead && tmpStudentInfoB->next == NULL) {    //如果系统只有一条教师信息
                free(pStudentInfoHead);
                pStudentInfoHead = NULL;
                printf("学生信息删除成功!\n");
                /*此处最好再加入删除该学生的成绩信息*/
                return;
            }
            tmpStudentInfoA->next = tmpStudentInfoB->next;
            if (pStudentInfoHead == tmpStudentInfoB)
                pStudentInfoHead = tmpStudentInfoB->next;
            free(tmpStudentInfoB);
            printf("学生信息删除成功!\n");
            /*此处最好再加入删除该学生的成绩信息*/
            return;
        } else {
            tmpStudentInfoA = tmpStudentInfoB;
            tmpStudentInfoB = tmpStudentInfoB->next;
        }
    }
    printf("对不起，不存在该学号的学生信息!\n");
}

void Admin_ScoreInfoManage() {            /*管理员对成绩信息管理*/
    int select = 0;
    while (5 != select) {
        printf("你好,管理员,你现在进入的是成绩信息管理功能模块,拥有下面的功能\n");
        printf("1--成绩信息查看  2--成绩信息添加  3--成绩信息修改  4--成绩信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                ScoreInfoView();
                continue;
            case 2:
                ScoreInfoAdd();
                continue;
            case 3:
                ScoreInfoModify();
                continue;
            case 4:
                ScoreInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void ScoreInfoView() { /*成绩信息查看*/
    char studentName[20], courseName[20];
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    if (NULL == tmpScoreInfo) {
        printf("对不起,现在系统中还不存在成绩信息的!\n");
        return;
    }
    printf("系统的成绩信息如下:\n");
    printf("学号            姓名    课程编号     课程名称    成绩\n");
    while (NULL != tmpScoreInfo) {    /*遍历所有成绩信息*/
        GetStudentName(tmpScoreInfo->studentNumber, studentName);    /*得到该学号的学生姓名*/
        GetCourseName(tmpScoreInfo->courseId, courseName);            /*得到该课程的名称*/
        printf("%s\t", tmpScoreInfo->studentNumber);
        printf("%s\t", studentName);
        printf("%d\t", tmpScoreInfo->courseId);
        printf("%s\t", courseName);
        printf("%f\n", tmpScoreInfo->score);

        tmpScoreInfo = tmpScoreInfo->next;
    }
}

/*****************************************************************
根据学号得到学生姓名: studentNumber-入口参数 studentName-出口参数
*****************************************************************/
void GetStudentName(char *studentNumber, char *studentName) {
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(studentNumber, tmpStudentInfo->studentNumber)) {
            strcpy(studentName, tmpStudentInfo->studentName);
            return;
        } else {
            tmpStudentInfo = tmpStudentInfo->next;
        }
    }
    strcpy(studentName, "ERROR");
}

/*****************************************************************
根据课程编号得到课程名: courseId-入口参数 courseName-出口参数
*****************************************************************/
void GetCourseName(int courseId, char *courseName) {
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    while (NULL != tmpCourseInfo) {
        if (courseId == tmpCourseInfo->courseId) {
            strcpy(courseName, tmpCourseInfo->courseName);
            return;
        } else {
            tmpCourseInfo = tmpCourseInfo->next;
        }
    }
    strcpy(courseName, "ERROR");
}


bool IsHavingStudentNumber(char *studentNumber) {    /*检查系统是否存在该学号的学生*/
    bool isHaving = false;
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(studentNumber, tmpStudentInfo->studentNumber)) {
            isHaving = true;
            break;
        }
        tmpStudentInfo = tmpStudentInfo->next;
    }
    return isHaving;
}

bool IsHavingCourseId(int courseId) {                /*检查系统是否存在该课程信息*/
    bool isHaving = false;
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    while (NULL != tmpCourseInfo) {
        if (courseId == tmpCourseInfo->courseId) {
            isHaving = true;
            break;
        }
        tmpCourseInfo = tmpCourseInfo->next;
    }
    return isHaving;
}

void CourseInfoManage() {
    int select = 0;
    while (5 != select) {
        printf("你好,管理员,你现在进入的是课程信息管理功能模块,拥有下面的功能\n");
        printf("1--课程信息查看  2--课程信息添加  3--课程信息修改  4--课程信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                CourseInfoView();
                continue;
            case 2:
                CourseInfoAdd();
                continue;
            case 3:
                CourseInfoModify();
                continue;
            case 4:
                CourseInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void CourseInfoView() {                    /*课程信息查看*/
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    if (NULL == tmpCourseInfo) {
        printf("对不起,目前系统中还没有课程信息的!\n");
        return;
    }
    printf("课程编号    课程名称        上课时间          上课教室\n");
    while (NULL != tmpCourseInfo) {
        printf("%d\t  ", tmpCourseInfo->courseId);
        printf("%s\t", tmpCourseInfo->courseName);
        printf("%s\t", tmpCourseInfo->courseTime);
        printf("%s\n", tmpCourseInfo->courseClassroom);

        tmpCourseInfo = tmpCourseInfo->next;
    }
}

void CourseInfoAdd() {                    /*课程信息添加*/
    /* 课程编号不需要输入,由程序自动生成*/
    CourseInfo courseInfo;
    printf("请输入课程名称:");
    scanf("%s", courseInfo.courseName);
    printf("请输入上课教室:");
    scanf("%s", courseInfo.courseClassroom);
    printf("请输入上课时间:");
    scanf("%s", courseInfo.courseTime);
    courseInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneCourseInfo(&courseInfo))
        printf("课程信息添加成功!\n");
}

void CourseInfoModify() {                /*课程信息修改*/
    int courseId;
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    printf("请输入你要修改的课程的课程编号:");
    scanf("%d", &courseId);
    while (NULL != tmpCourseInfo) {
        if (courseId == tmpCourseInfo->courseId) {    /*找到待修改的课程记录*/
            printf("课程编号为%d的课程信息如下:\n", &courseId);
            printf("课程名称: %s\n", tmpCourseInfo->courseName);
            printf("上课时间: %s\n", tmpCourseInfo->courseTime);
            printf("上课教室: %s\n", tmpCourseInfo->courseClassroom);
            printf("请输入新的信息:\n");
            printf("课程名称:");
            scanf("%s", tmpCourseInfo->courseName);
            printf("上课时间:");
            scanf("%s", tmpCourseInfo->courseTime);
            printf("上课教室:");
            scanf("%s", tmpCourseInfo->courseClassroom);
            printf("课程信息修改成功!\n");
            return;
        }
        tmpCourseInfo = tmpCourseInfo->next;
    }
    printf("找不到该课程的信息!\n");
}

void CourseInfoDelete() {                /*课程信息删除*/
    int courseId;    /*待删除的课程编号*/
    printf("请输入将被删除的课程的课程编号:");
    scanf("%d", &courseId);
    if (IsCourseInTeachInfo(courseId)) {
        printf("对不起,授课信息中存在本课程信息,请先把授课信息中的相关信息删除后再删除本课程信息!\n");
        return;
    }
    if (IsCourseInScoreInfo(courseId)) {
        printf("对不起,成绩信息中存在本课程信息,请先把成绩信息中的相关信息删除后再删除本课程信息!\n");
        return;
    }
    CourseInfo *tmpCourseInfoA, *tmpCourseInfoB;
    tmpCourseInfoA = tmpCourseInfoB = pCourseInfoHead;    /*tmpCourseInfoB指向要删除的记录，tmpCourseInfoA指向前一条记录*/
    if (NULL == tmpCourseInfoB) return;
    while (NULL != tmpCourseInfoB) {
        if (tmpCourseInfoB->courseId == courseId) {
            if (tmpCourseInfoB == pCourseInfoHead && tmpCourseInfoB->next == NULL) {    //如果系统只有一条课程信息
                free(pCourseInfoHead);
                pCourseInfoHead = NULL;
                printf("课程信息删除成功!\n");
                return;
            }
            tmpCourseInfoA->next = tmpCourseInfoB->next;
            if (pCourseInfoHead == tmpCourseInfoB)
                pCourseInfoHead = tmpCourseInfoB->next;
            free(tmpCourseInfoB);
            printf("课程信息删除成功!\n");
            return;
        } else {
            tmpCourseInfoA = tmpCourseInfoB;
            tmpCourseInfoB = tmpCourseInfoB->next;
        }
    }
    printf("对不起，不存在该课程编号的信息!\n");
}

bool IsCourseInTeachInfo(int courseId) {    /*判断某门课程是否在授课信息中存在*/
    bool isCourseInTinfo = false;
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    while (NULL != tmpCourseTeachInfo) {
        if (courseId == tmpCourseTeachInfo->courseId) {
            isCourseInTinfo = true;
            break;
        }
        tmpCourseTeachInfo = tmpCourseTeachInfo->next;
    }
    return isCourseInTinfo;
}

bool IsCourseInScoreInfo(int courseId) {    /*判断某门课程是否在成绩信息中存在*/
    bool isCourseInSinfo = false;
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    while (NULL != tmpScoreInfo) {
        if (courseId == tmpScoreInfo->courseId) {
            isCourseInSinfo = true;
            break;
        }
        tmpScoreInfo = tmpScoreInfo->next;
    }
    return isCourseInSinfo;
}

void CourseTeachInfoManage() {
    int select = 0;
    while (5 != select) {
        printf("你好,管理员,你现在进入的是授课信息管理功能模块,拥有下面的功能\n");
        printf("1--授课信息查看  2--授课信息添加  3--授课信息修改  4--授课信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                CourseTeachInfoView();
                continue;
            case 2:
                CourseTeachInfoAdd();
                continue;
            case 3:
                CourseTeachInfoModify();
                continue;
            case 4:
                CourseTeachInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void CourseTeachInfoView() {            /*授课信息查看*/
    char courseName[20], teacherName[20];
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    if (NULL == tmpCourseTeachInfo) {
        printf("对不起,目前系统中还不存在授课信息的!\n");
        return;
    }
    printf("课程编号  课程名称    教师编号    教师姓名\n");
    while (NULL != tmpCourseTeachInfo) {
        GetCourseName(tmpCourseTeachInfo->courseId, courseName);
        GetTeacherName(tmpCourseTeachInfo->teacherId, teacherName);
        printf("%d\t", tmpCourseTeachInfo->courseId);
        printf("%s\t", courseName);
        printf("%s\t", tmpCourseTeachInfo->teacherId);
        printf("%s\n", teacherName);

        tmpCourseTeachInfo = tmpCourseTeachInfo->next;
    }
}

void GetTeacherName(char *teacherId, char *teacherName) { /*根据教师编号得到教师姓名*/
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(tmpTeacherInfo->teacherId, teacherId)) { /*找到该教师信息*/
            strcpy(teacherName, tmpTeacherInfo->teacherName);
            break;
        }
        tmpTeacherInfo = tmpTeacherInfo->next;
    }

}

void CourseTeachInfoAdd() {                /*授课信息添加*/
    CourseTeachInfo courseTeachInfo;
    printf("请输入授课课程编号:");
    scanf("%d", &courseTeachInfo.courseId);
    if (!IsHavingCourseId(courseTeachInfo.courseId)) {
        printf("对不起,该课程编号不存在,请确认后再操作!\n");
        return;
    }
    printf("请输入授课教师编号:");
    scanf("%s", courseTeachInfo.teacherId);
    if (!IsHavingTeacherId(courseTeachInfo.teacherId)) {
        printf("对不起,该教师编号不存在,请确认后再操作!\n");
        return;
    }
    courseTeachInfo.next = NULL;
    /*此处最好再加入判断系统中是否已经存在本门课程的授课信息*/
    if (FUNCTION_SUCCESS == AddOneCourseTeachInfo(&courseTeachInfo))
        printf("授课信息添加成功!\n");
}

bool IsHavingTeacherId(char *teacherId) { /*判断是否存在某个教师信息*/
    bool isHaving = false;
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(tmpTeacherInfo->teacherId, teacherId)) {
            isHaving = true;
            break;
        }
        tmpTeacherInfo = tmpTeacherInfo->next;
    }
    return isHaving;
}

void CourseTeachInfoModify() {            /*授课信息修改*/
    int courseId;
    char teacherId[20];
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    printf("请输入你要修改的课程编号(整数):");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("对不起,你输入的课程编号不存在!\n");
        return;
    }
    while (NULL != tmpCourseTeachInfo) {
        if (courseId == tmpCourseTeachInfo->courseId) { /*找到要修改的授课信息*/
            printf("当前的授课教师编号是:%s\n", tmpCourseTeachInfo->teacherId);
            printf("请输入新的授课教师编号:");
            scanf("%s", teacherId);
            if (!IsHavingTeacherId(teacherId)) {
                printf("对不起,你输入的教师编号系统中不存在!\n");
                return;
            }
            strcpy(tmpCourseTeachInfo->teacherId, teacherId);
            printf("授课信息修改成功!\n");
            return;
        }
        tmpCourseTeachInfo = tmpCourseTeachInfo->next;
    }
    printf("对不起,没有找到对应课程编号的授课信息!\n");
}

void CourseTeachInfoDelete() {            /*授课信息删除*/
    int courseId;                        /*待删除的课程编号*/
    printf("请输入你要删除的课程编号:");
    scanf("%d", &courseId);
    CourseTeachInfo *tmpCourseTeachInfoA, *tmpCourseTeachInfoB;
    tmpCourseTeachInfoA = tmpCourseTeachInfoB = pCourseTeachInfoHead;    /*tmpCourseTeachInfoB指向要删除的记录，tmpCourseTeachInfoA指向前一条记录*/
    if (NULL == tmpCourseTeachInfoB) return;
    while (NULL != tmpCourseTeachInfoB) {
        if (courseId == tmpCourseTeachInfoB->courseId) {
            if (tmpCourseTeachInfoB == pCourseTeachInfoHead && tmpCourseTeachInfoB->next == NULL) {    //如果系统只有一条授课信息
                free(pCourseTeachInfoHead);
                pCourseTeachInfoHead = NULL;
                printf("授课信息删除成功!\n");
                return;
            }
            tmpCourseTeachInfoA->next = tmpCourseTeachInfoB->next;
            if (pCourseTeachInfoHead == tmpCourseTeachInfoB)
                pCourseTeachInfoHead = tmpCourseTeachInfoB->next;
            free(tmpCourseTeachInfoB);
            printf("授课信息删除成功!\n");
            return;
        } else {
            tmpCourseTeachInfoA = tmpCourseTeachInfoB;
            tmpCourseTeachInfoB = tmpCourseTeachInfoB->next;
        }
    }
    printf("对不起，不存在该课程编号的信息!\n");
}

void ShowTeacherMenu() {
    int select = 0;
    while (4 != select) {
        printf("你好,老师,你拥有下面的这些功能,请通过选择相应的序号进入\n");
        printf("1--个人信息修改\n");
        printf("2--学生信息管理:(只能查看学生的信息)\n");
        printf("3--成绩信息管理: 添加、修改、删除(只限该老师所授课程),查询(所有学生成绩)\n");
        printf("4--退出登陆系统\n");
        printf("请输入相应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                TeacherSelfInfoModify();
                continue;
            case 2:
                StudentInfoView();
                continue;
            case 3:
                Teacher_ScoreInfoManage();
                continue;
            default:
                continue;
        }
    }
    SelectLoginType();
}

void TeacherSelfInfoModify() {
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(currentUserName, tmpTeacherInfo->teacherId)) { /*找到该教师的记录信息*/
            printf("老师,你好,你的当前个人信息如下:\n");
            printf("教师姓名: %s\n", tmpTeacherInfo->teacherName);
            printf("教师性别: %s\n", tmpTeacherInfo->teacherSex);
            printf("教师生日: %s\n", tmpTeacherInfo->teacherBirthTime);
            printf("教师登陆密码: %s\n", tmpTeacherInfo->teacherPassword);
            printf("教师居住地址: %s\n", tmpTeacherInfo->teacherAddress);
            printf("请输入新的信息:\n");
            printf("你的姓名:");
            scanf("%s", tmpTeacherInfo->teacherName);
            printf("你的性别:");
            scanf("%s", tmpTeacherInfo->teacherSex);
            printf("你的生日:");
            scanf("%s", tmpTeacherInfo->teacherBirthTime);
            printf("你的登陆密码:");
            scanf("%s", tmpTeacherInfo->teacherPassword);
            printf("你的居住地址:");
            scanf("%s", tmpTeacherInfo->teacherAddress);
            printf("信息修改成功!");
        }
        tmpTeacherInfo = tmpTeacherInfo->next;
    }
}

void StudentInfoView() {    /*学生信息查看*/
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    printf("学号            姓名   性别      出生日期       登陆密码 居住地址\n");
    if (NULL == tmpStudentInfo) printf("对不起,目前还不存在任何学生信息!\n");
    while (NULL != tmpStudentInfo) {
        printf("%s\t", tmpStudentInfo->studentNumber);
        printf("%s\t", tmpStudentInfo->studentName);
        printf("%s\t", tmpStudentInfo->studentSex);
        printf("%s\t", tmpStudentInfo->studentBirthTime);
        printf("%s\t", tmpStudentInfo->studentPassword);
        printf("%s\n", tmpStudentInfo->studentAddress);

        tmpStudentInfo = tmpStudentInfo->next;
    }
}

void Teacher_ScoreInfoManage() {    /*教师对成绩信息的管理*/
    int select = 0;
    while (5 != select) {
        printf("你好,老师,你现在进入的是成绩信息管理功能模块,拥有下面的功能\n");
        printf("1--成绩信息查看  2--成绩信息添加  3--成绩信息修改  4--成绩信息删除  5--返回上级菜单\n");
        printf("请输入对应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                ScoreInfoView();
                continue;
            case 2:
                ScoreInfoAdd();
                continue;
            case 3:
                ScoreInfoModify();
                continue;
            case 4:
                ScoreInfoDelete();
                continue;
            default:
                continue;
        }
    }
    ShowAdminMenu();    /*返回上级菜单*/
}

void ScoreInfoAdd() {            /*教师对成绩的添加*/
    char studentNumber[20];
    int courseId;
    float score;
    ScoreInfo scoreInfo;
    printf("请输入学生的学号:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {    /*如果输入的学号不存在*/
        printf("对不起,你添加成绩的学生不存在,请确认后再操作!\n");
        return;
    }
    printf("请输入课程编号:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {            /*如果输入的课程不存在*/
        printf("对不起,你添加成绩的课程对象不存在,请确认后再操作!\n");
        return;
    }

    if (0 == strcmp(currentUserType, "teacher")) {    /*如果当前登陆的是教师身份需要进行操作权限判断*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("对不起,老师,因为你没有教该门课是是不能添加该门课程的成绩的!\n");
            return;
        }
    }

    printf("请输入成绩:");
    scanf("%f", &score);
    strcpy(scoreInfo.studentNumber, studentNumber);
    scoreInfo.courseId = courseId;
    scoreInfo.score = score;
    if (FUNCTION_SUCCESS == AddOneScoreInfo(&scoreInfo))
        printf("成绩信息添加成功!\n");
}

bool CanTeacherOpeScore(int courseId, char *teacherId) { /*判断某个老师是否有添加某门课程成绩的权限*/
    bool canAddScore = false;
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    while (NULL != tmpCourseTeachInfo) {
        if ((tmpCourseTeachInfo->courseId == courseId) && (0 == strcmp(tmpCourseTeachInfo->teacherId, teacherId))) {
            canAddScore = true;
            break;
        }
        tmpCourseTeachInfo = tmpCourseTeachInfo->next;
    }
    return canAddScore;
}

void ScoreInfoModify() {        /*教师对成绩的修改*/
    char studentNumber[20];
    int courseId;
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    printf("请输入你要修改成绩记录的学生学号:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {
        printf("对不起,不存在该学生信息,请确认你的输入是否正确!\n");
        return;
    }
    printf("请输入你要修改成绩记录的课程编号:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("对不起,不存在该课程信息,请确认你的输入是否正确!\n");
        return;
    }

    if (0 == strcmp(currentUserType, "teacher")) {    /*如果当前登陆的是教师身份需要进行操作权限判断*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("对不起,老师,你没有修改这门课程成绩的权限!\n");
            return;
        }
    }

    while (NULL != tmpScoreInfo) {
        if ((0 == strcmp(tmpScoreInfo->studentNumber, studentNumber)) && (tmpScoreInfo->courseId == courseId)) {
            printf("当前学号为%s课程编号为%d的成绩是: %f\n", studentNumber, courseId, tmpScoreInfo->score);
            printf("请输入新的成绩:");
            scanf("%f", &tmpScoreInfo->score);
            printf("成绩信息修改成功!\n");
            return;
        }
        tmpScoreInfo = tmpScoreInfo->next;
    }
    printf("对不起,找不到符合条件的成绩记录信息!\n");
}

void ScoreInfoDelete() {            /*教师对成绩的删除*/
    char studentNumber[20];
    int courseId;
    printf("请输入你要修改成绩记录的学生学号:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {
        printf("对不起,不存在该学生信息,请确认你的输入是否正确!\n");
        return;
    }
    printf("请输入你要修改成绩记录的课程编号:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("对不起,不存在该课程信息,请确认你的输入是否正确!\n");
        return;
    }
    if (0 == strcmp(currentUserType, "teacher")) {    /*如果当前登陆的是教师身份需要进行操作权限判断*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("对不起,老师,你没有操作本门课程的权限!\n");
            return;
        }
    }


    ScoreInfo *tmpScoreInfoA, *tmpScoreInfoB;
    tmpScoreInfoA = tmpScoreInfoB = pScoreInfoHead;    /*tmpScoreInfoB指向要删除的记录，tmpScoreInfoA指向前一条记录*/
    if (NULL == tmpScoreInfoB) return;
    while (NULL != tmpScoreInfoB) {
        if ((0 == strcmp(studentNumber, tmpScoreInfoB->studentNumber)) && (courseId == tmpScoreInfoB->courseId)) {
            if (tmpScoreInfoB == pScoreInfoHead && tmpScoreInfoB->next == NULL) {    //如果系统只有一条成绩信息
                free(pScoreInfoHead);
                pScoreInfoHead = NULL;
                printf("成绩信息删除成功!\n");
                return;
            }
            tmpScoreInfoA->next = tmpScoreInfoB->next;
            if (pScoreInfoHead == tmpScoreInfoB)
                pScoreInfoHead = tmpScoreInfoB->next;
            free(tmpScoreInfoB);
            printf("成绩信息删除成功!\n");
            return;
        } else {
            tmpScoreInfoA = tmpScoreInfoB;
            tmpScoreInfoB = tmpScoreInfoB->next;
        }
    }
    printf("对不起，符合条件的成绩信息!\n");
}

void ShowStudentMenu() {
    int select = 0;
    while (3 != select) {
        printf("你好,同学,你拥有下面的这些功能,请通过选择相应的序号进入\n");
        printf("1--个人信息修改\n");
        printf("2--本人成绩查询\n");
        printf("3--退出登陆系统\n");
        printf("请输入相应的功能号:");
        scanf("%d", &select);
        switch (select) {
            case 1:
                StudentSelfInfoModify();
                continue;
            case 2:
                Student_ScoreInfoView();
            default:
                continue;
        }
    }
    SelectLoginType();
}

void StudentSelfInfoModify() { /*学生个人信息修改*/
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(currentUserName, tmpStudentInfo->studentNumber)) { /*找到该学生的记录信息*/
            printf("同学,你好,你的当前个人信息如下:\n");
            printf("学生姓名: %s\n", tmpStudentInfo->studentName);
            printf("学生性别: %s\n", tmpStudentInfo->studentSex);
            printf("教师生日: %s\n", tmpStudentInfo->studentBirthTime);
            printf("学生登陆密码: %s\n", tmpStudentInfo->studentPassword);
            printf("学生居住地址: %s\n", tmpStudentInfo->studentAddress);
            printf("请输入新的信息:\n");
            printf("你的姓名:");
            scanf("%s", tmpStudentInfo->studentName);
            printf("你的性别:");
            scanf("%s", tmpStudentInfo->studentSex);
            printf("你的生日:");
            scanf("%s", tmpStudentInfo->studentBirthTime);
            printf("你的登陆密码:");
            scanf("%s", tmpStudentInfo->studentPassword);
            printf("你的居住地址:");
            scanf("%s", tmpStudentInfo->studentAddress);
            printf("信息修改成功!");
        }
        tmpStudentInfo = tmpStudentInfo->next;
    }
}

void Student_ScoreInfoView() { /*学生本人成绩查询*/
    char studentName[20], courseName[20];
    bool haveScore = false; /*系统中是否存在该同学的成绩信息标志变量*/
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    if (NULL == tmpScoreInfo) {
        printf("对不起,现在系统中还不存在成绩信息的!\n");
        return;
    }
    printf("系统的成绩信息如下:\n");
    printf("学号            姓名    课程编号     课程名称    成绩\n");
    while (NULL != tmpScoreInfo) {    /*遍历所有成绩信息*/
        if (0 == strcmp(tmpScoreInfo->studentNumber, currentUserName)) {
            haveScore = true;
            GetStudentName(tmpScoreInfo->studentNumber, studentName);    /*得到该学号的学生姓名*/
            GetCourseName(tmpScoreInfo->courseId, courseName);            /*得到该课程的名称*/
            printf("%s\t", tmpScoreInfo->studentNumber);
            printf("%s\t", studentName);
            printf("%d\t", tmpScoreInfo->courseId);
            printf("%s\t", courseName);
            printf("%f\n", tmpScoreInfo->score);
        }
        tmpScoreInfo = tmpScoreInfo->next;
    }
    if (!haveScore) printf("对不起,现在系统中还不存在该你的成绩信息!\n");
}

void SelectLoginType() {
    while (true) {
        printf("请选择你登陆本系统的身份: 1--管理员身份  2--教师身份  3--学生身份:");
        int select;
        scanf("%d", &select);
        switch (select) {
            case 1:
                AdminLogin();
                continue;
            case 2:
                TeacherLogin();
                continue;
            case 3:
                StudentLogin();
                continue;
            default:
                continue;
        }
    }
}

int main() {
    InitSystem();            //初始化系统
    ShowWelcomeMenu();        //显示欢迎菜单
    SelectLoginType();        //选择登陆系统
    return 0;
}




