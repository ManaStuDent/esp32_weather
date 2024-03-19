# esp32_weather
合宙 esp32c3 简约款 使用 platformio 开发墨水屏显示天气信息，效果图中的开发板可到小黄鱼中购买到。搜索用户名 Chengloong

# 注意点
- 申请彩云天气开发 API https://dashboard.caiyunapp.com/user/sign_in/
- 简约款需要在 platformio.ini 中添加 build_flags 后才可以打印串口信息
- 修改 DrawPaper.cpp 中 `http.begin("https://api.caiyunapp.com/v2.6/" + weatherKey + "/weather?alert=false&dailysteps=7&hourlysteps=0");` 最后添加 &lang=en_US 可以将天气预报的语言设定为 English (设定后部分功能布局需要修改，请自行适配)
- 烧录固件后会检测是否链接 WiFi，第一次使用将需要稍等一会，等待提示使用 SmartConfig 进行配网，手机下载 Esptouch 软件进行配置，注意一定要链接 2.4G WiFi 网络

# 效果
![](https://images.cnblogs.com/cnblogs_com/manastudent/1792948/o_230427070030_Snipaste_2023-04-27_14-58-53.png)
