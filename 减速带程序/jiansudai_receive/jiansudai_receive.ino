/*
 * 减速带接收程序
 * 
 * 减速带功能：
 * 1、检测载荷大小
 * 2、检测车流量大小
 * 3、检测环境光照强弱
 * 
 * 使用模块
 * arduino单片机
 * oled显示屏
 * 蓝牙模块
 * 
 */
#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>

//LCD_SH1106 lcd; /* for SH1106 OLED module */
LCD_SSD1306 lcd; /* for SSD1306 OLED module */

#include <SoftwareSerial.h>  //添加软串库文件 
SoftwareSerial mySerial(6,7);   //RX=6,TX=7

int num;
int light;
int Weight;

unsigned long premillis;
void setup() {
    lcd.begin();
    lcd.clear();
    Serial.begin(9600);
    mySerial.begin(9600);

}

void loop() {
    if(mySerial.available() > 0)
    {
        char getval = mySerial.read();
        switch(getval)
        {
            case 'A':num = mySerial.parseInt();
                break;
            case 'B':light = mySerial.parseInt();
                break;
            case 'C':Weight = mySerial.parseInt();
                break;
          }
      Serial.print("num    :");
      Serial.println(num);
      Serial.print("light  :");
      Serial.println(light);
      Serial.print("weight :");
      Serial.println(Weight);
      }
      
        if(millis() - premillis > 1000)
        {
            lcd.clear();
            premillis = millis();

            lcd.setCursor(0,2);
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      lcd.print("WEI :");
      lcd.printLong(Weight);
      lcd.setCursor(90,2);
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      lcd.println("g");
      lcd.setCursor(0,4);
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      lcd.print("NUM :");
      lcd.printLong(num);
      lcd.setCursor(0,6);
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      lcd.print("LIG :");

      if(light == 0){
        lcd.print("OFF");
        }
       else{
        lcd.print(" ON");
        }
          }
}
