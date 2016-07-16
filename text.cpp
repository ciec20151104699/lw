#include "stdafx.h"
#include"stdio.h"
#include"string.h"
#include<windows.h>
#include"math.h"
int main()
{
	char *content;
	int i,j,a,c;
	char lat[10],lon[11],daye[11],time[9];
	char day1[5],day2[3],day3[3];
	char time1[3],time2[3],time3[3];
	size_t length;
	FILE *fp,*fp1;
	fp=fopen("e:\\1\\export.txt","r");
	fp1=fopen("e:\\1\\12.csv","w");
	if(!fp) 
	{
		printf("无法打开文件\n");
         return -1;
	}
	fseek(fp,SEEK_SET,SEEK_END);
	length=ftell(fp);
	fseek(fp,0,SEEK_SET);
	content=new char[length+1];
	fread(content,sizeof(char),length,fp);
	content[length]=0;

	HWND hWnd=GetConsoleWindow();
	HDC hdc=GetWindowDC(hWnd);
	HPEN hpen;
	HPEN old_pen;

	i=0;
	a=1;
	double x=0,y=0;
	double da1,da2,da3,ti1,ti2,ti3;
	double m=0,n=0,p=0,s,v;
	MoveToEx(hdc,x,y,NULL);
	while(!(content[i]=='<'&&content[i+1]=='/'&&content[i+2]=='g'&&content[i+3]=='p'&&content[i+4]=='x'&&content[i+5]=='>'))
	{
		
		if(content[i]==' '&&content[i+1]=='l'&&content[i+2]=='a'&&content[i+3]=='t')
		{
			strncpy(lat,&content[i+6],9);
			strncpy(lon,&content[i+22],10);
			strncpy(daye,&content[i+44],10);
			strncpy(time,&content[i+55],8);

			strncpy(day1,&content[i+44],4);
			strncpy(day2,&content[i+49],2);
			strncpy(day3,&content[i+52],2);

			strncpy(time1,&content[i+55],2);
			strncpy(time2,&content[i+58],2);
			strncpy(time3,&content[i+61],2);

			lat[9]=0;			
			lon[10]=0;
			daye[10]=0;
			time[8]=0;

			day1[4]=0;
			day2[2]=0;
			day3[2]=0;

			time1[2]=0;
			time2[2]=0;
			time3[2]=0;

			size_t len = strlen(lat) + 1;
	        size_t converted = 0;
			wchar_t *WStr;
			WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,len,lat,_TRUNCATE);
			x=_ttof(WStr);
			free(WStr);

			size_t lent = strlen(lon) + 1;
			WStr=(wchar_t*)malloc(lent*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,lent,lon,_TRUNCATE);
			y=_ttof(WStr);
			free(WStr);
			
			size_t  d1= strlen(day1) + 1;
			WStr=(wchar_t*)malloc(d1*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,d1,day1,_TRUNCATE);
			da1=_ttof(WStr);
			free(WStr);
			size_t d2 = strlen(day2) + 1;
			WStr=(wchar_t*)malloc(d2*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,d2,day2,_TRUNCATE);
			da2=_ttof(WStr);
			free(WStr);
			size_t d3 = strlen(day3) + 1;
			WStr=(wchar_t*)malloc(d3*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,d3,day3,_TRUNCATE);
			da3=_ttof(WStr);
			free(WStr);

			size_t t1 = strlen(time1) + 1;
			WStr=(wchar_t*)malloc(t1*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,t1,time1,_TRUNCATE);
			ti1=_ttof(WStr);
			free(WStr);
			size_t t2 = strlen(time2) + 1;
			WStr=(wchar_t*)malloc(t2*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,t2,time2,_TRUNCATE);
			ti2=_ttof(WStr);
			free(WStr);
			size_t t3 = strlen(time3) + 1;
			WStr=(wchar_t*)malloc(t3*sizeof(wchar_t));
			mbstowcs_s(&converted,WStr,t3,time3,_TRUNCATE);
			ti3=_ttof(WStr);
			free(WStr);

			s=sqrt((x-m)*(x-m)*111000*111000+(y-n)*(y-n)*85276*85276);
			m=x,n=y;

			v=s/((ti3+ti2*60+ti1*3600+da3*86400)-(p));
			p=ti3+ti2*60+ti1*3600+da3*86400;

			int b;
			b=v;
			if(b<60)
			{

				hpen=CreatePen(PS_SOLID,5,RGB(b*4.25,180-b*3,0));
				old_pen=(HPEN)SelectObject(hdc,hpen);
				LineTo(hdc,x*1000-40770,y*1000-111670);
				SelectObject(hdc,old_pen);
				DeleteObject(hpen);
			}
			else
			{
				hpen=CreatePen(PS_SOLID,5,RGB(b*4.25,180,b*4.25));
				old_pen=(HPEN)SelectObject(hdc,hpen);
				LineTo(hdc,x*1000-40770,y*1000-111670);
				SelectObject(hdc,old_pen);
				DeleteObject(hpen);
			}


			//printf("%lf\n",v);
			fprintf(fp1,"%d,%s,%s,%s,%s\n",a,lat,lon,daye,time);
			a++;
		}
		i++;
	 }

	
	fclose(fp);
	fclose(fp1);
	return 0;

}
