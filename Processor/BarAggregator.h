//
// Created by Arthur Motelevicz on 09/12/23.
//

#ifndef BOTB2_BARAGGREGATOR_H
#define BOTB2_BARAGGREGATOR_H

#include "TickData.h"
#include "BarData.h"
#include "Interval.h"
#include <vector>

namespace botb2 {

    class BarAggregator {
    public:
        explicit BarAggregator(const Interval& interval);
        void addTick(const TickData& tick);
        BarData getBarData() const;
        void reset();

    private:
        Interval _interval;
        std::vector<TickData> _ticks;
    };

} // namespace botb2

#endif // BOTB2_BARAGGREGATOR_H
