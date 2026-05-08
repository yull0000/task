#include <stdio.h>
#include <string.h>
#define MAXSIZE 20
#define MAX_HISTORY 50
typedef struct {
    char name[MAXSIZE][30];
    int length;
} SeqList;
typedef struct {
    char action[100]; 
    int serialNum; 
} History;
typedef struct {
    History records[MAX_HISTORY];
    int count;
    int globalSerial;  
} HistoryList;
void InitHistory(HistoryList *H) {
    H->count = 0;
    H->globalSerial = 0;
}
void AddHistory(HistoryList *H, const char *action) {
    if (H->count >= MAX_HISTORY) {
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            H->records[i] = H->records[i + 1];
        }
        H->count = MAX_HISTORY - 1;
    }
    strcpy(H->records[H->count].action, action);
    H->globalSerial++;
    H->records[H->count].serialNum = H->globalSerial;
    H->count++;
}
void ShowHistory(HistoryList *H) {
    if (H->count == 0) {
        printf("\n暂无操作历史记录。\n");
        return;
    }   
    printf("\n===== 操作历史记录 =====\n");
    for (int i = 0; i < H->count; i++) {
        printf("%d. [操作#%d] %s\n", i + 1, H->records[i].serialNum, H->records[i].action);
    }
    printf("========================\n");
}
void ClearHistory(HistoryList *H) {
    H->count = 0;
    printf("操作历史已清空！\n");
}
void InitList(SeqList *L) {
    L->length = 0;
}
void AddBuilding(SeqList *L, char *str) {
    if (L->length >= MAXSIZE) {
        printf("列表已满，无法添加！\n");
        return;
    }
    strcpy(L->name[L->length], str);
    L->length++;
}
void ShowAll(SeqList *L) {
    printf("\n===== 校区楼宇列表 =====\n");
    for (int i = 0; i < L->length; i++) {
        printf("%d. %s\n", i + 1, L->name[i]);
    }
    printf("========================\n");
}
void SelectByNum(SeqList *L, int index) {
    if (index < 1 || index > L->length) {
        printf("编号无效！\n");
        return;
    }
    printf("\n你选择的是：%s\n", L->name[index - 1]);
}
void DeleteByNum(SeqList *L, int index) {
    if (index < 1 || index > L->length) {
        printf("编号无效，删除失败！\n");
        return;
    }
    for (int i = index - 1; i < L->length - 1; i++) {
        strcpy(L->name[i], L->name[i + 1]);
    }
    L->length--;
    printf("删除成功！\n");
}
void ModifyBuilding(SeqList *L, int index, char *newName) {
    if (index < 1 || index > L->length) {
        printf("编号无效，修改失败！\n");
        return;
    }
    strcpy(L->name[index - 1], newName);
    printf("修改成功！\n");
}

int main() {
    SeqList L;
    InitList(&L);
    AddBuilding(&L, "明理楼");
    AddBuilding(&L, "明德楼");
    AddBuilding(&L, "明治楼");
    AddBuilding(&L, "明善楼");
    AddBuilding(&L, "弘义楼");
    AddBuilding(&L, "致远楼");

    int op, num;
    char newName[30];

    while (1) {
        printf("\n========== 楼宇管理系统 ==========\n");
        printf("1. 查看所有楼宇\n");
        printf("2. 按编号选择楼宇\n");
        printf("3. 添加新楼宇\n");
        printf("4. 删除楼宇\n");
        printf("5. 修改楼宇名称\n");
        printf("0. 退出\n");
        printf("请输入操作：");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("已退出系统。\n");
                return 0;

            case 1:
                ShowAll(&L);
                break;

            case 2:
                ShowAll(&L);
                printf("请输入楼宇编号：");
                scanf("%d", &num);
                SelectByNum(&L, num);
                break;

            case 3:
                printf("请输入新楼宇名称：");
                scanf("%s", newName);
                AddBuilding(&L, newName);
                break;

            case 4:
                ShowAll(&L);
                printf("请输入要删除的楼宇编号：");
                scanf("%d", &num);
                DeleteByNum(&L, num);
                break;

            case 5:
                ShowAll(&L);
                printf("请输入要修改的楼宇编号：");
                scanf("%d", &num);
                printf("请输入新的名称：");
                scanf("%s", newName);
                ModifyBuilding(&L, num, newName);
                break;

            default:
                printf("输入错误，请重新选择！\n");
        }
    }
}
