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
        void processTick(const TickData& tick,Ticker* ticker) override;\
    private:
        void closesBar(double closePrice, Ticker* ticker);
        uint64_t _lastTime{0};
        double _priceChangeThreshold{0};
        double _lastPrice{0};
        double _excessPrice{0};
    };

}

#endif //BOTB2_PRICECHANGEBASEDSTRATEGY_H
