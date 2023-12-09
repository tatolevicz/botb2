//
// Created by Arthur Motelevicz on 09/12/23.
//

#ifndef BOTB2_TICKDATA_H
#define BOTB2_TICKDATA_H

#include "TimeValue.h"

namespace botb2 {
    struct TickData : public TimeValue {
        double volume = 0;
        TickData() = default;
        TickData(double val, uint64_t t, double vol): TimeValue(val, t),volume(vol){}
    };
}
#endif //BOTB2_TICKDATA_H
