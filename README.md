# Android-Paste  
## 安卓依赖dex实现的C++粘贴  
  
需要外部调用(shell和dex)  
仅支持安卓, 可在noroot环境运行  
仅在arm64-v8a android14进行测试  
  
### 小问题  
效率很低，粘贴操作要等待一秒左右  
但对此，开发了非阻塞方法  
需要shell环境中存在`app_process64`指令
  
## 对应小白  
  
源文件等在 src/ 文件夹下  
测试器源文件在 test/ 文件夹下  
build.sh是构建测试版本的构建指令  
注意需要安装有g++指令用来编译  
  
# 开发者  
  
'dex文件'及'阻塞获取方法的思路'来自于 [HYB](https://t.me/HYBB_love)  
  
'后续优化', '非阻塞方法'及开源者为 [F_Error11](https://t.me/FullError11)  

# 关于开源协议

我所见的多数开发者都不会遵守，所有不带协议了

但是，我还是希望能留下[开发者]的名字...
