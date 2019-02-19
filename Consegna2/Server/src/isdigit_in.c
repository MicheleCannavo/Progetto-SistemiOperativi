 /** **************************************************************************
 * \file        isdigit_in.c
 * \version     1.0
 * \date        20/12/2018
 * 
 * \brief      verifica input di monocaratteri numerici.
 * 
 * \param[out] *caracter   puntatore a int per memorizzare il carattere.
 *  
 * \retval    -1   Funzione fallita.
 * \retval     0   Input monocarattere numerico.
 * \retval     1   Input non conforme.*
 * 
 * \details    Questa funzione legge un input da stdin e veruififca se sia
 *              se  un carattere numerico. A differenza di funzioni simili,
 *              non accetta spazi, o qualsiasi altro carattere in ingresso. 
 *              L'unico input accettato e' un unico carattere numerico,
 *              il resto lo identifica come errore in input.
 * 
 *****************************************************************************/
#include "Server.h"

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
   if(*caracter!='\n')
        SBUFFER;

    *caracter=-1; 
    return 1;
}


/** ****************************************************************************
 * \file        isdigit_in.c
 * \version     1.0
 * \date        20/12/2018
 * 
 * \brief      verifica input di numeri senza segno.
 * 
 * \param[out] *caractert      puntatore a int per memorizzare il carattere.
 *  
 * \retval    -1   Funzione fallita.
 * \retval     0   Input carattere singolo.
 * \retval     1   Input non conforme. 
 * 
 * \details     La funzione analizza un input da tastiera e verifica se sia tra
 *              le opzioni scente. Se lo è ritorna 0, altrimenti ritorna 1. Se
 *              la funzione non può essere svolta ritorna -1. Il funzionamento
 *              e' semplice: prende un input un carattere alla volta e lo
 *              verifica. L'unico input accettato e' un input di un solo
 *              carattere alfabetico il resto degli input darà errore. un input
 *              maggiore di 1 carattere dara' errore, cosi come un input minore
 *              di un carattere.
 * 
 *****************************************************************************/
int  isalpha_in( int* caracter )
{
    if( caracter == NULL )
		return -1;

    *caracter = getchar();
	if(*caracter==10)// Invio
		return -1;

    if( isalpha( *caracter  ) && (getchar() == '\n') )
        return 0;

  //  SBUFFER;
   *caracter = -1;
    return 1;
}
/** ****************************************************************************
 * \file        isdigit_in.c
 * \version     1.0
 * \date        20/12/2018
 * 
 *  \brief      verifica input di numeri senza segno.
 * 
 *  \param[out] *result puntatore a unsigned int per memorizzare il numero.
 *  
 *  \retval    -1   Funzione fallita.
 *  \retval     0   Input unsigned int.
 *  \retval     1   Input non conforme. 
 * 
 *  \details    Questa funzione legge un input da stdin e verififca che sia
 *              se un numero intero nsigned. A differenza di funzioni simili,
 *              non accetta spazi, o qualsiasi altro caratterecol numero.
 *              L'unico input accettato e' un unico carattere numerico,
 *              il resto lo identifica come errore in input.
 *              Ha pure un semplice controllo dell'overflow con il limite
 *              dato dal sistema.
 * 
 *****************************************************************************/
int inputUInt( unsigned int *result )
{
// Verifico l'allocazione del puntatore
    if( result == NULL )
    {
        errno=EINVAL;
        perror(__FUNCTION__); 
        return -1 ;
    }

    int   c = getchar();
    *result = 0;
// Testo il 1° carattere
    if( c != '\n' )
    {
        do{ 
            if( isdigit( c ) ) 
            {
// VERIFICA OVERFLOW 
                if((DECIMO_UINT < *result) ||
                    ((DECIMO_UINT == *result) && (UNITA_UINT < (c - '0')))) 
                    {
                        SBUFFER;
                        *result = 0;
                        return  -1 ;
                    }

// Costruzione dell unsigned int
                else 
                    *result = ( *result * 10 ) + (unsigned)( c - '0' );
            } 
            else
            { 
                SBUFFER;
                *result = 0;
                return -1;
            }
        }while( ( c = getchar() ) != '\n' );
        return 0;

    } 
    else
    { 
        *result = 0;
        return 1;
    }
}

/**  ***************************************************************************
 * \file        isdigit_in.c
 * \version     1.0
 * \date        20/12/2018
 * 
 * \brief      verifica input di numeri.
 * 
 * \param[out] *result puntatore a int per memorizzare il numero.
 *  
 * \retval    -1   Funzione fallita.
 * \retval     0   Input int.
 * \retval     1   Input non conforme. 
 * 
 * \details    Questa funzione legge un input da stdin e verififca che sia
 *              se un numero intero. A differenza di funzioni simili,
 *              non accetta spazi, o qualsiasi altro caratterecol numero.
 *              L'unico input accettato e' un numerico senza neppure spazii,
 *              il resto lo identifica come errore in input.
 *              Ha pure un semplice controllo dell'overflow con il limite
 *              inferiore e superiore dato dal sistema.
 * 
 *****************************************************************************/
int inputInt( int *result )
{
// Verifico allocazione del puntatore
    if( result == NULL )
    {
        errno=EINVAL;
        perror(__FUNCTION__); 
        return -1 ;
    }

    unsigned int unit;  // Rappresentare le unita' dei valori limiti
             int segno; // Variabile per il segno del numero
             int c ;    // Variabile temporanea per il carattere 
    
    *result = 0;     
    c = getchar();    // Prelevo il primo carattere

// Verifico se in input c'è un segno '+' o '-'
    segno = ( c == '-' ) ? -1 : 1;
    unit = ( segno == 1 ) ? UNITAP : UNITAN;
    c = ( ( c == '-' ) || ( c == '+' ) ) ? getchar() : c;

// Controllo la pressione del tasto INVIO senza altro input 
    if( c != '\n' )
    {
        unsigned int tmp = 0; // Variabile temporanea unsigned
        do {            
            if( isdigit( c ) ) 
            {
// VERIFICA OVERFLOW 
                if( ( DECIMO_INT < tmp ) ||
                    ( ( DECIMO_INT == tmp ) && ( unit < (unsigned)( c - '0' ) ) ) )
                {
                    SBUFFER;
                    *result = 0;
                    return 1;
// Costruisco l'intero
                }
                else                 
                    tmp = ( tmp * 10 ) + ( c - '0' );
            } 
            else
            { // !isdigit( c )
                SBUFFER;
                *result = 0;
                return 1;
            }
        }while( ( c = getchar() ) != '\n' );
// Uscita con Successo
        *result = (int)tmp * segno;
        return 0;
    } 
// Se si preme invio senza altro input esce con errore
    else 
    { 
        *result = 0;
        return 1;
    }
}