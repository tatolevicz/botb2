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
            _priceChangeThreshold = percentResult.value();
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
            return;
        }

        double priceChangePercent = std::abs((tick.value - _lastPrice) / _lastPrice);

        if (priceChangePercent >= _priceChangeThreshold) {
            // Calcular o preço exato que atende ao threshold
            double thresholdPrice = _lastPrice * (1 + _priceChangeThreshold * (tick.value > _lastPrice ? 1 : -1));

            // Processar como se o tick tivesse esse valor de threshold
            closesBar(thresholdPrice, ticker);

            // Definir _lastPrice para o preço de threshold
            _lastPrice = thresholdPrice;

            // Verificar se o excesso atinge um novo threshold
            priceChangePercent = std::abs((tick.value - _lastPrice) / _lastPrice);
            if (priceChangePercent >= _priceChangeThreshold) {
                // Acumular o excesso para a próxima barra
                _excessPrice = tick.value;
            } else {
                _excessPrice = 0; // Resetar o excesso se não atingir um novo threshold
            }

        } else if (_excessPrice > 0) {
            // Se houver excesso acumulado, verificar se ele atinge um novo threshold
            priceChangePercent = std::abs((tick.value - _excessPrice) / _excessPrice);
            if (priceChangePercent >= _priceChangeThreshold) {
                closesBar(tick.value, ticker);
                _lastPrice = tick.value;
                _excessPrice = 0; // Resetar o excesso após processar a nova barra
            }
        }
    }

    void PriceChangeBasedStrategy::closesBar(double closePrice, Ticker *ticker) {
        // Obter os dados da barra atual
        auto barData = _aggregator->getBarData();
        barData.close = closePrice; // Definir o preço de fechamento

        // Notificar todos os Tickable com onClose
        for (auto &t : ticker->getTickables()) {
            t->onClose(barData);
        }
        // Resetar o agregador para a próxima barra
        _aggregator->reset();
    }
}
