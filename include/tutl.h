/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#include <unistd.h>
#include <stdio.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define NO_ERROR      0  

#define TEST_FORMAT  "# TEST %-5s %-10s >>%-20s<< %s(%04d)\n"

#define TEST_START_TXT  "START"
#define TEST_OK_TXT     "OK"
#define TEST_ERR_TXT    "ERR"

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

// -----------------------------------------------------------------------------
// old macros
// -----------------------------------------------------------------------------
#define startTestStep( comment ) printf("# testing\t%16s\tin %s line %d\n", \
                                           comment,  \
                                           __FILE__, \
                                           __LINE__  )

#define okTestStep( comment ) printf("# tested ok\t%16s\tin %s line %d\n", \
                                          comment,  \
                                          __FILE__, \
                                          __LINE__  )

#define errTestStep( comment ) printf("# test aborted\t%16s\tin %s line %d\n", \
                                          comment,  \
                                          __FILE__, \
                                          __LINE__  )

// -----------------------------------------------------------------------------
// new macros
// -----------------------------------------------------------------------------

#define FUNCTION_NAME_MACRO( n ) #n  

#define describeTestText( comment ) strcpy( _gTestDescription_, comment ) 

#define textMessage( step, function ) \
  printf( TEST_FORMAT               , \
  step                              , \
  FUNCTION_NAME_MACRO( funciton )  , \
  _gTestDescription_                , \
  __FILE__                          , \
  __LINE__ )

#define setupTest( comment, function ) describeTestText( comment ) ;         \
                                       textMessage( TEST_START_TXT, function )

#define testOK( )     textMessage( TEST_OK_TXT, function )

#define testErr( )   textMessage( TEST_OK_TXT, function )

#define doTest( description,      \
                rc,               \
                function, ...  )  \
{                                       \
  char _gTestDescription_[64] ;         \
  setupTest( description, function )  ; \
  int _rc = function ( __VA_ARGS__  ) ; \
  if( _rc != rc )                       \
  {                                     \
    testErr( ) ;                        \
    goto _door ;                        \
  }                                     \
  testOK( ) ;                           \
}

/******************************************************************************/
/*   S T R U C T S                                                            */
/******************************************************************************/
typedef struct sTstCfg tTstCfg ;

struct sTstCfg
{
  char *binary          ;      // binary to be started
  char **cmdLine        ;      // commad line attributes of the tested prg
  int  rc        ;             // exit code of the tested program
  char cmpFile[FILENAME_MAX] ; // compaire file for stdout of the tested prg
} ;

/******************************************************************************/
/*   G L O B A L S                   */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
//int checkFileRights( const char* fName, int mode ) ;
//int countWords( const char* str, int maxOffset ) ;
//char* allocWord( const char* str, const int wordIndex ) ;
//int readCfgFile( const char* cfgFile, tTstCfg *cfg ) ;
//int startChild( const char *tag, char *stdOut, char* stdErr, char** cmdLine ) ;
//int diff( const char* file1, const char* file2 ) ;
