//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_TICKPROCESSINGSTRATEGY_H
#define BOTB2_TICKPROCESSINGSTRATEGY_H

#include "TickData.h"
#include "Interval.h"
#include "BarAggregator.h"
#include "Ticker.h"

namespace botb2{

    class TickProcessingStrategy {
    public:
        explicit TickProcessingStrategy(const Interval& interval):
        _interval(interval){
            _aggregator = std::make_unique<BarAggregator>();
        }

        virtual void processTick(const TickData& tick, Ticker* ticker) {};

    protected:
        Interval _interval;
        std::unique_ptr<BarAggregator> _aggregator{nullptr};
    };
}
#endif //BOTB2_TICKPROCESSINGSTRATEGY_H
