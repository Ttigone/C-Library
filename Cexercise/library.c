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
    SetConsoleTitle("阳江校区图书馆系统");
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
                printf("您已退出系统，1秒后界面关闭");
                Sleep(1000);
                exit(0);
            }
            default: printf("输入错误\n");
        }
    system("pause");
    }
    return 0;
}


void Menu_1(void)
{
    system("color 3");
    printf("*****************欢迎来到广东海洋大学（阳江校区）图书管理系统*****************\n\n\n");
}
void Enter_Exit(void)
{
    int key;
    printf("\t\t\t\t1:登录系统\n\n");
    printf("tip:如果是\"第一次\"打开该系统(黑窗口)，那么请输入\"2\"进行书籍录入，在下一次打开系统(黑窗口)\n    时不必进行书籍录入\n\n");
    printf("您的操作是：");
    scanf("%d", &key);
    while (key != 1 && key != 2){
        printf("您输入的数字有误，请重新输入：");
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
    printf("        1:查找书籍  -----------****************-------------  2:我的书架\n");
    printf("        3:增添书籍  -----------****************-------------  4:删除书籍\n");
    printf("        5:借阅书籍  -----------****************-------------  6:归还书籍\n");
    printf("        7:图书馆藏书  ---------****************-------------  8:录入书籍\n");
    putchar('\n');
    printf("        ------------------      t:退出系统        --------------------    \n");
    printf("\n");
    printf("        ***************************************************************        \n");
    printf("\n");
    printf("请选择您要进行的操作：");
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
	system("cls"); //清屏功能
    Bookimf tem;
    //putchar('\n');putchar('\n');putchar('\n');
    printf("********************************************\n");
    printf("您的当前操作：查找书籍\n");
    printf("********************************************\n");
    printf("请输入您要查找的书名：");
    scanf("%s", tem.Name);
    Node *Position = Pospoint(tem);
    if(Position == NULL){
        printf("查询失败，图书馆未存有该书籍\n");
    }
    else{
        system("cls");
        printf("\n\n\t-----------------***********  书籍信息  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "书名", "作者", "数量", "价格");
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
    printf("您的当前操作：删除书籍\n");
    printf("********************************************\n");
    printf("请输入您要删除的书名：");
    scanf("%s", tem.Name);
    bool judge = DeteleNode(tem);
    if(!judge){
        printf("删除错误，未查询到该图书\n");
    }
    else{
        printf("删除成功\n");
        printf("输入\"1\"预览图书馆书籍，输入\"3\"退出系统\n"
			   "请输入：");
        int i;
        scanf("%d", &i);
        while(i != 1 && i != 0){
            printf("非法输入\n"
                   "输入\"1\"预览图书馆书籍，输入\"0\"退出系统\n"
                   "请重新输入：");
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
    printf("您的当前操作：录入书籍\n");
    printf("********************************************\n");
    printf("请输入要录入书籍的数量：");
    scanf("%d", &count);
    system("cls");
    printf("********************************************\n");
    printf("您的当前操作：录入书籍\n");
    printf("********************************************\n");
    FILE *fp = fopen(filename, "w");
    Bookimf tem;
    for(int i = 0; i < count; i++){
        system("cls");
        printf("请输入第 %d 本书籍信息\n", i + 1);putchar('\n');
        printf("书名：");scanf("%s", tem.author);putchar('\n');
        printf("作者：");scanf("%s", tem.Name);putchar('\n');
        printf("数量：");scanf("%d", &tem.num);putchar('\n');
        printf("价格：");scanf("%f", &tem.price);putchar('\n');
        fprintf(fp, "%s %s %d %f\n", tem.author, tem.Name, tem.num, tem.price);
    }
    system("cls");
    printf("录入成功！\n");
    fclose(fp);
    system("pause");
}

void AddBook()
{
    system("cls");
    printf("********************************************\n");
    printf("您的当前操作：增添书籍\n");
    printf("********************************************\n");
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    if(!Pmove){
        system("cls");
        int key;
        printf("由于图书馆内未存有书籍，请先录入图书\n");
        printf("输入\"1\"则进入录入书籍界面，输入\"0\"则退出系统\n");
        printf("请输入：");
        scanf("%d", &key);
        if(key){
            Enterbook();
            return;
        }
        else{
            printf("您已退出系统，3秒后界面关闭");
            //Sleep(3000);
            exit(0);
        }
    }
    Node *Pb = (Node *)malloc(Length);
    printf("\n请输入书籍信息\n");putchar('\n');
    printf("书名：");scanf("%s", Pb->data.Name);putchar('\n');
    printf("作者：");scanf("%s", Pb->data.author);putchar('\n');
    printf("数量：");scanf("%d", &Pb->data.num);putchar('\n');
    printf("价格：");scanf("%f", &Pb->data.price);putchar('\n');
    while(Pmove && Pmove->next != NULL){
        Pmove = Pmove->next;
    }
    Pmove->next = Pb;
    Pmove->next->next = NULL;
    printf("添加成功！\n");
    Writedata(headpt);
}

void displayBook()
{
    Node *Pmove = Insertdata();
    if(Pmove == NULL)
        printf("图书馆内没有书籍，请先录入书籍\n");
    else{
        system("cls");
        printf("\n\n\t-----------------***********  图书馆藏书  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "书名", "作者", "数量", "价格");
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
    printf("您的当前操作：借阅书籍\n");
    printf("********************************************\n");
    printf("请输入借阅书籍的名字：");
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    Bookimf tem, Mybook;
    scanf("%s", tem.Name);
    while(Pmove != NULL && strcmp(Pmove->data.Name, tem.Name)){  
        Pmove = Pmove->next;
    }
    if(Pmove == NULL){
        printf("借阅失败！图书馆系统内未有您要借阅的书籍！\n");
        return;
    }
    else if(Pmove->data.num > 0){
        Mybook = Pmove->data;
        (Pmove->data.num)--;
        Writedata(headpt);
        Mybook.num = 1;
        printf("借阅成功！\n");
        putbook(Mybook);
        }
    else{   //当前图书馆系统内，该书籍数为 0
        printf("对不起，该书籍已全部被借出\n");
        return;
    }
}

void Revert()
{
    system("cls");
	printf("********************************************\n");
    printf("您的当前操作：归还书籍\n");
    printf("********************************************\n");
    Node *headpt_user = Insertdata_user();
    Node *Pmove_user = headpt_user;
    Node *Pmove_mybook = headpt_user;
    Node *headpt = Insertdata();
    Node *Pmove = headpt;
    if(headpt_user == NULL){
        system("cls");
        printf("归还书籍失败，您的书架中并没有书籍\n");
        return;
    }
    else{
        system("cls");
        printf("\n\n\t-----------------***********  您的书架  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "书名", "作者", "数量", "价格");
        while(Pmove_mybook != NULL){
            printf("\t%-22s%-22s%-22d%-22.1f\n", Pmove_mybook->data.Name, Pmove_mybook->data.author, Pmove_mybook->data.num, Pmove_mybook->data.price);
            Pmove_mybook = Pmove_mybook->next;
        }
        printf("\n请输入归还的书籍名：");
        Bookimf tem;
        scanf("%s", tem.Name);
        while(Pmove_user != NULL && strcmp(Pmove_user->data.Name, tem.Name))
            Pmove_user = Pmove_user->next;
        if(Pmove_user == NULL){  //我的书架中没有这本书
            system("cls");
            printf("归还书籍失败！您的书架中并没有这本书\n"
                   "\n请检查书名输入是否错误\n");
            printf("\n输入\"1\"进入归还系统，输入\"0\"退出系统\n"
                   "请输入：");
            int key;
            scanf("%d", &key);
            while(key != 1 && key != 0){
                printf("输入有误\n"
                       "输入\"1\"则进入归还系统，输入\"0\"则退出系统\n"
                       "请重新输入：");
            scanf("%d", &key);
            }
            if(key == 1)
                Revert();
            else{
                printf("您已退出系统，1秒后系统关闭");
                Sleep(1000);
                exit(0);
            } 
        }
        else if(Pmove_user->data.num > 0){  //有这本书， 判断这本书的数量
            while(Pmove != NULL && strcmp(Pmove->data.Name, tem.Name)){
                Pmove = Pmove->next;
            }
            if(Pmove == NULL){ //图书馆藏书系统内没有这本书
                printf("归还失败！\n"
                       "您所归还的书籍并未录入在藏书系统内"
                       "\n您可联系管理员增添该本书\n");
                printf("\n输入\"1\"则可联系管理员增添图书，输入\"0\"则退出系统");
                int key;
                scanf("%d", &key);
                while(key != 1 && key != 0){
                    printf("输入有误！\n"
                           "输入\"1\"则联系管理员增添该本书,"
                           "输入\"0\"则退出系统\n"
                           "请重新输入：");
                    scanf("%d", &key);
                }
                if(key)
                    AddBook();
                else{
                    printf("您已退出系统，1秒后系统关闭");
                    Sleep(1000);
                    exit(0);
                }
            }
            else{
                (Pmove->data.num)++;
                Writedata(headpt);
                (Pmove_user->data.num)--;
                Writedata_user(headpt_user);
                printf("归还成功\n"
                       "输入\"1\"则前往我的书架,"
                       "输入\"2\"则前往图书藏书系统"
                       "输入\"0\"则退出系统\n");
                printf("请输入：");
                int key;
                scanf("%d", &key);
                while(key != 1 && key != 2 && key != 0){
                    printf("输入有误！\n"
                           "输入\"1\"则前往我的书架,"
                           "输入\"2\"则前往图书藏书系统"
                           "输入\"0\"则退出系统\n"
                           "请重新输入：");
                scanf("%d", &key);
                }
                if(key == 1)
                    Mybook();
                else if(key == 2)
                    displayBook();
                else{
                    printf("您已退出系统，1秒后系统关闭");
                    Sleep(1000);
                    exit(0);
                }
            }
        }
        else{
            system("cls");
            printf("归还失败!在您的书架中，该本书的数量为零\n");
            printf("\n输入\"1\"则前往的我的书架,输入\"0\"退出系统\n");
            printf("请输入：");
            int key;
            scanf("%d", &key);
            while(key != 1 && key != 0){
                printf("输入有误！\n"
                       "输入\"1\"则前往我的书架,"
                       "输入\"0\"则退出系统\n"
                       "\n请重新输入：");
                scanf("%d", &key);
            }
            if(key)
                Mybook();
            else{
                printf("您已退出系统，1秒后系统关闭");
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
        else{  //在我的书架内存在这本书  Pmove 正指向该节点
            (Pmove2->data.num)++;
            Writedata_user(ptem);
            printtip1();
        }
    }
    fclose(fp);
}

void printtip1()
{
    printf("输入\"1\"则进入我的书架，输入\"0\"则退出系统\n"
           "请输入：");
    int key;
    scanf("%d", &key);
    while(key != 1 && key != 0){
        printf("输入有误！\n"
               "输入\"1\"则进入我的书架，输入\"0\"则退出系统\n"
               "请重新输入：");
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
        printf("您的书架空荡荡的.....\n");
        printf("输入\"1\"则前往图书馆借阅书籍，输入\"0\"则退出系统\n"
               "请输入：");
        int key;
        scanf("%d", &key);
        while(key != 0 && key != 1){
            printf("输入有误！\n"
                   "输入\"1\"则前往图书馆借阅书籍，输入\"0\"则退出系统\n"
                   "请重新输入：");
            scanf("%d", &key);
        }
        if(key)
            Borrow();
        else{
            printf("您已退出系统，1秒后界面关闭");
            Sleep(1000);
            exit(0);
        }
    }
    else{
        Node *Pmove = Insertdata_user();
        printf("\n\n\t-----------------***********  您的书架  ***********-------------------\n");
        printf("\n\t%-22s%-22s%-22s%-22s\n", "书名", "作者", "数量", "价格");
        while(Pmove != NULL){
            printf("\t%-22s%-22s%-22d%-22.1f\n",Pmove->data.Name, Pmove->data.author, Pmove->data.num, Pmove->data.price);
            Pmove = Pmove->next;
        }
        putchar('\n');
    }
}