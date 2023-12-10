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
        void processTick(const TickData& tick,Ticker* ticker) override;

    private:
        uint64_t _lastTime{0};
        uint64_t _intervalTime{0};
    };

}
#endif //BOTB2_TIMEBASEDSTRATEGY_H
