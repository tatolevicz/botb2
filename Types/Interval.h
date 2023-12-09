//
// Created by Arthur Motelevicz on 08/12/23.
//

#ifndef MAGIATRADE_INTERVAL_H
#define MAGIATRADE_INTERVAL_H

#include <cassert>

namespace botb2 {
    
    
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

    inline static uint64_t toMilliseconds(const Interval &interval) {
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
                assert(false && "There is no ms for ticks");
            case Interval::OneSecond:
                return 1000;
            case Interval::FiveSeconds:
                return 5 * 1000;
            case Interval::TenSeconds:
                return 10 * 1000;
            case Interval::ThirtySeconds:
                return 30 * 1000;
            case Interval::OneMinute:
                return 60000;
            case Interval::ThreeMinutes:
                return 3 * 60000;
            case Interval::FiveMinutes:
                return 5 * 60000;
            case Interval::FifteenMinutes:
                return 15 * 60000;
            case Interval::ThirtyMinutes:
                return 30 * 60000;
            case Interval::OneHour:
                return 60 * 60000;
            case Interval::TwoHours:
                return 2 * 60 * 60000;
            case Interval::FourHours:
                return 4 * 60 * 60000;
            case Interval::SixHours:
                return 6 * 60 * 60000;
            case Interval::EightHours:
                return 8 * 60 * 60000;
            case Interval::TwelveHours:
                return 12 * 60 * 60000;
            case Interval::OneDay:
                return 24 * 60 * 60000;
            case Interval::ThreeDays:
                return static_cast<uint64_t>(3)  * 24 * 60 * 60000;
            case Interval::OneWeek:
                return static_cast<uint64_t>(7)  * 24 * 60 * 60000;
            case Interval::OneMonth:
                return static_cast<uint64_t>(30)  * 24 * 60 * 60000;
            case Interval::Unknown:
            default:
                assert(false && "Unknown interval");
        }
    }

    inline static uint64_t toTicks(const Interval &interval) {
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
            case Interval::OneMonth:
            case Interval::Unknown:
                assert(false && "There is no ticks for ms");
            default:
                assert(false && "Unknown interval");
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
            case Interval::OneMonth:
            case Interval::Unknown:
                return false;
            default:
                assert(false && "Unknown interval");
        }
    }
}
#endif //MAGIATRADE_INTERVAL_H