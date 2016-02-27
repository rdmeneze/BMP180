/**
 * @file    bmp180.h
 * @brief   declarations of a BMP180 Digital pressure sensor library.
 * @author  Rafael Dias <rdmeneze@gmail.com>
 * @date    fev/MMXVI
 */

#ifndef _BMP180_H_
#define _BMP180_H_

#include <stdint.h>

typedef enum
{
    BMP180_OK  ,
    BMP180_ERROR,
} BMP180_STATUS;

typedef struct SFE_BMP180 SFE_BMP180;

/**
 * @brief       initialize the BMP180
 * @return      BMP180_OK  initialization OK
 * @return      BMP180_ERROR initialization ERROR
 */
BMP180_STATUS Bmp180Init( SFE_BMP180* pBmp180 );

SFE_BMP180* Bmp180Create( void );



#endif 
