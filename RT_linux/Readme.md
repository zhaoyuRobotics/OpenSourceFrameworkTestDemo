# 实现实时Linux系统：RT_Linux

### １．为什么要用这个系统
　　实时系统一般提供抢占式调度机制，重要的高优先级任务可以剥夺低优先级任务对cpu的使用权，而不仅仅就是时间轮回，死等cpu空闲。当然这样就增加了 cpu 处理中断的时间开销。RT_Linux再次中间做了折中！
  

### ２．实现的步骤

(1)  下载 LInux 内核（注意：ｒｔ补丁包并不是所有的内核版本都有，我的是16.04对应的内核版本是4.10.0.  那么我找了相近的内核版本下载：4.9）

[Linux内核下载 (Kernel) 清华大学镜像源](https://mirror.tuna.tsinghua.edu.cn/kernel/v4.x/)

(2) 下载补丁包

[Patch(补丁包)下载](https://mirrors.edge.kernel.org/pub/linux/kernel/projects/rt/)


(3) 解压内核并且打补丁(将下载的两个文件放入同一目录下)
```xml
tar xzvf linux-4.9.201.tar.gz
cd  linux-4.9.201
patch -p1 < ../patch-4.9.201-rt134.patch
```

(4) 编译安装

　首先进行配置选择（这一步里面选择了抢占模式）, 依次选择：
 
    Processor type and features --->
	Preemption Model (Fully Preemptible Kernel (RT) )   --->
	Fully Preemptible Kernel (RT)

   最后保存

   安装编译所需要的依赖：
	
	sudo apt-get install libncurses-dev
    sudo apt-get install libssl-dev
	
编译内核（大概一小时）
```xml
make -j8  (开８个线程编译)

sudo make INSTALL_MOD_STRIP=1 modules_install  　
# 编译时加上 INSTALL_MOD_STRIP=1 可以生成没有调试信息的模块，大大减小内核的大小。

sudo make install -j2

 sudo update-grub2
```


重启，选择 option ubuntu 启动项里面多了关于 rt　字样的启动项，启动起来后查看版本：

```xml
　uname -a
```
会发现，是**4.9.201-rt134  PREEMPT RT
**

　　
  
### ３．测试
安装** rt-test**测试工具，该测试工具检查的原理就是比较　实际　和　理论　的线程循环时间差值
```xml
sudo cyclictest -p 80 -t5 -m -n -i 1000 -l 10000 --priospread
```
参数解释：
Ｔ：开启的线程序号  
Ｐ：优先级  
Ｃ：时间间隔没达到多少次，计数器加１  
Ｉ：时间间隔，默认是１０００微妙  
MIN:最小延迟  
ACT:  最近一次延迟  
AVG:平均延时  
MAX:最大延时  
  
五个线程比较测试（左侧为RT_Linux  右侧围标准内核）
![5_thread_test](https://github.com/zhaoyuRobotics/OpenSourceFrameworkTestDemo/blob/master/RT_linux/比较_5.png)  
  
  
  
十五个线程比较测试（左侧为RT_Linux  右侧围标准内核）
![15_thread_test](https://github.com/zhaoyuRobotics/OpenSourceFrameworkTestDemo/blob/master/RT_linux/比较15.png) 
  
  



### ４．补充

  1.判断一个内核是否打好　ＲＴ(real time)补丁方法：
```xml
$ cat /boot/config_4.9.201-rt134 | grep CONFIG_PREEMPT_RT

CONFIG_PREEMPT_RT_BASE=y
\#CONFIG_PREEMPT_RTB is not set
CONFIG_PREEMPT_RT_FULL = y
```
  
  2.自己试验后的数据结果：
   **(1)大体上测试延时会减小，但是有些仍会比优化前的延时高，这点没有得到论文中印证. ** 
   **(2)在重负载情况下还未验证，这里做个标记**
  
  　　
    
    
	
### 参考：
  https://blog.csdn.net/v6543210/article/details/80941906
