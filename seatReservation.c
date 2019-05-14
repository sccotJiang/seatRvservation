/**
> 巨人航空公司的机群由 12 个座位的飞机组成。它每天飞行一个航
> 班。根据下面的要求，编写一个座位预订程序。
> a.该程序使用一个内含 12 个结构的数组。每个结构中包括：一个成员
> 表示座位编号、一个成员表示座位是否已被预订、一个成员表示预订人的
> 名、一个成员表示预订人的姓。
> b.该程序显示下面的菜单：
> To choose a function, enter its letter label:
> a) Show number of empty seats
> b) Show list of empty seats
> c) Show alphabetical list of seats
> d) Assign a customer to a seat assignment
> e) Delete a seat assignment
> f) Quit
> c.该程序能成功执行上面给出的菜单。选择d)和e)要提示用户进行额外
> 输入，每个选项都能让用户中止输入。
> d.执行特定程序后，该程序再次显示菜单，除非用户选择f)。
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 12
#define FNAME_LEN 12
#define LNAME_LEN 12
struct plane {
	unsigned int num;
	int sub;
	char lastname[FNAME_LEN];
	char firstname[LNAME_LEN];
};
typedef struct plane PLANE;
char get_first();
char get_menu();
void get_emptyNum(PLANE arr[], int count);
void get_emptyseats(PLANE arr[], int count);
void get_alphabeticalseats(PLANE arr[], int count);
void get_name(char * lname, char * fname);
void assign_seats(PLANE arr[], int count, char lname[], char fname[]);
void delete_assign(PLANE arr[], char ch);
char get_choice();
void main()
{
	FILE * fp;
	if ((fp = fopen("plane.bat", "a+b")) == NULL) {
		printf("Can'topen plane.bat file\n", stderr);
		exit(1);
	}
	rewind(fp);
	int size = sizeof(struct plane);	
	char fname[FNAME_LEN];
	char lname[LNAME_LEN];
	PLANE obj[MAX];
	int i;
	char menu;
	char ch;
	int count = 0;
	
	for (i=0; i < MAX; i++) {
		obj[i].num = i + 97;
		obj[i].sub = 0;
	}

	while (count < MAX && fread(&obj[count], size, 1, fp)==1) {
                if (count == 0) {
                        printf("Current contents of plane.bat:\n");
                }
                printf("num: %d, sub status:%d,lastname:%s, firstname:%s\n", obj[count].num, obj[count].sub, obj[count].lastname, obj[count].firstname);
                count++;
        }
	fclose(fp);
	printf("To choose a function, enter its letter label:\n \
	a) Show number of empty seats\n \
	b) Show list of empty seats\n \
	c) Show alphabetical list of seats\n \
	d) Assign a customer to a seat assignment \n \
	e) Delete a seat assignment \n \
	f) Quit\n");
	while((menu = get_menu()) != 'f') {
		switch(menu) {
			case 'a':
				get_emptyNum(obj, MAX);
				break;
			case 'b':
				get_emptyseats(obj, MAX);
				break;
			case 'c':
				get_alphabeticalseats(obj, MAX);
				break;
			case 'd':
				assign_seats(obj, MAX, lname, fname);	
				break;
			case 'e':
				ch = get_choice();
				delete_assign(obj, ch);
				break;
				
		}
	}
	if ((fp=fopen("plane.bat", "w+b")) == NULL) {
		printf("Can not open file planet.bat\n", stderr);
		exit(1);
	}
	rewind(fp);
	fwrite(&obj[0], size, MAX, fp);
	fclose(fp);
}

char get_first() {
	char ch;
	char tmp;
	ch = getchar();
	while (isspace(ch)) {
		ch = getchar();	
	}
	while ((tmp = getchar()) != '\n') {
		continue;
	}
	return ch;
}
char get_menu() {
	char ch;
	ch = get_first();
	while (ch < 'a' || ch > 'f') {
		printf("Please respond with a,b,c,d,e,f\n");
		ch = get_first();
	}
	return ch;
}
void get_emptyNum(PLANE obj[], int num) {
	int i;
	int count = 0;
	for (i=0; i< num; i++) {
		if (obj[i].sub == 0) {
			count++;
		}	
	}
	printf("There has %d empty seats\n", count);
}
void get_emptyseats(PLANE obj[], int num) {
	int i;
	int status = 0;
	for (i=0; i < num ;i++) {
		if (obj[i].sub == 0) {
			printf("seats:%c is empty\n", obj[i].num);
			status = 1;
		}
	}
	if (status == 0) {
		printf("There has no empty seats\n");
	}
}
void get_alphabeticalseats(PLANE obj[], int num) {
	int i;
	printf("|%5s|%5s|%10s|%10s|\n", "num", "sub", "last_name", "first_name");
	for (i = 0; i< num; i++) {
		if (obj[i].sub == 0) {
			printf("|%5c|%5d|%10s|%10s|\n", obj[i].num, obj[i].sub, "", "");
		} else {
			printf("|%5c|%5d|%10s|%10s|\n", obj[i].num, obj[i].sub, obj[i].lastname, obj[i].firstname);
		}
	}
}
void get_name(char * lname,char * fname) {
	printf("Please enter lname:");
	scanf("%s", lname);
	printf("Please enter fname:");
	scanf("%s", fname);
}
void assign_seats(PLANE obj[], int num, char lname[], char fname[]) {
	get_name(lname, fname);
	int i;
	for (i = 0; i < num; i++) {
		if (obj[i].sub == 0) {
			obj[i].sub = 1;
			memcpy(obj[i].lastname, lname, LNAME_LEN);
			memcpy(obj[i].firstname, fname , LNAME_LEN);
			break;
		}																	
	}
}
void delete_assign(PLANE obj[], char ch) {
	int i = ch - 97;
	obj[i].sub = 0;
	memset(obj[i].lastname, 0, sizeof(obj[i].lastname));
	memset(obj[i].firstname, 0, sizeof(obj[i].firstname));
}
char get_choice() {
	char ch;
	printf("Please enter seat num you want to delete:");
	scanf("%c", &ch);
	return ch;
}
