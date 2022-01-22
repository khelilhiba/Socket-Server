#include<stdio.h>
#include<string.h>
void conversion_hex2bin(char* v_hexa, char v_bin[95])
{int i=0,j=0;
   
    for(i=0; i< strlen(v_hexa);i++)
        {
        if(v_hexa[i]=='0') {strcat(v_bin,"0000");}  
        else if(v_hexa[i]=='1') {strcat(v_bin,"0001");}  
        else if(v_hexa[i]=='2') {strcat(v_bin,"0010");}  
        else if(v_hexa[i]=='3') {strcat(v_bin,"0011");}  
        else if(v_hexa[i]=='4') {strcat(v_bin,"0100");}  
        else if(v_hexa[i]=='5') {strcat(v_bin,"0101");}  
        else if(v_hexa[i]=='6') {strcat(v_bin,"0110");}  
        else if(v_hexa[i]=='7') {strcat(v_bin,"0111");}  
        else if(v_hexa[i]=='8') {strcat(v_bin,"1000");}  
        else if(v_hexa[i]=='9') {strcat(v_bin,"1001");}  
        else if((v_hexa[i]=='A')||(v_hexa[i]=='a')){strcat(v_bin,"1010");}  
        else if((v_hexa[i]=='B')||(v_hexa[i]=='b')){strcat(v_bin,"1011");}  
        else if((v_hexa[i]=='C')||(v_hexa[i]=='c')){strcat(v_bin,"1100");}  
        else if((v_hexa[i]=='D')||(v_hexa[i]=='d')){strcat(v_bin,"1101");}  
        else if((v_hexa[i]=='E')||(v_hexa[i]=='e')){strcat(v_bin,"1110");}  
        else if((v_hexa[i]=='F')||(v_hexa[i]=='f')){strcat(v_bin,"1111");}  
        
        }
    //printf("v_bin[ = %s\n",v_bin);

   
}

int mul(int a, int b)
{int m=1;
    for(int i=0; i<b; i++)
        m=m*a;
    return m;
}


int conversion_b2D(char* bin)
{
 
    int i; int d=0;
    int dec=0;
    for(i=strlen(bin)-1; i>=0; i--)
    {   int v;
        if(bin[i]=='0') v=0;
        else v=1;
        dec = dec + (v*(mul(2,d)));
       
        d++;
    }
    return dec; 
    return 0;
}
