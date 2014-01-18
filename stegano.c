#include "stegano.h"

int stegano(char *arg[])
{
	FILE *fmsg,*fpic,*fenc;
	int i,j,k,size,offset;
	unsigned char pic_tmp,msg_tmp,tmp;

	switch(arg[1][0])
	{
		case 'e':
			fmsg = fopen(arg[4],"r");
			fseek(fmsg,0,SEEK_END);
			size = ftell(fmsg);
			fseek(fmsg,0,SEEK_SET);
			fpic = fopen(arg[2],"r");
			fenc = fopen(arg[3],"w");
		
			fseek(fpic,10,SEEK_SET);
			offset = fgetc(fpic);
			fseek(fpic,0,SEEK_SET);
			
			for(i=0;i<offset;i++) 
			{
		                pic_tmp=fgetc(fpic);
		                fputc(pic_tmp,fenc);	
			}
			//Вставляем в картинку размер сообщения
			for(j = 6,k = 192;j >= 0;j = j - 2,k = k / 4)
			{
				pic_tmp = fgetc(fpic);
				pic_tmp = pic_tmp & 252 | ((size & k) >> j);
				fputc(pic_tmp,fenc);
			}
			///////////////////////////////////////
			for(i = 1;i <= size; i++)
			{
				msg_tmp = fgetc(fmsg);
				for(j = 6,k = 192;j >= 0;j = j - 2,k = k / 4)
				{
					pic_tmp = fgetc(fpic);
					pic_tmp = pic_tmp & 252 | ((msg_tmp & k) >> j);
					fputc(pic_tmp,fenc);
				}
			}
			while(!feof(fpic))
			{
				pic_tmp = fgetc(fpic);
				fputc(pic_tmp,fenc);
			}
			fclose(fenc);
			fclose(fpic);
			fclose(fmsg);
			break;

		case 'd':
			fenc = fopen(arg[2],"r");
			fmsg = fopen(arg[3],"w");
			fseek(fenc,10,SEEK_SET);
			offset = fgetc(fenc);
			fseek(fenc,0,SEEK_SET);
			for(i=0;i<offset;i++) 
			{
	        	        pic_tmp=fgetc(fenc);	
			}
			//Считывание размера сообщения
			size=0;
			for(j = 6;j >= 0;j = j - 2)
			{
				pic_tmp = fgetc(fenc);
				tmp = (pic_tmp & 3) << j;
				size |= tmp;
			}	
			/////////////////////////////
			for(i = 1;i <= size;i++)
			{
				msg_tmp = 0;
				for(j = 6;j >= 0;j = j - 2)
				{
					pic_tmp = fgetc(fenc);
					tmp = (pic_tmp & 3) << j;
					msg_tmp |= tmp;
				}
				fputc(msg_tmp,fmsg);
			}
			fclose(fmsg);
			fclose(fenc);
			break;
	}
	return 0;
}
