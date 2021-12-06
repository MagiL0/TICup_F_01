# 2021 电赛F题 1车

### 介绍
- 电赛 F 题 1 车国赛满分程序

- 因为组委会失误成绩被取消

- **留作纪念**

### 架构

#### 硬件

- STM32RCT6为主控
- 树莓派进行数字识别处理，自带的CSI接口的picamera进行图像获取（本程序必须使用picamera）
- 7路灰度进行循迹
- OpenMV协助判断赛道标志位
- 12V航模电池+电机驱动+电机进行差速转向、移动，HC05与2车通信
- STM32使用降压模块输出的电压进行供电
- 树莓派使用充电宝供电
- **树莓派和单片机必须共地！！！**

#### 软件

- 树莓派上使用OpenCV模板匹配进行数字识别与与STM32单片机进行串口通讯
- 树莓派 getTem.py 可按 q 获取数字模板
- OpenMV对赛道的协同判断
- STM32 主控程序	

#### 使用说明

1.  树莓派使用软件串口ttyAma1，分别为GPIO1和GPIO0，需要提前进行配置
