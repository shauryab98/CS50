#include <stdio.h>
#include <cs50.h>
#include <math.h>

int amex[] = {34,37};
int mc[] = {51,52,53,54,55};

int getDigits(int number){
    int total = 0;
    int num = number;
    while(num !=0){
        int mod = num%10;
        num = num/10;
        total+=(mod);
    }
    return total;
}

int getLength(long long number){
    int length = 0;
    long long num = number;
    while(num!=0){
        length++;
        num = num/10;
    }
    return length;
}

int starting(float number, int length, int digits){
    return (int)(number/pow(10,length-digits));
}

int legit(long long number){
    int total = 0;
    long long num = number;
    int length = getLength(number);
    while(num!=0){
        total += getDigits(num%10);
        num = num/10;      
        total += getDigits(2*getDigits(num%10));
        num = num/10;       
    }
    if(total%10 == 0){
        if(length == 15){
            for(int i=0;i<2;i++){
                if(starting(number,length,2) == amex[i]){
                    printf("AMEX\n");
                    return 1;
                }
            }
        } else if((length == 16 || length ==13) && starting(number,length,1) == 4) {     
                    printf("VISA\n");
                    return 1;
       
        } else if(length == 16){
            for(int i=0;i<5;i++){
                if(starting(number,length,2) == mc[i]){
                    printf("MASTERCARD\n");
                    return 1;
                }
            }
        }  else{
            printf("INVALID\n");
            return 0;
            }
        }   
    else{
        printf("INVALID\n");
        return 0;
    }
    printf("INVALID\n");
    return 0;
}

int main(void){ 
    long long credit;  
    while(true){  
        printf("Number: "); 
        credit = GetLongLong();
        if (credit>0){
                break;
        }  
    }
    legit(credit);
    return 1; 
}
