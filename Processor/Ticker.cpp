//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#include "Ticker.h"
#include "ITickable.h"
#include "TickProcessingStrategy.h"

#include "TimeBasedStrategy.h"
#include "TickBasedStrategy.h"
#include "PriceChangeBasedStrategy.h"

namespace botb2 {
    Ticker::Ticker(const Interval& interval) :
    _interval(interval)
    {
        _processorStrategy = loadProcessor();
        assert(_processorStrategy != nullptr);
    }

    Ticker::~Ticker() {}

    void Ticker::addTickable(const std::shared_ptr<ITickable>& tickable) {
        _tickables.insert(tickable);
    }

    void Ticker::removeTickable(const std::shared_ptr<ITickable>& tickable){
        _tickables.erase(tickable);
    }

    void Ticker::tick(const TickData &data) {
        _processorStrategy->processTick(data);
    }

    std::unique_ptr<TickProcessingStrategy>  Ticker::loadProcessor(){
        std::unique_ptr<TickProcessingStrategy> output{nullptr};
        if(isTickInterval(_interval))
            output = std::make_unique<TickBasedStrategy>(_interval);
        else if(isTimeInterval(_interval))
            output = std::make_unique<TimeBasedStrategy>(_interval);
        else if(isRenkoInterval(_interval))
            output = std::make_unique<PriceChangeBasedStrategy>(_interval);

        return std::move(output);
    }
}