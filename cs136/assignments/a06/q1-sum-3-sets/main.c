/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// None
//
// Name: Oliver Tattersall
// login ID: omtatter
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "cs136-trace.h"



int main(void) {
    int n = 0;
    int retval = scanf("%d", &n);
    int sum[1000] ={};
    // for(int i = 0; i< n; i++){
    //     printf("%d\n", sum[i]);
    // }
    while(1){
        int temp = 0;
        retval = scanf("%d", &temp);
        if(retval!=1){
            break;
        }
        sum[0] = sum[0]+temp;
        for(int i = 1; i < n; i++){
            scanf("%d", &temp);
            sum[i] = sum[i]+temp;
            
        }
    }

    for(int i = 0; i< n; i++){
        printf("%d\n", sum[i]);
    }

    
}
