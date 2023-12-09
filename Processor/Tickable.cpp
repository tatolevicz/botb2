//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#include "Tickable.h"
#include "Utils.h"

namespace botb2 {
    Tickable::Tickable() {
        _id = utils::uuid::generate_uuid_v4();
    }

    Tickable::~Tickable() {}

    void Tickable::onOpen(const BarData &data) {}

    void Tickable::onTick(const BarData &data) {}

    void Tickable::onClose(const BarData &data) {}

    void Tickable::setPriority(int priority) {
        _priority = priority;
    }

    int Tickable::getPriority() const {
        return _priority;
    }

    const std::string &Tickable::getId() const {
        return _id;
    }
}
