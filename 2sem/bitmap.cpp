#include <string>

#include "header.hpp"

void help() {
    std::cout << "How to use the program??" << std::endl;
    std::cout << "To get the title: lsb --info --input ~/image.bmp " << std::endl;
    std::cout << "--input   full path to image. " << std::endl;
    std::cout << "hiding information :   lsb --crypt --input ~/original.bmp "
                 "--output ~/with_message.bmp --message ~/message.txt "
              << std::endl;
    std::cout << "--crypt - means that the program is running in hiding mode "
              << std::endl;
    std::cout << "--input - full path to original image; " << std::endl;
    std::cout << "--output - full path to the file with hidden information; "
              << std::endl;
    std::cout << "--message   full path to the file with information that "
                 "must be hidden in the image. "
              << std::endl;
    std::cout << "extraction of information: lsb --decrypt --input "
                 "~/with_message.bmp --message ~/out_message.txt"
              << std::endl;
    std::cout << "--decrypt -means that the program is running in the "
                 "retrieving information;"
              << std::endl;
    std::cout << "--input - full path to image with hidden message;" << std::endl;
    std::cout << "--message - full path to the file where you want to "
                 "record message from image"
              << std::endl;
}
void type_work(int argc, char* argv[]) {
    int count_if_type_work = 0;
    for (int i = 2; i < argc; ++i) {
        std::string type(argv[i]);
        if (type == "--info" || type == "--decrypt" || type == "--help" ||
            type == "--crypt")
            count_if_type_work++;
    }
    if (count_if_type_work > 1) throw std::invalid_argument("Usage:");
}
void check_format(int argc, char* argv[]) {
    for (int i = 2; i < argc; ++i) {
        std::string type(argv[i]);
        if (type == "--output" || type == "--input") {
            if (i != argc - 1) {
                std::string image(argv[i + 1]);
                std::string substr = image.substr(image.find(".") + 1, 3);
                if (substr != "bmp")
                    throw std::invalid_argument("NOT bmp format");
                else
                    break;
            } else {
                help();
                throw std::invalid_argument("Not enough arguments");
            }
        }
    }
}
void check_arguments(int argc, char* argv[]) {
    for (int i = 2; i < argc; ++i) {
        std::string type(argv[i]);
        if (type == "--input") {
            if (i != argc - 1) {
                std::string image(argv[i + 1]);
                if (image.find(".bmp") == std::string ::npos) {
                    help();
                    throw std::invalid_argument("Not enough arguments");
                }
            } else {
                help();
                throw std::invalid_argument("Not enough arguments");
            }
        }
        if (type == "--crypt" || type == "--decrypt") {
            bool message_flag = false;  //если встретим ,станет true
            for (int j = 2; j < argc; ++j) {
                std::string type1(argv[j]);
                if (type1 == "--message") message_flag = true;
            }
            if (!message_flag) {
                help();
                throw std::invalid_argument("dont have a message");
            }
        }

        //проверка на повтор аргументов
        int count_input = 0, count_output = 0, count_message = 0;
        if (type == "--message") count_message++;
        if (type == "--input") count_input++;
        if (type == "--output") count_output++;
        if (count_output > 1 || count_input > 1 || count_message > 1) {
            help();
            throw std::invalid_argument("several identical arguments");
        }
    }
}
void check_error(int argc, char* argv[]) {
    // 1. проверка на типы работы
    try {
        type_work(argc, argv);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "--info.." << std::endl;
        std::cout << "--decrypt" << std::endl;
        std::cout << "--crypt" << std::endl;
    }
    // 2. проверка на bmp format
    try {
        check_format(argc, argv);
    } catch (std::exception& ex) {
        std::cout << "we catch " << ex.what() << std::endl;
    }
    // 3. проверка на аргументы
    try {
        check_arguments(argc, argv);
    } catch (std::exception& ex) {
        std::cout << "we catch " << ex.what() << std::endl;
    }
    // 4. ошибка если текст больше ,чем емкость изображения
}
#endif  // INCLUDE_EXCEPTION_HPP_

#include <bitset>
#include <iostream>
#include <string>

#include "exception.hpp"

typedef int FXPT2DOT30;
#pragma pack(1)

typedef struct {
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
} CIEXYZ;
#pragma pack(1)

typedef struct {
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;
#pragma pack(1)

typedef struct tagBITMAPFILEHEADER {
    int16_t bfType;
    unsigned int bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;
// bitmap info header v1
#pragma pack(1)

typedef struct tagBITMAPINFOHEADER {
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    int16_t biPlanes;
    int16_t biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    unsigned int biXPelsPerMeter;
    unsigned int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;
// v2
typedef struct tagBITMAPINFOHEADER2 {
    unsigned int biRedMask;
    unsigned int biGreenMask;
    unsigned int biBlueMask;
} BITMAPINFOHEADER2;
// v3
typedef struct {
    unsigned int biAlphaMask;
} BITMAPINFOHEADER3;
// v4
typedef struct {
    unsigned int biCSType;
    CIEXYZTRIPLE biEndpoints;
    unsigned int biGammaRed;
    unsigned int biGammaGreen;
    unsigned int biGammaBlue;
} BITMAPINFOHEADER4;
// v5
typedef struct {
    unsigned int biIntent;
    unsigned int biProfileData;
    unsigned int biProfileSize;
    unsigned int biReserved;
} BITMAPINFOHEADER5;
// rgb quad
#pragma pack(1)
typedef struct tagRGBQUAD {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
} RGBQUAD;

int main(int argc, char *argv[]) {
    // проверка на ошибки
    //функция лежит в expection.hpp
    check_error(argc, argv);
    std::string inputPATH, messagePATH, outputPATH;
    bool flag_crypt = false;
    bool flag_decrypt = false;
    bool flag_info = false;
    for (int i = 2; i < argc; ++i) {
        std::string type(argv[i]);
        if (type == "--crypt") flag_crypt = true;
        if (type == "--decrypt") flag_decrypt = true;
        if (type == "--info") flag_info = true;
    }
    for (int i = 2; i < argc; ++i) {
        std::string type(argv[i]);
        if (flag_crypt) {
            if (type == "--input") {
                inputPATH = argv[i + 1];
                // inputPATH="C:\\Users\\ndp20\\Downloads\\raduga.bmp";
                std::cout << inputPATH;
            }
            if (type == "--message") {
                messagePATH = argv[i + 1];
            }
            if (type == "--output") {
                outputPATH = argv[i + 1];
            }
        }
        if (flag_decrypt) {
            if (type == "--input") {
                inputPATH = argv[i + 1];
            }
            if (type == "--message") {
                messagePATH = argv[i + 1];
            }
        }
        if (flag_info) {
            if (type == "--input") {
                inputPATH = argv[i + 1];
            }
        }
    }
    if (flag_crypt) {
        FILE *image = fopen(inputPATH.c_str(), "rb");
        if (!image) {
            std::cout << "incorrect path to image" << std::endl;
            return 0;
        }
        FILE *text = fopen(messagePATH.c_str(), "rb");
        if (!text) {
            std::cout << "incorrect path to text" << std::endl;
            return 0;
        }
        // seek to end of file
        fseek(text, 0, SEEK_END);
        // get current file position which is end from seek
        size_t size1 = ftell(text);
        std::string ss;
        // allocate string space and set length
        ss.resize(size1);
        // go back to beginning of file for read
        rewind(text);
        // read 1*size bytes from sfile into ss
        fread(&ss[0], 1, size1, text);
        // close the file
        fclose(text);
        std::string ssbit;
        for (char s : ss) {
            std::bitset<CHAR_BIT> l(s);
            ssbit += l.to_string();
        }
        std::bitset<32> size_of_crypt_bit(ssbit.length());
        tagBITMAPFILEHEADER *file_header = new tagBITMAPFILEHEADER();
        fread(&file_header->bfType, sizeof(unsigned char), 2, image);
        fread(&file_header->bfSize, sizeof(unsigned char), 4, image);
        fread(&file_header->bfReserved1, sizeof(unsigned char), 2, image);
        fread(&file_header->bfReserved2, sizeof(unsigned char), 2, image);
        fread(&file_header->bfOffBits, sizeof(unsigned char), 4, image);
        //Считываю infoheader
        tagBITMAPINFOHEADER *file_infoheader = new tagBITMAPINFOHEADER();
        tagBITMAPINFOHEADER2 *file_infoheaderV2 = new tagBITMAPINFOHEADER2();
        BITMAPINFOHEADER3 *file_infoheaderV3 = new BITMAPINFOHEADER3();
        BITMAPINFOHEADER4 *file_infoheaderV4 = new BITMAPINFOHEADER4();
        BITMAPINFOHEADER5 *file_infoheaderV5 = new BITMAPINFOHEADER5();
        fread(&file_infoheader->biSize, sizeof(unsigned char), 4, image);
        if (file_infoheader->biSize >= 40) {
            fread(&file_infoheader->biWidth, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biHeight, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biPlanes, sizeof(unsigned char), 2, image);
            fread(&file_infoheader->biBitCount, sizeof(unsigned char), 2, image);
            fread(&file_infoheader->biCompression, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biSizeImage, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biXPelsPerMeter, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biYPelsPerMeter, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biClrUsed, sizeof(unsigned char), 4, image);
            fread(&file_infoheader->biClrImportant, sizeof(unsigned char), 4, image);
        }
        if (file_infoheader->biSize >= 52) {
            fread(&file_infoheaderV2->biRedMask, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV2->biGreenMask, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV2->biBlueMask, sizeof(unsigned char), 4, image);
        }
        if (file_infoheader->biSize >= 56) {
            fread(&file_infoheaderV3->biAlphaMask, sizeof(unsigned char), 4, image);
        }
        if (file_infoheader->biSize >= 108) {
            fread(&file_infoheaderV4->biCSType, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV4->biEndpoints, sizeof(CIEXYZTRIPLE), 1, image);
            fread(&file_infoheaderV4->biGammaRed, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV4->biGammaGreen, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV4->biGammaBlue, sizeof(unsigned char), 4, image);
        }
        if (file_infoheader->biSize >= 124) {
            fread(&file_infoheaderV5->biIntent, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV5->biProfileData, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV5->biProfileSize, sizeof(unsigned char), 4, image);
            fread(&file_infoheaderV5->biReserved, sizeof(unsigned char), 4, image);
        }

        if (file_infoheader->biSize < 52) {
            delete file_infoheaderV2;
            delete file_infoheaderV3;
            delete file_infoheaderV4;
            delete file_infoheaderV5;
        } else if (file_infoheader->biSize < 56) {
            delete file_infoheaderV3;
            delete file_infoheaderV4;
            delete file_infoheaderV5;
        } else if (file_infoheader->biSize < 104) {
            delete file_infoheaderV4;
            delete file_infoheaderV5;
        } else if (file_infoheader->biSize < 124) {
            delete file_infoheaderV5;
        }
        //Считываю пиксели
        size_t size =
                ceil(float(file_header->bfSize - 14 - file_infoheader->biSize) / 4);
        tagRGBQUAD *data = new tagRGBQUAD[size];
        if (size < ssbit.length()) {
            std::cout << "The input image is too small to hide the message"
                      << std::endl;
            return 0;
        }
        for (size_t i = 0; i < size; ++i) {
            fread(&data[i], sizeof(tagRGBQUAD), 1, image);
        }
        fclose(image);
        for (size_t i = 0; i < size_of_crypt_bit.size(); ++i) {
            data[i].rgbRed = data[i].rgbRed >> 1;
            data[i].rgbRed = data[i].rgbRed << 1;
            data[i].rgbRed = data[i].rgbRed | size_of_crypt_bit[i];
        }
        for (size_t i = size_of_crypt_bit.size();
             i < ssbit.length() + size_of_crypt_bit.size(); ++i) {
            data[i].rgbRed = data[i].rgbRed >> 1;
            data[i].rgbRed = data[i].rgbRed << 1;
            data[i].rgbRed = data[i].rgbRed | ssbit[i - size_of_crypt_bit.size()];
        }
        FILE *modified_image = fopen(outputPATH.c_str(), "wb");
        if (file_infoheader->biSize >= 40) {
            fwrite(file_header, sizeof(tagBITMAPFILEHEADER), 1, modified_image);
            fwrite(file_infoheader, sizeof(tagBITMAPINFOHEADER), 1, modified_image);
        }
        if (file_infoheader->biSize >= 52) {
            fwrite(file_infoheaderV2, sizeof(BITMAPINFOHEADER2), 1, modified_image);
        }
        if (file_infoheader->biSize >= 56) {
            fwrite(file_infoheaderV3, sizeof(BITMAPINFOHEADER3), 1, modified_image);
        }
        if (file_infoheader->biSize >= 108) {
            fwrite(file_infoheaderV4, sizeof(BITMAPINFOHEADER4), 1, modified_image);
        }
        if (file_infoheader->biSize >= 124) {
            fwrite(file_infoheaderV5, sizeof(BITMAPINFOHEADER5), 1, modified_image);
        }
        fwrite(data, sizeof(tagRGBQUAD), size, modified_image);
        fclose(modified_image);
    }
    if (flag_decrypt) {
        FILE *imagetodecrypt = fopen(inputPATH.c_str(), "rb");
        if (!imagetodecrypt) {
            std::cout << "incorrect path to image";
            return 0;
        }
        auto *file_header2 = new tagBITMAPFILEHEADER();
        auto *file_infoheader2V2 = new tagBITMAPINFOHEADER2();
        auto *file_infoheader2V3 = new BITMAPINFOHEADER3();
        auto *file_infoheader2V4 = new BITMAPINFOHEADER4();
        auto *file_infoheader2V5 = new BITMAPINFOHEADER5();
        // reading
        fread(&file_header2->bfType, sizeof(unsigned char), 2, imagetodecrypt);
        fread(&file_header2->bfSize, sizeof(unsigned char), 4, imagetodecrypt);
        fread(&file_header2->bfReserved1, sizeof(unsigned char), 2, imagetodecrypt);
        fread(&file_header2->bfReserved2, sizeof(unsigned char), 2, imagetodecrypt);
        fread(&file_header2->bfOffBits, sizeof(unsigned char), 4, imagetodecrypt);
        auto *file_infoheader2 = new tagBITMAPINFOHEADER();
        fread(&file_infoheader2->biSize, sizeof(unsigned char), 4, imagetodecrypt);
        if (file_infoheader2->biSize >= 40) {
            fread(&file_infoheader2->biWidth, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biHeight, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biPlanes, sizeof(unsigned char), 2,
                  imagetodecrypt);
            fread(&file_infoheader2->biBitCount, sizeof(unsigned char), 2,
                  imagetodecrypt);
            fread(&file_infoheader2->biCompression, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biSizeImage, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biXPelsPerMeter, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biYPelsPerMeter, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biClrUsed, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2->biClrImportant, sizeof(unsigned char), 4,
                  imagetodecrypt);
        }
        if (file_infoheader2->biSize >= 52) {
            fread(&file_infoheader2V2->biRedMask, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V2->biGreenMask, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V2->biBlueMask, sizeof(unsigned char), 4,
                  imagetodecrypt);
        }
        if (file_infoheader2->biSize >= 56) {
            fread(&file_infoheader2V3->biAlphaMask, sizeof(unsigned char), 4,
                  imagetodecrypt);
        }
        if (file_infoheader2->biSize >= 108) {
            fread(&file_infoheader2V4->biCSType, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V4->biEndpoints, sizeof(CIEXYZTRIPLE), 1,
                  imagetodecrypt);
            fread(&file_infoheader2V4->biGammaRed, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V4->biGammaGreen, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V4->biGammaBlue, sizeof(unsigned char), 4,
                  imagetodecrypt);
        }
        if (file_infoheader2->biSize >= 124) {
            fread(&file_infoheader2V5->biIntent, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V5->biProfileData, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V5->biProfileSize, sizeof(unsigned char), 4,
                  imagetodecrypt);
            fread(&file_infoheader2V5->biReserved, sizeof(unsigned char), 4,
                  imagetodecrypt);
        }

        if (file_infoheader2->biSize < 52) {
            delete file_infoheader2V2;
            delete file_infoheader2V3;
            delete file_infoheader2V4;
            delete file_infoheader2V5;
        } else if (file_infoheader2->biSize < 56) {
            delete file_infoheader2V3;
            delete file_infoheader2V4;
            delete file_infoheader2V5;
        } else if (file_infoheader2->biSize < 104) {
            delete file_infoheader2V4;
            delete file_infoheader2V5;
        } else if (file_infoheader2->biSize < 124) {
            delete file_infoheader2V5;
        }
        int size2 =
                ceil(float(file_header2->bfSize - 14 - file_infoheader2->biSize) / 4);
        auto *data2 = new tagRGBQUAD[size2];
        for (int i = 0; i < size2; ++i) {
            fread(&data2[i], sizeof(tagRGBQUAD), 1, imagetodecrypt);
        }
        // decrypting
        std::string size_decrypt_bit;
        for (int i = 0; i < 32; ++i) {
            size_decrypt_bit += std::to_string(data2[i].rgbRed & 1);
        }
        reverse(size_decrypt_bit.begin(), size_decrypt_bit.end());
        auto buf_for_decrypt =
                std::bitset<32>(size_decrypt_bit.c_str()).to_ullong();
        std::string decrypt_text_bit;
        for (size_t i = 32; i < 32 + buf_for_decrypt; ++i) {
            decrypt_text_bit += std::to_string(data2[i].rgbRed & 1);
        }
        std::string final;
        for (size_t i = 0; i < decrypt_text_bit.length();) {
            std::string buf;
            for (int j = 0; j < 8; ++j, ++i) {
                buf += decrypt_text_bit[i];
            }
            final += char(std::bitset<8>(buf.c_str()).to_ullong());
        }
        // writing
        FILE *final_text = fopen(messagePATH.c_str(), "wb");
        fwrite(final.c_str(), final.size(), 1, final_text);
    }
    if (flag_info) {
        FILE *image = fopen(inputPATH.c_str(), "rb");
        if (!image) {
            std::cout << "incorrect path to image";
            return 0;
        }
        tagBITMAPFILEHEADER *file_header = new tagBITMAPFILEHEADER();
        fread(&file_header->bfType, sizeof(unsigned char), 2, image);
        fread(&file_header->bfSize, sizeof(unsigned char), 4, image);
        fread(&file_header->bfReserved1, sizeof(unsigned char), 2, image);
        fread(&file_header->bfReserved2, sizeof(unsigned char), 2, image);
        fread(&file_header->bfOffBits, sizeof(unsigned char), 4, image);
        tagBITMAPINFOHEADER *file_infoheader = new tagBITMAPINFOHEADER();
        fread(&file_infoheader->biSize, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biWidth, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biHeight, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biPlanes, sizeof(unsigned char), 2, image);
        fread(&file_infoheader->biBitCount, sizeof(unsigned char), 2, image);
        fread(&file_infoheader->biCompression, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biSizeImage, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biXPelsPerMeter, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biYPelsPerMeter, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biClrUsed, sizeof(unsigned char), 4, image);
        fread(&file_infoheader->biClrImportant, sizeof(unsigned char), 4, image);
        std::cout << "Size: " << file_infoheader->biSize << std::endl
                  << "Height: " << file_infoheader->biHeight << std::endl
                  << "Width: " << file_infoheader->biWidth << std::endl
                  << "Planes: " << file_infoheader->biPlanes << std::endl
                  << "Bit Count: " << file_infoheader->biBitCount << std::endl
                  << "Compression: " << file_infoheader->biCompression << std::endl
                  << "Size Image: " << file_infoheader->biSizeImage << std::endl
                  << "X Pels Per Meter: " << file_infoheader->biXPelsPerMeter
                  << std::endl
                  << "Y Pels Per Meter: " << file_infoheader->biYPelsPerMeter
                  << std::endl
                  << "Clr Used: " << file_infoheader->biClrUsed << std::endl
                  << "Clr Important: " << file_infoheader->biClrImportant
                  << std::endl;
    }
}