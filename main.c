#include "input.h"
#include "functions.h"

void start(){
    wprintf(L"Course work for option 5.9, created by Marina Konyaeva.\n");
}

void print(struct Text t){
    for (int i = 0; i < t.n; i++) {
        fputws(t.array[i]->str, stdout);
        wprintf(L"\n");
    }
}

int main() {
    setlocale(LC_CTYPE, "");
    start();
    wchar_t a = (wchar_t)getwchar();
    getwchar();
    switch (a) {
        case L'0': {
            struct Text t = readText();
            format(&t);
            print(t);
            freeText1(t);
            break;
        }
        case L'1': {
            struct Text t = readText();
            format(&t);
            ending(t);
            print(t);
            freeText1(t);
            break;
        }
        case L'2': {
            struct Text t = readText();
            format(&t);
            greenword(t);
            freeText1(t);
            freeText2(t);
            break;
        }
        case L'3': {
            struct Text t = readText();
            format(&t);
            qsort(t.array, t.n, sizeof(struct Sentence *), cmp);
            print(t);
            freeText1(t);
            break;
        }
        case L'4': {
            struct Text t = readText();
            format(&t);
            moreten(&t);
            print(t);
            freeText1(t);
            break;
        }
        case L'5':{
            wprintf(L"1)Изменить все слова в тексте заканчивающиеся на “ться” так чтобы они заканчивались на “тся” и наоборот.\n2)Вывести все предложения в которых встречается второе слово первого предложения. Данное слово необходимо выделить зеленым цветом.\n3)Отсортировать предложения по возрастанию количества слов в предложении.\n4)Удалить все предложения в которых больше 10 слов.\n");
            break;
        }
        case L'6':{
            wchar_t* sentence = meow();
            struct Text t = readText();
            format(&t);
            wchar_t** array  = (wchar_t**)malloc(sizeof(wchar_t*)*1);
            int count = 0;
            wchar_t *pt;
            wchar_t* word = wcstok(sentence,L" \n",&pt);
            while (word!= NULL)
            {
                array[count] = word;
                count++;
                array = realloc(array, (count+1) * sizeof(char*));
                word =  wcstok(NULL, L" \n",&pt);
            }
            naborslov(array,count,t);
            break;
        }
        default:
            wprintf(L"\nОшибка. Некорректная команда.\n"
                    L"Выход из программы...\n");
            return 1;
    }
    return 0;
}
