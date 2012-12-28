/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#include <unistd.h>
#include <stdio.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define NO_ERROR   0  

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
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
