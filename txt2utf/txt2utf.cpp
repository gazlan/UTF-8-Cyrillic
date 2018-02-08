/* ******************************************************************** **
** @@ Text Dictionary Transliterator
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include <stdafx.h>

#include "..\shared\file_find.h"
#include "..\shared\mmf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#endif 

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#define ASCII_SIZE      (256)

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

extern DWORD   dwKeepError = 0;

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */
                  
static int  pXLIT[ASCII_SIZE] =
{
   0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
   0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F,
   0x00000010, 0x00000011, 0x00000012, 0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017,
   0x00000018, 0x00000019, 0x0000001A, 0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000001F,
   0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025, 0x00000026, 0x00000027,
   0x00000028, 0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F,
   0x00000030, 0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036, 0x00000037,
   0x00000038, 0x00000039, 0x0000003A, 0x0000003B, 0x0000003C, 0x0000003D, 0x0000003E, 0x0000003F,
   0x00000040, 0x00000041, 0x00000042, 0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047,
   0x00000048, 0x00000049, 0x0000004A, 0x0000004B, 0x0000004C, 0x0000004D, 0x0000004E, 0x0000004F,
   0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054, 0x00000055, 0x00000056, 0x00000057,
   0x00000058, 0x00000059, 0x0000005A, 0x0000005B, 0x0000005C, 0x0000005D, 0x0000005E, 0x0000005F,
   0x00000060, 0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065, 0x00000066, 0x00000067,
   0x00000068, 0x00000069, 0x0000006A, 0x0000006B, 0x0000006C, 0x0000006D, 0x0000006E, 0x0000006F,
   0x00000070, 0x00000071, 0x00000072, 0x00000073, 0x00000074, 0x00000075, 0x00000076, 0x00000077,
   0x00000078, 0x00000079, 0x0000007A, 0x0000007B, 0x0000007C, 0x0000007D, 0x0000007E, 0x0000007F,
   0x000082D0, 0x000083D0, 0x009A80E2, 0x000093D1, 0x009E80E2, 0x00A680E2, 0x00A080E2, 0x00A180E2,
   0x00AC82E2, 0x00B080E2, 0x000089D0, 0x00B980E2, 0x00008AD0, 0x00008CD0, 0x00008BD0, 0x00008FD0,
   0x000092D1, 0x009880E2, 0x009980E2, 0x009C80E2, 0x009D80E2, 0x00A280E2, 0x009380E2, 0x009480E2,
   0x000098C2, 0x00A284E2, 0x000099D1, 0x00BA80E2, 0x00009AD1, 0x00009CD1, 0x00009BD1, 0x00009FD1,
   0x0000A0C2, 0x00008ED0, 0x00009ED1, 0x000088D0, 0x0000A4C2, 0x000090D2, 0x0000A6C2, 0x0000A7C2,
   0x000081D0, 0x0000A9C2, 0x000084D0, 0x0000ABC2, 0x0000ACC2, 0x0000ADC2, 0x0000AEC2, 0x000087D0,
   0x0000B0C2, 0x0000B1C2, 0x000086D0, 0x000096D1, 0x000091D2, 0x0000B5C2, 0x0000B6C2, 0x0000B7C2,
   0x000091D1, 0x009684E2, 0x000094D1, 0x0000BBC2, 0x000098D1, 0x000085D0, 0x000095D1, 0x000097D1,
   0x000090D0, 0x000091D0, 0x000092D0, 0x000093D0, 0x000094D0, 0x000095D0, 0x000096D0, 0x000097D0,
   0x000098D0, 0x000099D0, 0x00009AD0, 0x00009BD0, 0x00009CD0, 0x00009DD0, 0x00009ED0, 0x00009FD0,
   0x0000A0D0, 0x0000A1D0, 0x0000A2D0, 0x0000A3D0, 0x0000A4D0, 0x0000A5D0, 0x0000A6D0, 0x0000A7D0,
   0x0000A8D0, 0x0000A9D0, 0x0000AAD0, 0x0000ABD0, 0x0000ACD0, 0x0000ADD0, 0x0000AED0, 0x0000AFD0,
   0x0000B0D0, 0x0000B1D0, 0x0000B2D0, 0x0000B3D0, 0x0000B4D0, 0x0000B5D0, 0x0000B6D0, 0x0000B7D0,
   0x0000B8D0, 0x0000B9D0, 0x0000BAD0, 0x0000BBD0, 0x0000BCD0, 0x0000BDD0, 0x0000BED0, 0x0000BFD0,
   0x000080D1, 0x000081D1, 0x000082D1, 0x000083D1, 0x000084D1, 0x000085D1, 0x000086D1, 0x000087D1,
   0x000088D1, 0x000089D1, 0x00008AD1, 0x00008BD1, 0x00008CD1, 0x00008DD1, 0x00008ED1, 0x00008FD1
};

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ Cyrillic_2_UTF8()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Cyrillic_2_UTF8(DWORD& rDst,BYTE bySrc)
{  
   rDst = 0;  // Reset

   int   iRet = pXLIT[bySrc];
   
   strcat((char*)&rDst,(char*)&iRet); 
}

/* ******************************************************************** **
** @@ Proceed()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Proceed(const char* const pszFileName)
{
   char     pszBackName[_MAX_PATH];
   char     pszDrive   [_MAX_DRIVE];
   char     pszDir     [_MAX_DIR];
   char     pszFName   [_MAX_FNAME];
   char     pszExt     [_MAX_EXT];

   _splitpath(pszFileName,pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszBackName,pszDrive,pszDir,pszFName,"BAK");

   CopyFile(pszFileName,pszBackName,FALSE);

   FILE*    pOut = fopen(pszFileName,"wb");

   if (!pOut)
   {
      perror("\a\nOpen Output File Error !\n");
      return;
   }

   MMF   MF;

   if (!MF.OpenReadOnly(pszBackName))
   {
      // Error !
      ASSERT(0);
      return;
   }

   BYTE*    pBuf   = MF.Buffer();
   DWORD    dwSize = MF.Size();

   for (DWORD ii = 0; ii < dwSize; ++ii)
   {
      DWORD    dwTemp = 0;

      Cyrillic_2_UTF8(dwTemp,pBuf[ii]);

      if (dwTemp)
      {
         fprintf(pOut,"%s",(char*)&dwTemp);
      }
   }

   MF.Close();
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void ShowHelp()
{
   const char  pszCopyright[] = "-*-   TXT-2-UTF8 1.0   *   (c) gazlan@yandex.ru, 2016   -*-";
   const char  pszDescript [] = "Russian CP-1251 to UTF-8 converter";
   const char  pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: txt2utf.com [wildcards]\n\n");
   printf("%s\n",pszE_Mail);
}

/* ******************************************************************** **
** @@ main()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int main(int argc,char** argv)
{
   if (argc != 2)
   {
      ShowHelp();
      return 0;
   }

   if (argc == 2 && ((!strcmp(argv[1],"?")) || (!strcmp(argv[1],"/?")) || (!strcmp(argv[1],"-?")) || (!stricmp(argv[1],"/h")) || (!stricmp(argv[1],"-h"))))
   {
      ShowHelp();
      return 0;
   }

   FindFile   FF;

   FF.SetMask(argv[1]);

   while (FF.Fetch())
   {
      if ((FF._w32fd.dwFileAttributes | FILE_ATTRIBUTE_NORMAL) && !(FF._w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
         Proceed(FF._w32fd.cFileName);
      }
   }

   return 0;
}

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
