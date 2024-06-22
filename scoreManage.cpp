/** 
  C���Կγ������ĿԴ����: �ɼ�����ϵͳ

  ϵͳҪ��: ���������û�,����Ա,��ʦ,ѧ��
		����Ա����:			
				(1)���������޸�
				(2)��ʦ��Ϣ����:���,�޸�,��ѯ,ɾ��
				(3)ѧ����Ϣ����:���,�޸�,��ѯ,ɾ��
				(4)�ɼ���Ϣ����:���,�޸�,��ѯ,ɾ��
				(5)�γ���Ϣ����:���,�޸�,��ѯ,ɾ��
				(6)�ڿ���Ϣ����:���,�޸�,��ѯ,ɾ��
				(7)�˳���½ϵͳ
		��ʦ����: 
				(1)������Ϣ�޸�
				(2)ѧ����Ϣ����: ֻ�ܲ鿴ѧ������Ϣ
				(3)�ɼ���Ϣ����: ���,�޸�,ɾ��(ֻ�޸���ʦ���ڿγ�),��ѯ(����ѧ���ɼ�)
				(4)�˳���½ϵͳ
		ѧ������:
				(1)������Ϣ�޸�
				(2)�ɼ���Ϣ����: ֻ�ܲ�ѯ�Լ��ĳɼ�
				(3)�˳���½ϵͳ
**************************************************
	��������: ˫����  ������ʵ����:  ������
	����: 1985��2��26�� ����: ˫����
	Ѫ��: 0  ����: �Ĵ�����
	QQ: 287307421 �ֻ�:13558690869
	�Ա���: http://shop34864101.taobao.com
	��������ʱ��: 2008������ѽ� ����������㴫��,����Ҫ��������Ϣɾ��
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

/** ����Ա�����Ϣ�� **/
typedef struct AdminInfo {
    char adminName[20];                    //����Ա�ʺ�,����
    char password[20];                    //����Ա����
    struct AdminInfo *next;                //ָ����һ������Ա��Ϣ
} AdminInfo;


/** ��ʦ��Ϣ��  **/
typedef struct TeacherInfo {
    char teacherId[20];                    //�̹���,����
    char teacherPassword[20];            //��ʦ��½����
    char teacherName[20];                //��ʦ����
    char teacherSex[4];                    //��ʦ�Ա�
    char teacherBirthTime[15];            //��ʦ����
    char teacherAddress[50];            //��ʦ��ס��ַ
    struct TeacherInfo *next;            //ָ����һ����ʦ����Ϣ
} TeacherInfo;


/** ѧ����Ϣ **/
typedef struct StudentInfo {
    char studentNumber[20];                //ѧ��,����
    char studentName[10];                //����
    char studentPassword[20];            //ѧ����½����
    char studentSex[4];                    //ѧ���Ա�
    char studentBirthTime[15];            //ѧ������
    char studentAddress[50];            //ѧ����ס��ַ
    struct StudentInfo *next;            //ָ����һ��ѧ������Ϣ
} StudentInfo;


/** �γ���Ϣ **/
typedef struct CourseInfo {
    int courseId;                        //�γ̱��,����
    char courseName[20];                //�γ�����
    char courseClassroom[20];            //�Ͽ����ڽ���
    char courseTime[20];                //�Ͽ�ʱ��
    struct CourseInfo *next;            //ָ����һ�ſγ̵���Ϣ
} CourseInfo;

/** �ڿ���Ϣ **/
typedef struct CourseTeachInfo {
    int courseId;                        //�γ̱��
    char teacherId[20];                    //��ʦ���
    struct CourseTeachInfo *next;        //ָ����һ����ʦ�ڿ���Ϣ
} CourseTeachInfo;


/** ѧ���ɼ���Ϣ **/
typedef struct ScoreInfo {
    char studentNumber[20];                //ѧ��ѧ��
    int courseId;                        //�γ̱��
    float score;                        //�γ̳ɼ�
    struct ScoreInfo *next;                //ָ����һ���ɼ���Ϣ
} ScoreInfo;


static AdminInfo *pAdminInfoHead = NULL;                //ָ��ϵͳ����Ա��Ϣ��¼��ͷָ��
static CourseInfo *pCourseInfoHead = NULL;                //ָ��γ���Ϣ��¼��ͷָ��
static CourseTeachInfo *pCourseTeachInfoHead = NULL;    //ָ���ʦ�ڿ���Ϣ��¼��ͷָ��
static ScoreInfo *pScoreInfoHead = NULL;                //ָ��ɼ���¼��Ϣ��ͷָ��
static StudentInfo *pStudentInfoHead = NULL;            //ָ��ѧ����Ϣ��¼��ͷָ��
static TeacherInfo *pTeacherInfoHead = NULL;            //ָ���ʦ��Ϣ��¼��ͷָ��

static char currentUserName[20];                    /*�����½ϵͳ�ĵ�ǰ�ʺ�*/
static char currentUserType[20];                    /*�����½ϵͳ�����*/

void InitSystem();                            /*��ʼ��ϵͳ����,�������Ϣ�����м����������*/
int AddAdminInfo(AdminInfo *);                /*�����Ա��Ϣ�����м���һ������Ա��Ϣ*/
int AddOneCourseInfo(CourseInfo *);            /*��γ���Ϣ�����м���һ���γ���Ϣ*/
int AddOneTeacherInfo(TeacherInfo *);        /*���ʦ��Ϣ�����м���һ����ʦ��Ϣ*/
int AddOneStudentInfo(StudentInfo *);        /*��ѧ����Ϣ�����м���һ��ѧ����Ϣ*/
int AddOneCourseTeachInfo(CourseTeachInfo *);/*���ڿ���Ϣ�����м���һ���ڿ���Ϣ*/
int AddOneScoreInfo(ScoreInfo *);            /*��ɼ������м���һ���ɼ���Ϣ*/
void GetStudentName(char *, char *);            /*�õ�ĳ��ѧ�ŵ�ѧ������*/
void GetCourseName(int, char *);                /*�õ�ĳ�ſγ̱�ŵ�����*/
void GetTeacherName(char *, char *);            /*���ݽ�ʦ��ŵõ���ʦ����*/
bool IsHavingStudentNumber(char *);            /*�ж��Ƿ����ĳ��ѧ�ŵ�ѧ����Ϣ*/
bool IsHavingCourseId(int);                /*�ж��Ƿ����ĳ�ſγ̵���Ϣ*/
bool IsHavingTeacherId(char *);                /*�ж��Ƿ����ĳ����ʦ��Ϣ*/
bool CanTeacherOpeScore(int, char *);        /*�ж�ĳ����ʦ�Ƿ������ĳ�ſγ̳ɼ���Ȩ��*/
bool IsCourseInTeachInfo(int);                /*�ж�ĳ�ſγ��Ƿ����ڿ���Ϣ�д���*/
bool IsCourseInScoreInfo(int);                /*�ж�ĳ�ſγ��Ƿ��ڳɼ���Ϣ�д���*/
void ShowWelcomeMenu();                        /*��ʾϵͳ��ӭ�˵�*/
int AdminLogin();                            /*����Ա��ݵ�½ϵͳ*/
int TeacherLogin();                            /*��ʦ��ݵ�½ϵͳ*/
int StudentLogin();                            /*ѧ����ݵ�½ϵͳ*/
void SelectLoginType();                        /*ѡ���½ϵͳ�����*/
void ShowAdminMenu();                        /*��ʾ����Ա�����˵�*/
void AdminPasswordModify();                /*����Ա�޸��Լ�������*/
void TeacherInfoManage();                    /*��ʦ��Ϣ����*/
void TeacherInfoView();                    /*��ʦ��Ϣ�鿴*/
void TeacherInfoAdd();                    /*��ʦ��Ϣ���*/
void TeacherInfoModify();                /*��ʦ��Ϣ�޸�*/
void TeacherInfoDelete();                /*��ʦ��Ϣɾ��*/
void StudentInfoManage();                    /*ѧ����Ϣ����*/
/*ѧ����Ϣ�鿴����ͬ��ʦ��ݵ�½ʱ��ѧ����Ϣ�鿴һ��*/
void StudentInfoAdd();                    /*ѧ����Ϣ���*/
void StudentInfoModify();                /*ѧ����Ϣ�޸�*/
void StudentInfoDelete();                /*ѧ����Ϣɾ��*/
void Admin_ScoreInfoManage();                /*����Ա�Գɼ���Ϣ����*/
void ScoreInfoView();                    /*�ɼ���Ϣ�鿴*/
void ScoreInfoAdd();                    /*�ɼ���Ϣ���*/
void ScoreInfoModify();                    /*�ɼ���Ϣ�޸�*/
void ScoreInfoDelete();                    /*�ɼ���Ϣɾ��*/
void CourseInfoManage();                    /*�γ���Ϣ����*/
void CourseInfoView();                    /*�γ���Ϣ�鿴*/
void CourseInfoAdd();                    /*�γ���Ϣ���*/
void CourseInfoModify();                /*�γ���Ϣ�޸�*/
void CourseInfoDelete();                /*�γ���Ϣɾ��*/
void CourseTeachInfoManage();                /*�ڿ���Ϣ����*/
void CourseTeachInfoView();                /*�ڿ���Ϣ�鿴*/
void CourseTeachInfoAdd();                /*�ڿ���Ϣ���*/
void CourseTeachInfoModify();            /*�ڿ���Ϣ�޸�*/
void CourseTeachInfoDelete();            /*�ڿ���Ϣɾ��*/
void ShowTeacherMenu();                        /*��ʾ��ʦ��ݲ����˵�*/
void TeacherSelfInfoModify();                /*��ʦ��Ϣ�޸�*/
void StudentInfoView();                    /*ѧ����Ϣ�鿴*/
void Teacher_ScoreInfoManage();            /*��ʦ�Գɼ���Ϣ����*/
void ScoreInfoView();                    /*�ɼ���Ϣ�鿴*/
void ScoreInfoAdd();                    /*�ɼ���Ϣ���*/
void ScoreInfoModify();                    /*�ɼ���Ϣ�޸�*/
void ScoreInfoDelete();                    /*�ɼ���Ϣɾ��*/
void ShowStudentMenu();                        /*��ʾѧ����ݲ����˵�*/
void StudentSelfInfoModify();            /*ѧ��������Ϣ�޸�*/
void Student_ScoreInfoView();            /*ѧ�����˳ɼ���ѯ*/
void InitSystem() {                /*��ʼ��ϵͳ����,�������Ϣ�����м����������*/
    AdminInfo adminInfo;        /*��ʼ��һ������Ա��Ϣ*/
    strcpy(adminInfo.adminName, "admin");
    strcpy(adminInfo.password, "admin");
    adminInfo.next = NULL;
    AddAdminInfo(&adminInfo);    /*���������Ա��Ϣ���뵽����Ա��Ϣ������*/

    CourseInfo courseInfo[3];    /*��ʼ�����ſγ���Ϣ*/
    strcpy(courseInfo[0].courseClassroom, "6A-101");
    strcpy(courseInfo[1].courseClassroom, "6A-102");
    strcpy(courseInfo[2].courseClassroom, "6A-103");
    strcpy(courseInfo[0].courseName, "���������");
    strcpy(courseInfo[1].courseName, "ë��˼��");
    strcpy(courseInfo[2].courseName, "C���Գ������");
    strcpy(courseInfo[0].courseTime, "����һ����һ���ڿ�");
    strcpy(courseInfo[1].courseTime, "�������������Ľڿ�");
    strcpy(courseInfo[2].courseTime, "�������������ڿ�");
    courseInfo[0].next = courseInfo[1].next = courseInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneCourseInfo(&courseInfo[i]);

    TeacherInfo teacherInfo[3]; /*��ʼ��������ʦ��Ϣ*/
    strcpy(teacherInfo[0].teacherId, "TH001");
    strcpy(teacherInfo[1].teacherId, "TH002");
    strcpy(teacherInfo[2].teacherId, "TH003");
    strcpy(teacherInfo[0].teacherName, "����ʦ");
    strcpy(teacherInfo[1].teacherName, "����ʦ");
    strcpy(teacherInfo[2].teacherName, "����ʦ");
    strcpy(teacherInfo[0].teacherPassword, "TH001");
    strcpy(teacherInfo[1].teacherPassword, "TH002");
    strcpy(teacherInfo[2].teacherPassword, "TH003");
    strcpy(teacherInfo[0].teacherSex, "��");
    strcpy(teacherInfo[1].teacherSex, "Ů");
    strcpy(teacherInfo[2].teacherSex, "��");
    strcpy(teacherInfo[0].teacherBirthTime, "1975��3��12��");
    strcpy(teacherInfo[1].teacherBirthTime, "1980��7��5��");
    strcpy(teacherInfo[2].teacherBirthTime, "1978��1��17��");
    strcpy(teacherInfo[0].teacherAddress, "�Ĵ��ɶ�");
    strcpy(teacherInfo[1].teacherAddress, "���ϳ�ɳ");
    strcpy(teacherInfo[2].teacherAddress, "��������");
    teacherInfo[0].next = teacherInfo[1].next = teacherInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneTeacherInfo(&teacherInfo[i]);

    StudentInfo studentInfo[3];    /*��ʼ������ѧ����Ϣ*/
    strcpy(studentInfo[0].studentAddress, "�����人");
    strcpy(studentInfo[1].studentAddress, "�Ϻ�");
    strcpy(studentInfo[2].studentAddress, "�Ĵ�����");
    strcpy(studentInfo[0].studentBirthTime, "1987��3��18��");
    strcpy(studentInfo[1].studentBirthTime, "1989��9��19��");
    strcpy(studentInfo[2].studentBirthTime, "1988��6��15��");
    strcpy(studentInfo[0].studentName, "������");
    strcpy(studentInfo[1].studentName, "�Ÿ�Ǧ");
    strcpy(studentInfo[2].studentName, "����ʯ");
    strcpy(studentInfo[0].studentNumber, "200305030317");
    strcpy(studentInfo[1].studentNumber, "200305030318");
    strcpy(studentInfo[2].studentNumber, "200305030320");
    strcpy(studentInfo[0].studentPassword, "1234");
    strcpy(studentInfo[1].studentPassword, "1234");
    strcpy(studentInfo[2].studentPassword, "1234");
    strcpy(studentInfo[0].studentSex, "��");
    strcpy(studentInfo[1].studentSex, "Ů");
    strcpy(studentInfo[2].studentSex, "��");
    studentInfo[0].next = studentInfo[1].next = studentInfo[2].next = NULL;
    for (int i = 0; i < 3; i++) AddOneStudentInfo(&studentInfo[i]);

    CourseTeachInfo courseTeachInfo[3]; /*��ʼ��������ʦ�ڿ���Ϣ*/
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
    /* ����ѿռ��ڴ� */
    AdminInfo *pAdminInfoTmp = (AdminInfo *) malloc(sizeof(AdminInfo));
    if (NULL == pAdminInfoTmp) {
        printf("�Բ�����ӹ���Ա��Ϣʱ,���ڴ����ʧ��!");
        return FUNCTION_FAILED;
    }
    /* ���ƹ���Ա��Ϣ */
    strcpy(pAdminInfoTmp->adminName, pAdminInfo->adminName);
    strcpy(pAdminInfoTmp->password, pAdminInfo->password);
    /* ֱ�ӽ��ѿռ�ĸü�¼����һ����¼ָ��ָ��ͷָ�� */
    pAdminInfoTmp->next = pAdminInfoHead;
    /* �ٽ�ͷָ������ָ�������¼ */
    pAdminInfoHead = pAdminInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneCourseInfo(CourseInfo *pCourseInfo) {
    int courseId;            //�����Զ����ɿγ̱��
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
        printf("�Բ���,��ӿγ���Ϣʱ,���ڴ����ʧ��!");
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
    /* ����ѿռ��ڴ� */
    TeacherInfo *pTeacherInfoTmp = (TeacherInfo *) malloc(sizeof(TeacherInfo));
    if (NULL == pTeacherInfoTmp) {
        printf("�Բ�����ӽ�ʦ��Ϣʱ,���ڴ����ʧ��!");
        return FUNCTION_FAILED;
    }
    /* ���ƽ�ʦ��Ϣ */
    strcpy(pTeacherInfoTmp->teacherAddress, pTeacherInfo->teacherAddress);
    strcpy(pTeacherInfoTmp->teacherBirthTime, pTeacherInfo->teacherBirthTime);
    strcpy(pTeacherInfoTmp->teacherId, pTeacherInfo->teacherId);
    strcpy(pTeacherInfoTmp->teacherName, pTeacherInfo->teacherName);
    strcpy(pTeacherInfoTmp->teacherPassword, pTeacherInfo->teacherPassword);
    strcpy(pTeacherInfoTmp->teacherSex, pTeacherInfo->teacherSex);
    /* ֱ�ӽ��ѿռ�ĸü�¼����һ����¼ָ��ָ��ͷָ�� */
    pTeacherInfoTmp->next = pTeacherInfoHead;
    /* �ٽ�ͷָ������ָ�������¼ */
    pTeacherInfoHead = pTeacherInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneStudentInfo(StudentInfo *pStudentInfo) {
    /* ����ѿռ��ڴ� */
    StudentInfo *pStudentInfoTmp = (StudentInfo *) malloc(sizeof(StudentInfo));
    if (NULL == pStudentInfoTmp) {
        printf("�Բ������ѧ����Ϣʱ,���ڴ����ʧ��!");
        return FUNCTION_FAILED;
    }
    /* ����ѧ����Ϣ */
    strcpy(pStudentInfoTmp->studentAddress, pStudentInfo->studentAddress);
    strcpy(pStudentInfoTmp->studentBirthTime, pStudentInfo->studentBirthTime);
    strcpy(pStudentInfoTmp->studentName, pStudentInfo->studentName);
    strcpy(pStudentInfoTmp->studentNumber, pStudentInfo->studentNumber);
    strcpy(pStudentInfoTmp->studentPassword, pStudentInfo->studentPassword);
    strcpy(pStudentInfoTmp->studentSex, pStudentInfo->studentSex);

    /* ֱ�ӽ��ѿռ�ĸü�¼����һ����¼ָ��ָ��ͷָ�� */
    pStudentInfoTmp->next = pStudentInfoHead;
    /* �ٽ�ͷָ������ָ�������¼ */
    pStudentInfoHead = pStudentInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneCourseTeachInfo(CourseTeachInfo *pCourseTeachInfo) {
    /* ����ѿռ� */
    CourseTeachInfo *pCourseTeachInfoTmp = (CourseTeachInfo *) malloc(sizeof(CourseTeachInfo));
    if (NULL == pCourseTeachInfoTmp) {
        printf("�Բ���,����ڿ���Ϣʱ���ڴ����ʧ��!");
        return FUNCTION_FAILED;
    }
    /* �����ڿ���Ϣ */
    strcpy(pCourseTeachInfoTmp->teacherId, pCourseTeachInfo->teacherId);
    pCourseTeachInfoTmp->courseId = pCourseTeachInfo->courseId;
    /* ֱ�ӽ��ѿռ�ĸü�¼����һ����¼ָ��ָ��ͷָ�� */
    pCourseTeachInfoTmp->next = pCourseTeachInfoHead;
    /* �ٽ�ͷָ������ָ�������¼ */
    pCourseTeachInfoHead = pCourseTeachInfoTmp;
    return FUNCTION_SUCCESS;
}

int AddOneScoreInfo(ScoreInfo *pScoreInfo) {            /*��ɼ������м���һ���ɼ���Ϣ*/
    /* ������ڴ�ռ� */
    ScoreInfo *pScoreInfoTmp = (ScoreInfo *) malloc(sizeof(ScoreInfo));
    if (NULL == pScoreInfoTmp) {
        printf("�Բ���,��ӳɼ���Ϣʱ���ڴ�ռ����ʧ��!");
        return FUNCTION_FAILED;
    }
    /* ���Ƴɼ���Ϣ */
    pScoreInfoTmp->courseId = pScoreInfo->courseId;
    strcpy(pScoreInfoTmp->studentNumber, pScoreInfo->studentNumber);
    pScoreInfoTmp->score = pScoreInfo->score;
    /* ֱ�ӽ��ѿռ�ĸü�¼����һ����¼ָ��ָ��ͷָ�� */
    pScoreInfoTmp->next = pScoreInfoHead;
    /* �ٽ�ͷָ������ָ�������¼ */
    pScoreInfoHead = pScoreInfoTmp;
    return FUNCTION_SUCCESS;
}

void ShowWelcomeMenu() {
    printf("********************************************************************************");
    printf("                 C���Կγ������Ŀ: �ɼ�����ϵͳ                 \n");
    printf("                                          �������by:˫����  QQ:287307421\n");
    printf("����Ա����:\n");
    printf("  (1)���������޸�\n");
    printf("  (2)��ʦ��Ϣ����:���,�޸�,��ѯ,ɾ��\n");
    printf("  (3)ѧ����Ϣ����:���,�޸�,��ѯ,ɾ��\n");
    printf("  (4)�ɼ���Ϣ����:���,�޸�,��ѯ,ɾ��\n");
    printf("  (5)�γ���Ϣ����:���,�޸�,��ѯ,ɾ��\n");
    printf("  (6)�ڿ���Ϣ����:���,�޸�,��ѯ,ɾ��\n");
    printf("  (7)�˳���½ϵͳ\n");
    printf("��ʦ����:\n");
    printf("  (1)������Ϣ�޸�\n");
    printf("  (2)ѧ����Ϣ����: ֻ�ܲ鿴ѧ������Ϣ\n");
    printf("  (3)�ɼ���Ϣ����: ���,�޸�,ɾ��(ֻ�޸���ʦ���ڿγ�),��ѯ(����ѧ���ɼ�)\n");
    printf("  (4)�˳���½ϵͳ\n");
    printf("ѧ������:\n");
    printf("  (1)������Ϣ�޸�\n");
    printf("  (2)�ɼ���Ϣ����:ֻ�ܲ鿴�Լ��ĳɼ�\n");
    printf("  (3)�˳���½ϵͳ\n");
    printf("********************************************************************************");
}

int AdminLogin() {
    char adminName[20], password[20];
    bool haveAdminUser = false;        /*ϵͳ�Ƿ���ڸ��ʺű�־*/
    AdminInfo *tmpAdminInfo;
    printf("���,������ѡ����ǹ���Ա��ݵ�½ϵͳ,��������ĵ�½�ʺź�����\n");
    printf("��½�ʺ�:");
    scanf("%s", adminName);
    printf("����:");
    scanf("%s", password);
    tmpAdminInfo = pAdminInfoHead;
    if (NULL == tmpAdminInfo) return FUNCTION_FAILED;
    while (NULL != tmpAdminInfo) {
        if (0 == strcmp(adminName, tmpAdminInfo->adminName)) {    /*�ҵ����ʺ���Ϣ*/
            haveAdminUser = true;                                /*���ô��ڱ�־*/
            if (0 == strcmp(password, tmpAdminInfo->password)) {    /*��������Ҳ��ȷ*/
                strcpy(currentUserName, adminName);                /*���浱ǰ�ʺ�*/
                strcpy(currentUserType, "admin");                /*���õ�ǰ���Ϊ����Ա*/
                ShowAdminMenu();                                /*��ʾ����Ա�����˵�*/
                return FUNCTION_SUCCESS;
            } else {
                printf("�Բ���,��������������!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpAdminInfo = tmpAdminInfo->next;
        }
    }
    if (false == haveAdminUser) {
        printf("�Բ���,������Ĺ���Ա�ʺŲ�����!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;

}

int TeacherLogin() {
    char teacherId[20], teacherPassword[20];
    bool haveTeacherInfo = false;        /*ϵͳ�Ƿ���ڸ��ʺű�־*/
    TeacherInfo *tmpTeacherInfo;
    printf("���,������ѡ����ǽ�ʦ��ݵ�½ϵͳ,��������ĵ�½�ʺź�����\n");
    printf("��½�ʺ�(��ʦ���):");
    scanf("%s", teacherId);
    printf("����:");
    scanf("%s", teacherPassword);
    tmpTeacherInfo = pTeacherInfoHead;
    if (NULL == tmpTeacherInfo) return FUNCTION_FAILED;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(teacherId, tmpTeacherInfo->teacherId)) {                    /*�ҵ����ʺ���Ϣ*/
            haveTeacherInfo = true;                                                /*���ô��ڱ�־*/
            if (0 == strcmp(teacherPassword, tmpTeacherInfo->teacherPassword)) {    /*��������Ҳ��ȷ*/
                strcpy(currentUserName, teacherId);                                /*���浱ǰ�ʺ�*/
                strcpy(currentUserType, "teacher");                                /*���õ�ǰ���Ϊ����Ա*/
                ShowTeacherMenu();                                                /*��ʾ��ʦ���������˵�*/
                return FUNCTION_SUCCESS;
            } else {
                printf("�Բ���,��������������!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpTeacherInfo = tmpTeacherInfo->next;
        }
    }
    if (false == haveTeacherInfo) {
        printf("�Բ���,������Ľ�ʦ��Ų�����!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;
}

int StudentLogin() {
    char studentNumber[20], studentPassword[20];
    bool haveStudentInfo = false;        /*ϵͳ�Ƿ���ڸ��ʺű�־*/
    StudentInfo *tmpStudentInfo;
    printf("���,������ѡ�����ѧ����ݵ�½ϵͳ,��������ĵ�½�ʺź�����\n");
    printf("��½�ʺ�(ѧ��):");
    scanf("%s", studentNumber);
    printf("����:");
    scanf("%s", studentPassword);
    tmpStudentInfo = pStudentInfoHead;
    if (NULL == tmpStudentInfo) return FUNCTION_FAILED;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(studentNumber, tmpStudentInfo->studentNumber)) {            /*�ҵ����ʺ���Ϣ*/
            haveStudentInfo = true;                                                /*���ô��ڱ�־*/
            if (0 == strcmp(studentPassword, tmpStudentInfo->studentPassword)) {    /*��������Ҳ��ȷ*/
                strcpy(currentUserName, studentNumber);                            /*���浱ǰ�ʺ�*/
                strcpy(currentUserType, "student");                                /*���õ�ǰ���Ϊ����Ա*/
                ShowStudentMenu();                                                /*��ʾ��ʦ���������˵�*/
                return FUNCTION_SUCCESS;
            } else {
                printf("�Բ���,��������������!");
                return FUNCTION_FAILED;
            }
        } else {
            tmpStudentInfo = tmpStudentInfo->next;
        }
    }
    if (false == haveStudentInfo) {
        printf("�Բ���,�������ѧ�Ų�����!");
        return FUNCTION_FAILED;
    }
    return FUNCTION_SUCCESS;
}

void ShowAdminMenu() {
    int select = 0;
    while (7 != select) {
        printf("���,����Ա,��ӵ���������Щ����,��ͨ��ѡ����Ӧ����Ž���\n");
        printf("1--���������޸�\n");
        printf("2--��ʦ��Ϣ����\n");
        printf("3--ѧ����Ϣ����\n");
        printf("4--�ɼ���Ϣ����\n");
        printf("5--�γ���Ϣ����\n");
        printf("6--�ڿ���Ϣ����\n");
        printf("7--�˳���½ϵͳ\n");
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

void AdminPasswordModify() {            /*����Ա�޸��Լ�������*/
    char oldPassword[20], newPassword[20], newPassword2[20];
    printf("�����뵱ǰ������:\n");
    scanf("%s", oldPassword);
    AdminInfo *tmpAdminInfo = pAdminInfoHead;
    while (NULL != tmpAdminInfo) {
        if (0 == strcmp(currentUserName, tmpAdminInfo->adminName)) {    /*�����ҵ�Ҫ�޸ĵļ�¼*/
            if (0 == strcmp(oldPassword, tmpAdminInfo->password)) {    /*�������������ȷ*/
                printf("�������µ�����:\n");
                scanf("%s", newPassword);
                printf("���ٴ�ȷ��������:\n");
                scanf("%s", newPassword2);
                if (0 == strcmp(newPassword, newPassword2)) {            /*��������µ�����һ��*/
                    strcpy(tmpAdminInfo->password, newPassword);
                    printf("�����޸ĳɹ�!\n");
                } else
                    printf("�Բ���,����������������벻һ��!\n");
            } else {
                printf("�Բ���,��ľ��������벻��ȷ!\n");
            }
            break;
        } else {
            tmpAdminInfo = tmpAdminInfo->next;
        }
    }

}

void TeacherInfoManage() {                /*��ʦ��Ϣ����*/
    int select = 0;
    while (5 != select) {
        printf("���,����Ա,�����ڽ�����ǽ�ʦ��Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--��ʦ��Ϣ�鿴  2--��ʦ��Ϣ���  3--��ʦ��Ϣ�޸�  4--��ʦ��Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void TeacherInfoView() {
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    printf("��ʦ��� ����   �Ա�    ��������       ��½���� ��ס��ַ\n");
    if (NULL == tmpTeacherInfo) printf("�Բ���,Ŀǰ���������κν�ʦ��Ϣ!\n");
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
    printf("�������ʦ���:");
    scanf("%s", teacherInfo.teacherId);
    printf("�������ʦ����:");
    scanf("%s", teacherInfo.teacherName);
    printf("�������ʦ�Ա�:");
    scanf("%s", teacherInfo.teacherSex);
    printf("�������ʦ��������:");
    scanf("%s", teacherInfo.teacherBirthTime);
    printf("�������ʦ��½����:");
    scanf("%s", teacherInfo.teacherPassword);
    printf("�������ʦ��ס��ַ:");
    scanf("%s", teacherInfo.teacherAddress);
    teacherInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneTeacherInfo(&teacherInfo))
        printf("��ʦ��Ϣ��ӳɹ�!\n");
}

void TeacherInfoModify() {
    char teacherId[20];
    bool haveTeacherId = false;
    TeacherInfo *tmpTeacherInfo;
    printf("������Ҫ�޸ĵĽ�ʦ���:");
    scanf("%s", teacherId);
    tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(tmpTeacherInfo->teacherId, teacherId)) {  /*�ҵ�Ҫ�޸ĵĽ�ʦ��Ϣ��¼*/
            haveTeacherId = true;                                /*�޸Ľ�ʦ��Ŵ��ڱ�־*/
            printf("��ʦ���Ϊ%s����Ϣ����:\n", teacherId);        /*��ʾ�ý�ʦ��ԭ����Ϣ*/
            printf("��ʦ����: %s\n", tmpTeacherInfo->teacherName);
            printf("��ʦ�Ա�: %s\n", tmpTeacherInfo->teacherSex);
            printf("��ʦ����: %s\n", tmpTeacherInfo->teacherPassword);
            printf("��ʦ����: %s\n", tmpTeacherInfo->teacherBirthTime);
            printf("��ʦ��ס��ַ: %s\n", tmpTeacherInfo->teacherAddress);
            printf("������ý�ʦ������Ϣ:\n");                    /*�����������ʦ������Ϣ*/
            printf("��ʦ����:");
            scanf("%s", tmpTeacherInfo->teacherName);
            printf("��ʦ�Ա�:");
            scanf("%s", tmpTeacherInfo->teacherSex);
            printf("��ʦ����:");
            scanf("%s", tmpTeacherInfo->teacherPassword);
            printf("��ʦ����:");
            scanf("%s", tmpTeacherInfo->teacherBirthTime);
            printf("��ʦ��ס��ַ:");
            scanf("%s", tmpTeacherInfo->teacherAddress);
            printf("��ʦ��Ϣ�޸ĳɹ�!");
            break;
        } else {
            tmpTeacherInfo = tmpTeacherInfo->next;
        }
    }
    if (false == haveTeacherId)
        printf("�Բ���,�������Ҫ�޸ĵĽ�ʦ���!\n");
}

void TeacherInfoDelete() {
    char teacherId[20];                            /*��ɾ���Ľ�ʦ���*/
    printf("��������Ҫɾ���Ľ�ʦ���:");
    scanf("%s", teacherId);
    TeacherInfo *tmpTeacherInfoA, *tmpTeacherInfoB;
    tmpTeacherInfoA = tmpTeacherInfoB = pTeacherInfoHead;    /*tmpTeacherInfoBָ��Ҫɾ���ļ�¼��tmpTeacherInfoAָ��ǰһ����¼*/
    if (NULL == tmpTeacherInfoB) return;
    while (NULL != tmpTeacherInfoB) {
        if (0 == strcmp(tmpTeacherInfoB->teacherId, teacherId)) {
            if (tmpTeacherInfoB == pTeacherInfoHead && tmpTeacherInfoB->next == NULL) {    //���ϵͳֻ��һ����ʦ��Ϣ
                free(pTeacherInfoHead);
                pTeacherInfoHead = NULL;
                printf("��ʦ��Ϣɾ���ɹ�!\n");
                /*�˴�����ټ���ɾ������ʦ�ڿε���Ϣ*/
                return;
            }
            tmpTeacherInfoA->next = tmpTeacherInfoB->next;
            if (pTeacherInfoHead == tmpTeacherInfoB)
                pTeacherInfoHead = tmpTeacherInfoB->next;
            free(tmpTeacherInfoB);
            printf("��ʦ��Ϣɾ���ɹ�!\n");
            /*�˴�����ټ���ɾ������ʦ�ڿε���Ϣ*/
            return;
        } else {
            tmpTeacherInfoA = tmpTeacherInfoB;
            tmpTeacherInfoB = tmpTeacherInfoB->next;
        }
    }
    printf("�Բ��𣬲����ڸý�ʦ��ŵ���Ϣ!\n");
}

void StudentInfoManage() {                /*ѧ����Ϣ����*/
    int select = 0;
    while (5 != select) {
        printf("���,����Ա,�����ڽ������ѧ����Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--ѧ����Ϣ�鿴  2--ѧ����Ϣ���  3--ѧ����Ϣ�޸�  4--ѧ����Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void StudentInfoAdd() {    /*ѧ����Ϣ���*/
    StudentInfo studentInfo;
    printf("������ѧ��:");
    scanf("%s", studentInfo.studentNumber);
    printf("����������:");
    scanf("%s", studentInfo.studentName);
    printf("�������Ա�:");
    scanf("%s", studentInfo.studentSex);
    printf("�������������:");
    scanf("%s", studentInfo.studentBirthTime);
    printf("������ѧ����½����:");
    scanf("%s", studentInfo.studentPassword);
    printf("������ѧ����ס��ַ:");
    scanf("%s", studentInfo.studentAddress);
    studentInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneStudentInfo(&studentInfo))
        printf("ѧ����Ϣ��ӳɹ�!\n");
}

void StudentInfoModify() { /*ѧ����Ϣ�޸�*/
    char studentNumber[20];
    bool haveStudentNumber = false;    /*�Ƿ���ڸ�ѧ��ѧ����־����*/
    StudentInfo *tmpStudentInfo;
    printf("������Ҫ�޸ĵ�ѧ��ѧ��:");
    scanf("%s", studentNumber);
    tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(tmpStudentInfo->studentNumber, studentNumber)) {  /*�ҵ�Ҫ�޸ĵ�ѧ����Ϣ��¼*/
            haveStudentNumber = true;                            /*�޸�ѧ�Ŵ��ڱ�־*/
            printf("ѧ��Ϊ%s����Ϣ����:\n", studentNumber);        /*��ʾ��ѧ����ԭ����Ϣ*/
            printf("ѧ������: %s\n", tmpStudentInfo->studentName);
            printf("ѧ���Ա�: %s\n", tmpStudentInfo->studentSex);
            printf("ѧ������: %s\n", tmpStudentInfo->studentPassword);
            printf("ѧ������: %s\n", tmpStudentInfo->studentBirthTime);
            printf("ѧ����ס��ַ: %s\n", tmpStudentInfo->studentAddress);
            printf("�������ѧ��������Ϣ:\n");                    /*�����������ʦ������Ϣ*/
            printf("ѧ������:");
            scanf("%s", tmpStudentInfo->studentName);
            printf("ѧ���Ա�:");
            scanf("%s", tmpStudentInfo->studentSex);
            printf("ѧ������:");
            scanf("%s", tmpStudentInfo->studentPassword);
            printf("ѧ������:");
            scanf("%s", tmpStudentInfo->studentBirthTime);
            printf("ѧ����ס��ַ:");
            scanf("%s", tmpStudentInfo->studentAddress);
            printf("ѧ����Ϣ�޸ĳɹ�!\n");
            break;
        } else {
            tmpStudentInfo = tmpStudentInfo->next;
        }
    }
    if (false == haveStudentNumber)
        printf("�Բ���,�������Ҫ�޸ĵ�ѧ��!\n");
}

void StudentInfoDelete() { /*ѧ����Ϣɾ��*/
    char studentNumber[20];            /*��ɾ����ѧ��ѧ��*/
    printf("��������Ҫɾ����ѧ��ѧ��:");
    scanf("%s", studentNumber);
    StudentInfo *tmpStudentInfoA, *tmpStudentInfoB;
    tmpStudentInfoA = tmpStudentInfoB = pStudentInfoHead;    /*tmpStudentInfoBָ��Ҫɾ���ļ�¼��tmpStudentInfoAָ��ǰһ����¼*/
    if (NULL == tmpStudentInfoB) return;
    while (NULL != tmpStudentInfoB) {
        if (0 == strcmp(tmpStudentInfoB->studentNumber, studentNumber)) {
            if (tmpStudentInfoB == pStudentInfoHead && tmpStudentInfoB->next == NULL) {    //���ϵͳֻ��һ����ʦ��Ϣ
                free(pStudentInfoHead);
                pStudentInfoHead = NULL;
                printf("ѧ����Ϣɾ���ɹ�!\n");
                /*�˴�����ټ���ɾ����ѧ���ĳɼ���Ϣ*/
                return;
            }
            tmpStudentInfoA->next = tmpStudentInfoB->next;
            if (pStudentInfoHead == tmpStudentInfoB)
                pStudentInfoHead = tmpStudentInfoB->next;
            free(tmpStudentInfoB);
            printf("ѧ����Ϣɾ���ɹ�!\n");
            /*�˴�����ټ���ɾ����ѧ���ĳɼ���Ϣ*/
            return;
        } else {
            tmpStudentInfoA = tmpStudentInfoB;
            tmpStudentInfoB = tmpStudentInfoB->next;
        }
    }
    printf("�Բ��𣬲����ڸ�ѧ�ŵ�ѧ����Ϣ!\n");
}

void Admin_ScoreInfoManage() {            /*����Ա�Գɼ���Ϣ����*/
    int select = 0;
    while (5 != select) {
        printf("���,����Ա,�����ڽ�����ǳɼ���Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--�ɼ���Ϣ�鿴  2--�ɼ���Ϣ���  3--�ɼ���Ϣ�޸�  4--�ɼ���Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void ScoreInfoView() { /*�ɼ���Ϣ�鿴*/
    char studentName[20], courseName[20];
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    if (NULL == tmpScoreInfo) {
        printf("�Բ���,����ϵͳ�л������ڳɼ���Ϣ��!\n");
        return;
    }
    printf("ϵͳ�ĳɼ���Ϣ����:\n");
    printf("ѧ��            ����    �γ̱��     �γ�����    �ɼ�\n");
    while (NULL != tmpScoreInfo) {    /*�������гɼ���Ϣ*/
        GetStudentName(tmpScoreInfo->studentNumber, studentName);    /*�õ���ѧ�ŵ�ѧ������*/
        GetCourseName(tmpScoreInfo->courseId, courseName);            /*�õ��ÿγ̵�����*/
        printf("%s\t", tmpScoreInfo->studentNumber);
        printf("%s\t", studentName);
        printf("%d\t", tmpScoreInfo->courseId);
        printf("%s\t", courseName);
        printf("%f\n", tmpScoreInfo->score);

        tmpScoreInfo = tmpScoreInfo->next;
    }
}

/*****************************************************************
����ѧ�ŵõ�ѧ������: studentNumber-��ڲ��� studentName-���ڲ���
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
���ݿγ̱�ŵõ��γ���: courseId-��ڲ��� courseName-���ڲ���
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


bool IsHavingStudentNumber(char *studentNumber) {    /*���ϵͳ�Ƿ���ڸ�ѧ�ŵ�ѧ��*/
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

bool IsHavingCourseId(int courseId) {                /*���ϵͳ�Ƿ���ڸÿγ���Ϣ*/
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
        printf("���,����Ա,�����ڽ�����ǿγ���Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--�γ���Ϣ�鿴  2--�γ���Ϣ���  3--�γ���Ϣ�޸�  4--�γ���Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void CourseInfoView() {                    /*�γ���Ϣ�鿴*/
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    if (NULL == tmpCourseInfo) {
        printf("�Բ���,Ŀǰϵͳ�л�û�пγ���Ϣ��!\n");
        return;
    }
    printf("�γ̱��    �γ�����        �Ͽ�ʱ��          �Ͽν���\n");
    while (NULL != tmpCourseInfo) {
        printf("%d\t  ", tmpCourseInfo->courseId);
        printf("%s\t", tmpCourseInfo->courseName);
        printf("%s\t", tmpCourseInfo->courseTime);
        printf("%s\n", tmpCourseInfo->courseClassroom);

        tmpCourseInfo = tmpCourseInfo->next;
    }
}

void CourseInfoAdd() {                    /*�γ���Ϣ���*/
    /* �γ̱�Ų���Ҫ����,�ɳ����Զ�����*/
    CourseInfo courseInfo;
    printf("������γ�����:");
    scanf("%s", courseInfo.courseName);
    printf("�������Ͽν���:");
    scanf("%s", courseInfo.courseClassroom);
    printf("�������Ͽ�ʱ��:");
    scanf("%s", courseInfo.courseTime);
    courseInfo.next = NULL;
    if (FUNCTION_SUCCESS == AddOneCourseInfo(&courseInfo))
        printf("�γ���Ϣ��ӳɹ�!\n");
}

void CourseInfoModify() {                /*�γ���Ϣ�޸�*/
    int courseId;
    CourseInfo *tmpCourseInfo = pCourseInfoHead;
    printf("��������Ҫ�޸ĵĿγ̵Ŀγ̱��:");
    scanf("%d", &courseId);
    while (NULL != tmpCourseInfo) {
        if (courseId == tmpCourseInfo->courseId) {    /*�ҵ����޸ĵĿγ̼�¼*/
            printf("�γ̱��Ϊ%d�Ŀγ���Ϣ����:\n", &courseId);
            printf("�γ�����: %s\n", tmpCourseInfo->courseName);
            printf("�Ͽ�ʱ��: %s\n", tmpCourseInfo->courseTime);
            printf("�Ͽν���: %s\n", tmpCourseInfo->courseClassroom);
            printf("�������µ���Ϣ:\n");
            printf("�γ�����:");
            scanf("%s", tmpCourseInfo->courseName);
            printf("�Ͽ�ʱ��:");
            scanf("%s", tmpCourseInfo->courseTime);
            printf("�Ͽν���:");
            scanf("%s", tmpCourseInfo->courseClassroom);
            printf("�γ���Ϣ�޸ĳɹ�!\n");
            return;
        }
        tmpCourseInfo = tmpCourseInfo->next;
    }
    printf("�Ҳ����ÿγ̵���Ϣ!\n");
}

void CourseInfoDelete() {                /*�γ���Ϣɾ��*/
    int courseId;    /*��ɾ���Ŀγ̱��*/
    printf("�����뽫��ɾ���Ŀγ̵Ŀγ̱��:");
    scanf("%d", &courseId);
    if (IsCourseInTeachInfo(courseId)) {
        printf("�Բ���,�ڿ���Ϣ�д��ڱ��γ���Ϣ,���Ȱ��ڿ���Ϣ�е������Ϣɾ������ɾ�����γ���Ϣ!\n");
        return;
    }
    if (IsCourseInScoreInfo(courseId)) {
        printf("�Բ���,�ɼ���Ϣ�д��ڱ��γ���Ϣ,���Ȱѳɼ���Ϣ�е������Ϣɾ������ɾ�����γ���Ϣ!\n");
        return;
    }
    CourseInfo *tmpCourseInfoA, *tmpCourseInfoB;
    tmpCourseInfoA = tmpCourseInfoB = pCourseInfoHead;    /*tmpCourseInfoBָ��Ҫɾ���ļ�¼��tmpCourseInfoAָ��ǰһ����¼*/
    if (NULL == tmpCourseInfoB) return;
    while (NULL != tmpCourseInfoB) {
        if (tmpCourseInfoB->courseId == courseId) {
            if (tmpCourseInfoB == pCourseInfoHead && tmpCourseInfoB->next == NULL) {    //���ϵͳֻ��һ���γ���Ϣ
                free(pCourseInfoHead);
                pCourseInfoHead = NULL;
                printf("�γ���Ϣɾ���ɹ�!\n");
                return;
            }
            tmpCourseInfoA->next = tmpCourseInfoB->next;
            if (pCourseInfoHead == tmpCourseInfoB)
                pCourseInfoHead = tmpCourseInfoB->next;
            free(tmpCourseInfoB);
            printf("�γ���Ϣɾ���ɹ�!\n");
            return;
        } else {
            tmpCourseInfoA = tmpCourseInfoB;
            tmpCourseInfoB = tmpCourseInfoB->next;
        }
    }
    printf("�Բ��𣬲����ڸÿγ̱�ŵ���Ϣ!\n");
}

bool IsCourseInTeachInfo(int courseId) {    /*�ж�ĳ�ſγ��Ƿ����ڿ���Ϣ�д���*/
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

bool IsCourseInScoreInfo(int courseId) {    /*�ж�ĳ�ſγ��Ƿ��ڳɼ���Ϣ�д���*/
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
        printf("���,����Ա,�����ڽ�������ڿ���Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--�ڿ���Ϣ�鿴  2--�ڿ���Ϣ���  3--�ڿ���Ϣ�޸�  4--�ڿ���Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void CourseTeachInfoView() {            /*�ڿ���Ϣ�鿴*/
    char courseName[20], teacherName[20];
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    if (NULL == tmpCourseTeachInfo) {
        printf("�Բ���,Ŀǰϵͳ�л��������ڿ���Ϣ��!\n");
        return;
    }
    printf("�γ̱��  �γ�����    ��ʦ���    ��ʦ����\n");
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

void GetTeacherName(char *teacherId, char *teacherName) { /*���ݽ�ʦ��ŵõ���ʦ����*/
    TeacherInfo *tmpTeacherInfo = pTeacherInfoHead;
    while (NULL != tmpTeacherInfo) {
        if (0 == strcmp(tmpTeacherInfo->teacherId, teacherId)) { /*�ҵ��ý�ʦ��Ϣ*/
            strcpy(teacherName, tmpTeacherInfo->teacherName);
            break;
        }
        tmpTeacherInfo = tmpTeacherInfo->next;
    }

}

void CourseTeachInfoAdd() {                /*�ڿ���Ϣ���*/
    CourseTeachInfo courseTeachInfo;
    printf("�������ڿογ̱��:");
    scanf("%d", &courseTeachInfo.courseId);
    if (!IsHavingCourseId(courseTeachInfo.courseId)) {
        printf("�Բ���,�ÿγ̱�Ų�����,��ȷ�Ϻ��ٲ���!\n");
        return;
    }
    printf("�������ڿν�ʦ���:");
    scanf("%s", courseTeachInfo.teacherId);
    if (!IsHavingTeacherId(courseTeachInfo.teacherId)) {
        printf("�Բ���,�ý�ʦ��Ų�����,��ȷ�Ϻ��ٲ���!\n");
        return;
    }
    courseTeachInfo.next = NULL;
    /*�˴�����ټ����ж�ϵͳ���Ƿ��Ѿ����ڱ��ſγ̵��ڿ���Ϣ*/
    if (FUNCTION_SUCCESS == AddOneCourseTeachInfo(&courseTeachInfo))
        printf("�ڿ���Ϣ��ӳɹ�!\n");
}

bool IsHavingTeacherId(char *teacherId) { /*�ж��Ƿ����ĳ����ʦ��Ϣ*/
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

void CourseTeachInfoModify() {            /*�ڿ���Ϣ�޸�*/
    int courseId;
    char teacherId[20];
    CourseTeachInfo *tmpCourseTeachInfo = pCourseTeachInfoHead;
    printf("��������Ҫ�޸ĵĿγ̱��(����):");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("�Բ���,������Ŀγ̱�Ų�����!\n");
        return;
    }
    while (NULL != tmpCourseTeachInfo) {
        if (courseId == tmpCourseTeachInfo->courseId) { /*�ҵ�Ҫ�޸ĵ��ڿ���Ϣ*/
            printf("��ǰ���ڿν�ʦ�����:%s\n", tmpCourseTeachInfo->teacherId);
            printf("�������µ��ڿν�ʦ���:");
            scanf("%s", teacherId);
            if (!IsHavingTeacherId(teacherId)) {
                printf("�Բ���,������Ľ�ʦ���ϵͳ�в�����!\n");
                return;
            }
            strcpy(tmpCourseTeachInfo->teacherId, teacherId);
            printf("�ڿ���Ϣ�޸ĳɹ�!\n");
            return;
        }
        tmpCourseTeachInfo = tmpCourseTeachInfo->next;
    }
    printf("�Բ���,û���ҵ���Ӧ�γ̱�ŵ��ڿ���Ϣ!\n");
}

void CourseTeachInfoDelete() {            /*�ڿ���Ϣɾ��*/
    int courseId;                        /*��ɾ���Ŀγ̱��*/
    printf("��������Ҫɾ���Ŀγ̱��:");
    scanf("%d", &courseId);
    CourseTeachInfo *tmpCourseTeachInfoA, *tmpCourseTeachInfoB;
    tmpCourseTeachInfoA = tmpCourseTeachInfoB = pCourseTeachInfoHead;    /*tmpCourseTeachInfoBָ��Ҫɾ���ļ�¼��tmpCourseTeachInfoAָ��ǰһ����¼*/
    if (NULL == tmpCourseTeachInfoB) return;
    while (NULL != tmpCourseTeachInfoB) {
        if (courseId == tmpCourseTeachInfoB->courseId) {
            if (tmpCourseTeachInfoB == pCourseTeachInfoHead && tmpCourseTeachInfoB->next == NULL) {    //���ϵͳֻ��һ���ڿ���Ϣ
                free(pCourseTeachInfoHead);
                pCourseTeachInfoHead = NULL;
                printf("�ڿ���Ϣɾ���ɹ�!\n");
                return;
            }
            tmpCourseTeachInfoA->next = tmpCourseTeachInfoB->next;
            if (pCourseTeachInfoHead == tmpCourseTeachInfoB)
                pCourseTeachInfoHead = tmpCourseTeachInfoB->next;
            free(tmpCourseTeachInfoB);
            printf("�ڿ���Ϣɾ���ɹ�!\n");
            return;
        } else {
            tmpCourseTeachInfoA = tmpCourseTeachInfoB;
            tmpCourseTeachInfoB = tmpCourseTeachInfoB->next;
        }
    }
    printf("�Բ��𣬲����ڸÿγ̱�ŵ���Ϣ!\n");
}

void ShowTeacherMenu() {
    int select = 0;
    while (4 != select) {
        printf("���,��ʦ,��ӵ���������Щ����,��ͨ��ѡ����Ӧ����Ž���\n");
        printf("1--������Ϣ�޸�\n");
        printf("2--ѧ����Ϣ����:(ֻ�ܲ鿴ѧ������Ϣ)\n");
        printf("3--�ɼ���Ϣ����: ��ӡ��޸ġ�ɾ��(ֻ�޸���ʦ���ڿγ�),��ѯ(����ѧ���ɼ�)\n");
        printf("4--�˳���½ϵͳ\n");
        printf("��������Ӧ�Ĺ��ܺ�:");
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
        if (0 == strcmp(currentUserName, tmpTeacherInfo->teacherId)) { /*�ҵ��ý�ʦ�ļ�¼��Ϣ*/
            printf("��ʦ,���,��ĵ�ǰ������Ϣ����:\n");
            printf("��ʦ����: %s\n", tmpTeacherInfo->teacherName);
            printf("��ʦ�Ա�: %s\n", tmpTeacherInfo->teacherSex);
            printf("��ʦ����: %s\n", tmpTeacherInfo->teacherBirthTime);
            printf("��ʦ��½����: %s\n", tmpTeacherInfo->teacherPassword);
            printf("��ʦ��ס��ַ: %s\n", tmpTeacherInfo->teacherAddress);
            printf("�������µ���Ϣ:\n");
            printf("�������:");
            scanf("%s", tmpTeacherInfo->teacherName);
            printf("����Ա�:");
            scanf("%s", tmpTeacherInfo->teacherSex);
            printf("�������:");
            scanf("%s", tmpTeacherInfo->teacherBirthTime);
            printf("��ĵ�½����:");
            scanf("%s", tmpTeacherInfo->teacherPassword);
            printf("��ľ�ס��ַ:");
            scanf("%s", tmpTeacherInfo->teacherAddress);
            printf("��Ϣ�޸ĳɹ�!");
        }
        tmpTeacherInfo = tmpTeacherInfo->next;
    }
}

void StudentInfoView() {    /*ѧ����Ϣ�鿴*/
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    printf("ѧ��            ����   �Ա�      ��������       ��½���� ��ס��ַ\n");
    if (NULL == tmpStudentInfo) printf("�Բ���,Ŀǰ���������κ�ѧ����Ϣ!\n");
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

void Teacher_ScoreInfoManage() {    /*��ʦ�Գɼ���Ϣ�Ĺ���*/
    int select = 0;
    while (5 != select) {
        printf("���,��ʦ,�����ڽ�����ǳɼ���Ϣ������ģ��,ӵ������Ĺ���\n");
        printf("1--�ɼ���Ϣ�鿴  2--�ɼ���Ϣ���  3--�ɼ���Ϣ�޸�  4--�ɼ���Ϣɾ��  5--�����ϼ��˵�\n");
        printf("�������Ӧ�Ĺ��ܺ�:");
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
    ShowAdminMenu();    /*�����ϼ��˵�*/
}

void ScoreInfoAdd() {            /*��ʦ�Գɼ������*/
    char studentNumber[20];
    int courseId;
    float score;
    ScoreInfo scoreInfo;
    printf("������ѧ����ѧ��:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {    /*��������ѧ�Ų�����*/
        printf("�Բ���,����ӳɼ���ѧ��������,��ȷ�Ϻ��ٲ���!\n");
        return;
    }
    printf("������γ̱��:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {            /*�������Ŀγ̲�����*/
        printf("�Բ���,����ӳɼ��Ŀγ̶��󲻴���,��ȷ�Ϻ��ٲ���!\n");
        return;
    }

    if (0 == strcmp(currentUserType, "teacher")) {    /*�����ǰ��½���ǽ�ʦ�����Ҫ���в���Ȩ���ж�*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("�Բ���,��ʦ,��Ϊ��û�н̸��ſ����ǲ�����Ӹ��ſγ̵ĳɼ���!\n");
            return;
        }
    }

    printf("������ɼ�:");
    scanf("%f", &score);
    strcpy(scoreInfo.studentNumber, studentNumber);
    scoreInfo.courseId = courseId;
    scoreInfo.score = score;
    if (FUNCTION_SUCCESS == AddOneScoreInfo(&scoreInfo))
        printf("�ɼ���Ϣ��ӳɹ�!\n");
}

bool CanTeacherOpeScore(int courseId, char *teacherId) { /*�ж�ĳ����ʦ�Ƿ������ĳ�ſγ̳ɼ���Ȩ��*/
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

void ScoreInfoModify() {        /*��ʦ�Գɼ����޸�*/
    char studentNumber[20];
    int courseId;
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    printf("��������Ҫ�޸ĳɼ���¼��ѧ��ѧ��:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {
        printf("�Բ���,�����ڸ�ѧ����Ϣ,��ȷ����������Ƿ���ȷ!\n");
        return;
    }
    printf("��������Ҫ�޸ĳɼ���¼�Ŀγ̱��:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("�Բ���,�����ڸÿγ���Ϣ,��ȷ����������Ƿ���ȷ!\n");
        return;
    }

    if (0 == strcmp(currentUserType, "teacher")) {    /*�����ǰ��½���ǽ�ʦ�����Ҫ���в���Ȩ���ж�*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("�Բ���,��ʦ,��û���޸����ſγ̳ɼ���Ȩ��!\n");
            return;
        }
    }

    while (NULL != tmpScoreInfo) {
        if ((0 == strcmp(tmpScoreInfo->studentNumber, studentNumber)) && (tmpScoreInfo->courseId == courseId)) {
            printf("��ǰѧ��Ϊ%s�γ̱��Ϊ%d�ĳɼ���: %f\n", studentNumber, courseId, tmpScoreInfo->score);
            printf("�������µĳɼ�:");
            scanf("%f", &tmpScoreInfo->score);
            printf("�ɼ���Ϣ�޸ĳɹ�!\n");
            return;
        }
        tmpScoreInfo = tmpScoreInfo->next;
    }
    printf("�Բ���,�Ҳ������������ĳɼ���¼��Ϣ!\n");
}

void ScoreInfoDelete() {            /*��ʦ�Գɼ���ɾ��*/
    char studentNumber[20];
    int courseId;
    printf("��������Ҫ�޸ĳɼ���¼��ѧ��ѧ��:");
    scanf("%s", studentNumber);
    if (!IsHavingStudentNumber(studentNumber)) {
        printf("�Բ���,�����ڸ�ѧ����Ϣ,��ȷ����������Ƿ���ȷ!\n");
        return;
    }
    printf("��������Ҫ�޸ĳɼ���¼�Ŀγ̱��:");
    scanf("%d", &courseId);
    if (!IsHavingCourseId(courseId)) {
        printf("�Բ���,�����ڸÿγ���Ϣ,��ȷ����������Ƿ���ȷ!\n");
        return;
    }
    if (0 == strcmp(currentUserType, "teacher")) {    /*�����ǰ��½���ǽ�ʦ�����Ҫ���в���Ȩ���ж�*/
        if (!CanTeacherOpeScore(courseId, currentUserName)) {
            printf("�Բ���,��ʦ,��û�в������ſγ̵�Ȩ��!\n");
            return;
        }
    }


    ScoreInfo *tmpScoreInfoA, *tmpScoreInfoB;
    tmpScoreInfoA = tmpScoreInfoB = pScoreInfoHead;    /*tmpScoreInfoBָ��Ҫɾ���ļ�¼��tmpScoreInfoAָ��ǰһ����¼*/
    if (NULL == tmpScoreInfoB) return;
    while (NULL != tmpScoreInfoB) {
        if ((0 == strcmp(studentNumber, tmpScoreInfoB->studentNumber)) && (courseId == tmpScoreInfoB->courseId)) {
            if (tmpScoreInfoB == pScoreInfoHead && tmpScoreInfoB->next == NULL) {    //���ϵͳֻ��һ���ɼ���Ϣ
                free(pScoreInfoHead);
                pScoreInfoHead = NULL;
                printf("�ɼ���Ϣɾ���ɹ�!\n");
                return;
            }
            tmpScoreInfoA->next = tmpScoreInfoB->next;
            if (pScoreInfoHead == tmpScoreInfoB)
                pScoreInfoHead = tmpScoreInfoB->next;
            free(tmpScoreInfoB);
            printf("�ɼ���Ϣɾ���ɹ�!\n");
            return;
        } else {
            tmpScoreInfoA = tmpScoreInfoB;
            tmpScoreInfoB = tmpScoreInfoB->next;
        }
    }
    printf("�Բ��𣬷��������ĳɼ���Ϣ!\n");
}

void ShowStudentMenu() {
    int select = 0;
    while (3 != select) {
        printf("���,ͬѧ,��ӵ���������Щ����,��ͨ��ѡ����Ӧ����Ž���\n");
        printf("1--������Ϣ�޸�\n");
        printf("2--���˳ɼ���ѯ\n");
        printf("3--�˳���½ϵͳ\n");
        printf("��������Ӧ�Ĺ��ܺ�:");
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

void StudentSelfInfoModify() { /*ѧ��������Ϣ�޸�*/
    StudentInfo *tmpStudentInfo = pStudentInfoHead;
    while (NULL != tmpStudentInfo) {
        if (0 == strcmp(currentUserName, tmpStudentInfo->studentNumber)) { /*�ҵ���ѧ���ļ�¼��Ϣ*/
            printf("ͬѧ,���,��ĵ�ǰ������Ϣ����:\n");
            printf("ѧ������: %s\n", tmpStudentInfo->studentName);
            printf("ѧ���Ա�: %s\n", tmpStudentInfo->studentSex);
            printf("��ʦ����: %s\n", tmpStudentInfo->studentBirthTime);
            printf("ѧ����½����: %s\n", tmpStudentInfo->studentPassword);
            printf("ѧ����ס��ַ: %s\n", tmpStudentInfo->studentAddress);
            printf("�������µ���Ϣ:\n");
            printf("�������:");
            scanf("%s", tmpStudentInfo->studentName);
            printf("����Ա�:");
            scanf("%s", tmpStudentInfo->studentSex);
            printf("�������:");
            scanf("%s", tmpStudentInfo->studentBirthTime);
            printf("��ĵ�½����:");
            scanf("%s", tmpStudentInfo->studentPassword);
            printf("��ľ�ס��ַ:");
            scanf("%s", tmpStudentInfo->studentAddress);
            printf("��Ϣ�޸ĳɹ�!");
        }
        tmpStudentInfo = tmpStudentInfo->next;
    }
}

void Student_ScoreInfoView() { /*ѧ�����˳ɼ���ѯ*/
    char studentName[20], courseName[20];
    bool haveScore = false; /*ϵͳ���Ƿ���ڸ�ͬѧ�ĳɼ���Ϣ��־����*/
    ScoreInfo *tmpScoreInfo = pScoreInfoHead;
    if (NULL == tmpScoreInfo) {
        printf("�Բ���,����ϵͳ�л������ڳɼ���Ϣ��!\n");
        return;
    }
    printf("ϵͳ�ĳɼ���Ϣ����:\n");
    printf("ѧ��            ����    �γ̱��     �γ�����    �ɼ�\n");
    while (NULL != tmpScoreInfo) {    /*�������гɼ���Ϣ*/
        if (0 == strcmp(tmpScoreInfo->studentNumber, currentUserName)) {
            haveScore = true;
            GetStudentName(tmpScoreInfo->studentNumber, studentName);    /*�õ���ѧ�ŵ�ѧ������*/
            GetCourseName(tmpScoreInfo->courseId, courseName);            /*�õ��ÿγ̵�����*/
            printf("%s\t", tmpScoreInfo->studentNumber);
            printf("%s\t", studentName);
            printf("%d\t", tmpScoreInfo->courseId);
            printf("%s\t", courseName);
            printf("%f\n", tmpScoreInfo->score);
        }
        tmpScoreInfo = tmpScoreInfo->next;
    }
    if (!haveScore) printf("�Բ���,����ϵͳ�л������ڸ���ĳɼ���Ϣ!\n");
}

void SelectLoginType() {
    while (true) {
        printf("��ѡ�����½��ϵͳ�����: 1--����Ա���  2--��ʦ���  3--ѧ�����:");
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
    InitSystem();            //��ʼ��ϵͳ
    ShowWelcomeMenu();        //��ʾ��ӭ�˵�
    SelectLoginType();        //ѡ���½ϵͳ
    return 0;
}




