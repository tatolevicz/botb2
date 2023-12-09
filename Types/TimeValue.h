//
// Created by Arthur Motelevicz on 09/12/23.
//

#ifndef BOTB2_TIMEVALUE_H
#define BOTB2_TIMEVALUE_H

#include <cinttypes>

namespace botb2 {
    struct TimeValue {
        double value = 0;
        uint64_t time = 0;

        TimeValue() = default;

        TimeValue(double val, uint64_t t) : value(val), time(t) {}

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
}

#endif //BOTB2_TIMEVALUE_H
