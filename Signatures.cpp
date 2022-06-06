//---------------------------------------------------------------------------

#pragma hdrstop

#include "Signatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
BYTE jpeg[]={0xFF,0xD8,0xFF,0xE0};
BYTE png[]={0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
BYTE zip[]={0x50,0x4B,0x03,0x04};
BYTE rar[]={0x52,0x61,0x72,0x21,0x1A,0x07,0x01};
BYTE gzip[]={0x1F,0x8B,0x08,0x00};
BYTE zip7[]={0x37,0x7A,0xBC,0xAF,0x27};
BYTE *Signatures[]={jpeg,png,zip,rar,gzip,zip7};
int i;
int j;

int SignatureSearch(BYTE* Content){
	for(i = 0; i<6;i++){
		for(j=0;j<sizeof(Signatures[i]);j++)
		{
			if(Content[j]==Signatures[i][j]){
				if(j==sizeof(Signatures[i])-1)
				{
                    return i;
				}
				else{
                    break;
                }
			}
		}

	}
return -1;

}
