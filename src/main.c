/******************************************************************************/
/*                    T E S T   U T I L I T Y   -   M A I N                   */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>

#ifdef __sun
#include <strings.h>
#endif

#ifdef linux
#include <string.h>
#endif

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "main.h"
#include "genlib.h" 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define DOTS_STR "..............."
#define DOTS_LEN (int) strlen( DOTS_STR )

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define mAbbort( str ) { perror( str );  goto _door ; }

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                                  M A I N                                   */
/*                                                                            */
/******************************************************************************/
//#ifndef __TDD__

int main(int argc, const char* argv[] )
{
  char childPrg[256]   ;
  char stdOutFile[256] ;
  char stdErrFile[256] ;
  char logFile[256]    ;
  char cmpOutFile[256] ;
  char cmpErrFile[256] ;
  char cmpLogFile[256] ;
  char doneFile[256]   ;

  FILE *stdOutFp ;
  FILE *stdErrFp ;
//FILE *stdLogFp ;

  memset( childPrg  , '\0', 256 ) ;
  memset( stdOutFile, '\0', 256 ) ;
  memset( stdErrFile, '\0', 256 ) ;
  memset( logFile   , '\0', 256 ) ;
  memset( cmpOutFile, '\0', 256 ) ;
  memset( cmpErrFile, '\0', 256 ) ;
  memset( cmpLogFile, '\0', 256 ) ;
  memset( doneFile  , '\0', 256 ) ;

  FILE *doneFP ;

  int i ;

  char *cmdLn[5] ;
  for( i=0; i<5; i++ ) {cmdLn[i]=NULL;} 

  int sysRc = NO_ERROR ;

  sysRc = cmdLineHandler( argc, argv, childPrg,
                                      stdOutFile,
                                      stdErrFile,
                                      logFile   ,
                                      cmpOutFile,
                                      cmpErrFile,
                                      cmpLogFile,
                                      doneFile ) ;

  #ifdef __TDD__
  
    printf("%s\n",childPrg);
    printf("%s\n",stdOutFile);
    printf("%s\n",stdErrFile);
    printf("%s\n",logFile);
    printf("%s\n",cmpOutFile);
    printf("%s\n",cmpErrFile);
    printf("%s\n",cmpLogFile);
    printf("%s\n",doneFile ) ;

  #endif

  if( sysRc != NO_ERROR ) { usage(0) ; exit(1) ; }

  #if(0)
  // -------------------------------------------------------
  // check the rights on config file
  // -------------------------------------------------------
  sysRc = checkFileRights( cfgFile, R_OK );
  if( sysRc != NO_ERROR ) mAbbort( "checkFileRights" );

  // -------------------------------------------------------
  // read config file
  // -------------------------------------------------------
  sysRc = readCfgFile( cfgFile, &cfg ) ;
  if( sysRc != 0 ) mAbbort( "readCfgFile" ) ;
  #endif

  // -------------------------------------------------------
  // forking process
  // -------------------------------------------------------
  cmdLn[0] = childPrg ;
  cmdLn[1] = NULL ;

  // ---------------------------------------------------
  // open files
  // ---------------------------------------------------
  stdOutFp = fopen( stdOutFile, "w" ) ;
  if( stdOutFp == NULL )
  {
    sysRc = errno  ;       // error handling
    perror( stdOutFile ) ; //
    goto _door     ;       // quit function with errno
  }

  stdErrFp = fopen( stdErrFile, "w" ) ;
  if( stdErrFp == NULL )
  {
    sysRc = errno  ;       // error handling
    perror( stdErrFile ) ; //
    goto _door     ;       // quit function with errno
  }

#if(0)
  stdLogFp = fopen( logFile, "r" ) ;  // remove log file if exists
  if( stdLogFp != NULL )  // remove log file if exists
  {
    fclose( stdLogFp ) ;
  }
    if( errno != ENOENT ) unlink( logFile ) ;
#endif
  flushFile( logFile ) ;

  sysRc = startChild( childPrg, stdOutFp, stdErrFp, cmdLn ) ;

  if( sysRc != 0 ) 
  {
    fprintf( stderr, "%s: test failed\n",basename(childPrg) ) ;
//  goto _door ;
//  mAbbort("startChild") ;
  }
  else
  {
    sysRc = 0 ;
  }

  // -------------------------------------------------------
  // compare files
  // -------------------------------------------------------
  sysRc = diffLog( stdOutFile, cmpOutFile ) ;
  if( sysRc != NO_ERROR ) 
  {
    fprintf( stderr, "diff failed: %s\t%s\n", stdOutFile, cmpOutFile ) ;
    goto _door ;
  //mAbbort( stdOutFile ) ;
  }

  sysRc = diffLog( cmpErrFile, stdErrFile ) ;
  if( sysRc != NO_ERROR ) 
  {
    fprintf( stderr, "diff failed: %s\t%s\n", stdErrFile, cmpErrFile) ;
    goto _door ;
  //mAbbort( stdErrFile ) ;
  }

  sysRc = diffLog( cmpLogFile, logFile ) ;
  if( sysRc != NO_ERROR ) 
  {
    fprintf( stderr, "diff failed: %s, %s\n",logFile, cmpLogFile ) ;
    goto _door ;
  //mAbbort( stdErrFile ) ;
  }

  doneFP = fopen( doneFile, "w" ) ;
  if( doneFP == NULL ) 
  {
    mAbbort( doneFile ) ;
  }

  fclose( doneFP ) ;

_door :

  printf("test: %s %.*s ", 
                    (char*) basename( childPrg )     ,
                    ( DOTS_LEN < (int) strlen( basename( childPrg )) ) ?  0 \
                    : DOTS_LEN - (int) strlen( basename( childPrg ))     ,
                      DOTS_STR ) ;
  
  if( sysRc == 0 ) { printf("ok\n") ; }
  else             { printf("err\n") ; }

  return sysRc ;
}

//#endif

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* usage                                                                      */
/******************************************************************************/
#if 0
void usage()
{
  printf("usage: \n");
  printf("tutl bin stdout stderr cmpout cmperr done\n");
  printf("\tbin:\tbinary including tests\n");
  printf("\tstdout:\tstdout redirection file\n");
  printf("\tstderr:\tstderr redirection file\n");
  printf("\tcmpout:\tstdout compare file\n");
  printf("\tcmperr:\tstderr compare file\n");
  printf("\tlog   :\tstderr compare file\n");
  printf("\tcmplog:\tlog    compare file\n");
  printf("\tdone:\tdone file, created if succesfull\n");
}
#endif

/******************************************************************************/
/* command line handler                                                       */
/******************************************************************************/
int cmdLineHandler( const int argc            ,
                    const char** argv         ,
                          char* pChildPrg     ,
                          char* pStdOutFile   ,
                          char* pStdErrFile   ,
                          char* pLogOutFile   ,
                          char* pCmpOutFile   ,
                          char* pCmpErrFile   ,
                          char* pLogCmpFile   ,
                          char* pFlagDoneFile )
{
  int rc = 0 ;

//*pStdOutFile = NULL ;
//*pStdErrFile = NULL ;

  // -------------------------------------------------------
  // print out cmdline for test moudles only
  // -------------------------------------------------------
  #ifdef __TDD__
    int i;

    for( i=0; i<argc; i++ )
    {
      printf("argv[%d/%d] : %s\n", i, argc, argv[i] );
    }
  #endif

  if( argc < 2 )                    // check for at least one cmd line attr
  {                                 //   if not exists   
    rc = 1     ;                    //     return error 
    goto _door ;                    //     
  }                                 //
  strcpy( pChildPrg, argv[1] ) ;    // set child prg
                                    //
  if( argc == 2 )                   // check for 2nd cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  strcpy( pStdOutFile, argv[2] ) ;  // set stdOut
                                    //
  if( argc == 3 )                   // check for 3th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  strcpy( pStdErrFile, argv[3] ) ;  //
                                    //
  if( argc == 4 )                   // check for 4th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  strcpy( pLogOutFile, argv[4] ) ;  // set log file
                                    //
  if( argc == 5 )                   // check for 5th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  strcpy( pCmpOutFile, argv[5] ) ;  // set stdOut
                                    //
  if( argc == 6 )                   // check for 6th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  strcpy( pCmpErrFile, argv[6] ) ;  // set stdOut
                                    //
  if( argc == 7 )                   // check 7th cmd line attr
  {                                 //  if not exists
    rc = 0 ;                        //    return from func 
    goto _door ;                    //    without an error
  }                                 //
  strcpy( pLogCmpFile, argv[7] ) ;  // set log compaire file
                                    //
  if( argc == 8 )                   // check 8th cmd line attr
  {                                 //  if not exists
    rc = 0 ;                        //    return from func 
    goto _door ;                    //    without an error
  }                                 //
                                    //
  strcpy( pFlagDoneFile, argv[8] ) ;//
                                    //
  if( argc > 9 )                    // check for more then 9 arguments
  {                                 //   return error
    rc = 1     ;                    //
    goto _door ;                    //
  }                                 //

_door:
  return rc ;
}

