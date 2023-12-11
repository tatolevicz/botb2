//
// Created by Arthur Motelevicz on 10/12/23.
//

#include "TimeBasedStrategy.h"
#include "Ticker.h"
#include "ITickable.h"

namespace botb2 {
    TimeBasedStrategy::TimeBasedStrategy(const Interval& interval):
    TickProcessingStrategy(interval){
        auto timeResult =  toMilliseconds(_interval);
        if(timeResult.has_value())
            _intervalTime = timeResult.value();
        else
            assert(false && "Error getting time result!");//TODO:: log
    }

    void TimeBasedStrategy::processTick(const TickData& tick, Ticker* ticker) {

        //ignores some wrong tick
        if(tick.time < _lastTime)
            return;//TODO:: log

        if(_lastTime == 0) { // Tratamento para o primeiro tick
            // Ajustar _lastTime para o início do intervalo atual
            uint64_t intervalRemainder = tick.time % _intervalTime;
            _lastTime = tick.time - intervalRemainder;
        }

        auto dt = tick.time - _lastTime;

        //is it time time to close the bar?
        if(dt >= _intervalTime){

            //get the last bar completed
            auto barData = _aggregator->getBarData();

            //call onClose on tickables
            for(auto &t : ticker->getTickables()){
                t->onClose(barData);
            }

            //reset bar to open a new one in the next tick
            _aggregator->reset();
            _lastTime = tick.time;
        }

        //save the status of aggregator before tick it again
        auto isNewBar = _aggregator->isNewBar();

        //now tick the aggregator and all the tickables onTick
        _aggregator->addTick(tick);

        auto barData = _aggregator->getBarData();

        for(auto &t : ticker->getTickables()){
            t->onTick(barData);
        }

        //now trigger the onOpen if it's a new bar
        if(isNewBar){
            for(auto &t : ticker->getTickables()){
                t->onOpen(barData);
            }
        }
    }
}