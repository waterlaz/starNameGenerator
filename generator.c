#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* prefix[] = {
    #include "prefixes.h"
};

const char* trigrams[] = {
    #include "trigrams.h"
};

void generate(char* s, int maxLength){
    if(maxLength<4){
        s[0] = '\0';
        return;
    }
    int nPrefix = sizeof(prefix)/sizeof(char*);
    int nTrigrams = sizeof(trigrams)/sizeof(char*);
    int p = rand()%nPrefix;
    s[0] = prefix[p][0];
    s[1] = prefix[p][1];
    s[2] = prefix[p][2];
    int i=3;
    while(i<maxLength-1){
        int t=0;
        while(t<nTrigrams){
            if(   s[i-3] == trigrams[t][0]
               && s[i-2] == trigrams[t][1]
               && s[i-1] == trigrams[t][2] ){
               break;
            }
            t++;
        }
        /* failed to find a trigram? break in two words */
        if(t==nTrigrams){
            if(maxLength-i-1 == 0){
                s[i] = '\0';
                return;
            }
            s[i] = ' ';
            generate(s+i+1, maxLength-i-1);
            return;
        }
        const char* letters = trigrams[t] + 3;
        int n = strlen(letters);
        s[i] = letters[rand()%n];
        i++;
    }
    s[i] = '\0';
}

int main(){
    srand(time(NULL));
    char s[100];
    while(1){
        generate(s, 20);
        printf("%s\n", s);
    }
}
