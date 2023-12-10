//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#include "ITickable.h"
#include "Utils.h"

namespace botb2 {
    ITickable::ITickable() {
        _id = utils::uuid::generate_uuid_v4();
    }

    ITickable::~ITickable() {}

    void ITickable::onOpen(const BarData &data) {}

    void ITickable::onTick(const BarData &data) {}

    void ITickable::onClose(const BarData &data) {}

    void ITickable::setPriority(int priority) {
        _priority = priority;
    }

    int ITickable::getPriority() const {
        return _priority;
    }

    const std::string &ITickable::getId() const {
        return _id;
    }
}
