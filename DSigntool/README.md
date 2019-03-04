
https://www.52pojie.cn/thread-877849-1-1.html

##### Tip
欢迎使用JemmyLoveJenny修改版的数字签名工具！
本工具基于TrustAsia亚洲诚信数字签名工具专业版，版本3.2.0修改

##### 修改版本与原版的区别
```
1.在原版中，若想使用已过期的数字证书进行签名，则需要修改整个系统的时间。在修改版本中您可以通过编辑hook.ini修改签名工具获取到的时间，免去修改系统时间的麻烦。
2.修改了原版时间戳列表，删除Entrust时间戳，增加了我自建的上海域联专用时间戳（签名时间为 2011-04-01 00:00:00 UTC），因此可以在签名的同时打上时间戳。
  若将我的 JemmyLoveJenny EV Root CA 添加进系统根证书信任列表，过期的上海域联证书+此专用时间戳可以直接通过WinXP-Win10所有系统的驱动加载签名检查。
  EVRootCA.crt就是我自签名的根证书。为了便于添加信任，我制作了注册表添加方式，运行EVRootCA.reg也可以达到的目的。
```

##### 修改过程
```
1.编译HookSigntool.dll，使用微软Detur库Hook了签名工具的函数 crypt32.dll!CertVerifyTimeValidity 和 kernel32.dll!GetLocalTime。
2.修改DSigntool.exe，PE头部导入表添加 HookSigntool.dll!attach 达到Hook函数的目的。
3.修改Dsigntool.exe，将Entrust的时间戳地址更换为我自己的专用时间戳。
```
##### 用法

```
1.安装原版签名工具，获取地址为 https://www.trustasia.com/sign-tools （其实不安装也可以）
2.下载本修改版工具，替换文件到安装位置。
3.编辑hook.ini文件，自定义日期（默认设为2011-04-01）
4.启动DSigntool.exe尽情享用吧。

```