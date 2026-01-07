#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 0 通常是内置摄像头，1 开始是外接摄像头；若不确定可逐个试
    int camera_id = 1;
    cv::VideoCapture cap(camera_id);

    if (!cap.isOpened())
    {
        std::cerr << "ERROR: 无法打开摄像头 " << camera_id << "\n";
        return -1;
    }

    std::cout << "摄像头已打开，按 ESC 退出...\n";

    cv::Mat frame;
    while (true)
    {
        cap >> frame;                 // 抓取一帧
        if (frame.empty()) break;     // 意外断流

        cv::imshow("USB Camera", frame);

        if (cv::waitKey(1) == 27)     // ESC 键
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}