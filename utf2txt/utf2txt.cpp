/* ******************************************************************** **
** @@ UTF-2-TXT
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

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

static char    pXLAT[ASCII_SIZE] =
{
   '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x98', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 00 - C2 9x
   '\xA0', '\x00', '\x00', '\x00', '\xA4', '\x00', '\xA6', '\xA7', '\x00', '\xA9', '\x00', '\xAB', '\xAC', '\xAD', '\xAE', '\x00', // 01 - C2 Ax
   '\xB0', '\xB1', '\x00', '\x00', '\x00', '\xB5', '\xB6', '\xB7', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', // 02 - C2 Bx 
   '\x00', '\xA8', '\x80', '\x81', '\xAA', '\xBD', '\xB2', '\xAF', '\xA3', '\x8A', '\x8C', '\x8E', '\x8D', '\x00', '\xA1', '\x8F', // 03 - D0 8x 
   '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF', // 04 - D0 9x 
   '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF', // 05 - D0 Ax 
   '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF', // 06 - D0 Bx 
   '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF', // 07 - D1 8x 
   '\x00', '\xB8', '\x90', '\x83', '\xBA', '\xBE', '\xB3', '\xBF', '\xBC', '\x9A', '\x9C', '\x9E', '\x9D', '\x00', '\xA2', '\x9F', // 08 - D1 9x 
   '\xA5', '\xB4', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 09 - D2 9x 
   '\x00', '\x00', '\x00', '\x96', '\x97', '\x00', '\x00', '\x00', '\x91', '\x92', '\x82', '\x00', '\x93', '\x94', '\x84', '\x00', // 0A - E2 80 9x 
   '\x86', '\x87', '\x95', '\x00', '\x00', '\x00', '\x85', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 0B - E2 80 Ax 
   '\x89', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x8B', '\x9B', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 0C - E2 80 Bx 
   '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x88', '\x00', '\x00', '\x00', // 0D - E2 82 Ax 
   '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xB9', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 0E - E2 84 9x 
   '\x00', '\x00', '\x99', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', // 0F - E2 84 Ax 
};
/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

static char UTF8_2_Cyrillic(const BYTE* const pBuf,int iNdx,int& rLen)
{
   rLen = 1;   // Just goto NEXT !

   if (IsBadReadPtr((pBuf + iNdx),2))
   {
      // Error !
      ASSERT(0);
      return 0;
   }

   BYTE     Lo = (BYTE) (*(pBuf + iNdx + 1) & 0x0F);
   BYTE     Hi = (BYTE)((*(pBuf + iNdx + 1) & 0xF0) >> 4);

   switch (*(pBuf + iNdx))
   {
      case 0xC2:
      {
         switch (Hi)
         {
            case 0x09:
            {
               // 00 - C2 9x     
               rLen = 2;
               return pXLAT[(0x00 << 4) + Lo];
            }
            case 0x0A:
            {
               // 01 - C2 Ax     
               rLen = 2;
               return pXLAT[(0x01 << 4) + Lo];
            }
            case 0x0B:
            {
               // 02 - C2 Bx 
               rLen = 2;
               return pXLAT[(0x02 << 4) + Lo];
            }
            default:
            {
               // Error !
               ASSERT(0);
               return 0;
            }
         }
      }
      case 0xD0:
      {
         switch (Hi)
         {
            case 0x08:
            {
               // 03 - D0 8x      
               rLen = 2;
               return pXLAT[(0x03 << 4) + Lo];
            }
            case 0x09:
            {
               // 04 - D0 9x     
               rLen = 2;
               return pXLAT[(0x04 << 4) + Lo];
            }
            case 0x0A:
            {
               // 05 - D0 Ax     
               rLen = 2;
               return pXLAT[(0x05 << 4) + Lo];
            }
            case 0x0B:
            {
               // 06 - D0 Bx     
               rLen = 2;
               return pXLAT[(0x06 << 4) + Lo];
            }
            default:
            {
               // Error !
               ASSERT(0);
               return 0;
            }
         }
      }
      case 0xD1:
      {
         switch (Hi)
         {
            case 0x08:
            {
               // 07 - D1 8x     
               rLen = 2;
               return pXLAT[(0x07 << 4) + Lo];
            }
            case 0x09:
            {
               // 08 - D1 9x      
               rLen = 2;
               return pXLAT[(0x08 << 4) + Lo];
            }
            default:
            {
               // Error !
               ASSERT(0);
               return 0;
            }
         }
      }
      case 0xD2:
      {
         switch (Hi)
         {
            case 0x09:
            {
               // 09 - D2 9x      
               rLen = 2;
               return pXLAT[(0x09 << 4) + Lo];
            }
            default:
            {
               // Error !
               ASSERT(0);
               return 0;
            }
         }
      }
      case 0xE2:
      {
         if (Hi != 0x08)
         {
            // Error !
            ASSERT(0);
            return 0;
         }
         
         if (IsBadReadPtr((pBuf + iNdx + 2),1))
         {
            // Error !
            ASSERT(0);
            return 0;
         }

         BYTE     Lo2 = (BYTE) (*(pBuf + iNdx + 2) & 0x0F);
         BYTE     Hi2 = (BYTE)((*(pBuf + iNdx + 2) & 0xF0) >> 4);

         switch (Lo)
         {
            case 0x00:
            {
               switch (Hi2)
               {
                  case 0x09:
                  {
                     // 0A - E2 80 9x  
                     rLen = 3;
                     return pXLAT[(0x0A << 4) + Lo2];
                  }
                  case 0x0A:
                  {
                     // 0B - E2 80 Ax  
                     rLen = 3;
                     return pXLAT[(0x0B << 4) + Lo2];
                  }
                  case 0x0B:
                  {
                     // 0C - E2 80 Bx  
                     rLen = 3;
                     return pXLAT[(0x0C << 4) + Lo2];
                  }
                  default:
                  {
                     // Error !
                     ASSERT(0);
                     return 0;
                  }
               }
            }
            case 0x02:
            {
               switch (Hi2)
               {
                  case 0x0A:
                  {
                     // 0D - E2 82 Ax  
                     rLen = 3;
                     return pXLAT[(0x0D << 4) + Lo2];
                  }
                  default:
                  {
                     // Error !
                     ASSERT(0);
                     return 0;
                  }
               }
            }
            case 0x04:
            {
               switch (Hi2)
               {
                  case 0x09:
                  {
                     // 0E - E2 84 9x  
                     rLen = 3;
                     return pXLAT[(0x0E << 4) + Lo2];
                  }
                  case 0x0A:
                  {
                     // 0F - E2 84 Ax  
                     rLen = 3;
                     return pXLAT[(0x0F << 4) + Lo2];
                  }
                  default:
                  {
                     // Error !
                     ASSERT(0);
                     return 0;
                  }
               }
            }
            default:
            {
               // Error !
               ASSERT(0);
               return 0;
            }
         }
      }
      default:
      {
         // Error !
         ASSERT(0);
         return 0;
      }
   }
}

/* ******************************************************************** **
** @@ Proceed()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Modify :
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

   BYTE*    pData = pBuf;

   if ((pData[0] == 0xEF) && (pData[1] == 0xBB) && (pData[2] == 0xBF))
   {
      // LE - EF BB BF
      pData  += 3;
      dwSize -= 3;

      printf("[I]: LE BOM marker found.\n");
   }
   else if ((pData[0] == 0xBF) && (pData[1] == 0xBB) && (pData[2] == 0xEF))
   {
      // BE - BF BB EF
      // Not Supported !
      ASSERT(0);
      printf("\a[E]: BOM: BE order is NOT supported.\n");
      return;
   }
   else
   {
      printf("[I]: No BOM marker found, LE order assumed.\n");
   }

   for (DWORD ii = 0; ii < dwSize; )
   {
      if (pData[ii] < 0x80)
      {
         // Just ASCII
         fprintf(pOut,"%c",pData[ii++]);
      }
      else
      {
         // Possible UTF-8
         int      iLen = 0;

         char     cTemp = UTF8_2_Cyrillic(pData,ii,iLen);

         ASSERT((iLen == 2) || (iLen == 3));

         fprintf(pOut,"%c",cTemp  ?  cTemp  :  0x3F);

         ii += iLen;
      }
   }

   MF.Close();

   fclose(pOut);
   pOut = NULL;
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt :     
** @  Author :
** @  Modify :
** @  Modify :
** @  Notes  :
** ******************************************************************** */

static void ShowHelp()
{
   const char  pszCopyright[] = "-*-   UTF-2-TXT 1.01   *   (c) gazlan@yandex.ru, 2016   -*-";
   const char  pszDescript [] = "UTF-8 to Russian CP-1251 converter";
   const char  pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: utf2txt.com wildcards\n\n");
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
** @@                   The End
** ******************************************************************** */
