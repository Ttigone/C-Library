#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define filename "library.txt"
#define filename_user "Mybook.txt"
#define Length sizeof(Node)
typedef struct book
{
    int num;
    char Name[20];
    char author[20];
    float price;
}Bookimf;

typedef struct Node 
{
    Bookimf data;  
    struct Node* next;
}Node;

Node* Insertdata();
void Writedata();
Node* Insertdata_user();
void Writedata_user();
bool DeteleNode();
Node *Pospoint(Bookimf);

void Enter_Exit();
void Menu_1();
char Menu_2();

void Enterbook();
void FindBook();
void Mybook();
void AddBook();
void DeteleBook();
void Borrow();
void Revert();
void displayBook();

void putbook(Bookimf);
void printtip1();

int main(void)
{
    SetConsoleTitle("����У��ͼ���ϵͳ");
    Menu_1();Enter_Exit();
    while(1){
        char k = Menu_2();
        switch (k){
            case '1': FindBook();break;
            case '2': Mybook();break;
            case '3': AddBook();break;
            case '4': DeteleBook();break;
            case '5': Borrow();break;
            case '6': Revert();break;   
            case '7': displayBook();break;
            case '8': Enterbook();break;
            case 'T':
            case 't':{
                printf("�����˳�ϵͳ��1������ر�");
                Sleep(1000);
                exit(0);
            }
            default: printf("�������\n");
        }
    system("pause");
    }
    return 0;
}


void Menu_1(void)
{
    system("color 3");
    printf("*****************��ӭ�����㶫�����ѧ������У����ͼ�����ϵͳ*****************\n\n\n");
}
void Enter_Exit(void)
{
    int key;
    printf("\t\t\t\t1:��¼ϵͳ\n\n");
    printf("tip:�����\"��һ��\"�򿪸�ϵͳ(�ڴ���)����ô������\"2\"�����鼮¼�룬����һ�δ�ϵͳ(�ڴ���)\n    ʱ���ؽ����鼮¼��\n\n");
    printf("���Ĳ����ǣ�");
    scanf("%d", &key);
    while (key != 1 && key != 2){
        printf("������������������������룺");
        scanf("%d", &key);
    }
    if(key == 2)
        Enterbook();
    else;
}
char Menu_2(void)
{
	system("cls");
	char ch = 0;
    putchar('\n');putchar('\n');
    printf("        ***************************************************************        \n");
    printf("\n");
    printf("        1:�����鼮  -----------****************-------------  2:�ҵ����\n");
    printf("        3:�����鼮  -----------****************-------------  4:ɾ���鼮\n");
    printf("        5:�����鼮  -----------****************-------------  6:�黹�鼮\n");
    printf("        7:ͼ��ݲ���  ---------****************-------------  8:¼���鼮\n");
    putchar('\n');
    printf("        ------------------      t:�˳�ϵͳ        --------------------    \n");
    printf("\n");
    printf("        ***************************************************************        \n");
    printf("\n");
    printf("��ѡ����Ҫ���еĲ�����");
    while((ch = getchar()) == '\n');
    return ch;
}


Node* Insertdata()
{
    FILE *fp = fopen(filename, "r");
    Node *headpt = NULL, *tail = NULL;
    Bookimf keep;
    while(fscanf(fp, "%s %s %d %f", keep.Name, keep.author, &keep.num, &keep.price) != EOF){
        Node *Pmove = (Node *)malloc(Length);
        Pmove->data = keep;
        if(headpt == NULL)
            headpt = Pmove;
        if(tail != NULL)
            tail->next = Pmove;
        tail = Pmove;
        tail->next = NULL;
    }
    fclose(fp);
    return headpt;
}

void Writedata(Node *headpt)
{
    FILE *fp = fopen(filename, "w");
    Node *Pmove = headpt;
    while(Pmove != NULL){
        fprintf(fp, "%s %s %d %.1f\n", Pmove->data.Name, Pmove->data.author, Pmove->data.num, Pmove->data.price);
        Pmove = Pmove->next;
    }
    fclose(fp);
}

Node* Insertdata_user()
{
    FILE *fp = fopen(filename_user, "r");
    Node *headpt = NULL, *tail = NULL;
    Bookimf keep;
    while(fscanf(fp, "%s %s %d %f", keep.Name, keep.author, &keep.num, &keep.price) != EOF){
        Node *Pmove = (Node *)malloc(Length);
        Pmove->data = keep;
        if(headpt == NULL)
            headpt = Pmove;
        if(tail != NULL)
            tail->next = Pmove;
        tail = Pmove;
        tail->next = NULL;
    }
    fclose(fp);
    return headpt;
}
void Writedata_user(Node *headpt)
{
    FILE *fp = fopen(filename_user, "w");
    Node *Pmove = headpt;
    while(Pmove != NULL){
        fprintf(fp, "%s %s %d %.1f\n", Pmove->data.Name, Pmove->data.author, Pmove->data.num, Pmove->data.price);
        Pmove = Pmove->next;
    }
    fclose(fp);
}

bool DeteleNode(Bookimf tem)
{
    Node *headpt = Insertdata();
    Node *Pleft = headpt, *Pmove = headpt;
    while(Pmove->next != NULL && strcmp(Pmove->data.Name, tem.Name)){
        Pleft = Pmove;
        Pmove = Pmove->next;
    }
    if(Pmove->next == NULL && Pleft->next == NULL && !strcmp(Pmove->data.Name, tem.Name)){
        FILE *fp = fopen(filename, "w");
        //Node *Newheadpt = Insertdata();
        fclose(fp);
        //Writedata(Newheadpt);
        return true;
    }
    else if(Pmove->next == NULL && !strcmp(Pmove->data.Name, tem.Name)){
        free(Pmove);
        Pleft->next = NULL;
        Writedata(headpt);
        return true;
    }
    else if(Pmove->next == NULL && strcmp(Pmove->data.Name, tem.Name))
        return false;
    else if(headpt == Pmove && !strcmp(Pmove->data.Name, tem.Name)){
        headpt = Pmove->next;
        free(Pmove);
        Writedata(headpt);
        return true;
    }
    else{   
        Pleft->next = Pmove->next;
        free(Pmove);
        Pmove = NULL;
        Writedata(headpt);
        return true;
    }
}

Node *Pospoint(Bookimf keep)
{
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    while(Pmove != NULL && strcmp(Pmove->data.Name, keep.Name)){
        Pmove = Pmove->next;
    }
    return Pmove;
}

void FindBook()
{
	system("cls"); //��������
    Bookimf tem;
    //putchar('\n');putchar('\n');putchar('\n');
    printf("********************************************\n");
    printf("���ĵ�ǰ�����������鼮\n");
    printf("********************************************\n");
    printf("��������Ҫ���ҵ�������");
    scanf("%s", tem.Name);
    Node *Position = Pospoint(tem);
    if(Position == NULL){
        printf("��ѯʧ�ܣ�ͼ���δ���и��鼮\n");
    }
    else{
        system("cls");
        printf("\n\n\t-----------------***********  �鼮��Ϣ  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "����", "����", "����", "�۸�");
        printf("\t%-22s%-22s%-22d%-22.1f\n",Position->data.Name, Position->data.author, Position->data.num, Position->data.price);
        putchar('\n');
    }

}

void DeteleBook()
{
    Bookimf tem;
    system("cls");
    displayBook();
    printf("********************************************\n");
    printf("���ĵ�ǰ������ɾ���鼮\n");
    printf("********************************************\n");
    printf("��������Ҫɾ����������");
    scanf("%s", tem.Name);
    bool judge = DeteleNode(tem);
    if(!judge){
        printf("ɾ������δ��ѯ����ͼ��\n");
    }
    else{
        printf("ɾ���ɹ�\n");
        printf("����\"1\"Ԥ��ͼ����鼮������\"3\"�˳�ϵͳ\n"
			   "�����룺");
        int i;
        scanf("%d", &i);
        while(i != 1 && i != 0){
            printf("�Ƿ�����\n"
                   "����\"1\"Ԥ��ͼ����鼮������\"0\"�˳�ϵͳ\n"
                   "���������룺");
            scanf("%d", &i);
        }
        if(i == 1)
            displayBook();
        else
            return;
    }
}

void Enterbook()
{
    int count;
    system("cls");
    printf("********************************************\n");
    printf("���ĵ�ǰ������¼���鼮\n");
    printf("********************************************\n");
    printf("������Ҫ¼���鼮��������");
    scanf("%d", &count);
    system("cls");
    printf("********************************************\n");
    printf("���ĵ�ǰ������¼���鼮\n");
    printf("********************************************\n");
    FILE *fp = fopen(filename, "w");
    Bookimf tem;
    for(int i = 0; i < count; i++){
        system("cls");
        printf("������� %d ���鼮��Ϣ\n", i + 1);putchar('\n');
        printf("������");scanf("%s", tem.author);putchar('\n');
        printf("���ߣ�");scanf("%s", tem.Name);putchar('\n');
        printf("������");scanf("%d", &tem.num);putchar('\n');
        printf("�۸�");scanf("%f", &tem.price);putchar('\n');
        fprintf(fp, "%s %s %d %f\n", tem.author, tem.Name, tem.num, tem.price);
    }
    system("cls");
    printf("¼��ɹ���\n");
    fclose(fp);
    system("pause");
}

void AddBook()
{
    system("cls");
    printf("********************************************\n");
    printf("���ĵ�ǰ�����������鼮\n");
    printf("********************************************\n");
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    if(!Pmove){
        system("cls");
        int key;
        printf("����ͼ�����δ�����鼮������¼��ͼ��\n");
        printf("����\"1\"�����¼���鼮���棬����\"0\"���˳�ϵͳ\n");
        printf("�����룺");
        scanf("%d", &key);
        if(key){
            Enterbook();
            return;
        }
        else{
            printf("�����˳�ϵͳ��3������ر�");
            //Sleep(3000);
            exit(0);
        }
    }
    Node *Pb = (Node *)malloc(Length);
    printf("\n�������鼮��Ϣ\n");putchar('\n');
    printf("������");scanf("%s", Pb->data.Name);putchar('\n');
    printf("���ߣ�");scanf("%s", Pb->data.author);putchar('\n');
    printf("������");scanf("%d", &Pb->data.num);putchar('\n');
    printf("�۸�");scanf("%f", &Pb->data.price);putchar('\n');
    while(Pmove && Pmove->next != NULL){
        Pmove = Pmove->next;
    }
    Pmove->next = Pb;
    Pmove->next->next = NULL;
    printf("��ӳɹ���\n");
    Writedata(headpt);
}

void displayBook()
{
    Node *Pmove = Insertdata();
    if(Pmove == NULL)
        printf("ͼ�����û���鼮������¼���鼮\n");
    else{
        system("cls");
        printf("\n\n\t-----------------***********  ͼ��ݲ���  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "����", "����", "����", "�۸�");
        while(Pmove != NULL){
            printf("\t%-22s%-22s%-22d%-22.1f\n", Pmove->data.Name, Pmove->data.author, Pmove->data.num, Pmove->data.price);
            Pmove = Pmove->next;
        }
        putchar('\n');
    }

}

void Borrow()
{
    system("cls");
	printf("********************************************\n");
    printf("���ĵ�ǰ�����������鼮\n");
    printf("********************************************\n");
    printf("����������鼮�����֣�");
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    Bookimf tem, Mybook;
    scanf("%s", tem.Name);
    while(Pmove != NULL && strcmp(Pmove->data.Name, tem.Name)){  
        Pmove = Pmove->next;
    }
    if(Pmove == NULL){
        printf("����ʧ�ܣ�ͼ���ϵͳ��δ����Ҫ���ĵ��鼮��\n");
        return;
    }
    else if(Pmove->data.num > 0){
        Mybook = Pmove->data;
        (Pmove->data.num)--;
        Writedata(headpt);
        Mybook.num = 1;
        printf("���ĳɹ���\n");
        putbook(Mybook);
        }
    else{   //��ǰͼ���ϵͳ�ڣ����鼮��Ϊ 0
        printf("�Բ��𣬸��鼮��ȫ�������\n");
        return;
    }
}

void Revert()
{
    system("cls");
	printf("********************************************\n");
    printf("���ĵ�ǰ�������黹�鼮\n");
    printf("********************************************\n");
    Node *headpt_user = Insertdata_user();
    Node *Pmove_user = headpt_user;
    Node *Pmove_mybook = headpt_user;
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    if(headpt_user == NULL){
        system("cls");
        printf("�黹�鼮ʧ�ܣ���������в�û���鼮\n");
        return;
    }
    else{
        system("cls");
        printf("\n\n\t-----------------***********  �������  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "����", "����", "����", "�۸�");
        while(Pmove_mybook != NULL){
            printf("\t%-22s%-22s%-22d%-22.1f\n", Pmove_mybook->data.Name, Pmove_mybook->data.author, Pmove_mybook->data.num, Pmove_mybook->data.price);
            Pmove_mybook = Pmove_mybook->next;
        }
        printf("\n������黹���鼮����");
        Bookimf tem;
        scanf("%s", tem.Name);
        while(Pmove_user != NULL && strcmp(Pmove_user->data.Name, tem.Name))
            Pmove_user = Pmove_user->next;
        if(Pmove_user == NULL){  //�ҵ������û���Ȿ��
            system("cls");
            printf("�黹�鼮ʧ�ܣ���������в�û���Ȿ��\n"
                   "\n�������������Ƿ����\n");
            printf("\n����\"1\"����黹ϵͳ������\"0\"�˳�ϵͳ\n"
                   "�����룺");
            int key;
            scanf("%d", &key);
            while(key != 1 && key != 0){
                printf("��������\n"
                       "����\"1\"�����黹ϵͳ������\"0\"���˳�ϵͳ\n"
                       "���������룺");
            scanf("%d", &key);
            }
            if(key == 1)
                Revert();
            else{
                printf("�����˳�ϵͳ��1���ϵͳ�ر�");
                Sleep(1000);
                exit(0);
            } 
        }
        else if(Pmove_user->data.num > 0){  //���Ȿ�飬 �ж��Ȿ�������
            while(Pmove != NULL && strcmp(Pmove->data.Name, tem.Name)){
                Pmove = Pmove->next;
            }
            if(Pmove == NULL){ //ͼ��ݲ���ϵͳ��û���Ȿ��
                printf("�黹ʧ�ܣ�\n"
                       "�����黹���鼮��δ¼���ڲ���ϵͳ��"
                       "\n������ϵ����Ա����ñ���\n");
                printf("\n����\"1\"�����ϵ����Ա����ͼ�飬����\"0\"���˳�ϵͳ");
                int key;
                scanf("%d", &key);
                while(key != 1 && key != 0){
                    printf("��������\n"
                           "����\"1\"����ϵ����Ա����ñ���,"
                           "����\"0\"���˳�ϵͳ\n"
                           "���������룺");
                    scanf("%d", &key);
                }
                if(key)
                    AddBook();
                else{
                    printf("�����˳�ϵͳ��1���ϵͳ�ر�");
                    Sleep(1000);
                    exit(0);
                }
            }
            else{
                (Pmove->data.num)++;
                Writedata(headpt);
                (Pmove_user->data.num)--;
                Writedata_user(headpt_user);
                printf("�黹�ɹ�\n"
                       "����\"1\"��ǰ���ҵ����,"
                       "����\"2\"��ǰ��ͼ�����ϵͳ"
                       "����\"0\"���˳�ϵͳ\n");
                printf("�����룺");
                int key;
                scanf("%d", &key);
                while(key != 1 && key != 2 && key != 0){
                    printf("��������\n"
                           "����\"1\"��ǰ���ҵ����,"
                           "����\"2\"��ǰ��ͼ�����ϵͳ"
                           "����\"0\"���˳�ϵͳ\n"
                           "���������룺");
                scanf("%d", &key);
                }
                if(key == 1)
                    Mybook();
                else if(key == 2)
                    displayBook();
                else{
                    printf("�����˳�ϵͳ��1���ϵͳ�ر�");
                    Sleep(1000);
                    exit(0);
                }
            }
        }
        else{
            system("cls");
            printf("�黹ʧ��!����������У��ñ��������Ϊ��\n");
            printf("\n����\"1\"��ǰ�����ҵ����,����\"0\"�˳�ϵͳ\n");
            printf("�����룺");
            int key;
            scanf("%d", &key);
            while(key != 1 && key != 0){
                printf("��������\n"
                       "����\"1\"��ǰ���ҵ����,"
                       "����\"0\"���˳�ϵͳ\n"
                       "\n���������룺");
                scanf("%d", &key);
            }
            if(key)
                Mybook();
            else{
                printf("�����˳�ϵͳ��1���ϵͳ�ر�");
                Sleep(1000);
                exit(0);
            }
        }
    }

}


void putbook(Bookimf keep)
{
    FILE *fp = fopen(filename_user, "r");
    if(fp == NULL)
        fp = fopen(filename_user, "w");
    Node *ptem = Insertdata_user();
    Node *Pmove1 = ptem, *Pmove2 = ptem;
    if(ptem == NULL){
        Node *Newheadpt_user = (Node *)malloc(Length);
        Newheadpt_user->next = NULL;
        Newheadpt_user->data = keep;
        Writedata_user(Newheadpt_user);
        printtip1();
    }
    else{
        while(Pmove2 != NULL && strcmp(Pmove2->data.Name, keep.Name)){
            Pmove2 = Pmove2->next;
        }
        if(Pmove2 == NULL){  
            Node *Pb = (Node *)malloc(Length);  
            Pb->data = keep;
            while(Pmove1 && Pmove1->next != NULL){  
                Pmove1 = Pmove1->next;
            }
            Pmove1->next = Pb;
            Pb->next = NULL;
            Writedata_user(ptem);
            printtip1();
        }
        else{  //���ҵ�����ڴ����Ȿ��  Pmove ��ָ��ýڵ�
            (Pmove2->data.num)++;
            Writedata_user(ptem);
            printtip1();
        }
    }
    fclose(fp);
}

void printtip1()
{
    printf("����\"1\"������ҵ���ܣ�����\"0\"���˳�ϵͳ\n"
           "�����룺");
    int key;
    scanf("%d", &key);
    while(key != 1 && key != 0){
        printf("��������\n"
               "����\"1\"������ҵ���ܣ�����\"0\"���˳�ϵͳ\n"
               "���������룺");
        scanf("%d", &key);
    }
    if(key)
        Mybook();
    else{
        return;
    }
}


void Mybook()
{
    system("cls");
    Node *Pmove = Insertdata_user();
    if(Pmove == NULL){
        printf("������ܿյ�����.....\n");
        printf("����\"1\"��ǰ��ͼ��ݽ����鼮������\"0\"���˳�ϵͳ\n"
               "�����룺");
        int key;
        scanf("%d", &key);
        while(key != 0 && key != 1){
            printf("��������\n"
                   "����\"1\"��ǰ��ͼ��ݽ����鼮������\"0\"���˳�ϵͳ\n"
                   "���������룺");
            scanf("%d", &key);
        }
        if(key)
            Borrow();
        else{
            printf("�����˳�ϵͳ��1������ر�");
            Sleep(1000);
            exit(0);
        }
    }
    else{
        Node *Pmove = Insertdata_user();
        printf("\n\n\t-----------------***********  �������  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "����", "����", "����", "�۸�");
        while(Pmove != NULL){
            printf("\t%-22s%-22s%-22d%-22.1f\n",Pmove->data.Name, Pmove->data.author, Pmove->data.num, Pmove->data.price);
            Pmove = Pmove->next;
        }
        putchar('\n');
    }
}