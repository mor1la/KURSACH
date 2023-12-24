
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

int greenword(struct Text t){
    wchar_t *temp = (wchar_t *) malloc((t.array[0]->len+1)* sizeof(wchar_t));
    wcscpy(temp,t.array[0]->str);
    wchar_t* token = wcstok(temp, L" \t\n,.",&temp);
    token = wcstok(NULL, L" \t\n,.", &temp);
    if (token==NULL){
        return 0;
    }
    wchar_t alphabet[] = L"ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    for (int i = 0;i<t.n;i++){
        wchar_t *temp1 = (wchar_t *) malloc((t.array[i]->len+1)* sizeof(wchar_t));
        wcscpy(temp1,t.array[i]->str);
        if (check(temp1,token)==1){
            wchar_t *temp2 = (wchar_t *) malloc((t.array[i]->len+1) * sizeof(wchar_t));
            wchar_t *temp3 = (wchar_t *) malloc((t.array[i]->len+1) * sizeof(wchar_t));
            wcscpy(temp2,t.array[i]->str);
            wcscpy(temp3,t.array[i]->str);
            wchar_t* word = wcstok(temp2,L" ,\t\n.",&temp2);
            wchar_t* sep  = wcstok(temp3,alphabet,&temp3);
            while(word!=NULL){
                if (wcsncmp(word, token,sizeof(token)) == 0){
                    wprintf(L"%s%ls",GREEN,word);
                }else{
                    wprintf(L"%s%ls",NONE,word);
                }
                if(sep!=NULL){
                    wprintf(L"%s%ls",NONE,sep);
                }
                word = wcstok(NULL, L" ,\t\n.", &temp2);
                sep = wcstok(NULL, alphabet, &temp3);
            }
            free(temp1);
            free(temp2);
            free(temp3);
            wprintf(L"\n");
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





