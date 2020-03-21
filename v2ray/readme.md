## 记录　v2ray　linux 客户端使用过程  
  
### 参考
https://www.wandouip.com/t5i197953/   重点讲了如何安装 v2ray 客户端  
https://www.imcaviare.com/2018-12-18-1/  重点讲了启动和关闭 v2ray　的命令和PAC的设置，在这里 PAC 我没有设置成功，导致自己还需要手动切换“国内”和“国外”  
  

### 1.离线安装v2ray客户端(因为在线装慢)：  
　　
   离线的　**安装包 https://github.com/v2ray/v2ray-core/releases ** 和 **脚本文件**  
  
   运行命令:  
   
```
     sudo bash go.sh --local ./v2ray-linux-64.zip  
```  
   
   其中go.sh是安装自动化脚本，使用该脚本执行下载下来的离线安装包，安装过程需要root权限.


### 2.配置客户端参数　　
　　这里将 windows　下导出的 JSON 格式的参数复制到　**/etc/v2ray/config.json** 文件来配置你需要的代理方式；

### 3.v2ray 服务启动和关闭命令  
```
    sudo systemctl start v2ray

　　 sudo systemctl stop v2ray

　 　sudo systemctl restart v2ray

```  
 ### 4.设置代理
　　　打开网络设置，代理设置为手动，更改　SOcks Host:127.0.0.1 端口是自己配置的参数：10808

<div align=center>
<img src="https://github.com/zhaoyuRobotics/OpenSourceFrameworkTestDemo/blob/master/v2ray/proxy.png" width="636" height="510" align=center/>
</div>



### 5.使用google浏览器测试


### 注意：这里没有设置成功　PAC 分流代理（区分国内国外网址，这样做的好处是当启动代理后国内的网址也可以很快的访问）
    还是记录下生成PAC的命令： 
 
```
     genpac --proxy="SOCKS 127.0.0.1:10808" --gfwlist-proxy="SOCKS5 127.0.0.1:10808" -o autoproxy.pac --gfwlist-url="https://raw.githubusercontent.com/gfwlist/gfwlist/master/gfwlist.txt"

```




