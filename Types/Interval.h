//
// Created by Arthur Motelevicz on 08/12/23.
//

#ifndef MAGIATRADE_INTERVAL_H
#define MAGIATRADE_INTERVAL_H

#include <optional>
#include <iostream>

namespace botb2 {

    constexpr char UnknownIntervalErrorMsg[] = "Unknown interval\n";
    constexpr char ConversionNotPossibleErrorMsg[] = "Conversion not possible!\n";

    constexpr uint64_t MillisecondsPerSecond = 1000ull;
    constexpr uint64_t MillisecondsPerMinute = 60 * MillisecondsPerSecond;
    constexpr uint64_t MillisecondsPerHour = 60 * MillisecondsPerMinute;
    constexpr uint64_t MillisecondsPerDay = 24 * MillisecondsPerHour;

    enum class Interval {
        Renko_00001_Percent, //-> 0.0001 %
        Renko_00005_Percent,
        Renko_0001_Percent,
        Renko_0005_Percent,
        Renko_001_Percent,
        Renko_005_Percent,
        Renko_01_Percent,
        Renko_05_Percent,
        Renko_1_Percent,
        Renko_2_Percent,
        Renko_3_Percent,
        Renko_5_Percent,
        Renko_10_Percent,
        Renko_20_Percent,
        Renko_30_Percent,
        FiveTicks,
        TenTicks,
        FifteenTicks,
        TwentyTicks,
        FiftyTicks,
        HundredTicks,
        TwoHundredTicks,
        FiveHundredTicks,
        ThousandTicks,
        FiveThousandTicks,
        TenThousandTicks,
        OneSecond,
        FiveSeconds,
        TenSeconds,
        ThirtySeconds,
        OneMinute,
        ThreeMinutes,
        FiveMinutes,
        FifteenMinutes,
        ThirtyMinutes,
        OneHour,
        TwoHours,
        FourHours,
        SixHours,
        EightHours,
        TwelveHours,
        OneDay,
        ThreeDays,
        OneWeek,
        OneMonth,
        Unknown,
    };

    inline static std::optional<uint64_t> toMilliseconds(const Interval &interval) {
        switch (interval) {
            case Interval::Renko_00001_Percent:
            case Interval::Renko_00005_Percent:
            case Interval::Renko_0001_Percent:
            case Interval::Renko_0005_Percent:
            case Interval::Renko_001_Percent:
            case Interval::Renko_005_Percent:
            case Interval::Renko_01_Percent:
            case Interval::Renko_05_Percent:
            case Interval::Renko_1_Percent:
            case Interval::Renko_2_Percent:
            case Interval::Renko_3_Percent:
            case Interval::Renko_5_Percent:
            case Interval::Renko_10_Percent:
            case Interval::Renko_20_Percent:
            case Interval::Renko_30_Percent:
            case Interval::FiveTicks:
            case Interval::TenTicks:
            case Interval::FifteenTicks:
            case Interval::TwentyTicks:
            case Interval::FiftyTicks:
            case Interval::HundredTicks:
            case Interval::TwoHundredTicks:
            case Interval::FiveHundredTicks:
            case Interval::ThousandTicks:
            case Interval::FiveThousandTicks:
            case Interval::TenThousandTicks: {
                std::cerr << ConversionNotPossibleErrorMsg;
                return std::nullopt;
            }
            case Interval::OneSecond:
                return MillisecondsPerSecond;
            case Interval::FiveSeconds:
                return 5 * MillisecondsPerSecond;
            case Interval::TenSeconds:
                return 10 * MillisecondsPerSecond;
            case Interval::ThirtySeconds:
                return 30 * MillisecondsPerSecond;
            case Interval::OneMinute:
                return MillisecondsPerMinute;
            case Interval::ThreeMinutes:
                return 3 * MillisecondsPerMinute;
            case Interval::FiveMinutes:
                return 5 * MillisecondsPerMinute;
            case Interval::FifteenMinutes:
                return 15 * MillisecondsPerMinute;
            case Interval::ThirtyMinutes:
                return 30 * MillisecondsPerMinute;
            case Interval::OneHour:
                return MillisecondsPerHour;
            case Interval::TwoHours:
                return 2 * MillisecondsPerHour;
            case Interval::FourHours:
                return 4 *MillisecondsPerHour;
            case Interval::SixHours:
                return 6 * MillisecondsPerHour;
            case Interval::EightHours:
                return 8 * MillisecondsPerHour;
            case Interval::TwelveHours:
                return 12 * MillisecondsPerHour;
            case Interval::OneDay:
                return MillisecondsPerDay;
            case Interval::ThreeDays:
                return 3  * MillisecondsPerDay;
            case Interval::OneWeek:
                return 7 * MillisecondsPerDay;
            case Interval::OneMonth:
                return 30  * MillisecondsPerDay;
            case Interval::Unknown:
            default: {
                std::cerr << UnknownIntervalErrorMsg;
                return std::nullopt;
            }
        }
    }

    inline static std::optional<uint64_t> toTicks(const Interval &interval) {
        switch (interval) {
            case Interval::FiveTicks:
                return 5;
            case Interval::TenTicks:
                return 10;
            case Interval::FifteenTicks:
                return 15;
            case Interval::TwentyTicks:
                return 20;
            case Interval::FiftyTicks:
                return 50;
            case Interval::HundredTicks:
                return 100;
            case Interval::TwoHundredTicks:
                return 200;
            case Interval::FiveHundredTicks:
                return 500;
            case Interval::ThousandTicks:
                return 1000;
            case Interval::FiveThousandTicks:
                return 5000;
            case Interval::TenThousandTicks:
                return 10000;
            case Interval::Renko_00001_Percent:
            case Interval::Renko_00005_Percent:
            case Interval::Renko_0001_Percent:
            case Interval::Renko_0005_Percent:
            case Interval::Renko_001_Percent:
            case Interval::Renko_005_Percent:
            case Interval::Renko_01_Percent:
            case Interval::Renko_05_Percent:
            case Interval::Renko_1_Percent:
            case Interval::Renko_2_Percent:
            case Interval::Renko_3_Percent:
            case Interval::Renko_5_Percent:
            case Interval::Renko_10_Percent:
            case Interval::Renko_20_Percent:
            case Interval::Renko_30_Percent:
            case Interval::OneSecond:
            case Interval::FiveSeconds:
            case Interval::TenSeconds:
            case Interval::ThirtySeconds:
            case Interval::OneMinute:
            case Interval::ThreeMinutes:
            case Interval::FiveMinutes:
            case Interval::FifteenMinutes:
            case Interval::ThirtyMinutes:
            case Interval::OneHour:
            case Interval::TwoHours:
            case Interval::FourHours:
            case Interval::SixHours:
            case Interval::EightHours:
            case Interval::TwelveHours:
            case Interval::OneDay:
            case Interval::ThreeDays:
            case Interval::OneWeek:
            case Interval::OneMonth:{
                std::cerr << ConversionNotPossibleErrorMsg;
                return std::nullopt;
            }
            case Interval::Unknown:
            default: {
                std::cerr << UnknownIntervalErrorMsg;
                return std::nullopt;
            }
        }
    }


    inline static std::optional<double> toPercent(const Interval &interval) {
        switch (interval) {
            case Interval::FiveTicks:
            case Interval::TenTicks:
            case Interval::FifteenTicks:
            case Interval::TwentyTicks:
            case Interval::FiftyTicks:
            case Interval::HundredTicks:
            case Interval::TwoHundredTicks:
            case Interval::FiveHundredTicks:
            case Interval::ThousandTicks:
            case Interval::FiveThousandTicks:
            case Interval::TenThousandTicks:{
                std::cerr << ConversionNotPossibleErrorMsg;
                return std::nullopt;
            }
            case Interval::Renko_00001_Percent: return 0.000001;
            case Interval::Renko_00005_Percent: return 0.000005;
            case Interval::Renko_0001_Percent:  return 0.00001;
            case Interval::Renko_0005_Percent:  return 0.00005;
            case Interval::Renko_001_Percent:   return 0.0001;
            case Interval::Renko_005_Percent:   return 0.0005;
            case Interval::Renko_01_Percent:    return 0.001;
            case Interval::Renko_05_Percent:    return 0.005;
            case Interval::Renko_1_Percent:     return 0.01;
            case Interval::Renko_2_Percent:     return 0.02;
            case Interval::Renko_3_Percent:     return 0.03;
            case Interval::Renko_5_Percent:     return 0.05;
            case Interval::Renko_10_Percent:    return 0.1;
            case Interval::Renko_20_Percent:    return 0.2;
            case Interval::Renko_30_Percent:    return 0.3;
            case Interval::OneSecond:
            case Interval::FiveSeconds:
            case Interval::TenSeconds:
            case Interval::ThirtySeconds:
            case Interval::OneMinute:
            case Interval::ThreeMinutes:
            case Interval::FiveMinutes:
            case Interval::FifteenMinutes:
            case Interval::ThirtyMinutes:
            case Interval::OneHour:
            case Interval::TwoHours:
            case Interval::FourHours:
            case Interval::SixHours:
            case Interval::EightHours:
            case Interval::TwelveHours:
            case Interval::OneDay:
            case Interval::ThreeDays:
            case Interval::OneWeek:
            case Interval::OneMonth:{
                std::cerr << ConversionNotPossibleErrorMsg;
                return std::nullopt;
            }
            case Interval::Unknown:
            default: {
                std::cerr << UnknownIntervalErrorMsg;
                return std::nullopt;
            }
        }
    }

    inline static bool isTickInterval(const Interval &interval) {
        switch (interval) {
            case Interval::FiveTicks:
            case Interval::TenTicks:
            case Interval::FifteenTicks:
            case Interval::TwentyTicks:
            case Interval::FiftyTicks:
            case Interval::HundredTicks:
            case Interval::TwoHundredTicks:
            case Interval::FiveHundredTicks:
            case Interval::ThousandTicks:
            case Interval::FiveThousandTicks:
            case Interval::TenThousandTicks:
                return true;
            case Interval::Renko_00001_Percent:
            case Interval::Renko_00005_Percent:
            case Interval::Renko_0001_Percent:
            case Interval::Renko_0005_Percent:
            case Interval::Renko_001_Percent:
            case Interval::Renko_005_Percent:
            case Interval::Renko_01_Percent:
            case Interval::Renko_05_Percent:
            case Interval::Renko_1_Percent:
            case Interval::Renko_2_Percent:
            case Interval::Renko_3_Percent:
            case Interval::Renko_5_Percent:
            case Interval::Renko_10_Percent:
            case Interval::Renko_20_Percent:
            case Interval::Renko_30_Percent:
            case Interval::OneSecond:
            case Interval::FiveSeconds:
            case Interval::TenSeconds:
            case Interval::ThirtySeconds:
            case Interval::OneMinute:
            case Interval::ThreeMinutes:
            case Interval::FiveMinutes:
            case Interval::FifteenMinutes:
            case Interval::ThirtyMinutes:
            case Interval::OneHour:
            case Interval::TwoHours:
            case Interval::FourHours:
            case Interval::SixHours:
            case Interval::EightHours:
            case Interval::TwelveHours:
            case Interval::OneDay:
            case Interval::ThreeDays:
            case Interval::OneWeek:
            case Interval::OneMonth:{
                return false;
            }
            case Interval::Unknown:
            default:
                std::cerr << UnknownIntervalErrorMsg;
                return false;
        }
    }

    inline static bool isTimeInterval(const Interval &interval) {
        switch (interval) {
            case Interval::Renko_00001_Percent:
            case Interval::Renko_00005_Percent:
            case Interval::Renko_0001_Percent:
            case Interval::Renko_0005_Percent:
            case Interval::Renko_001_Percent:
            case Interval::Renko_005_Percent:
            case Interval::Renko_01_Percent:
            case Interval::Renko_05_Percent:
            case Interval::Renko_1_Percent:
            case Interval::Renko_2_Percent:
            case Interval::Renko_3_Percent:
            case Interval::Renko_5_Percent:
            case Interval::Renko_10_Percent:
            case Interval::Renko_20_Percent:
            case Interval::Renko_30_Percent:
            case Interval::FiveTicks:
            case Interval::TenTicks:
            case Interval::FifteenTicks:
            case Interval::TwentyTicks:
            case Interval::FiftyTicks:
            case Interval::HundredTicks:
            case Interval::TwoHundredTicks:
            case Interval::FiveHundredTicks:
            case Interval::ThousandTicks:
            case Interval::FiveThousandTicks:
            case Interval::TenThousandTicks:
                return false;
            case Interval::OneSecond:
            case Interval::FiveSeconds:
            case Interval::TenSeconds:
            case Interval::ThirtySeconds:
            case Interval::OneMinute:
            case Interval::ThreeMinutes:
            case Interval::FiveMinutes:
            case Interval::FifteenMinutes:
            case Interval::ThirtyMinutes:
            case Interval::OneHour:
            case Interval::TwoHours:
            case Interval::FourHours:
            case Interval::SixHours:
            case Interval::EightHours:
            case Interval::TwelveHours:
            case Interval::OneDay:
            case Interval::ThreeDays:
            case Interval::OneWeek:
            case Interval::OneMonth:{
                return true;
            }
            case Interval::Unknown:
            default:
                std::cerr << UnknownIntervalErrorMsg;
                return false;
        }
    }

    inline static bool isRenkoInterval(const Interval &interval) {
        switch (interval) {
            case Interval::Renko_00001_Percent:
            case Interval::Renko_00005_Percent:
            case Interval::Renko_0001_Percent:
            case Interval::Renko_0005_Percent:
            case Interval::Renko_001_Percent:
            case Interval::Renko_005_Percent:
            case Interval::Renko_01_Percent:
            case Interval::Renko_05_Percent:
            case Interval::Renko_1_Percent:
            case Interval::Renko_2_Percent:
            case Interval::Renko_3_Percent:
            case Interval::Renko_5_Percent:
            case Interval::Renko_10_Percent:
            case Interval::Renko_20_Percent:
            case Interval::Renko_30_Percent:
                return true;
            case Interval::FiveTicks:
            case Interval::TenTicks:
            case Interval::FifteenTicks:
            case Interval::TwentyTicks:
            case Interval::FiftyTicks:
            case Interval::HundredTicks:
            case Interval::TwoHundredTicks:
            case Interval::FiveHundredTicks:
            case Interval::ThousandTicks:
            case Interval::FiveThousandTicks:
            case Interval::TenThousandTicks:
            case Interval::OneSecond:
            case Interval::FiveSeconds:
            case Interval::TenSeconds:
            case Interval::ThirtySeconds:
            case Interval::OneMinute:
            case Interval::ThreeMinutes:
            case Interval::FiveMinutes:
            case Interval::FifteenMinutes:
            case Interval::ThirtyMinutes:
            case Interval::OneHour:
            case Interval::TwoHours:
            case Interval::FourHours:
            case Interval::SixHours:
            case Interval::EightHours:
            case Interval::TwelveHours:
            case Interval::OneDay:
            case Interval::ThreeDays:
            case Interval::OneWeek:
            case Interval::OneMonth:{
                return false;
            }
            case Interval::Unknown:
            default:
                std::cerr << UnknownIntervalErrorMsg;
                return false;
        }
    }
}
#endif //MAGIATRADE_INTERVAL_H