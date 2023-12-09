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
        explicit BarAggregator();
        void addTick(const TickData& tick);
        BarData getBarData() const;
        void reset();

    private:
        void updateCurrentBar(const TickData& tick);
        void resetBar();
        BarData _currentBar;
        bool _isNewBar;
    };

} // namespace botb2

#endif // BOTB2_BARAGGREGATOR_H
