
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mfunc.h"
#include "tutl.h" 

int main(int argc, char* argv[] )
{
  tTstCfg cfg ;

  char *stdOutFile = NULL ;
  char *stdErrFile = NULL ;

  int sysRc = NO_ERROR ;

  if( argc < 2 ) { usage(); return 1 ; }
  const char *cfgFile = argv[1] ;

  if( argc < 3 )
  {
    stdOutFile = argv[2] ;
  }

  if( argc == 3 ) { usage(); return 3 ; }
  stdErrFile = argv[3] ;

  if( argc > 3 ) { usage(); return 4 ; }

  // -------------------------------------------------------
  // testing countWords
  // -------------------------------------------------------
  printf("\n");
  printf("test empty string:\t\t");
  if( countWords("",0) != 0 ) 
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ; 
  }
  printf("ok\n");

  printf("test buffer overflow to low:\t");
  if( countWords("",-1) != -1 ) 
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ; 
  }
  printf("ok\n");

  printf("test one word :\t\t\t");
  if( countWords("hello",sizeof("hello")) != 1 ) 
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ; 
  }
  printf("ok\n");

  printf("test one word :\t\t\t");
  if( countWords(" hello ",sizeof(" hello   ")) != 1 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test buffer overflow:\t\t");
  if( countWords(" hello ",(sizeof(" hello ")-1)) != -1 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test two words:\t\t\t");
  if( countWords("hello world",255) != 2 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test mulitple blanks:\t\t");
  if( countWords("hello   world",255) != 2 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test non printilble :\t\t");
  if( countWords("hello   world",255) != -2 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  // -------------------------------------------------------
  // testing getting words 
  // -------------------------------------------------------
  char *word ;
  printf("\n\n"); 

  printf("test empty string:\t\t");
  word = allocWord( "", 1 ) ;
  if( word != NULL )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test blank string:\t\t");
  word = allocWord( "    ", 1 ) ;
  if( word != NULL )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");

  printf("test one word:\t\t\t");
  word = allocWord( "hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test one word:\t\t\t");
  word = allocWord( " hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test one letter:\t\t");
  word = allocWord( "a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test blank - one letter:\t");
  word = allocWord( " a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test one letter - blank :\t");
  word = allocWord( "a ", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test first of two words:\t");
  word = allocWord( "hello world", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test second of two words:\t");
  word = allocWord( " hello world", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  printf("test second of two words:\t");
  word = allocWord( " hello   world  ", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }
  printf("ok\n");
  free(word) ;

  // -------------------------------------------------------
  // testing readCfgFile with valid data
  // -------------------------------------------------------
  sysRc = readCfgFile( cfgFile, &cfg ) ;
  if( sysRc != 0 )
  {
    perror("readCfgFile") ;
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

  // -------------------------------------------------------
  // forking process
  // -------------------------------------------------------
  sysRc = startChild( cfg.binary, cfg.cmdLine ) ;
  if( sysRc != 0 )
  {
    perror("readCfgFile") ;
    goto _door ;
  }

_door :

  return sysRc ;
}
