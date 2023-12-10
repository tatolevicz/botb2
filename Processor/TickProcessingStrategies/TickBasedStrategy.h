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
    };

}
#endif //BOTB2_TICKBASEDSTRATEGY_H
