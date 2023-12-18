
#include "functions.h"
#include "input.h"

void ending(struct Text t){
    for (int i = 0;i < t.n;i++) {
        for (int j = 0; j < t.array[i]->len-3; j++) {
            if ((t.array[i]->str[j] == L'т') && (t.array[i]->str[j+1] == L'ь') && (t.array[i]->str[j+2] == L'с') && (t.array[i]->str[j+3] == L'я')){
                wmemmove(&t.array[i]->str[j+1],&t.array[i]->str[j+2],(t.array[i]->len-j-1));
                t.array[i]->len = t.array[i]->len-1;
                j+=3;
            }
            if ((t.array[i]->str[j] == L'т') && (t.array[i]->str[j+1] == L'с') && (t.array[i]->str[j+2] == L'я')){
                wmemmove(&t.array[i]->str[j+2],&t.array[i]->str[j+1],(t.array[i]->len-j-1));
                t.array[i]->str[j+1]=L'ь';
                t.array[i]->len = t.array[i]->len+1;
            }
        }
    }
}
void moreten(struct Text *t){
    for (int i = 0;i<t->n;i++){
        if (t->array[i]->countwords>10){
            free(t->array[i]);
            memmove(&t->array[i], &t->array[i + 1], sizeof(struct Sentence *) * (t->n - i - 1));
            t->n-=1;
        }
    }
}
int cmp(const void* sent1,const void* sent2){
    struct Sentence *f = *(struct Sentence **) sent1;
    struct Sentence *s = *(struct Sentence **) sent2;
    int amount1 = f->countwords;
    int amount2 = s->countwords;
    if(amount1<amount2)
        return -1;
    if (amount1>amount2)
        return 1;
    return 0;
}
void arrofwords(struct Text *t){
    for (int i = 0;i < t->n;i++){
        int countwords = 0;
        t->array[i]->arrofwords = malloc(sizeof(wchar_t *)*t->array[i]->countwords);
        if (t->array[i]->arrofwords == NULL){
            wprintf(L"Error: ошибка выделения памяти для массива указателей на слова\n");
            exit(0);
        }
        wchar_t *temp = (wchar_t *) malloc((t->array[i]->len+1) * sizeof(wchar_t));
        wcscpy(temp,t->array[i]->str);
        wchar_t *pt;
        wchar_t *pch = wcstok(temp,L" ,\t.\n",&pt);
        while (pch!=NULL){
            t->array[i]->arrofwords[countwords] = pch;
            countwords++;
            pch = wcstok(NULL,L" ,\t.\n",&pt);
        }
        free(pt);
        free(pch);
    }
}

void search_seps(struct Text t) {
    for (int i = 0; i < t.n; i++) {
        t.array[i]->arrofseps = malloc(sizeof(wchar_t));
        if (t.array[i]->arrofseps == NULL) {
            wprintf(L"Error: ошибка выделения памяти для массива разделителей\n");
            exit(0);
        }
        unsigned countseps = 0;
        for (int j = 0; j < t.array[i]->len - 1; j++) {
            if (t.array[i]->str[j] == L',' && t.array[i]->str[j + 1] == L' ') {
                t.array[i]->arrofseps[countseps] = L'!';
                countseps+=1;
                j += 1;
            } else if (t.array[i]->str[j] == L',' || t.array[i]->str[j] == L' ') {
                t.array[i]->arrofseps[countseps] = t.array[i]->str[j];
                countseps+=1;
            }
            t.array[i]->arrofseps = realloc(t.array[i]->arrofseps, sizeof(wchar_t) * (countseps + 1));

            if (t.array[i]->arrofseps == NULL) {
                wprintf(L"Error: ошибка перераспределения памяти для массива разделителей\n");
                exit(0);
            }
        }
        t.array[i]->countseps = countseps;
    }
}
int greenword(struct Text t){
    arrofwords(&t);
    search_seps(t);
    wchar_t* buffer1;
    wchar_t* token = wcstok(t.array[0]->str, L" \t\n,.",&buffer1);
    token = wcstok(NULL, L" \t\n,.", &buffer1);
    if (token==NULL){
        return 0;
    }
    for (int i = 0;i<t.n;i++){
        wchar_t *temp1 = (wchar_t *) malloc((t.array[i]->len+1)* sizeof(wchar_t));
        wcscpy(temp1,t.array[i]->str);
        if (check(temp1,token)==1){
            for (int j = 0;j<t.array[i]->countwords-1;j++){
                if (wcscmp(t.array[i]->arrofwords[j], token) == 0) {
                    wprintf(L"%s%ls",GREEN,t.array[i]->arrofwords[j]);
                }else{
                    wprintf(L"%s%ls",NONE,t.array[i]->arrofwords[j]);
                }
                if (t.array[i]->arrofseps[j] == L'!'){
                    wprintf(L"%s, ",NONE);
                }
                else{
                    wprintf(L"%s%lc",NONE, t.array[i]->arrofseps[j]);
                }
            }
            if (wcsncmp(t.array[i]->arrofwords[t.array[i]->countwords-1], token,sizeof(token)) == 0) {
                wprintf(L"%s%ls.\n",GREEN,t.array[i]->arrofwords[t.array[i]->countwords-1]);
            }else{
                wprintf(L"%s%ls.\n",NONE,t.array[i]->arrofwords[t.array[i]->countwords-1]);
            }
        }
    }
    return 1;
}
int check(wchar_t* sent,wchar_t* token){
    wchar_t* buffer1;
    wchar_t* word = wcstok(sent,L" ,\t.\n",&buffer1);
    while(word!=NULL) {
        if (wcscmp(word, token) == 0)
            return 1;
        word = wcstok(NULL, L" ,\t.\n", &buffer1);
    }
    return 0;
}
void freeText1(struct Text t) {
    for (int i = 0; i < t.n; i++) {
        free(t.array[i]->str);
        free(t.array[i]);
    }
}
void freeText2(struct Text t) {
    for (int i = 0; i < t.n; i++) {
        free(t.array[i]->arrofseps);
        free(t.array[i]->arrofwords);
    }
}
int naborslov(wchar_t** nabor,int kolvo,struct Text t){
    arrofwords(&t);
    search_seps(t);
    for (int i = 0;i<t.n;i++){
        int flag = 0;
        for (int j = 0;j<t.array[i]->countwords;j++){
            flag = 0;
            for (int k = 0;k<kolvo;k++){
                if (wcslen(t.array[i]->arrofwords[j])==wcslen(nabor[k])){
                    if (RepeatingSentence(t.array[i]->arrofwords[j], nabor[k], wcslen(nabor[k]))==0) {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag==0){
                break;
            }
    }
        if (flag){
            wprintf(L"%ls\n",t.array[i]->str);
        }
    }
}
wchar_t* meow() {
    int size = MEM_STEP1;
    int n = 0;
    wchar_t *buf = (wchar_t *) malloc(size * sizeof(wchar_t));
    wchar_t temp;
    do {
        if (n >= size - 2) {
            size += MEM_STEP1;
            wchar_t *t = (wchar_t *) realloc(buf, (size) * sizeof(wchar_t));
            if (!t) {
                wprintf(L"Ошибка, не удается выделить память!\n");
                free(t);
                exit(1);
            } else {
                buf = t;
            }
        }
        temp = (wchar_t) getwchar();
        buf[n] = temp;
        n++;
    }while ((temp!= L'\n'));
    buf[n]=L'\0';
    return buf;
}
