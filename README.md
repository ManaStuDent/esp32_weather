# esp32_weather
合宙 esp32c3 简约款 使用 platformio 开发墨水屏显示天气信息

# 注意点
- 申请彩云天气开发 API https://dashboard.caiyunapp.com/user/sign_in/
- 修改 ESP32C3 的分区表解决编译内存不足问题 https://www.cnblogs.com/manastudent/p/17202598.html
- 简约款需要在 platformio.ini 中添加 build_flags 后才可以打印串口信息
- 修改 DrawPaper.cpp 中 `http.begin("https://api.caiyunapp.com/v2.6/" + weatherKey + "/weather?alert=false&dailysteps=7&hourlysteps=0");` 最后添加 &lang=en_US 可以将天气预报的语言设定为 English (设定后部分功能布局需要修改，请自行适配)

# 效果
![](https://images.cnblogs.com/cnblogs_com/manastudent/1792948/o_230418031916_%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20230418111859.jpg)
