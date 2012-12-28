/******************************************************************************/
/*  test util                                                                 */
/*                                                                            */
/*  test: t000                                                                */
/*                                                                            */
/*  tests:                                                                    */
/*    - testing command line                                                  */
/*    - testing check file rights                                             */
/******************************************************************************/

/******************************************************************************/
/*  includes                                                                  */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own
// ---------------------------------------------------------
#include "main.h"
#include "tutl.h"
#include "genlib.h"

/******************************************************************************/
/*  defines                                                                   */
/******************************************************************************/
#define NO_FILE "/do/not/exists"

/******************************************************************************/
/*  main                                                                      */
/******************************************************************************/
int main(int argc, const char** argv )
{
#if(0)
  int rc ;
  int i ;

  tTstCfg cfg ;
#endif

  int sysRc = NO_ERROR ;

  // -------------------------------------------------------  
  // command line tests
  // -------------------------------------------------------  

//char *cfgFile    ;

#if(0)
  startTestStep( "commandLine" ) ;

  char *stdOutFile ;
  char *stdErrFile ;
  char *doneFile   ;

  sysRc = cmdLineHandler( argc, argv, &cfgFile, 
                                      &stdOutFile, 
                                      &stdErrFile, 
                                      &doneFile ) ;

  printf("config file:\t%s\n", cfgFile    );
  printf("stdout file:\t%s\n", stdOutFile );
  printf("stderr file:\t%s\n", stdErrFile );
  printf("done file:\t%s\n"  , doneFile   );

  if( sysRc != NO_ERROR ) 
  {
    errTestStep( "commandLine" ) ;
    goto _door ;
  }

  okTestStep( "commandLine" ) ;
#endif

  // -------------------------------------------------------  
  // check for not existing file
  // -------------------------------------------------------  

  startTestStep( "check file rights" ) ;

  sysRc = checkFileRights( "/do/not/exists", R_OK ) ;  
  if( sysRc != ENOENT )
  {
    errTestStep( "check file rights" ) ;
    goto _door ; 
  }
  else
  {
    sysRc = 0 ;
  }

  okTestStep( "check file rights" ) ;

  startTestStep( "check file rights" ) ;

  sysRc = checkFileRights( argv[0], R_OK|X_OK ) ;  
  if( sysRc != NO_ERROR )
  {
    errTestStep( "checking exec rights failed" );
    return 1 ;
  }

  okTestStep( "check file rights" ) ;

  // -------------------------------------------------------
  // testing countWords
  // -------------------------------------------------------

  startTestStep( "count words empty sring" ) ;

  if( countWords("",0) != 0 )
  {
    errTestStep( "count words empty sring" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words empty sring" ) ;

  startTestStep( "count words buffer overflow" ) ;
  
  if( countWords("",-1) != -1 )
  {
    errTestStep( "count words buffer overflow" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  errTestStep( "count words buffer overflow" ) ;
  
  startTestStep( "count words one word" ) ;

  if( countWords("hello",sizeof("hello")) != 1 )
  {
    errTestStep( "count words one word" ) ;
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words one word" ) ;

  startTestStep( "count words one word" ) ;
  
  if( countWords(" hello ",sizeof(" hello   ")) != 1 )
  {
    errTestStep( "count words one word" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words one word" ) ;

  startTestStep( "count words buffer overflow" ) ;
  
  if( countWords(" hello ",(sizeof(" hello ")-1)) != -1 )
  {
    errTestStep( "count words buffer overflow" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words buffer overflow" ) ;

  startTestStep( "count words two words" ) ;
  
  if( countWords("hello world",255) != 2 )
  {
    errTestStep( "count words two words" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words two words" ) ;

  startTestStep( "count words multiple blanks" ) ;

  if( countWords("hello   world",255) != 2 )
  {
    errTestStep( "count words multiple blanks" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words multiple blanks" ) ;

  startTestStep( "count words non pritible" ) ;
  
  if( countWords("hello  world",255) != -2 )
  {
    errTestStep( "count words non pritible" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words non pritible" ) ;

  // -------------------------------------------------------
  // testing getting words
  // -------------------------------------------------------
  char *word ;

  startTestStep( "alloc word empty string" ) ;
  
  word = allocWord( "", 1 ) ;
  if( word != NULL )
  {
    errTestStep( "alloc word empty string" ) ;
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "alloc word empty string" ) ;

  startTestStep( "alloc word blank string" ) ;
  
  word = allocWord( "    ", 1 ) ;
  if( word != NULL )
  {
    errTestStep( "alloc word blank string" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "alloc word blank string" ) ;
 
  startTestStep( "alloc word test one word" );
  
  word = allocWord( "hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word test one word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one word" );

  startTestStep( "alloc word test one word" );
 
  word = allocWord( " hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word test one word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one word" );

  startTestStep( "alloc word test one letter" );
  
  word = allocWord( "a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word test one letter" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one letter" );

  startTestStep( "alloc word blank - one letter" );

  word = allocWord( " a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word blank - one letter" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word blank - one letter" );

  startTestStep( "alloc word one letter - blank" );

  word = allocWord( "a ", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word one letter - blank" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word one letter - blank" );

  startTestStep( "alloc word first out of two word" );
  
  word = allocWord( "hello world", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word first out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word first out of two word" );

  startTestStep( "alloc word secound out of two word" );
  
  word = allocWord( " hello world", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    errTestStep( "alloc word secound out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word secound out of two word" );

  startTestStep( "alloc word secound out of two word" );
  
  word = allocWord( " hello   world  ", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    errTestStep( "alloc word secound out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word secound out of two word" );

  // -------------------------------------------------------
  // testing readCfgFile with valid data
  // -------------------------------------------------------

#if(0)
  startTestStep( "read config file" );

  sysRc = readCfgFile( cfgFile, &cfg ) ;
  if( sysRc != 0 )
  {
    errTestStep( "read config file" );
    printf("# cfg file %s\n", cfgFile ) ; 
    goto _door ;
  }


  int i = 0 ;
  while(1)
  {
    if( cfg.cmdLine[i] == NULL ) break ;
    printf("arg[%d]:\t%s\n", i, cfg.cmdLine[i] ) ;
    i++ ;
  }
  printf("rc:\t%d\n", cfg.rc ) ;
  printf("stdout:\t%s\n", cfg.cmpFile ) ;

  okTestStep( "read config file" );
#endif

  // -------------------------------------------------------
  // forking process
  // -------------------------------------------------------
#if(0)
  startTestStep( "start child " );

  sysRc = startChild( cfg.binary, cfg.cmdLine ) ;
  if( sysRc != 0 )
  {
    errTestStep( "start child " );
    goto _door ;
  }

  okTestStep( "start child " );
#endif
_door :
  return sysRc ;
}
