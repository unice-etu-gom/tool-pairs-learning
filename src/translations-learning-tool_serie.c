#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//typedef struct  SStats
//{
//    int countTotal;
//    int countOK;

//}   TSStats;

typedef struct  SContext
{
    FILE*   fileDescriptor;
    int     fileLinesCount;

//    TSStats*    statsList;

}   TSContext;

/* ########################################################################## */
/* ########################################################################## */

int askTranslation( char* argAsked, char* argExpected )
{
    size_t  lBufferSize = 512;
    char*   p_buffer    = NULL;
    int     retVal      = EXIT_SUCCESS;


    p_buffer    = malloc( sizeof(char) * lBufferSize );


    printf( "\nTraduction de '%s' ? ==> ",
            argAsked );

//    fscanf( stdin, "%s", lBuffer );
    while( getline( &p_buffer, &lBufferSize, stdin ) == -1 );

    if(     p_buffer != 0
        &&  p_buffer[ strlen( p_buffer ) - 1 ] == '\n' )
    {
        p_buffer[ strlen( p_buffer ) - 1 ]  = '\0';
    }



    if( strncmp( argExpected, p_buffer, lBufferSize ) )
    {
        printf( "\n    Perdu ! La reponse attendue était : '%s'\n\n",
                argExpected );
        retVal  = EXIT_FAILURE;
    }
    else
    {
        printf( "\n    Gagné ! '%s' <=> '%s'\n\n",
                argAsked, argExpected );
    }

    free( p_buffer );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int context_clear(TSContext* argContextPtr)
{
    int retVal  = EXIT_SUCCESS;

    argContextPtr->fileDescriptor   = NULL;
    argContextPtr->fileLinesCount   = -1;

//    if( argContextPtr->statsList != NULL )
//    {
//        free( argContextPtr->statsList );
//        argContextPtr->statsList    = NULL;
//    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

char*   file_getLine(FILE* argFile, int argLineNbr)
{
    size_t  lBufferSize     = 512;
    int     lLine           = 0;
    char*   p_buffer        = NULL;
    char*   retVal          = NULL;


    p_buffer    = malloc( sizeof(char) * lBufferSize );

    rewind( argFile );
    while( getline( &p_buffer, &lBufferSize, argFile ) != -1 )
    {
        if( lLine == argLineNbr )
        {
            retVal  = p_buffer;
            break;
        }
        lLine++;
    }
    if(     retVal != 0
        &&  retVal[ strlen( retVal ) - 1 ] == '\n' )
    {
        retVal[ strlen( retVal ) - 1 ]  = '\0';
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int file_linesCount(FILE* argFile)
{
    size_t  lBufferSize = 512;
    char*   p_buffer    = NULL;
    int     retVal      = 0;


    p_buffer    = malloc( sizeof(char) * lBufferSize );


    rewind( argFile );
    while( getline( &p_buffer, &lBufferSize, argFile ) != -1 )
    {
        retVal++;
    }

    free( p_buffer );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int initialize( TSContext* argContextPtr,
                int argc, char** argv )
{
    int lIntTmp = 0;
    int retVal  = EXIT_SUCCESS;


    if( argc != 2 )
    {
        fprintf( stderr, "Nombre d'arguments invalide.\n" );
        retVal  = EXIT_FAILURE;
    }

    else if(    (argContextPtr->fileDescriptor = fopen( argv[ 1 ], "r" ))
            ==  NULL )
    {
        fprintf( stderr, "Erreur a l'ouverture du fichier '%s'\n",
                 argv[ 1 ] );
        retVal  = EXIT_FAILURE;
    }
    else
    {
        argContextPtr->fileLinesCount
                = file_linesCount( argContextPtr->fileDescriptor );
        printf( "Nombre de lignes : %d\n",
                argContextPtr->fileLinesCount );

//        argContextPtr->statsList
//                = malloc( sizeof( TSStats ) * argContextPtr->fileLinesCount );
//        for( lIntTmp = 0 ; lIntTmp < argContextPtr->fileLinesCount ; lIntTmp++ )
//        {
//            argContextPtr->statsList[ lIntTmp ].countOK     = 0;
//            argContextPtr->statsList[ lIntTmp ].countTotal  = 0;
//        }
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int process(TSContext* argContextPtr)
{
    int lFlagContinue   = 1;
    int lLineNbr        = 0;
    int retVal          = EXIT_SUCCESS;


    do
    {

        char*   p_strLine   = file_getLine( argContextPtr->fileDescriptor,
                                            lLineNbr );

        printf( "\n--------------------\n" );
//        printf( "Ligne designée : n°%d : %s\n",
//                lLineNbr,
//                p_strLine );

        char*   p_value2    = p_strLine;
        char*   p_value1    = strsep( &p_value2, ";" );

//        printf( "Valeur 1 : %s ; Valeur 2 : %s\n",
//                p_value1, p_value2 );

        int lAnswerOK   = EXIT_FAILURE;
        int lCounter    = 0;
        do
        {
            if( rand() % 2 )
            {
                lAnswerOK   = askTranslation( p_value1, p_value2 );
            }
            else
            {
                lAnswerOK   = askTranslation( p_value2, p_value1 );
            }

            if( lAnswerOK != EXIT_SUCCESS )
            {
                lCounter += 4;
            }
            else
            {
                lCounter--;
            }
        } while( lCounter > 0 );


//        argContextPtr->statsList[ lLineNbr ].countTotal++;
//        if( lAnswerOK == EXIT_SUCCESS )
//        {
//            argContextPtr->statsList[ lLineNbr ].countOK++;
//        }


        free( p_strLine );

        lLineNbr++;
        lLineNbr    %= argContextPtr->fileLinesCount;

    } while( lFlagContinue );


    return  retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int terminate(TSContext* argContextPtr)
{
    int retVal  = EXIT_SUCCESS;


    if( fclose( argContextPtr->fileDescriptor ) != 0 )
    {
        fprintf( stderr,
                 "Erreur a la fermeture du fichier.\n" );
        retVal  = EXIT_FAILURE;
    }

    if( context_clear( argContextPtr ) != EXIT_SUCCESS )
    {
        fprintf( stderr,
                 "Erreur durant le nettoyage du contexte.\n" );
        retVal  = EXIT_FAILURE;
    }


    return  retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int main(int argc, char** argv)
{
    TSContext   lContext;
    int         retVal      = EXIT_SUCCESS;

    context_clear( &lContext );

    if( initialize( &lContext, argc, argv ) != EXIT_SUCCESS )
    {
        fprintf( stderr, "\n\nErreur à l'initialisation.\n\n" );
        retVal  = EXIT_FAILURE;
    }
    else
    {
        if( process( &lContext ) != EXIT_SUCCESS )
        {
            fprintf( stderr, "\n\nErreur durant le process.\n\n" );
            retVal  = EXIT_FAILURE;
        }

        if( terminate( &lContext ) != EXIT_SUCCESS )
        {
            fprintf( stderr, "\n\nErreur durant la terminaison.\n\n" );
            retVal  = EXIT_FAILURE;
        }
    }


    return  retVal;
}

/* ########################################################################## */
/* ########################################################################## */
