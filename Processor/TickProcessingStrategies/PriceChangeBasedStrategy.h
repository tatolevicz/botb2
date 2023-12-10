//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_PRICECHANGEBASEDSTRATEGY_H
#define BOTB2_PRICECHANGEBASEDSTRATEGY_H

#include "TickProcessingStrategy.h"

namespace botb2{
    class PriceChangeBasedStrategy : public TickProcessingStrategy {
    public:
        PriceChangeBasedStrategy(const Interval& interval);
        void processTick(const TickData& tick,Ticker* ticker) override;
    };

}

#endif //BOTB2_PRICECHANGEBASEDSTRATEGY_H
