/*
 * 减速带发送端程序
 * 
 * 减速带功能：
 * 1、检测载荷大小
 * 2、检测车流量大小
 * 3、检测环境光照强弱
 * 
 * 使用模块：
 * arduino单片机
 * 蓝牙模块
 * 红外模块
 * 称重模块
 * 光照强度模块
 * 
 * 更新时间：2021年1月21日
 * 作    者：彭大伟
 * 
 */

/*
 * 接线
HX711 sck--2
HX711 dt --3
红外      --4
光照      --5
蓝牙      --6&7
灯光      --8
*/

/**
 * #define HX711_SCK 2
 * #define HX711_DT 3    //默认HX711连接IO
 */

#include "HX711.h"       //添加库文件 HX711
#include <SoftwareSerial.h>  //添加软串库文件 
SoftwareSerial mySerial(6,7);   //RX=6,TX=7

#define irro 4   //红外
#define guangzhao 5 //光照强度
#define light 8   //灯光
#define buzzer 9  //蜂鸣器

int Weight = 0;        //定义载荷重量
unsigned int num = 0;    //车流量计数
bool mark = 0;


void setup() {

    Init_Hx711();        //初始化HX711模块连接的IO设置
    
    Serial.begin(9600);  //设置波特率9600
    mySerial.begin(9600);

    pinMode(irro,INPUT);    //引脚定义
    pinMode(guangzhao,INPUT);
    pinMode(light,OUTPUT);
    pinMode(buzzer,OUTPUT);
    digitalWrite(buzzer,LOW);
    
    delay(3000);         //延时1秒
    Get_Maopi();         //清零
}

void loop() {

    Getnum();
    Getlight();
    Getweight();
    sender();

    Serial.print("num    :");
    Serial.println(num);
    Serial.print("light  :");
    Serial.println(digitalRead(guangzhao));
    Serial.print("weight :");
    Serial.println(Weight);
    delay(300);
    
}
void sender()
{
    mySerial.print("A");
    mySerial.println(num);
    mySerial.print("B");
    mySerial.println(digitalRead(guangzhao));
    mySerial.print("C");
    mySerial.println(Weight);
  }
/*
 * 获取载荷大小
 */
void Getweight()
{
    Weight = abs(Get_Weight());
    if(Weight > 4500){
        digitalWrite(buzzer,HIGH);
      }
    else if(Weight < 4500){
        digitalWrite(buzzer,LOW);
      }
  }
/*
 * 获取环境光强
 */
void Getlight()
{
    if(digitalRead(guangzhao) == 1)
    {
        digitalWrite(light,HIGH);
      }
    else if(digitalRead(guangzhao) == 0)
    {
        digitalWrite(light,LOW);
      }
  }
/**
 * 车流量检测
 */
void Getnum(void)
{
    if(digitalRead(irro) == 0)
    {
        mark = 0;
      }
     if(digitalRead(irro) == 1)
    {
        if(mark == 0)
        {
            num++;
            mark = 1;
          }
      }
  }
