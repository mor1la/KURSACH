#pragma once
#include "library.h"

void ending(struct Text t);
void moreten(struct Text *t);
int cmp(const void* sent1,const void* sent2);
int greenword(struct Text t);
int check(wchar_t* sent,wchar_t* token);
void arrofwords(struct Text *t);
void search_seps(struct Text t);
void freeText1(struct Text t);
void freeText2(struct Text t);
wchar_t* meow();
int naborslov(wchar_t** nabor,int kolvo,struct Text t);