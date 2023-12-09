//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#include "Ticker.h"
#include "Tickable.h"
#include "../Common/Utils.h"

namespace botb2 {
    Ticker::Ticker(const Interval& interval) :
    _interval(interval), _runTimer(true)
    {
        if(isTickInterval(interval)){
            _intervalTime = toTicks(interval);
        } else {
            _intervalTime = toMs(interval);

            uint64_t timeSinceEpoch = utils::time::timeSinceEpochMillisec();//Todo:: get server time on this
            uint64_t timeSinceLastBar = timeSinceEpoch % _intervalTime;
            uint64_t initialDelay = _intervalTime - timeSinceLastBar;

            startTimer(initialDelay);
        }
    }

    Ticker::~Ticker() {}


    void Ticker::startTimer(uint64_t initialDelay) {
        _timerThread = std::thread([this, initialDelay]() {
            // Primeiro delay pode ser menor para sincronizar com o intervalo da barra
            std::this_thread::sleep_for(std::chrono::milliseconds(initialDelay));

            while (_runTimer) {
                {
                    std::lock_guard<std::mutex> lock(_timerMutex);
                    if (_runTimer) {
                        checkAndCloseBar();
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(_intervalTime));
            }
        });
    }

    void Ticker::checkAndCloseBar() {
        // Obter o tempo atual
        uint64_t currentTime = utils::time::timeSinceEpochMillisec();

        // Verificar se o intervalo desde o último tick excedeu intervalTimeMs
        if (currentTime - _lastTickTime >= _intervalTime) {
            // Fechar a barra atual
            if (!_currentBarData.isEmpty()) {
                _currentBarData.close_time_ms = currentTime;
                _currentBarData.close = _currentBarData.value; // Supondo que 'value' é o último valor de tick

                for (auto& tickable : _tickables) {
                    tickable->onClose(_currentBarData);
                }
            }

            // Preparar para a próxima barra
            prepareForNextBar(currentTime);
        }
    }

    void Ticker::prepareForNextBar(uint64_t currentTime) {
        // Reinicializa os dados da barra atual
        _currentBarData.clear();
        _lastTickTime = currentTime;
    }

    void Ticker::addTickable(const std::shared_ptr<Tickable>& tickable) {
        _tickables.insert(tickable);
    }

    void Ticker::removeTickable(const std::shared_ptr<Tickable>& tickable){
        _tickables.erase(tickable);
    }

    void Ticker::tick(const TickData &data) {

        aggregateTicks(data);

        for (auto &tickable: _tickables) {

//            tickable->onTick(data);
        }
    }

    void Ticker::aggregateTicks(const TickData& tick) {
        // Se é o primeiro tick da barra, inicialize os valores de abertura
        if (_currentBarData.open_time_ms == 0) {
            _currentBarData.open_time_ms = tick.time;
            _currentBarData.open = tick.value;
            _currentBarData.low = tick.value;
            _currentBarData.high = tick.value;
        }

        // Atualiza os valores de alta, baixa e volume
        _currentBarData.high = std::max(_currentBarData.high, tick.value);
        _currentBarData.low = std::min(_currentBarData.low, tick.value);
        _currentBarData.volume += tick.volume;

        // Atualizar o valor de fechamento com o último tick
        _currentBarData.close = tick.value;
        _currentBarData.close_time_ms = tick.time;
    }

    bool Ticker::isIntervalCompleted() {
        // Verifica se o intervalo está completo
        // Essa lógica depende da sua definição de Interval e da unidade de tempo
        return (_currentBarData.close_time_ms - _currentBarData.open_time_ms) >= _intervalTime;
    }

    BarData Ticker::buildBarData() {
        // Retorna a barra completa e reinicia para a próxima barra
        BarData completedBar = _currentBarData;
        _currentBarData.clear(); // Reinicia os dados da barra atual
        return completedBar;
    }

    void Ticker::clearAggregateTicks() {
        _currentBarData.clear();
    }

    bool Ticker::isStartOfNewBar(const TickData& data) {
        if (_tickCount == 0) return true;

        switch (_interval) {
            // Casos para intervalos baseados em ticks
            case Interval::Interval_5_ticks: return _tickCount % 5 == 0;
            case Interval::Interval_10_ticks: return _tickCount % 10 == 0;
            case Interval::Interval_15_ticks: return _tickCount % 15 == 0;
            case Interval::Interval_20_ticks: return _tickCount % 20 == 0;
            case Interval::Interval_50_ticks: return _tickCount % 50 == 0;
            case Interval::Interval_100_ticks: return _tickCount % 100 == 0;
            case Interval::Interval_200_ticks: return _tickCount % 200 == 0;
            case Interval::Interval_500_ticks: return _tickCount % 500 == 0;
            case Interval::Interval_1000_ticks: return _tickCount % 1000 == 0;
            case Interval::Interval_5000_ticks: return _tickCount % 5000 == 0;
            case Interval::Interval_10000_ticks: return _tickCount % 10000 == 0;

                // Casos para intervalos baseados em tempo
            case Interval::Interval_1_Second: return (data.time - _lastTickTime) >= 1000;
            case Interval::Interval_5_Seconds: return (data.time - _lastTickTime) >= 5*1000;
            case Interval::Interval_10_Seconds: return (data.time - _lastTickTime) >= 10*1000;
            case Interval::Interval_30_Seconds: return (data.time - _lastTickTime) >= 30*1000;
            case Interval::Interval_1_Minute: return (data.time - _lastTickTime) >= 60000;
            case Interval::Interval_3_Minutes: return (data.time - _lastTickTime) >= 3*60000;
            case Interval::Interval_5_Minutes: return (data.time - _lastTickTime) >= 5*60000;
            case Interval::Interval_15_Minutes: return (data.time - _lastTickTime) >= 15*60000;
            case Interval::Interval_30_Minutes: return (data.time - _lastTickTime) >= 30*60000;
            case Interval::Interval_1_Hour: return (data.time - _lastTickTime) >= 60*60000;
            case Interval::Interval_2_Hours: return (data.time - _lastTickTime) >= 2*60*60000;
            case Interval::Interval_4_Hours: return (data.time - _lastTickTime) >= 4*60*60000;
            case Interval::Interval_6_Hours: return (data.time - _lastTickTime) >= 6*60*60000;
            case Interval::Interval_8_Hours: return (data.time - _lastTickTime) >= 8*60*60000;
            case Interval::Interval_12_Hours: return (data.time - _lastTickTime) >= 12*60*60000;
            case Interval::Interval_1_Day: return (data.time - _lastTickTime) >= 24*60*60000;
            case Interval::Interval_3_Days: return (data.time - _lastTickTime) >= static_cast<uint64_t>(3) *24*60*60000;
            case Interval::Interval_1_Week: return (data.time - _lastTickTime) >= static_cast<uint64_t>(7) *24*60*60000;
            case Interval::Interval_1_Month: return (data.time - _lastTickTime) >= static_cast<uint64_t>(30) *24*60*60000;

            default: return false;
        }
    }



}