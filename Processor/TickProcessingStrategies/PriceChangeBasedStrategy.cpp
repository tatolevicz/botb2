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

    void PriceChangeBasedStrategy::processTick(const TickData& tick, Ticker* ticker) {

        //ignores some wrong tick
        if(tick.time < _lastTime)
            return;//TODO:: log

        if (_lastTime == 0) {
            _lastPrice = tick.value;
            _lastTime = tick.time;
            _aggregator->addTick(tick);
            auto barData = _aggregator->getBarData();
            for(auto &t : ticker->getTickables()){
                t->onOpen(barData);
            }
            return;
        }

        double priceChangePercent = std::abs((tick.value - _lastPrice) / _lastPrice);

        //1 - verifica se o delta já é maior do que o treshhold
            //1.1 - se for identifica o preço limite da barra do treshhold
                //1.1.1 se sobrar algo além do treshhold guarda o quanto desse tick
                //1.1.2 fecha a barra com o tresh hold limite  e reinicia o processo com o restante do que passou recursivamente
            //1.2 guarda o estado antes da barra pra saber se é nova ou nao
            //1.3 faz o tick dos tickables
            //1.4 verifica se é barra nova e caso positivo faz o onOpen

        //1
        if (priceChangePercent >= _percentChangeThreshold) {

            auto directionSignal =  (tick.value > _lastPrice ? 1 : -1);
            //1.1
            double thresholdPrice = _lastPrice * (1 + _percentChangeThreshold * directionSignal);

            //1.1.1
            _excessDeltaPercent = priceChangePercent - _percentChangeThreshold;

            //1.1.2
            auto deltaPercent = _percentChangeThreshold/priceChangePercent;

            TickData closingTick;
            closingTick.volume =  deltaPercent * tick.volume;
            closingTick.value = thresholdPrice;
            closingTick.time = tick.time;

            closesBar(closingTick, ticker);
            _lastPrice = thresholdPrice;

            auto newPrice = tick.value;//thresholdPrice * (1 + (_excessDeltaPercent * directionSignal));
            TickData recursiveTick;
            recursiveTick.volume = (1 - deltaPercent) * tick.volume;
            recursiveTick.value = newPrice;
            recursiveTick.time = tick.time;

            processTick(recursiveTick, ticker);
        }
        else{
            _excessDeltaPercent = 0;
            auto isNewBar = _aggregator->isNewBar();
            _aggregator->addTick(tick);
            auto barData = _aggregator->getBarData();

            for(auto &t : ticker->getTickables()){
                t->onTick(barData);
            }

            if(isNewBar){
                for(auto &t : ticker->getTickables()){
                    t->onOpen(barData);
                }
            }

            _lastPrice = tick.value;
        }
    }

    void PriceChangeBasedStrategy::closesBar(const TickData& tick, Ticker *ticker) {

        _aggregator->addTick(tick);

        auto barData = _aggregator->getBarData();

        for (auto &t : ticker->getTickables()) {
            t->onClose(barData);
        }

        _aggregator->reset();
    }
}
