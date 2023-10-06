#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <windows.h>

namespace fs = std::filesystem;

std::string loadCachedFolderPath() {
    std::ifstream file("cached_folder_path.txt");
    std::string folderPath;
    if (file.is_open()) {
        std::getline(file, folderPath);
        file.close();
    }
    return folderPath;
}

void saveFolderPathToCache(const std::string& folderPath) {
    std::ofstream file("cached_folder_path.txt");
    if (file.is_open()) {
        file << folderPath;
        file.close();
    }
}

void startGame(const std::string& folderPath) {
    std::string gameExePath = folderPath + "\\Yuanshen.exe";

    if (fs::exists(gameExePath)) {
        std::string command = "start \"\" \"" + gameExePath + "\"";
        std::system(command.c_str());
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        std::cout << "游戏可执行文件不存在。\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

int main() {
    bool shouldContinue = true;
    bool hasTargetFolder = false;
    std::string targetFolderPath;

    targetFolderPath = loadCachedFolderPath();

    while (shouldContinue) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); // 设置文本颜色为绿色
        std::cout << "最新一键端下载/闲聊吹水:Q群124750952。\n"; // 将文本显示为绿色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 恢复默认文本颜色
        std::cout << 
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
            "4:启动游戏(请先补丁客户端)\n"
            "5:一键跑路\n"
            "[Y/N/1/2/3/4/5]: \n";

        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "Y" || answer == "y") {
            std::string command = "Main_services\\Runtime.bat";
            std::system(command.c_str());
        }
        else if (answer == "1") {
            std::string url = "https://qm.qq.com/q/Vw5YO9looE";
            std::string command;

#ifdef _WIN32
            command = "start " + url;
#elif __linux__
            command = "xdg-open " + url;
#elif __APPLE__
            command = "open " + url;
#endif

            std::system(command.c_str());
        }
        else if (answer == "2") {
            if (targetFolderPath.empty()) {
                std::cout << "请输入游戏文件夹路径：(不需要带Yuanshen,exe与双引号)";
                std::getline(std::cin, targetFolderPath);
                hasTargetFolder = true;
                saveFolderPathToCache(targetFolderPath);
            }

            if (!fs::exists(targetFolderPath)) {
                fs::create_directory(targetFolderPath);
            }

            std::string currentDirectory = fs::current_path().string();

            std::string sourceFolderPath = currentDirectory + "\\RSAPatch";
            std::string fileName = "mhypbase.dll";
            std::string sourceFilePath = sourceFolderPath + "\\" + fileName;
            std::string destinationFilePath = targetFolderPath + "\\" + fileName;

            if (fs::exists(destinationFilePath)) {
                std::string renamedFilePath = targetFolderPath + "\\mhypbase-patched.dll";
                fs::rename(destinationFilePath, renamedFilePath);
            }

            try {
                fs::copy(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                std::cout << "客户端补丁成功！\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            catch (const std::exception& ex) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                std::cerr << "补丁失败：" << ex.what() << "\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            hasTargetFolder = true;
        }
        else if (answer == "3") {
            if (!hasTargetFolder) {
                std::cout << "请输入游戏文件夹路径：(不需要带Yuanshen,exe与双引号)";
                std::getline(std::cin, targetFolderPath);
                hasTargetFolder = true;
                saveFolderPathToCache(targetFolderPath);
            }

            std::string fileName = "mhypbase.dll";
            std::string sourceFilePath = targetFolderPath + "\\" + fileName;
            std::string patchedFilePath = targetFolderPath + "\\mhypbase-patched.dll";
            std::string destinationFilePath = targetFolderPath + "\\" + fileName;

            if (fs::exists(sourceFilePath)) {
                fs::remove(sourceFilePath);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                std::cout << "补丁文件已删除！\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                std::cout << "补丁不存在，无法删除。\n";
            }

            if (fs::exists(patchedFilePath)) {
                fs::rename(patchedFilePath, destinationFilePath);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                std::cout << "文件重命名成功！\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                std::cout << "mhypbase-patched.dll 不存在，无法重命名。\n";
            }
        }
        else if (answer == "4") {
            if (targetFolderPath.empty()) {
                std::cout << "请输入游戏文件夹路径：(不需要带Yuanshen,exe与双引号)";
                std::getline(std::cin, targetFolderPath);
                hasTargetFolder = true;
                saveFolderPathToCache(targetFolderPath);
            }

            startGame(targetFolderPath);
        }
        else if (answer == "5") {
            std::cout << "确认要删除当前运行目录下的所有文件吗？(输入Y并回车确认，输入其他内容并回车取消): ";
            std::string confirmation;
            std::getline(std::cin, confirmation);

            if (confirmation == "Y" || confirmation == "y") {
                std::string currentDirectory = fs::current_path().string();

                for (const auto& entry : fs::directory_iterator(currentDirectory)) {
                    try {
                        if (fs::is_regular_file(entry)) {
                            fs::remove(entry);
                        }
                        else if (fs::is_directory(entry)) {
                            fs::remove_all(entry);
                        }
                    }
                    catch (const std::exception& ex) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        std::cerr << "删除文件或目录时出错：" << ex.what() << "\n";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                std::cout << "当前目录下的所有文件和子目录已被删除。\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                std::cout << "删除操作已取消。\n";
            }
        }
        else if (answer == "N" || answer == "n") {
            shouldContinue = false;
        }
        else {
            std::cout << "无效的选项，请重新输入。\n";
        }
    }

    return 0;
}
