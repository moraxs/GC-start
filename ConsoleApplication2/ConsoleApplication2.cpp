#include <cstdlib>
#include <iostream>

int main() {

    system("echo 使用请加群124750952，本程序是基于Github开源项目Grasscutter制作的一键启动包，仅供研究交流用，禁止用于商业及非法用途。使用本软件造成的事故与损失，与作者无关。本程序完全免费，如果您是花钱买的，说明您被骗了。请尽快退款，以减少您的损失[0m");
    std::cout << "输入Y并回车代表您已经同意以上条款并继续运行。输入N则退出程序[Y/N]默认N" << std::endl;
    std::string input;
    std::cin >> input;
    if (input == "Y" || input == "y") {
        // continue running
    }
    else {
        exit(0); // stop running
    }
    system("title Program startup-by-Morax");
    system("cd /d %~dp0");
    system("echo MongoDB starting...");
    system("cd %~dp0\"Dataserver\\MongoDB\"");
    system("start mongodb.bat");
    system("ping 127.0.0.1 -n 5 >nul");
    system("echo Grasscutter starting ...");
    system("cd %~dp0\"Main_services\"");
    system("start grasscutter.bat");
    system("cd %~dp0\"Grasscuttertools\"");
    system("start GrasscutterTools.exe");
    system("cd %~dp0\"Proxytools\"");
    system("start Proxytools");
}
