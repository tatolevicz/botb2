//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#ifndef BOTB2_TICKER_H
#define BOTB2_TICKER_H

#include <unordered_set>
#include <memory>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

#include "../Types/Interval.h"

namespace botb2 {
    enum class Interval;
    class Tickable;
    class TickData;

    class Ticker {
    public:
        Ticker(const Interval& interval);

        virtual ~Ticker();
        void addTickable(const std::shared_ptr<Tickable>& tickable);
        void removeTickable(const std::shared_ptr<Tickable>& tickable);
        void tick(const TickData &data);

    private:
        void aggregateTicks(const TickData& tick);
        bool isIntervalCompleted();
        BarData buildBarData();
        void clearAggregateTicks();

        void startTimer(uint64_t initialDelay);

        bool isStartOfNewBar(const TickData& data);
        void updateCurrentBarData(const TickData& data);
        void checkAndCloseBar();
        void prepareForNextBar(uint64_t currentTime);


        uint64_t _tickCount;
        uint64_t _lastTickTime;

        BarData _currentBarData; // Dados da barra atual


        std::atomic<bool> _runTimer;
        std::thread _timerThread;
        std::mutex _timerMutex;

        uint64_t _intervalTime;
        std::unordered_set<std::shared_ptr<Tickable>> _tickables;
        Interval _interval;
    };



}
#endif //BOTB2_TICKER_H
