//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_TICKPROCESSINGSTRATEGY_H
#define BOTB2_TICKPROCESSINGSTRATEGY_H

#include "TickData.h"
#include "Interval.h"

namespace botb2{
    class TickProcessingStrategy {
    public:
        explicit TickProcessingStrategy(const Interval& interval):
        _interval(interval){}

        virtual void processTick(const TickData& tick) {};

    protected:
        Interval _interval;
    };
}
#endif //BOTB2_TICKPROCESSINGSTRATEGY_H
