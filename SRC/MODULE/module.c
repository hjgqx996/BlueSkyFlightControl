/**********************************************************************************************************
                                天穹飞控 —— 致力于打造中国最好的多旋翼开源飞控
                                Github: github.com/loveuav/BlueSkyFlightControl
                                技术讨论：bbs.loveuav.com/forum-68-1.html
 * @文件     module.c
 * @说明     提供通用的传感器数据接口,除了对数据实时性要求较高的IMU之外（即读即用），其它传感器的数据更新与使用并不完全同步
 * @版本  	 V1.0
 * @作者     BlueSky
 * @网站     bbs.loveuav.com
 * @日期     2018.05 
**********************************************************************************************************/
#include "module.h"
#include "mpu6000.h"
#include "ms5611.h"
#include "qmc5883.h"
#include "ublox.h"
#include "drv_pwm.h"
#include "faultDetect.h"

/**********************************************************************************************************
*函 数 名: GyroSensorInit
*功能说明: 陀螺仪传感器初始化
*形    参: 无
*返 回 值: 陀螺仪存在状态 
**********************************************************************************************************/
void GyroSensorInit(void)
{
    #if (GYRO_TYPE == MPU6000)
    if(MPU6000_Detect())
    {
        MPU6000_Init();
    }
    else
    {
        //未检测到陀螺仪
        FaultDetectSetError(GYRO_UNDETECTED);
    }        
    #endif
    
    
}

/**********************************************************************************************************
*函 数 名: MagSensorInit
*功能说明: 磁力传感器初始化
*形    参: 无
*返 回 值: 磁力计存在状态 
**********************************************************************************************************/
void MagSensorInit(void)
{
    #if (MAG_TYPE == QMC5883)
    if(QMC5883_Detect())
    {
        QMC5883_Init();
    }
    else
    {
        //未检测到磁力计
        FaultDetectSetError(MAG_UNDETECTED);
    }        
    #endif   
}

/**********************************************************************************************************
*函 数 名: BaroSensorInit
*功能说明: 气压传感器初始化
*形    参: 无
*返 回 值: 气压计存在状态
**********************************************************************************************************/
void BaroSensorInit(void)
{
    #if (BARO_TYPE == MS5611)
    if(MS5611_Detect())
    {
        MS5611_Init();
    }
    else
    {
        //未检测到磁力计
        FaultDetectSetError(BARO_UNDETECTED);
    }        
    #endif
}

/**********************************************************************************************************
*函 数 名: GPSModuleInit
*功能说明: GPS模块初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void GPSModuleInit(void)
{
    Ublox_Init();
}


/**********************************************************************************************************
*函 数 名: GyroSensorRead
*功能说明: 角速度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void GyroSensorRead(Vector3f_t* gyro)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadGyro(gyro);
    #endif    
}

/**********************************************************************************************************
*函 数 名: AccSensorRead
*功能说明: 加速度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void AccSensorRead(Vector3f_t* acc)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadAcc(acc);
    #endif    
}

/**********************************************************************************************************
*函 数 名: TempSensorRead
*功能说明: 陀螺仪温度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void TempSensorRead(float* temp)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadTemp(temp);
    #endif    
}

/**********************************************************************************************************
*函 数 名: MagSensorUpdate
*功能说明: 罗盘数据更新
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void MagSensorUpdate(void)
{
    #if (MAG_TYPE == QMC5883)
    QMC5883_Update();  
    #endif      
}

/**********************************************************************************************************
*函 数 名: MagSensorRead
*功能说明: 罗盘数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void MagSensorRead(Vector3f_t* mag)
{
    #if (MAG_TYPE == QMC5883)
    QMC5883_Read(mag);
    #endif  
}

/**********************************************************************************************************
*函 数 名: BaroSensorUpdate
*功能说明: 气压高度数据更新
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void BaroSensorUpdate(void)
{
    #if (BARO_TYPE == MS5611)
    MS5611_Update();  
    #endif    
}

/**********************************************************************************************************
*函 数 名: BaroSensorRead
*功能说明: 气压高度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void BaroSensorRead(int32_t* baroAlt)
{
    #if (BARO_TYPE == MS5611)
    MS5611_Read(baroAlt);  
    #endif     
}

/**********************************************************************************************************
*函 数 名: TempControlSet
*功能说明: 陀螺仪传感器加热数值设置（0-1000）
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void TempControlSet(int16_t value)
{
    TempControlPWMSet(value);
}


