//
// Created by Arthur Motelevicz on 10/12/23.
//

#include "TimeBasedStrategy.h"

namespace botb2 {
    TimeBasedStrategy::TimeBasedStrategy(const Interval& interval):
    TickProcessingStrategy(interval){}

    void TimeBasedStrategy::processTick(const TickData& tick) {

    }
}