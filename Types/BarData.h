//
// Created by Arthur Motelevicz on 09/12/23.
//

#ifndef BOTB2_BARDATA_H
#define BOTB2_BARDATA_H

#include "TimeValue.h"

namespace botb2{
    struct BarData : TimeValue{
    public:
        uint64_t openTime = 0; //ms
        uint64_t closeTime = 0; //ms
        double open = 0;
        double high = 0;
        double low = 0;
        double close = 0;
        double volume = 0;

        BarData() = default;

        BarData(uint64_t ot, uint64_t ct, double o, double h, double l, double c, double vol): TimeValue(c, ct),
        openTime(ot),
        closeTime(ct),
        open(o),
        high(h),
        low(l),
        close(c),
        volume(vol)
        {};

        bool isEmpty() const {
            return openTime == 0;
        }

        void clear() {
            openTime = 0;
            closeTime = 0;
            open = 0;
            high = 0;
            low = 0;
            close = 0;
            volume = 0;
        };
    };
}
#endif //BOTB2_BARDATA_H
