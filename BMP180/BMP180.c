/**
 * @file    bmp180.h
 * @brief   implementation of a BMP180 Digital pressure sensor library.
 * @author  Rafael Dias <rdmeneze@gmail.com>
 * @date    fev/MMXVI
 */


#include "BMP180.h"
#include "ttimer.h"
#include "util.h"
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <inc/hw_memmap.h>
#include <driverlib/i2c.h>
#include <driverlib/pin_map.h>

//-----------------------------------------------------------------------------

#define N_BMP189 1

//-----------------------------------------------------------------------------

/**
 * @brief definition of SFE_BMP180 struct
 */
struct SFE_BMP180
{
    int16_t AC1;
    int16_t AC2;
    int16_t AC3;
    int16_t VB1;
    int16_t VB2;
    int16_t MB;
    int16_t MC;
    int16_t MD;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6; 
    double c5;
    double c6;
    double mc;
    double md;
    double x0;
    double x1;
    double x2;
    double y0;
    double y1;
    double y2;
    double p0;
    double p1;
    double p2;
    char _error;
    
    uint8_t bInit;
    
    uint32_t dwSYSCTL_PERIPH_I2C;
    uint32_t dwSYSCTL_PERIPH_GPIO;
    uint32_t dwGPIO_I2CSDA;
    uint32_t dwGPIO_I2CSCL;
    uint32_t dwGPIO_I2CSDA_PORT_BASE;
    uint32_t dwGPIO_I2CSCL_PORT_BASE;
    uint32_t dwGPIO_I2CSDA_PIN;
    uint32_t dwGPIO_I2CSCL_PIN;
};

//-----------------------------------------------------------------------------

static uint8_t bBmp180Count = 0;

static SFE_BMP180 xBmp180[] = 
{
    [0] = 
    {
        .dwSYSCTL_PERIPH_I2C    = SYSCTL_PERIPH_I2C1,
        .dwSYSCTL_PERIPH_GPIO   = SYSCTL_PERIPH_GPIOG,
        .dwGPIO_I2CSDA          = GPIO_PG1_I2C1SDA,
        .dwGPIO_I2CSCL          = GPIO_PG0_I2C1SCL,
        .dwGPIO_I2CSDA_PORT_BASE= GPIO_PORTG_BASE,
        .dwGPIO_I2CSCL_PORT_BASE=GPIO_PORTG_BASE,
        .dwGPIO_I2CSDA_PIN      = GPIO_PIN_1,
        .dwGPIO_I2CSCL_PIN      = GPIO_PIN_0,
    }
};


//-----------------------------------------------------------------------------

BMP180_STATUS Bmp180Init( SFE_BMP180* pBmp180 )
{
    BMP180_STATUS xRet = BMP180_ERROR;

    if ( NULL != pBmp180 )
    {
        if ( FALSE == pBmp180->bInit )
        {
            SysCtlPeripheralEnable( pBmp180->dwSYSCTL_PERIPH_I2C );
            SysCtlPeripheralEnable( pBmp180->dwSYSCTL_PERIPH_GPIO );

            //
            // Enable pin PG1 for I2C1 I2C1SDA
            //
            GPIOPinConfigure(pBmp180->dwGPIO_I2CSDA );
            GPIOPinTypeI2C( pBmp180->dwGPIO_I2CSDA_PORT_BASE , pBmp180->dwGPIO_I2CSDA_PIN );

            //
            // Enable pin PG0 for I2C1 I2C1SCL
            //
            GPIOPinConfigure(pBmp180->dwGPIO_I2CSCL );
            GPIOPinTypeI2CSCL( pBmp180->dwGPIO_I2CSCL_PORT_BASE , pBmp180->dwGPIO_I2CSCL_PIN );     
            
            pBmp180->bInit = TRUE;
        }
    }
    
    return xRet;
}

//-----------------------------------------------------------------------------

SFE_BMP180* Bmp180Create( void )
{
    SFE_BMP180* pBmp180 = NULL;
    
    pBmp180 = &xBmp180[bBmp180Count];
        
    bBmp180Count++;
    if ( bBmp180Count ==  N_BMP189 )
    {
        bBmp180Count = 0;
    }
    
    return pBmp180;
}

//-----------------------------------------------------------------------------
