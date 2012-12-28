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

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "main.h"
#include "genlib.h" 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

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
#ifndef __TDD__

int main(int argc, const char* argv[] )
{
  char *childPrg   ;
  char *stdOutFile ;
  char *stdErrFile ;
  char *cmpOutFile ;
  char *cmpErrFile ;
  char *doneFile   ;

  FILE *doneFP ;

  char *cmdLn[5] ;

  int sysRc = NO_ERROR ;

  sysRc = cmdLineHandler( argc, argv, &childPrg,
                                      &stdOutFile,
                                      &stdErrFile,
                                      &cmpOutFile,
                                      &cmpErrFile,
                                      &doneFile ) ;

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
  sysRc = startChild( childPrg, stdOutFile, stdErrFile, cmdLn ) ;
  if( sysRc != 0 ) 
  {
    mAbbort("startChild") ;
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
    mAbbort( stdOutFile ) ;
  }

  sysRc = diff( cmpErrFile, stdErrFile ) ;
  if( sysRc != NO_ERROR ) 
  {
    mAbbort( stdErrFile ) ;
  }

  doneFP = fopen( doneFile, "w" ) ;
  if( doneFP == NULL ) 
  {
    mAbbort( doneFile ) ;
  }

  fclose( doneFP ) ;

_door :

  printf("test: %s\t", (char*) basename( childPrg ) );
  if( sysRc == 0 ) { printf("ok\n") ; }
  else             { printf("err\n") ; }

  return sysRc ;
}

#endif

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* usage                                                                      */
/******************************************************************************/
void usage()
{
  printf("usage: \n");
  printf("tutl bin stdout stderr cmpout cmperr done\n");
  printf("\tbin:\tbinary including tests\n");
  printf("\tstdout:\tstdout redirection file\n");
  printf("\tstderr:\tstderr redirection file\n");
  printf("\tcmpout:\tstdout compare file\n");
  printf("\tcmperr:\tstderr compare file\n");
  printf("\tdone:\tdone file, created if succesfull\n");
}

/******************************************************************************/
/* command line handler                                                       */
/******************************************************************************/
int cmdLineHandler( const int argc             ,
                    const char** argv          ,
                          char** pChildPrg     ,
                          char** pStdOutFile   ,
                          char** pStdErrFile   ,
                          char** pCmpOutFile   ,
                          char** pCmpErrFile   ,
                          char** pFlagDoneFile )
{
  int rc = 0 ;

  *pStdOutFile = NULL ;
  *pStdErrFile = NULL ;

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
  *pChildPrg = (char*) argv[1] ;    // set child prg
                                    //
  if( argc == 2 )                   // check for 2nd cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  *pStdOutFile = (char*) argv[2] ;  // set stdOut
                                    //
  if( argc == 3 )                   // check for 3th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  *pStdErrFile = (char*) argv[3] ;  //
                                    //
  if( argc == 4 )                   // check for 4th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  *pCmpOutFile = (char*) argv[4] ;  // set stdOut

  if( argc == 5 )                   // check for 4th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  *pCmpErrFile = (char*) argv[5] ;  // set stdOut

  if( argc == 6 )                   // check for 4th cmd line attr
  {                                 //  if not exists 
    rc = 0     ;                    //    return from func 
    goto _door ;                    //    whithout an error
  }                                 //
  *pFlagDoneFile = (char*) argv[6] ;//
                                    //
  if( argc > 7 )                    // check for more then 4 arguments
  {                                 //   return error
    rc = 1     ;                    //
    goto _door ;                    //
  }                                 //

_door:
  return rc ;
}

