
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
  if( sysRc != cfg.rc )
  {
    perror("startChild") ;
    goto _door ;
  }
  else
  {
    sysRc = 0 ;
  }


_door :

  return sysRc ;
}
