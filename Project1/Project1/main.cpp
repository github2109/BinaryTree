#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h> 
#include <fstream>
#define MAX 100
using namespace cv;
using namespace std;
Mat drawing(1000, 3000, CV_8UC3, Scalar(255, 255, 255)); // Tao 1 doi tuong do hoa drawing 
char Stack[MAX];
int top = -1, i = 0;

void Errors(int x)
{
	switch (x)
	{
	case 1: printf("\n Khong du bo nho.");
		break;
	case 2: printf("\n Khong co chuc nang nay.Moi ban thu lai.");
		break;
	case 3: printf("\n Du lieu nhap ko dung");
		break;
	case 5: printf("\n Cay hien dang rong.Khong the thuc hien thao tac.");
		break;
	case 6: printf("\n Khong mo duoc file.Please try again");
		getch();
		break;
	}
	printf("\n\t********\n");
}
int precedence(char symbol) {
	if (symbol == '@' || symbol == '#' || symbol == '$' || symbol == '&' || symbol == '~' || symbol == '|' || symbol == '!') return 4;
	else if (symbol == '^')
	{
		return(3);
	}
	else if (symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if (symbol == '+' || symbol == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

char TrigotoOperater(char item[]) {
	if (!strcmp(item, "sin")) return '@';
	else if (!strcmp(item, "cos")) return '#';
	else if (!strcmp(item, "tan")) return '$';
	else if (!strcmp(item, "cot")) return '&';
	else if (!strcmp(item, "log")) return '~';
	else if (!strcmp(item, "exp")) return '|';
	else return 'k';
}

void push(char item) {
	if (top >= MAX - 1)
	{
		printf("\n Stack Overflow.");
	}
	else
	{
		top = top + 1;
		Stack[top] = item;
	}
}

char pop()
{
	char item;
	if (top < 0)
	{
		printf("stack under flow: invalid infix expression");
		getchar();
		return 0;
	}
	else
	{
		item = Stack[top];
		Stack[top] = NULL;
		top = top - 1;
		return(item);
	}
}

char Top() {
	return Stack[top];
}

void removeString(char item[]) {
	for (int x = 0; x < MAX; x++) item[x] = NULL;
}
void InfixtoPostfix(char Infix[], char Postfix[][10]) {
	char temp = Infix[0], x;
	push('(');
	strcat(Infix, ")");
	int  j = 0, k = 0;
	while (1) {
		if (temp == NULL) {
			break;
		}
		if (isdigit(temp) || isalpha(temp)) {
			Postfix[i][j] = temp;
			j++;
		}
		else if (temp == '(') {
			if (isalpha(Postfix[i][j - 1])) {
				temp = TrigotoOperater(Postfix[i]);
				removeString(Postfix[i]);
				j = 0;
				k--;
				continue;
			}
			push(temp);
		}
		else if (precedence(temp) != 0) {
			if (isdigit(Postfix[i][0])) {
				i++;
				j = 0;
			}
			x = pop();
			while (precedence(x) != 0 && precedence(x) >= precedence(temp)) {

				Postfix[i][0] = x;
				i++;
				x = pop();
			}
			push(x);
			push(temp);
		}
		else if (temp == ')') {
			if (isdigit(Postfix[i][0])) {
				i++;
				j = 0;
			}
			x = pop();
			while (x != '(')
			{
				Postfix[i][0] = x;
				i++;
				x = pop();
			}
		}
		else
		{
			printf("\nInvalid infix Expression.\n");
			getchar();
		}
		k++;
		temp = Infix[k];
	}
}
// TREE STRUCTURE //
typedef struct tree
{
	char info[10];                  // to account for operators as nodes
	struct tree* left;
	struct tree* right;
}BTREE;
BTREE* root = NULL;
// STACK STRUCTURE //
typedef struct stack {
	BTREE* info[MAX];         // stack contains node's addresses
	int top;
}STACK;
STACK s;
BTREE* getnode(void)
{
	BTREE* p;
	p = (BTREE*)malloc(sizeof(BTREE));
	return(p);
}
BTREE* maketree(char item[])
{
	BTREE* p;
	p = getnode();
	strcpy(p->info, item);
	p->left = NULL;
	p->right = NULL;
	return(p);
}
void pushs(BTREE* item)
{
	if (s.top == MAX - 1)
	{
		printf("\n Stack Overflow!");
		getch();
		exit(1);
	}
	s.info[++s.top] = item;
}
BTREE* pops(void)
{
	if (s.top == -1)
	{
		printf("\n Stack Underflow!");
		getch();
		exit(1);
	}
	return(s.info[s.top--]);
}

void CreateExprTree(char Postfix[][10])
{
	BTREE* p;
	int x = 0;
	char temp[5];
	while (Postfix[x][0] != NULL)
	{
		if (isdigit(Postfix[x][0]))
		{
			p = maketree(Postfix[x]);
			pushs(p);
		}
		else     // char is operator
		{
			;
			if (precedence(Postfix[x][0]) == 4) {
				if (Postfix[x][0] == '@') strcpy(temp, "sin");
				else if (Postfix[x][0] == '#') strcpy(temp, "cos");
				else if (Postfix[x][0] == '$') strcpy(temp, "tan");
				else if (Postfix[x][0] == '&') strcpy(temp, "cot");
				else if (Postfix[x][0] == '|') strcpy(temp, "exp");
				else if (Postfix[x][0] == '~') strcpy(temp, "log");
				if (Postfix[x][0] == '!') {
					p = maketree(Postfix[x]);
					p->left = pops();
					p->right = NULL;
				}
				else if (Postfix[x][0] == '~') {
					p = maketree(temp);
					p->right = pops();
					p->left = pops();

				}
				else {
					p = maketree(temp);
					p->left = NULL;
					p->right = pops();
				}
			}
			else {

				p = maketree(Postfix[x]);
				p->right = pops();
				p->left = pops();
			}
			pushs(p);
		}
		x++;
	}
	root = pops();      // stack now contains address of root node omlu                                          
}


void structure(BTREE* root, int level, float x, int k)
{
	int i;
	if (root != NULL) {
		if (x != 600) cv::line(drawing, cv::Point(x, (level - 1) * 110 + 50), cv::Point(x + k * (900 / (pow(2, level)) + 80), level * 110 + 50), cv::Scalar(0, 0, 255), 1);
		structure(root->right, level + 1, x + k * (900 / (pow(2, level)) + 80), 1);
		if (TrigotoOperater(root->info) != 'k') {
			cv::putText(drawing, root->info, cv::Point(-23 + x + k * (900 / (pow(2, level)) + 80), 5 + level * 110 + 50), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0), 2);
			cv::circle(drawing, cv::Point(x + k * (900 / (pow(2, level)) + 80), level * 110 + 50), 38, cv::Scalar(128, 0, 128), 2);
		}
		else {
			cv::putText(drawing, root->info, cv::Point(-12 + x + k * (900 / (pow(2, level)) + 80), 10 + level * 110 + 50 - 2), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0), 2);
			cv::circle(drawing, cv::Point(x + k * (900 / (pow(2, level)) + 80), level * 110 + 50), 30, cv::Scalar(128, 0, 128), 2);
		}
		structure(root->left, level + 1, x + k * (900 / (pow(2, level)) + 80), -1);
	}
}
void DestroyBTree(BTREE* root)
{
	if (root)
	{
		DestroyBTree((*root).left);
		DestroyBTree((*root).right);
		delete root;
	}
	root = NULL;
}
int Menu()
{
	int Router;
	printf("\n\t\t 	           ษออออออออออออออออออออออออออ\t\t");
	printf("\n\t\t                   บ   CAY NHI PHAN BIEU THUC บ");
	printf("\n\t\t 	           ศออออออออออออออออออออออออออผ");
	printf("\n\n 	            ษอออออออออออออออออออออออออออออออออออออออออออออออออออออ");
	printf("\n	            บ                 MOI BAN CHON CHUC NANG              บ");
	printf("\n	            ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
	printf("\n 	            บ 0. THOAT KHOI CHUONG TRINH		 	  บ ");
	printf("\n 	            วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ");
	printf("\n 	            บ 1. NHAP BIEU THUC      	                          บ");
	printf("\n 	            วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ");
	printf("\n 	            บ 2. IN RA CAY NHI PHAN BIEU THUC      	          บ");
	printf("\n 	            วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ");
	printf("\n 	            บ 3. HUY CAY NHI PHAN BIEU THUC VUA TAO               บ");
	printf("\n	            ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
	printf("\n\n 	Ban chon chuc nang : ");
	scanf("%d", &Router);
	return Router;
}

void MenuInput(char Infix[]) {
	int RouterInput;
	printf("\n\t------------------------------------------------------");
	printf("\n\tฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
	printf("\n\tณ Ban muon nhap theo phuong phap     ณ");
	printf("\n\tรฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤด");
	printf("\n\tณ 1. Nhap truc tiep.                 ณ");
	printf("\n\tณ                                    ณ");
	printf("\n\tณ 2. Nhap tu file.                   ณ");
	printf("\n\tภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
	printf("\n\n\tNhap theo phuong phap : ");
	scanf("%d", &RouterInput);
	printf("\n------------------------------------------------------");
	switch (RouterInput) {
	case 1: printf("\n Nhap bieu thuc :");
		scanf("%s", Infix);
		break;
	case 2:
		FILE * fi;
		fi = fopen("data.txt", "r");
		if (fi == NULL) {
			printf("Error!");
			exit(1);
		}
		fscanf(fi, "%s", Infix);
		printf("\nBieu thuc: ");
		printf("%s", Infix);
		fclose(fi);
		break;
	default: Errors(2);
	}
}
void TiepTuc() {
	printf("\n\nBam phim bat ky de tiep tuc...");
	getch();
	system("cls");
}
/* main function begins */
void reset(char Infix[], BTREE* root) {
	i = 0;
	drawing = Scalar(255, 255, 255);
	removeString(Infix);
	DestroyBTree(root);
}

int main() {
	printf("\n\n                                PBL 1: DO AN LAP TRINH TINH TOAN\n");
	printf("\n              De Tai 805: Ve cay nhi phan bieu thuc duoi cau truc du lieu cay nhi phan \n");
	getch();

	char Infix[MAX], Postfix[MAX][10];
	char suggest;
	int Router;
	reset(Infix, root);
	do
	{
		Router = Menu();
		system("cls");
		switch (Router) {
		case 1:
			if (Infix[0] != NULL) {
				printf("Hay xoa cay truoc khi nhap bieu thuc moi!!");
				TiepTuc();
				break;
			}
			else {
				MenuInput(Infix);
				for (int k = 0; k < MAX; k++) {
					Stack[k] = NULL;
					for (int j = 0; j < 10; j++) {
						Postfix[k][j] = NULL;
					}
				}
				InfixtoPostfix(Infix, Postfix);
				CreateExprTree(Postfix);
				s.top = -1;
				structure(root, 0, 600, 1);
				TiepTuc();
				break;
			}
		case 2: printf("\n------------------------------------------------------\n");
			namedWindow("Image", WINDOW_NORMAL);
			imshow("Image", drawing);
			waitKey(0);
			printf("Ban co muon luu lai anh nay khong (c,k) ?\n");
			getchar();
			scanf("%c", &suggest);
			switch (suggest) {
			case 'c':
				imwrite("../DataImg/img.jpg", drawing);
				printf("Anh da duoc luu thanh cong !");
				TiepTuc();
				break;
			default:
				printf("Anh chua duoc luu !");
				TiepTuc();
				break;
			}
			break;
		case 3: printf("\n------------------------------------------------------");
			reset(Infix, root);
			printf("\n\t Da huy thanh cong !");
			printf("\n------------------------------------------------------");
			TiepTuc();
			break;
		}
	} while (Router != 0);
	return 0;
}

