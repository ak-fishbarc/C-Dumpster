#include <stdio.h>
#include <string.h>

int romanToInt(char s[])
{   
    int ret = 0;
    int l;
    for(l = 0; l < strlen(s); l++){

        switch(s[l]){
        
        case 'I' :
            if(s[l+1] == 'V' || s[l+1] == 'X'){
                ret -= 1;
            } else {
                ret += 1;
            }
            break;
            
        case 'V' :
            ret += 5;
            break;
            
        case 'X' :
            if(s[l+1] == 'L' || s[l+1] == 'C'){
                ret -= 10;
            } else {
                ret += 10;
            }
            break;
            
        case 'L' :
            ret += 50;
            break;
            
        case 'C' :
            if(s[l+1] == 'D' || s[l+1] == 'M'){
                ret -= 100;
            } else {
                ret += 100;
            }
            break;
            
        case 'D' :
            ret += 500;
            break;
            
        case 'M' :
            ret += 1000;
            break;
            
        }
    }
    
    printf("%d\n", ret);
    return ret;
    
}


int main()
{
    
    char numeral[] = "IV";
    romanToInt(numeral);
    
    char numeral2[] = "III";
    romanToInt(numeral2);
    
    char numeral3[] = "MCMXCIV";
    romanToInt(numeral3);
    
    return 0;
    
}