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
}
#endif //MAGIATRADE_INTERVAL_H