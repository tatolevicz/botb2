//
// Created by Arthur Motelevicz on 09/12/23.
//

#include "BarAggregator.h"

namespace botb2{

    BarAggregator::BarAggregator():
    _isNewBar(true) {}

    void BarAggregator::reset(){
        _isNewBar = true;
        resetBar();
    }

    bool BarAggregator::isNewBar(){
        return _isNewBar;
    }

    void BarAggregator::addTick(const TickData& tick){

        if (_isNewBar) {
            resetBar();
            _currentBar.openTime = tick.time;
            _currentBar.closeTime = tick.time;
            _currentBar.open = tick.value;
            _currentBar.high = tick.value;
            _currentBar.low = tick.value;
            _currentBar.close = tick.value;
            _currentBar.volume = tick.volume;
            _isNewBar = false;
            return;
        }

        updateCurrentBar(tick);
    }

    BarData BarAggregator::getBarData() const{
        return _currentBar;
    }

    void BarAggregator::resetBar(){
        _currentBar = BarData();
    }

    void BarAggregator::updateCurrentBar(const TickData& tick) {
        _currentBar.high = std::max(_currentBar.high, tick.value);
        _currentBar.low = std::min(_currentBar.low, tick.value);
        _currentBar.close = tick.value;
        _currentBar.closeTime = tick.time;
        _currentBar.volume += tick.volume;
    }
}