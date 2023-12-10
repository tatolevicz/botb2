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

    void onOpen(const BarData& data) override {
        onOpenCount++;
        // Adicionalmente, armazene ou verifique algo sobre 'data' se necessário
    }

    void onClose(const BarData& data) override {
        onCloseCount++;
        // Adicionalmente, armazene ou verifique algo sobre 'data' se necessário
    }

    void onTick(const BarData& data) override {
        onTickCount++;
        // Adicionalmente, armazene ou verifique algo sobre 'data' se necessário
    }
};


#endif //BOTB2_MOCKTICKABLE_H
