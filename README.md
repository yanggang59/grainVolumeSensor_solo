# grainVolumeSensor4.2

/**
*这一版的程序修改了一个概念，流量指的是体积，也就是产量，而不是传统意义上的流量,因此不需要计算总的累计时间
*/

另外需要将谷物的容重（也就是密度等）参数放进去才能计算出最终的产量（重量），下一版本的设计最好写一个配置文件，每一次将参数写进配置文件
这样，每一次可以只修改配置文件，程序的整体框架不需要变动，免去了重新编译的麻烦

另外需要注意的是，最终得到的谷物的流量单位是kg


#solo版本
针对单相机处理流量问题的解决

