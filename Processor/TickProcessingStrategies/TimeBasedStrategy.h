//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_TIMEBASEDSTRATEGY_H
#define BOTB2_TIMEBASEDSTRATEGY_H

#include "TickProcessingStrategy.h"

namespace botb2{
    class TimeBasedStrategy : public TickProcessingStrategy {
    public:
        TimeBasedStrategy(const Interval& interval);
        void processTick(const TickData& tick) override;
    };

}
#endif //BOTB2_TIMEBASEDSTRATEGY_H
