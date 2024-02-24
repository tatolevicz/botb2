//
// Created by Arthur Motelevicz on 10/12/23.
//

#ifndef BOTB2_MOCKTICKABLE_H
#define BOTB2_MOCKTICKABLE_H

#include <botb2.h>
using namespace botb2;

class MockTickable : public ITickable {
public:
    int onOpenCount = 0;
    int onCloseCount = 0;
    int onTickCount = 0;
    double accumulatedVolume = 0;
    double accumulatedOnTickVolume = 0;


    void onOpen(const BarData& data) override {
        onOpenCount++;
    }

    void onClose(const BarData& data) override {
        onCloseCount++;
        accumulatedVolume += data.volume;
    }

    void onTick(const TickData& data, const BarData& currentBar) override {
        accumulatedOnTickVolume += data.volume;
//        accumulatedVolume += currentBar.volume;
        onTickCount++;
    }
};


#endif //BOTB2_MOCKTICKABLE_H
