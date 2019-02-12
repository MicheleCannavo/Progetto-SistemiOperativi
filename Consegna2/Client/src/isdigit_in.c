#include "Client.h"

 /** **************************************************************************
 *  \file       isdigit_in.c
 *  \version    1.0
 * 
 *  \brief      verifica input di monocaratteri numerici.
 * 
 *  \details    Questa funzione legge un input da stdin e veruififca se sia
 *              se  un carattere numerico. A differenza di funzioni simili,
 *              non accetta spazi, o qualsiasi altro carattere in ingresso. 
 *              L'unico input accettato e' un unico carattere numerico,
 *              il resto lo identifica come errore in input.
 * 
 *  \param[out] *caracter   puntatore a int per memorizzare il carattere.
 *  
 *  \retval    -1   Funzione fallita.
 *  \retval     0   Input monocarattere numerico.
 *  \retval     1   Input non conforme.
 *****************************************************************************/

int  isdigit_in( int* caracter )
{
// Verifica allocazione del puntatore
    if( caracter == NULL )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    *caracter = getchar();
// Verifica che l'nput sia di un solo carattere numerico
    if( isdigit( *caracter ) && getchar() == '\n' )
    {
        *caracter -= '0';
        return 0;
    }

// Controlla che non sia stat premuto "INVIO" senza altri input
   if(*caracter!=10)
        SBUFFER;

    *caracter=-1; 
    return 1;
}

int inputUInt( unsigned int *result )
{
    if( result == NULL )
    {
        errno=EINVAL;
        perror("Errore in InputUInt()"); 
        return -1 ;
    }

    int   c = getchar();
    *result = 0;

    if( c != '\n' ){// testo il 1° carattere
        do{// 
            if( isdigit( c ) ) {
/****************************** VERIFICA OVERFLOW *****************************/
                if((DECIMO_UINT < *result) ||
                    ((DECIMO_UINT == *result) && (UNITA_UINT < (c - '0')))) {
                    SBUFFER;
                    *result = 0;
                    return  -1 ;
/****************************** VERIFICA OVERFLOW *****************************/

                }else //- !(DECIMO_INT < *result) || . . .
                    *result = ( *result * 10 ) + (unsigned)( c - '0' );

            } else{ //- !isdigit( c )
                SBUFFER;
                    *result = 0;
                return -1;
            }
        } while( ( c = getchar() ) != '\n' );
        return 0;

    } else{ //- Se si preme invio senza altro input esce con errore
                    *result = 0;
        return -1;
    }
}

int inputInt( int *result )
{
    if( result == NULL )
    {
        errno=EINVAL;
        perror("Errore in InputInt()"); 
        return -1 ;
    }


    unsigned int unit;    // Rappresentare le unita' dei valori limiti
    int segno;            // Variabile per il segno del numero
    int c = getchar();    // Variabile temporanea per il carattere 
    *result = 0;
    segno = ( c == '-' ) ? -1 : 1;
    unit = ( segno == 1 ) ? UNITAP : UNITAN;
    c = ( ( c == '-' ) || ( c == '+' ) ) ? getchar() : c;

    if( c != '\n' )// Controllo la pressione del tasto INVIO senza altro input 
    {
         unsigned int tmp = 0; // Variabile temporanea unsigned
        do {            
            if( isdigit( c ) ) 
            {
/****************************** VERIFICA OVERFLOW *****************************/
                if( ( DECIMO_INT < tmp ) ||
                    ( ( DECIMO_INT == tmp ) && ( unit < (unsigned)( c - '0' ) ) ) ) {
                    SBUFFER;
                    *result = 0;
                    return -1;
/******************************************************************************/
                } else // !(DECIMO_INT < *result) || . . .
                    tmp = ( tmp * 10 ) + ( c - '0' );

            } else { // !isdigit( c )
                SBUFFER;
                *result = 0;
                return -1;
            }
        } while( ( c = getchar() ) != '\n' );
        *result = (int)tmp * segno;
        return 0;
    } else { // Se si preme invio senza altro input esce con errore
        *result = 0;
        return -1;
    }
}