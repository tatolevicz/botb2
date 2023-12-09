//
// Created by Arthur Abel Motelevicz on 20/07/22.
//

#ifndef BOTBUILDER_TICKABLE_H
#define BOTBUILDER_TICKABLE_H

#include <memory>
#include <string>
#include <functional>

namespace botb2 {

    class Ticker;
    class TickData;
    class BarData;

    class Tickable {
    public:

        Tickable();

        virtual ~Tickable();

        virtual void onOpen(const BarData& data);

        virtual void onClose(const BarData& data);

        virtual void onTick(const BarData& data);

        void setPriority(int priority);

        int getPriority() const;

        const std::string& getId() const;

        bool operator<(const std::shared_ptr<Tickable>& rhs) const {
            return _id < rhs->getId();
        }

    protected:
        std::string _id;
    private:
        int _priority = 0;
    };

    struct TickableHash {
        size_t operator()(const std::shared_ptr<Tickable>& tickable) const {
            return std::hash<std::string>()(tickable->getId());
        }
    };

    struct TickableEqual {
        bool operator()(const std::shared_ptr<Tickable>& lhs, const std::shared_ptr<Tickable>& rhs) const {
            return lhs->getId() == rhs->getId();
        }
    };
}
//

#endif //BOTBUILDER_TICKABLE_H
