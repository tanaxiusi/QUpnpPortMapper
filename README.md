# QUpnpPortMapper
upnp端口映射

使用Qt编写，4.8.6和5.7.0测试过。



使用方法：

open(QHostAddress)或open(QNetworkInterface)填入本地IPv4地址，或者填入网卡。

discover扫描upnp。

queryExternalAddressFinished获取外网地址。

addPortMapping添加端口映射。

deletePortMapping删除端口映射。
