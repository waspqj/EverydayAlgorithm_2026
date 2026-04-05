#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

const char* SERVER_IP = "110.40.166.16";
const uint16_t SERVER_PORT = 8080;

SOCKET sockfd = INVALID_SOCKET;
sockaddr_in serverAddr;

// GBK 转 UTF-8
std::string GBKToUTF8(const std::string& gbkStr) {
    int len = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    std::string result(str);
    delete[] wstr;
    delete[] str;
    return result;
}

// UTF-8 转 GBK
std::string UTF8ToGBK(const std::string& utf8Str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len];
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    std::string result(str);
    delete[] wstr;
    delete[] str;
    return result;
}

void Send() {
    while (true) {
        std::string buff;
        std::getline(std::cin, buff);
        // 将 GBK 转为 UTF-8 再发送
        std::string utf8 = GBKToUTF8(buff);
        int ret = sendto(sockfd, utf8.c_str(), (int)utf8.size(), 0,
            (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (ret == SOCKET_ERROR) {
            std::cerr << "sendto error: " << WSAGetLastError() << std::endl;
        }
    }
}

void Recv() {
    char rcbuff[1024000];
    sockaddr_in fromAddr;
    int fromLen = sizeof(fromAddr);
    while (true) {
        memset(rcbuff, 0, sizeof(rcbuff));
        int n = recvfrom(sockfd, rcbuff, sizeof(rcbuff) - 1, 0,
            (sockaddr*)&fromAddr, &fromLen);
        if (n == SOCKET_ERROR) {
            std::cerr << "recvfrom error: " << WSAGetLastError() << std::endl;
            continue;
        }
        rcbuff[n] = '\0';
        // 将接收到的 UTF-8 转为 GBK 显示
        std::string utf8(rcbuff);
        std::string gbk = UTF8ToGBK(utf8);
        std::cout << gbk << std::endl;
    }
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "socket error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 绑定本地端口（接收需要）
    sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);
    if (bind(sockfd, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
        std::cerr << "bind error: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    std::cout << "Client started, connecting to " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    std::thread sendThread(Send);
    std::thread recvThread(Recv);

    sendThread.join();
    recvThread.join();

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
//#include <iostream>
//#include <string>
//#include <cstring>
//#include <thread>
//#include <WinSock2.h>
//#include <Windows.h>
//
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable : 4996)
//
//// 硬编码服务器 IP 和端口
//const char* SERVER_IP = "110.40.166.16";
//const uint16_t SERVER_PORT = 8080;
//
//SOCKET sockfd = INVALID_SOCKET;
//sockaddr_in serverAddr;
//
//void Send() {
//    while (true) {
//        std::string buff;
//        std::getline(std::cin, buff);
//        int ret = sendto(sockfd, buff.c_str(), (int)buff.size(), 0,
//            (sockaddr*)&serverAddr, sizeof(serverAddr));
//        if (ret == SOCKET_ERROR) {
//            std::cerr << "sendto error: " << WSAGetLastError() << std::endl;
//        }
//    }
//}
//
//void Recv() {
//    char rcbuff[1024];
//    sockaddr_in fromAddr;
//    int fromLen = sizeof(fromAddr);
//    while (true) {
//        memset(rcbuff, 0, sizeof(rcbuff));
//        int n = recvfrom(sockfd, rcbuff, sizeof(rcbuff) - 1, 0,
//            (sockaddr*)&fromAddr, &fromLen);
//        if (n == SOCKET_ERROR) {
//            std::cerr << "recvfrom error: " << WSAGetLastError() << std::endl;
//            continue;
//        }
//        rcbuff[n] = '\0';
//        std::cout << rcbuff << std::endl;
//    }
//}
//
//int main() {
//    // 初始化 Winsock
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "WSAStartup failed" << std::endl;
//        return 1;
//    }
//
//    // 创建 UDP socket
//    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sockfd == INVALID_SOCKET) {
//        std::cerr << "socket error: " << WSAGetLastError() << std::endl;
//        WSACleanup();
//        return 1;
//    }
//
//    // 设置服务器地址
//    memset(&serverAddr, 0, sizeof(serverAddr));
//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_port = htons(SERVER_PORT);
//    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
//
//    // 可选：绑定本地端口（不绑定也可以，Windows 下 UDP 发送前会自动分配，但接收需要绑定）
//    // 为了让 recvfrom 能收到数据，必须绑定一个本地端口
//    sockaddr_in localAddr;
//    memset(&localAddr, 0, sizeof(localAddr));
//    localAddr.sin_family = AF_INET;
//    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    localAddr.sin_port = htons(0);  // 让系统自动分配端口
//    if (bind(sockfd, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
//        std::cerr << "bind error: " << WSAGetLastError() << std::endl;
//        closesocket(sockfd);
//        WSACleanup();
//        return 1;
//    }
//
//    std::cout << "Client started, connecting to " << SERVER_IP << ":" << SERVER_PORT << std::endl;
//
//    // 启动发送和接收线程
//    std::thread sendThread(Send);
//    std::thread recvThread(Recv);
//
//    sendThread.join();
//    recvThread.join();
//
//    // 清理（不会执行到这里）
//    closesocket(sockfd);
//    WSACleanup();
//    return 0;
//}
//

//#include <iostream>
//#include <string>
//#include <cstring>
//#include <thread>
//#include <WinSock2.h>
//#include <Windows.h>
//
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable : 4996)
//
//const std::string SERVER_IP = "110.40.166.16";
//const uint16_t SERVER_PORT = 8080;
//
//class Addr {
//public:
//    Addr() {
//        memset(&addr, 0, sizeof(addr));
//        addr.sin_family = AF_INET;
//    }
//    Addr(const std::string& ip, uint16_t port) {
//        memset(&addr, 0, sizeof(addr));
//        addr.sin_family = AF_INET;
//        addr.sin_addr.s_addr = inet_addr(ip.c_str());
//        addr.sin_port = htons(port);
//    }
//    Addr(const sockaddr_in& sa) : addr(sa) {}
//
//    sockaddr* AddrPtr() { return (sockaddr*)&addr; }
//    int AddrLen() const { return sizeof(addr); }
//    const sockaddr_in& Get() const { return addr; }
//
//private:
//    sockaddr_in addr;
//};
//
//SOCKET sockfd = INVALID_SOCKET;
//Addr Server;
//
//void Send() {
//    while (true) {
//        std::string buff;
//        std::getline(std::cin, buff);
//        if (buff.empty()) continue;
//
//        int ret = sendto(sockfd, buff.c_str(), (int)buff.size(), 0,
//            Server.AddrPtr(), Server.AddrLen());
//        if (ret == SOCKET_ERROR) {
//            std::cerr << "sendto error: " << WSAGetLastError() << std::endl;
//        }
//    }
//}
//
//void Recv() {
//    char rcbuff[1024];
//    sockaddr_in saddr;
//    int saddr_len = sizeof(saddr);
//
//    while (true) {
//        memset(rcbuff, 0, sizeof(rcbuff));
//        // Windows UDP recvfrom 阻塞模式正常
//        int n = recvfrom(sockfd, rcbuff, sizeof(rcbuff) - 1, 0,
//            (sockaddr*)&saddr, &saddr_len);
//
//        if (n == SOCKET_ERROR) {
//            int err = WSAGetLastError();
//            // 10054 是对方断开，正常忽略；其他错误打印
//            if (err != 10054) {
//                std::cerr << "recvfrom error: " << err << std::endl;
//            }
//            continue;
//        }
//
//        rcbuff[n] = '\0';
//        std::cout << "\r[Server] " << rcbuff << std::endl;
//        std::cout << "Send: " << std::flush;
//    }
//}
//
//int main() {
//    // 初始化 Winsock
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "WSAStartup failed" << std::endl;
//        return 1;
//    }
//
//    // 创建 UDP socket
//    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    if (sockfd == INVALID_SOCKET) {
//        std::cerr << "socket error: " << WSAGetLastError() << std::endl;
//        WSACleanup();
//        return 1;
//    }
//
//    Server = Addr(SERVER_IP, SERVER_PORT);
//
//    std::cout << "UDP Chat Client Started. Type message to send." << std::endl;
//    std::cout << "Send: " << std::flush;
//
//    std::thread sendThread(Send);
//    std::thread recvThread(Recv);
//
//    sendThread.detach();
//    recvThread.join();
//
//    closesocket(sockfd);
//    WSACleanup();
//    return 0;
//}
//#include <iostream>
//#include <string>
//#include <cstring>
//#include <thread>
//#include <WinSock2.h>
//#include <Windows.h>
//
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable : 4996)
//
//class Addr {
//public:
//    Addr() {
//        memset(&addr, 0, sizeof(addr));
//        addr.sin_family = AF_INET;
//    }
//    Addr(const std::string& ip, uint16_t port) {
//        memset(&addr, 0, sizeof(addr));
//        addr.sin_family = AF_INET;
//        addr.sin_addr.s_addr = inet_addr(ip.c_str());
//        addr.sin_port = htons(port);
//    }
//    Addr(const sockaddr_in& sa) : addr(sa) {}
//
//    sockaddr* AddrPtr() { return (sockaddr*)&addr; }
//    int AddrLen() const { return sizeof(addr); }
//    const sockaddr_in& Get() const { return addr; }
//
//private:
//    sockaddr_in addr;
//};
//
//SOCKET sockfd = INVALID_SOCKET;
//Addr Server;
//
//// 硬编码服务器地址和端口（请修改为你的实际服务器IP和端口）
//const std::string SERVER_IP = "110.40.166.16";
//const uint16_t SERVER_PORT = 8080;
//
//void Send() {
//    while (true) {
//        std::string buff;
//        std::getline(std::cin, buff);
//        int ret = sendto(sockfd, buff.c_str(), (int)buff.size(), 0,
//            Server.AddrPtr(), Server.AddrLen());
//        if (ret == SOCKET_ERROR) {
//            std::cerr << "sendto error: " << WSAGetLastError() << std::endl;
//        }
//    }
//}
//
//void Recv() {
//    char rcbuff[1024];
//    sockaddr_in saddr;
//    int saddr_len = sizeof(saddr);
//    while (true) {
//        memset(rcbuff, 0, sizeof(rcbuff));
//        int n = recvfrom(sockfd, rcbuff, sizeof(rcbuff) - 1, 0,
//            (sockaddr*)&saddr, &saddr_len);
//        if (n == SOCKET_ERROR) {
//            std::cerr << "recvfrom error: " << WSAGetLastError() << std::endl;
//            continue;
//        }
//        rcbuff[n] = '\0';
//        std::cout << rcbuff << std::endl;
//    }
//}
//
//int main() {
//    // 初始化 Winsock
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "WSAStartup failed" << std::endl;
//        return 1;
//    }
//
//    // 创建 UDP socket
//    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sockfd == INVALID_SOCKET) {
//        std::cerr << "socket error: " << WSAGetLastError() << std::endl;
//        WSACleanup();
//        return 1;
//    }
//
//    // 设置服务器地址（使用硬编码）
//    Server = Addr(SERVER_IP, SERVER_PORT);
//
//    // 启动发送和接收线程
//    std::thread sendThread(Send);
//    std::thread recvThread(Recv);
//
//    sendThread.join();
//    recvThread.join();
//
//    // 清理
//    closesocket(sockfd);
//    WSACleanup();
//    return 0;
//}
//#include <iostream>
//#include <cstdio>
//#include <thread>
//#include <string>
//#include <cstdlib>
//#include <WinSock2.h>
//#include <Windows.h>
//
//#pragma warning(disable : 4996)
//#pragma comment(lib, "ws2_32.lib")
//
//std::string serverip = "110.40.166.16"; // 填写你的云服务器ip
//uint16_t serverport = 8080; // 填写你的云服务开放的端⼝号
//int main()
//{
//	WSADATA wsd;
//	WSAStartup(MAKEWORD(2, 2), &wsd);
//	struct sockaddr_in server;
//	memset(&server, 0, sizeof(server));
//	server.sin_family = AF_INET;
//	server.sin_port = htons(serverport); //?
//	server.sin_addr.s_addr = inet_addr(serverip.c_str());
//	SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//	if (sockfd == SOCKET_ERROR)
//	{
//		std::cout << "socker error" << std::endl;
//		return 1;
//	}
//	std::string message;
//	char buffer[1024];
//	while (true)
//	{
//		std::cout << "Please Enter@ ";
//		std::getline(std::cin, message);
//		if (message.empty()) continue;
//		sendto(sockfd, message.c_str(), (int)message.size(), 0, (struct
//			sockaddr*)&server, sizeof(server));
//		struct sockaddr_in temp;
//		int len = sizeof(temp);
//		int s = recvfrom(sockfd, buffer, 1023, 0, (struct sockaddr*)&temp,
//			&len);
//		if (s > 0)
//		{
//			buffer[s] = 0;
//			std::cout << buffer << std::endl;
//		}
//	}
//	closesocket(sockfd);
//	WSACleanup();
//	return 0;
//}