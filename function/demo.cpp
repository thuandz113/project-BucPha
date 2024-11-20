#include <opencv2/opencv.hpp>

int main() {
    // Mở camera (sử dụng camera mặc định)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Không thể mở camera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;  // Đọc ảnh từ camera
        if (frame.empty()) {
            std::cerr << "Không thể đọc ảnh từ camera." << std::endl;
            break;
        }

        // Khởi tạo QRCodeDetector
        cv::QRCodeDetector qrDecoder;

        // Biến chứa kết quả quét mã QR
        std::string qrCodeData;

        // Quét mã QR từ ảnh
        bool found = qrDecoder.detectAndDecode(frame, qrCodeData);

        if (found) {
            std::cout << "Dữ liệu QR Code: " << qrCodeData << std::endl;

            // Hiển thị lên cửa sổ OpenCV
            cv::putText(frame, "QR Code: " + qrCodeData, cv::Point(10, 30),
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(frame, "Chua quet duoc QR Code", cv::Point(10, 30),
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        // Hiển thị cửa sổ chứa ảnh video
        cv::imshow("QR Code Scanner", frame);

        // Dừng lại nếu nhấn phím 'q'
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Giải phóng tài nguyên và đóng cửa sổ
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
