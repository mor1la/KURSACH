#pragma once
#include "library.h"

void ending(struct Text t);
void moreten(struct Text *t);
int cmp(const void* sent1,const void* sent2);
int check(wchar_t* sent,wchar_t* token);
void freeText1(struct Text t);
int greenword(struct Text t);