//
// Created by Arthur Motelevicz on 10/12/23.
//

#include "TickBasedStrategy.h"

namespace botb2 {
    TickBasedStrategy::TickBasedStrategy(const Interval& interval):
    TickProcessingStrategy(interval){}

    void TickBasedStrategy::processTick(const TickData& tick,Ticker* ticker) {

    }
}