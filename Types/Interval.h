//
// Created by Arthur Motelevicz on 08/12/23.
//

#ifndef MAGIATRADE_INTERVAL_H
#define MAGIATRADE_INTERVAL_H

#include <cassert>

namespace botb2 {

    using longl = long long;

    struct TimeValue {
        double value;
        longl time;

        //the operators are needed for upper_bound and lower_bound operations
        bool operator==(TimeValue const &obj) const {
            return time == obj.time;
        }

        bool operator>=(TimeValue const &obj) const {
            return time >= obj.time;
        }

        bool operator>(TimeValue const &obj) const {
            return time > obj.time;
        }

        bool operator<=(TimeValue const &obj) const {
            return time <= obj.time;
        }

        bool operator<(TimeValue const &obj) const {
            return time < obj.time;
        }
    };

    struct TickData : public TimeValue {
        double volume;

        TickData() {
            volume = 0;
        }
    };

    struct BarData : public TickData {
    public:
        double open_time_ms = 0;
        double close_time_ms = 0;
        double open = 0;
        double high = 0;
        double low = 0;
        double close = 0;

        bool isEmpty() const {
            // Exemplo: considera a barra vazia se o tempo de abertura ainda é zero
            // Você pode ajustar esta lógica com base em como você inicializa uma nova BarData
            return open_time_ms == 0;
        }

        void clear() {
            open_time_ms = 0;
            close_time_ms = 0;
            open = 0;
            high = 0;
            low = 0;
            close = 0;
        };
    };

    enum class Interval {
        Interval_5_ticks,
        Interval_10_ticks,
        Interval_15_ticks,
        Interval_20_ticks,
        Interval_50_ticks,
        Interval_100_ticks,
        Interval_200_ticks,
        Interval_500_ticks,
        Interval_1000_ticks,
        Interval_5000_ticks,
        Interval_10000_ticks,
        Interval_1_Second,
        Interval_5_Seconds,
        Interval_10_Seconds,
        Interval_30_Seconds,
        Interval_1_Minute,
        Interval_3_Minutes,
        Interval_5_Minutes,
        Interval_15_Minutes,
        Interval_30_Minutes,
        Interval_1_Hour,
        Interval_2_Hours,
        Interval_4_Hours,
        Interval_6_Hours,
        Interval_8_Hours,
        Interval_12_Hours,
        Interval_1_Day,
        Interval_3_Days,
        Interval_1_Week,
        Interval_1_Month,
        Interval_Unknown,
    };

    inline static uint64_t toMs(const Interval &interval) {
        switch (interval) {
            case Interval::Interval_5_ticks:
            case Interval::Interval_10_ticks:
            case Interval::Interval_15_ticks:
            case Interval::Interval_20_ticks:
            case Interval::Interval_50_ticks:
            case Interval::Interval_100_ticks:
            case Interval::Interval_200_ticks:
            case Interval::Interval_500_ticks:
            case Interval::Interval_1000_ticks:
            case Interval::Interval_5000_ticks:
            case Interval::Interval_10000_ticks:
                assert(false && "There is no ms for ticks");
            case Interval::Interval_1_Second:
                return 1000;
            case Interval::Interval_5_Seconds:
                return 5 * 1000;
            case Interval::Interval_10_Seconds:
                return 10 * 1000;
            case Interval::Interval_30_Seconds:
                return 30 * 1000;
            case Interval::Interval_1_Minute:
                return 60000;
            case Interval::Interval_3_Minutes:
                return 3 * 60000;
            case Interval::Interval_5_Minutes:
                return 5 * 60000;
            case Interval::Interval_15_Minutes:
                return 15 * 60000;
            case Interval::Interval_30_Minutes:
                return 30 * 60000;
            case Interval::Interval_1_Hour:
                return 60 * 60000;
            case Interval::Interval_2_Hours:
                return 2 * 60 * 60000;
            case Interval::Interval_4_Hours:
                return 4 * 60 * 60000;
            case Interval::Interval_6_Hours:
                return 6 * 60 * 60000;
            case Interval::Interval_8_Hours:
                return 8 * 60 * 60000;
            case Interval::Interval_12_Hours:
                return 12 * 60 * 60000;
            case Interval::Interval_1_Day:
                return 24 * 60 * 60000;
            case Interval::Interval_3_Days:
                return static_cast<uint64_t>(3)  * 24 * 60 * 60000;
            case Interval::Interval_1_Week:
                return static_cast<uint64_t>(7)  * 24 * 60 * 60000;
            case Interval::Interval_1_Month:
                return static_cast<uint64_t>(30)  * 24 * 60 * 60000;
            case Interval::Interval_Unknown:
            default:
                assert(false && "Unknown interval");
        }
    }

    inline static longl toTicks(const Interval &interval) {
        switch (interval) {
            case Interval::Interval_5_ticks:
                return 5;
            case Interval::Interval_10_ticks:
                return 10;
            case Interval::Interval_15_ticks:
                return 15;
            case Interval::Interval_20_ticks:
                return 20;
            case Interval::Interval_50_ticks:
                return 50;
            case Interval::Interval_100_ticks:
                return 100;
            case Interval::Interval_200_ticks:
                return 200;
            case Interval::Interval_500_ticks:
                return 500;
            case Interval::Interval_1000_ticks:
                return 1000;
            case Interval::Interval_5000_ticks:
                return 5000;
            case Interval::Interval_10000_ticks:
                return 10000;
            case Interval::Interval_1_Second:
            case Interval::Interval_5_Seconds:
            case Interval::Interval_10_Seconds:
            case Interval::Interval_30_Seconds:
            case Interval::Interval_1_Minute:
            case Interval::Interval_3_Minutes:
            case Interval::Interval_5_Minutes:
            case Interval::Interval_15_Minutes:
            case Interval::Interval_30_Minutes:
            case Interval::Interval_1_Hour:
            case Interval::Interval_2_Hours:
            case Interval::Interval_4_Hours:
            case Interval::Interval_6_Hours:
            case Interval::Interval_8_Hours:
            case Interval::Interval_12_Hours:
            case Interval::Interval_1_Day:
            case Interval::Interval_3_Days:
            case Interval::Interval_1_Week:
            case Interval::Interval_1_Month:
            case Interval::Interval_Unknown:
                assert(false && "There is no ticks for ms");
            default:
                assert(false && "Unknown interval");
        }
    }

    inline static bool isTickInterval(const Interval &interval) {
        switch (interval) {
            case Interval::Interval_5_ticks:
            case Interval::Interval_10_ticks:
            case Interval::Interval_15_ticks:
            case Interval::Interval_20_ticks:
            case Interval::Interval_50_ticks:
            case Interval::Interval_100_ticks:
            case Interval::Interval_200_ticks:
            case Interval::Interval_500_ticks:
            case Interval::Interval_1000_ticks:
            case Interval::Interval_5000_ticks:
            case Interval::Interval_10000_ticks:
                return true;
            case Interval::Interval_1_Second:
            case Interval::Interval_5_Seconds:
            case Interval::Interval_10_Seconds:
            case Interval::Interval_30_Seconds:
            case Interval::Interval_1_Minute:
            case Interval::Interval_3_Minutes:
            case Interval::Interval_5_Minutes:
            case Interval::Interval_15_Minutes:
            case Interval::Interval_30_Minutes:
            case Interval::Interval_1_Hour:
            case Interval::Interval_2_Hours:
            case Interval::Interval_4_Hours:
            case Interval::Interval_6_Hours:
            case Interval::Interval_8_Hours:
            case Interval::Interval_12_Hours:
            case Interval::Interval_1_Day:
            case Interval::Interval_3_Days:
            case Interval::Interval_1_Week:
            case Interval::Interval_1_Month:
            case Interval::Interval_Unknown:
                return false;
            default:
                assert(false && "Unknown interval");
        }
    }
}
#endif //MAGIATRADE_INTERVAL_H