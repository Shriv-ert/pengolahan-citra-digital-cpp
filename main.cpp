#include <opencv2/opencv.hpp>
#define M_PI 3.14159265358979323846

// Tidak menggunakan using namespace std/cv agar lebih mudah untuk membedakan.

cv::Mat imgBGRtoGray(const cv::Mat& img){
    cv::Mat result(img.rows, img.cols, CV_8UC1);
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);  // Get BGR
            // rasio BGR=  0.2989 : 0.5870 : 0.1140
            result.at<uchar>(y, x) = std::round(pixel[0]*0.1140) + std::round(pixel[1]*0.5870) +  std::round(0.2989*pixel[2]);
        }
    }
    return result;
}

cv::Mat imgToNegative(const cv::Mat& img){
    cv::Mat result(img.rows, img.cols, CV_8UC3);
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
        }
    }
    return result;
}

cv::Mat translasiIMG(const cv::Mat& img, int horizontal = 0, int vertical = 0){
    cv::Mat result(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            if(y - vertical >= img.rows || x + horizontal >= img.cols ||
                y - vertical < 0 || x + horizontal < 0) continue;
            result.at<cv::Vec3b>(y - vertical, x + horizontal) = pixel;
        }
    }
    return result;
}

cv::Mat rotasiIMG(const cv::Mat& img, int angle){
    double radian = angle * M_PI / 180;
    double norm_x = img.cols / 2.0;
    double norm_y = img.rows / 2.0;
    double c = std::cos(radian);
    double s = std::sin(radian);
    cv::Mat result(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            // Reverse mapping: pixel output mencari asalnya di gambar input.
            double src_x = std::round((x - norm_x) * c + (y - norm_y) * s + norm_x);
            double src_y = std::round(-(x - norm_x) * s + (y - norm_y) * c + norm_y);
            if(src_x < 0 || src_x >= img.cols || src_y < 0 || src_y >= img.rows) continue;

            result.at<cv::Vec3b>(y, x) = img.at<cv::Vec3b>(src_y, src_x);
        }
    }
    return result;
}

cv::Mat scaleIMG(const cv::Mat& img, double scale = 1.0){
    cv::Mat result(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            // Perhitungan koordinat baru dengan pembagian oleh skala(reverse mapping)
            double src_x = std::round(x / scale);
            double src_y = std::round((y - img.rows) / scale + img.rows);
            if(src_x >= img.cols || src_x < 0 
            || src_y >= img.rows || src_y < 0) continue;
            result.at<cv::Vec3b>(y, x) = img.at<cv::Vec3b>(src_y, src_x);
        }
    }
    return result;
}

cv::Mat flipHorizontalIMG(const cv::Mat& img){
    cv::Mat result(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            result.at<cv::Vec3b>(y, img.cols - 1 - x) = pixel;
        }
    }
    return result;
}

cv::Mat flipVerticalIMG(const cv::Mat& img){
    cv::Mat result(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            result.at<cv::Vec3b>(img.rows - 1 - y, x) = pixel;
        }
    }
    return result;
}

cv::Mat compareIMG(const cv::Mat& img, const cv::Mat& imgEdited, const cv::Mat& imgEditedGray){
    cv::Mat result(img.rows, img.cols * 3, CV_8UC3, cv::Scalar(0, 0, 0));
    int maxRow1 = std::min(img.rows, result.rows);
    int maxCol1 = std::min(img.cols, result.cols);
    for(int y = 0; y < maxRow1; y++){
        for(int x = 0; x < maxCol1; x++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            result.at<cv::Vec3b>(y, x) = pixel;
        }
    } 
    int maxRow2 = std::min(imgEdited.rows, result.rows);
    int maxCol2 = std::min(imgEdited.cols, img.cols);
    for(int y = 0; y < maxRow2; y++){
        for(int x = 0; x < maxCol2; x++){
            cv::Vec3b pixel = imgEdited.at<cv::Vec3b>(y, x);
            result.at<cv::Vec3b>(y, img.cols + x) = pixel;
            
        }
    }
    int maxRow3 = std::min(imgEditedGray.rows, result.rows);
    int maxCol3 = std::min(imgEditedGray.cols, img.cols);
    for(int y = 0; y < maxRow3; y++){
        for(int x = 0; x < maxCol3; x++){
            uchar pixel = imgEditedGray.at<uchar>(y, x);
            result.at<cv::Vec3b>(y, 2 * img.cols + x) = cv::Vec3b(pixel, pixel, pixel);
        }
    }
    return result;
}


int main() {
    const std::string inputPath = "img/gambar.png";
    const std::string PathCompareImgNegGray = "img/CompareImageNegativeGrayscale.png";
    const std::string PathCompareGray = "img/CompareGrayscale.png";
    const std::string PathCompareTranslasi = "img/CompareTranslasi.png";
    const std::string PathCompareRotasi = "img/CompareRotasi.png";
    const std::string PathCompareScale = "img/CompareScale.png";
    const std::string PathCompareFlipHorizontal = "img/CompareFlipHorizontal.png";
    const std::string PathCompareFlipVertical = "img/CompareFlipVertical.png";

    cv::Mat img = cv::imread(inputPath);
    if (img.empty()) {
        std::cerr << "Gagal membaca gambar input: " << inputPath << '\n';
        return 1;
    }

    cv::Mat gray = imgBGRtoGray(img);
    cv::Mat translasi = translasiIMG(img, -30, -100);
    cv::Mat rotasi = rotasiIMG(img, 43);
    cv::Mat scale = scaleIMG(img, 10);
    cv::Mat flipHorizontal = flipHorizontalIMG(img);
    cv::Mat flipVertical = flipVerticalIMG(img);
    cv::Mat compareTranslasi = compareIMG(img, translasi, imgBGRtoGray(translasi));
    cv::Mat compareRotasi = compareIMG(img, rotasi, imgBGRtoGray(rotasi));
    cv::Mat compareScale = compareIMG(img, scale, imgBGRtoGray(scale));
    cv::Mat compareFlipHorizontal = compareIMG(img, flipHorizontal, imgBGRtoGray(flipHorizontal));
    cv::Mat compareFlipVertical = compareIMG(img, flipVertical, imgBGRtoGray(flipVertical));
    cv::Mat compareImgNegGray = compareIMG(img, imgToNegative(img), imgBGRtoGray(img));

    if (!cv::imwrite(PathCompareImgNegGray, compareImgNegGray)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareImgNegGray << '\n';
        return 1;
    }
    if (!cv::imwrite(PathCompareTranslasi, compareTranslasi)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareTranslasi << '\n';
        return 1;
    }
    if (!cv::imwrite(PathCompareRotasi, compareRotasi)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareRotasi << '\n';
        return 1;
    }
    if (!cv::imwrite(PathCompareScale, compareScale)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareScale << '\n';
        return 1;
    }
    if (!cv::imwrite(PathCompareFlipHorizontal, compareFlipHorizontal)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareFlipHorizontal << '\n';
        return 1;
    }
    if (!cv::imwrite(PathCompareFlipVertical, compareFlipVertical)) {
        std::cerr << "Gagal menyimpan gambar: " << PathCompareFlipVertical << '\n';
        return 1;
    }

    std::cout << "Gambar tersimpan di  : " << PathCompareTranslasi << '\n';
    std::cout << "Gambar tersimpan di  : " << PathCompareRotasi << '\n';
    std::cout << "Gambar tersimpan di  : " << PathCompareScale << '\n';
    std::cout << "Gambar tersimpan di  : " << PathCompareFlipHorizontal << '\n';
    std::cout << "Gambar tersimpan di  : " << PathCompareFlipVertical << '\n';
    std::cout << "Gambar tersimpan di  : " << PathCompareImgNegGray << '\n';

    return 0;
}