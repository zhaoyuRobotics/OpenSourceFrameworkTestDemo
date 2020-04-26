###  结果:  
　　<br>
  **在使用　rt_linux　系统，并且线程绑定cpu 和 grub设置孤立cpu　后，　延时5ms还是很准的**  

<br>
###  设置步骤：  

1. 线程中绑定cpu，详见main.cpp  
<br>

2. cpu孤立:  
<br>
在系统中通过 /etc/default/grub 修改 编辑 /etc/default/grub 文件 ,在 quiet splash后面加上 isolcpus=2　(2指的是逻辑核，详细操作以及验证见pdf)



