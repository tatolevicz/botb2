//
// Created by Arthur Motelevicz on 10/12/23.
//

#include "PriceChangeBasedStrategy.h"
#include "Ticker.h"
#include "ITickable.h"

namespace botb2 {
    PriceChangeBasedStrategy::PriceChangeBasedStrategy(const Interval& interval) :
    TickProcessingStrategy(interval), _lastPrice(0)
    {
        auto percentResult = toPercent(_interval);
        if (percentResult.has_value())
            _percentChangeThreshold = percentResult.value();
        else
            assert(false && "Error getting percent result!"); // TODO: log
    }

    void PriceChangeBasedStrategy::recursiveProcessTick(const TickData& tick,Ticker* ticker, double priceChangePercent, bool isInternalCall){

        if (priceChangePercent >= _percentChangeThreshold) {

            auto directionSignal =  (tick.value > _lastPrice ? 1 : -1);

            double thresholdPrice = _lastPrice * (1 + _percentChangeThreshold * directionSignal);

            auto deltaPercent = _percentChangeThreshold/priceChangePercent;

            TickData closingTick;
            closingTick.volume =  deltaPercent * tick.volume;
            closingTick.value = thresholdPrice;
            closingTick.time = tick.time;

            closesBar(closingTick);

            _lastPrice = thresholdPrice;

            TickData recursiveTick;
            recursiveTick.volume = (1 - deltaPercent) * tick.volume;
            recursiveTick.value = tick.value;
            recursiveTick.time = tick.time;

            //before process the tick again check if it is already bigger than the threshold to open the next bar already
            double newPriceChangePercent = std::abs((tick.value - _lastPrice) / _lastPrice);
            if (newPriceChangePercent >= _percentChangeThreshold) {
                TickData openingTick;
                openingTick.volume = 0;
                openingTick.value = _lastPrice;
                openingTick.time = tick.time;
                opensBar(openingTick);
            }

            recursiveProcessTick(recursiveTick, ticker, newPriceChangePercent, true);
        }
    }

    void PriceChangeBasedStrategy::processTick(const TickData& tick, Ticker* ticker) {

        //ignores some wrong tick
        if(tick.time < _lastTime)
            return;//TODO:: log

        if (_lastTime == 0) {
            _lastPrice = tick.value;
            _lastTime = tick.time;

            TickData openingTick;
            openingTick.volume = tick.volume;
            openingTick.value = _lastPrice;
            openingTick.time = _lastTime;
            opensBar(openingTick);

            notifyOnTick(tick, ticker);
            notifyOnOpen(ticker);
            return;
        }

        double priceChangePercent = std::abs((tick.value - _lastPrice) / _lastPrice);

        if (priceChangePercent < _percentChangeThreshold) {
            ticksBar(tick);
            notifyOnTick(tick, ticker);
            _lastPrice = tick.value;
            return;
        }

        recursiveProcessTick(tick, ticker, priceChangePercent);

    }

    void PriceChangeBasedStrategy::notifyOnOpen(Ticker *ticker) {
        for (auto &t : ticker->getTickables()) {
            t->onOpen(_currentBar);
        }
    }

    void PriceChangeBasedStrategy::notifyOnClose(Ticker *ticker) {
        for (auto &t : ticker->getTickables()) {
            t->onClose(_currentBar);
        }
    }

    void PriceChangeBasedStrategy::notifyOnTick(const TickData &tick, Ticker *ticker) {
        for(auto &t : ticker->getTickables()){
            t->onTick(tick, _currentBar);
        }
    }

    void PriceChangeBasedStrategy::closesBar(const TickData& tick) {
        _aggregator->addTick(tick);
        _currentBar = _aggregator->getBarData();
        _aggregator->reset();
    }

    void PriceChangeBasedStrategy::opensBar(const TickData& tick) {
        _aggregator->reset();
        _aggregator->addTick(tick);
        _currentBar = _aggregator->getBarData();
    }

    void PriceChangeBasedStrategy::ticksBar(const TickData& tick) {
        _aggregator->addTick(tick);
        _currentBar = _aggregator->getBarData();
    }


}
