//
// Created by Arthur Motelevicz on 08/12/23.
//

#ifndef MAGIATRADE_UTILS_H
#define MAGIATRADE_UTILS_H

#include <cstdlib>
#include <random>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <fmt/format.h>
#include <algorithm>

namespace botb2 {
    template <typename T>
    class TD;

    //1 - situation example
//    template <typename T>
//    void f(T& param){
//        //  std::cout << "Type: " << typeid(param).name() << "\n";
//        TD<T> pTypeType;
//        TD<decltype(param)> pType;
//    }

    namespace utils {

        namespace text{
            static void toLowerCase(std::string& str) {
                std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
            }

            static void toUpperCase(std::string& str) {
                std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::toupper(c); });
            }
        }
        namespace time {
            static uint64_t timeSinceEpochMillisec() {
                using namespace std::chrono;
                return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            }


            static tm getTimeStructFromTimestamp(uint64_t ms){
                uint64_t inSecs = ms / 1000;
                time_t aux = inSecs;
                return *std::localtime(&aux);;
            }


            static uint64_t getTimestampFromTimeStruct(tm timeInfo){
                uint64_t out =  mktime(&timeInfo)*1000;//timelocal(&timeInfo) * 1000;
                return out;
            }

//            static std::string timeSinceEpochMillisecFormated(){
//                auto ts = timeSinceEpochMillisec();
//                auto infoTime = getTimeStructFromTimestamp(ts);
//                std::string outTime = "";
//                outTime = fmt::format("{}-{}-{}",infoTime.tm_mon,infoTime.tm_mday,infoTime.tm_year + 1900);
//                return outTime;
//            }

            static std::string formattedTimeStamp(uint64_t ts){
                auto infoTime = getTimeStructFromTimestamp(ts);
                std::string outTime = "";
                outTime = fmt::format("{}/{}/{}",infoTime.tm_mon + 1,infoTime.tm_mday,infoTime.tm_year + 1900);
                return outTime;
            }

            static std::string formattedTimeStampMilis(uint64_t ts){
                auto infoTime = getTimeStructFromTimestamp(ts);
                std::string outTime = "";
                outTime = fmt::format("{}/{}/{} {}:{}:{}",infoTime.tm_mon + 1,infoTime.tm_mday,infoTime.tm_year + 1900, infoTime.tm_hour, infoTime.tm_min, infoTime.tm_sec);
                return outTime;
            }

        }

        namespace uuid {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, 15);
            static std::uniform_int_distribution<> dis2(8, 11);

            static std::string generate_uuid_v4() {
                std::stringstream ss;
                int i;
                ss << std::hex;
                for (i = 0; i < 8; i++) {
                    ss << dis(gen);
                }
                ss << "-";
                for (i = 0; i < 4; i++) {
                    ss << dis(gen);
                }
                ss << "-4";
                for (i = 0; i < 3; i++) {
                    ss << dis(gen);
                }
                ss << "-";
                ss << dis2(gen);
                for (i = 0; i < 3; i++) {
                    ss << dis(gen);
                }
                ss << "-";
                for (i = 0; i < 12; i++) {
                    ss << dis(gen);
                };
                return ss.str();
            }

            static std::string generate_short_id(int size) {
                const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                static std::random_device rd;
                static std::mt19937_64 mt(rd());
                std::uniform_int_distribution<> dist(0, alphabet.size() - 1);
                std::string id;
                for (int i = 0; i < size; ++i) {
                    id += alphabet[dist(mt)];
                }
                return id;
            }
        }


        namespace rand {
            inline static float randomNumber() {
                return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
            }
        }
    }//ultils namespace
}// botb namespace
#endif //MAGIATRADE_UTILS_H
