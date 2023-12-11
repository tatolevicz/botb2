//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_TICKBASEDSTRATEGY_H
#define BOTB2_TICKBASEDSTRATEGY_H
#include "TickProcessingStrategy.h"

namespace botb2{
    class TickBasedStrategy : public TickProcessingStrategy {
    public:
        TickBasedStrategy(const Interval& interval);
        void processTick(const TickData& tick,Ticker* ticker) override;

    private:
        uint64_t _lastTime{0};
        uint64_t _intervalTicks{0};
        uint64_t _ticksCounter{0};
    };

}
#endif //BOTB2_TICKBASEDSTRATEGY_H
