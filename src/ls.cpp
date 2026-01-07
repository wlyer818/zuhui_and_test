#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// 最小二乘直线拟合  y = ax + b
void lineplofit(const vector<Point2f>& pts, float& a, float& b) {
    if (pts.empty()) { a = b = 0; return; }
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    for (auto& p : pts) {
        sx  += p.x;
        sy  += p.y;
        sxx += p.x * p.x;
        sxy += p.x * p.y;
    }
    int n = pts.size();
    double den = n * sxx - sx * sx;
    if (fabs(den) < 1e-6) { a = b = 0; return; }
    a = (n * sxy - sx * sy) / den;
    b = (sxx * sy - sx * sxy) / den;
}

// 点 (x0,y0) 到直线 ax + by + c = 0 的垂直距离
static inline float distToLine(float x0, float y0, float a, float b) {
    // 直线写成 ax - y + b = 0
    return std::abs(a * x0 - y0 + b) / std::sqrt(a * a + 1.0f);
}
// 随机生成 N 个二维点，范围 [xMin,xMax] × [yMin,yMax]
std::vector<cv::Point2f> generateRandomPoints(int N,
                                              float xMin, float xMax,
                                              float yMin, float yMax,
                                              float noise = 0.0f)   // 可选噪声
{
    std::vector<cv::Point2f> pts;
    pts.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dx(xMin, xMax);
    std::uniform_real_distribution<float> dy(yMin, yMax);
    std::uniform_real_distribution<float> dn(-noise,  noise);

    // 先拟一条“真”直线 y = 2x + 1，再加高斯噪声
    for (int i = 0; i < N; ++i) {
        float x = dx(gen);
        float y = 2.0f * x + 1.0f + dn(gen);   // 加噪声
        pts.emplace_back(x, y);
    }
    return pts;
}
int main() {
    vector<Point2f> pts = generateRandomPoints(100, 0, 5, 0, 10, 0.5f);

    float a, b;
    lineplofit(pts, a, b);
    cout << "y = " << a << "x + " << b << endl;

    const int W = 600, H = 400;
    Mat img(H, W, CV_8UC3, Scalar(255,255,255));

    // 坐标变换：Point2f -> 像素坐标
    auto toImg = [&](float x, float y) -> Point {
        return Point(static_cast<int>(x * 40 + 50),
                     static_cast<int>(H - (y * 40 + 50)));
    };

    // 画点
    for (auto& p : pts)
        circle(img, toImg(p.x, p.y), 6, Scalar(0,0,255), FILLED);

    // 画直线
    float x1 = 0, y1 = a * x1 + b;
    float x2 = 6, y2 = a * x2 + b;
    line(img, toImg(x1, y1), toImg(x2, y2), Scalar(255,0,0), 2);
    // --- 计算最大距离 ---
    float maxDist = 0.0f;
    for (const auto& p : pts) {
        float d = distToLine(p.x, p.y, a, b);
        maxDist = std::max(maxDist, d);
    }

    // 把距离也画到图上
    putText(img, format("Max distance = %.2f", maxDist),
            Point(10, 60),              // 放在方程下方
            FONT_HERSHEY_SIMPLEX, 0.7,
            Scalar(0, 128, 255), 2);
    // 文字
    putText(img, format("y = %.2fx + %.2f", a, b),
            Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0,0,0), 2);

    imshow("Line Fit", img);
    waitKey(0);
    return 0;
}