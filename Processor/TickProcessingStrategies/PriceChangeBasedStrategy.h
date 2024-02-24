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
    private:
        void recursiveProcessTick(const TickData& tick,Ticker* ticker,double priceChangePercent, bool isInternalCall = false);

        void closesBar(const TickData& tick);
        void opensBar(const TickData& tick);
        void ticksBar(const TickData& tick);

        void notifyOnOpen   (Ticker* ticker);
        void notifyOnClose  (Ticker* ticker);
        void notifyOnTick   (const TickData& tick, Ticker* ticker);

        BarData _currentBar;
        uint64_t _lastTime{0};
        double _percentChangeThreshold{0};
        double _lastPrice{0};
//        double _excessDeltaPercent{0};
    };

}

#endif //BOTB2_PRICECHANGEBASEDSTRATEGY_H
