//
// Created by Arthur Motelevicz on 10/12/23.
//

#include "PriceChangeBasedStrategy.h"

namespace botb2 {
    PriceChangeBasedStrategy::PriceChangeBasedStrategy(const Interval& interval):
    TickProcessingStrategy(interval){}
    void PriceChangeBasedStrategy::processTick(const TickData& tick) {

    }
}