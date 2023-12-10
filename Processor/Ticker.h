//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#ifndef BOTB2_TICKER_H
#define BOTB2_TICKER_H

#include <unordered_set>
#include <memory>

#include "Interval.h"

namespace botb2 {

    class Tickable;
    class TickData;
    class TickProcessingStrategy;

    class Ticker {
    public:
        Ticker(const Interval& interval);

        virtual ~Ticker();
        void addTickable(const std::shared_ptr<Tickable>& tickable);
        void removeTickable(const std::shared_ptr<Tickable>& tickable);
        void tick(const TickData &data);
    private:
        std::unique_ptr<TickProcessingStrategy> loadProcessor();
        std::unordered_set<std::shared_ptr<Tickable>> _tickables;
        Interval _interval;
        std::unique_ptr<TickProcessingStrategy> _processorStrategy;
    };
}
#endif //BOTB2_TICKER_H
