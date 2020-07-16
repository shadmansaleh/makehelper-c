#include <string.h>
#include <stdlib.h>
char * strfr(char * a,char *f,char *r){
	char *s=a;
	int sizeS=strlen(s);
	int sizeF=strlen(f);
	int sizeR=strlen(r);
	int sizeM=sizeS+(sizeS*sizeR/sizeF)+1;
	char *m=malloc(sizeof(char)*sizeM);
//	char m[sizeM];
	char * p=NULL;
	int j=0;
	int k=0;
	char * i=s;
	char * rr=r;
	for (;i<s+sizeS;){
		if((p=strstr(s,f))==NULL){
			p=a+sizeS;
		}
		while(i<p){
			*(m+j)=*i;
			j++;
			i++;
			s++;
		}
		if(p!=a+sizeS){
			while(k<sizeR){
				*(m+j)=*rr;
				j++;
				rr++;
				k++;
			}
		rr=r;
		k=0;
		i+=sizeF;
		s+=sizeF;
		}
		else
			break;
	}
//	s=m;
	*(m+j)='\0';
	return m;
}
