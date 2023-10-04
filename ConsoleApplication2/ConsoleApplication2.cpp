#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    bool shouldContinue = true; // 添加一个标志来控制是否继续运行程序
    bool hasTargetFolder = false; // 添加一个标志来标记用户是否已输入文件夹路径
    std::string targetFolderPath; // 声明 targetFolderPath 变量


    
    while (shouldContinue) {
        std::cout << "最新一键端下载/闲聊吹水:Q群124750952。\n"
            "本程序是基于Github开源项目Grasscutter制作的一键启动包，仅供研究交流用，禁止用于商业及非法用途。"
            "使用本软件造成的事故与损失，与作者无关。\n"
            "本程序完全免费，如果您是花钱买的，说明您被骗了。"
            "请尽快退款，以减少您的损失。\n"
            "请输入您的选择 \n"
            "Y:一键启动服务器\n"
            "N:退出本程序\n"
            "1:快捷加群\n"
            "2:一键补丁客户端\n"
            "3:还原客户端\n"
            "[Y/N/1/2/3]: \n";

        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "Y" || answer == "y") {
            std::string command = "Main_services\\Runtime.bat";
            std::system(command.c_str());
        }

        else if (answer == "1") {
            std::string url = "https://qm.qq.com/q/Vw5YO9looE";
            std::string command;

            // 根据不同操作系统选择合适的命令来打开链接
#ifdef _WIN32
            command = "start " + url;
#elif __linux__
            command = "xdg-open " + url;
#elif __APPLE__
            command = "open " + url;
#endif

            // 执行打开链接的命令
            std::system(command.c_str());
        }
        else if (answer == "2") {
            std::cout << "请输入游戏文件夹路径：(不需要带Yuanshen,exe与双引号)";
            std::getline(std::cin, targetFolderPath); // 更新 targetFolderPath 变量

            // 检查目标文件夹是否存在，如果不存在则创建
            if (!fs::exists(targetFolderPath)) {
                fs::create_directory(targetFolderPath);
            }

            // 获取当前程序运行的目录
            std::string currentDirectory = fs::current_path().string();

            // 构建源文件夹路径和文件名
            std::string sourceFolderPath = currentDirectory + "\\RSAPatch";
            std::string fileName = "mhypbase.dll";
            std::string sourceFilePath = sourceFolderPath + "\\" + fileName;
            std::string destinationFilePath = targetFolderPath + "\\" + fileName;

            // 如果目标文件已存在，则将其重命名为 "mhypbase-patched.dll"
            if (fs::exists(destinationFilePath)) {
                std::string renamedFilePath = targetFolderPath + "\\mhypbase-patched.dll";
                fs::rename(destinationFilePath, renamedFilePath);
            }

            // 使用文件系统库中的copy函数复制文件并替换
            try {
                fs::copy(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing);
                std::cout << "客户端补丁成功！\n";
            }
            catch (const std::exception& ex) {
                std::cerr << "补丁失败：可能是不存在相关文件或程序权限不足" << ex.what() << "\n";
            }

            hasTargetFolder = true; // 用户已经输入了文件夹路径
        }
        else if (answer == "3") {
            if (!hasTargetFolder) {
                std::cout << "请输入游戏文件夹路径：(不需要带Yuanshen,exe与双引号)";
                std::getline(std::cin, targetFolderPath);
                hasTargetFolder = true; // 用户已经输入了文件夹路径
            }

            // 构建源文件夹路径和文件名
            std::string fileName = "mhypbase.dll";
            std::string sourceFilePath = targetFolderPath + "\\" + fileName;
            std::string patchedFilePath = targetFolderPath + "\\mhypbase-patched.dll";
            std::string destinationFilePath = targetFolderPath + "\\" + fileName;

            // 删除目标文件
            if (fs::exists(sourceFilePath)) {
                fs::remove(sourceFilePath);
                std::cout << "补丁文件已删除！\n";
            }
            else {
                std::cout << "补丁不存在，无法删除。\n";
            }

            // 重命名 mhypbase-patched.dll 为 mhypbase.dll
            if (fs::exists(patchedFilePath)) {
                fs::rename(patchedFilePath, destinationFilePath);
                std::cout << "文件重命名成功！\n";
            }
            else {
                std::cout << "mhypbase-patched.dll 不存在，无法重命名。\n";
            }
        }
        else if (answer == "N" || answer == "n") {
            shouldContinue = false; // 用户选择退出程序
        }
        else {
            std::cout << "无效的选项，请重新输入。\n";
        }
    }

    return 0;
}
