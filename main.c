//**********************************************
//
//  !file  :    Main
//  !Author:    FireAnts
//  !Date  :    11/2015
//  !brief :
//
//**********************************************
#include "include.h"
//**********************************************
//
//      @Global Variable
//
//**********************************************
#ifdef      DEBUG
//void    __error__( const uint8_t )
#endif
int16_t AccelX, AccelY, AccelZ, GyroX, GyroY, GyroZ;
float gyroRoll, gyroPitch;
float compRoll, compPitch;
double kalRoll, kalPitch;
Kalman RollKalman, PitchKalman;
bool KalmanStarted = false;

UARTType newUART0 = {       // Add new UART
    UART0_BASE,             // Select UART0_BASE
    115200,                 // baudrate 115200
    8,                      // data bits :  8 bits
    None,                   // parity    : None
    1,                      // Stop bits : one
    &UART0_Handler          // Interrupt Service routine function
};

//**********************************************
//
//!  brief:         Main function
//!
//!  function   :  main
//!  Description:
//!
//!  \return     :
//
//**********************************************

void main(void)
{
    /*  Set Clock                               */
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    /* Configure UART0_BASE, PA0_RX, PA1_TX     */
    ConfigUART(&newUART0);
    /* Led Initilize, use PF1, PF2, PF3         */
    LedInit();
    buttonInit();
    /*  QEI Init  QEI0 and QEI1                 */
    i2c_Config();
    mpu6050_Config();
    qei_init(Ts *1000);
    /*  Configure   timer, use Timer 2          */
    timerInit(Ts * 1000);
    Config_PWM();
    ConfigDRV_Enable();
    ConfigBoostCircuit();
    enableBoostCircuit(1);
    speed_Enable_Hbridge(1);

    initKalman(&PitchKalman);
    initKalman(&RollKalman);
//  mpu6050_Read_AccelXYZ(&AccelX, &AccelY, &AccelZ);
    mpu6050_Read_All(&AccelX, &AccelY, &AccelZ,&GyroX, &GyroY, &GyroZ);

    double roll  = atan2(AccelY, AccelZ) * RAD_TO_DEG;
    double pitch = atan(-AccelX / sqrt(AccelY * AccelY + AccelZ * AccelZ)) * RAD_TO_DEG;

    // Set starting angle
    setAngle(&RollKalman,roll);
    setAngle(&PitchKalman,pitch);
    gyroRoll = roll;
    gyroPitch = pitch;
    compPitch = roll;
    compPitch = pitch;

    KalmanStarted = true;
    while(1)
    {
        Implement_Process();
    }
}

