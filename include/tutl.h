/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
void *gRcVoidPointer ;  // used in doPointTest

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#include <unistd.h>
#include <stdio.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define NO_ERROR      0  
#define TEST_ERROR    1  

#define TEST_FORMAT   "# TEST %-5s %-10s >>%-20s<< %s(%04d)\n"
#define CHECK_FORMAT  "# CHECK %-4s %-10s >>%-20s<< %s(%04d)\n"

#define TEST_START_TXT  "START"
#define TEST_OK_TXT     "OK"
#define TEST_ERR_TXT    "ERR"

#define RC_IS_NULL      !=
#define RC_NOT_NULL     ==

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

// -----------------------------------------------------------------------------
// new macros
// -----------------------------------------------------------------------------

#define checkMessage( step, function ) \
  printf( CHECK_FORMAT               , \
  step                               , \
  #function                          , \
  " "                                , \
  __FILE__                           , \
  __LINE__ )

// ---------------------------------------------------------
// macro for printing out the line, 
//     it can only be called from macro doTest
// ---------------------------------------------------------
#define textMessage( step, function ) \
  printf( TEST_FORMAT               , \
  step                              , \
  #function                         , \
  _gTestDescription_                , \
  __FILE__                          , \
  __LINE__ )

// ---------------------------------------------------------
// testing macros 
//   callg the function 
//   check the output
// ---------------------------------------------------------

// ---------------------------------------------------------
// function returns int
// ---------------------------------------------------------
#define doIntTest( description,         \
                   rc         ,         \
                   function   , ...  )  \
{                                                   \
  char _gTestDescription_[64] ;                     \
                                                    \
  strcpy(      _gTestDescription_, description ) ;  \
  textMessage( TEST_START_TXT    , function    ) ;  \
  errno = 0 ;      \
  sysRc = NO_ERROR ;                                \
                                                    \
  int _rc = function ( __VA_ARGS__  ) ;             \
  if( _rc != rc )                                   \
  {                                                 \
    textMessage( TEST_ERR_TXT, function ) ;         \
    printf( "              rcReal:  %03d rcGoal: %03d\n",_rc,rc ) ; \
    sysRc = _rc ;                                   \
    goto _door ;                                    \
  }                                                 \
  textMessage( TEST_OK_TXT, function ) ;            \
}

// ---------------------------------------------------------
// function returns pointer
// ---------------------------------------------------------
#define doPointTest( description,                         \
                     operator   ,                         \
                     function   , ...  )                  \
{                                                         \
  char _gTestDescription_[64] ;                           \
  gRcVoidPointer = NULL ;                                 \
                                                          \
  strcpy(      _gTestDescription_, description ) ;        \
  textMessage( TEST_START_TXT    , function    ) ;        \
  sysRc = NO_ERROR ;                                      \
                                                          \
  gRcVoidPointer = (void*) function ( __VA_ARGS__   ) ;   \
  if( ((void*) gRcVoidPointer) operator ((void*) NULL) )  \
  {                                                       \
    textMessage( TEST_ERR_TXT, function ) ;               \
    sysRc = TEST_ERROR ;                                  \
    goto _door ;                                          \
  }                                                       \
  textMessage( TEST_OK_TXT, function ) ;                  \
}

// -----------------------------------------------------------------------------
// old macros
//   old macros are needed for compatibility
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
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
//int checkFileRights( const char* fName, int mode ) ;
//int countWords( const char* str, int maxOffset ) ;
//char* allocWord( const char* str, const int wordIndex ) ;
//int readCfgFile( const char* cfgFile, tTstCfg *cfg ) ;
//int startChild( const char *tag, char *stdOut, char* stdErr, char** cmdLine ) ;
//int diff( const char* file1, const char* file2 ) ;
