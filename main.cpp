//
// Created by Arthur Motelevicz on 12/12/23.
//


#include <iostream>

int main(){

    std::cout << "Hello" << "\n";

    return 0;
}

//#include <vector>
//#include <botb2.h>
//#include "rapidcsv.h"
//#include "../tests/MockTickable.h"
//#include <cassert>
//
//std::vector<TickData> loadTicks(const std::string& filePath) {
//
//    std::vector<TickData> output;
//
//    try {
//        rapidcsv::Document doc(filePath, rapidcsv::LabelParams(-1, -1));
//
//        for(int i = 1; i < doc.GetRowCount(); i++)
//        {
//            TickData tick;
//
//            tick.value = doc.GetCell<double>(1,i);
//            tick.volume = doc.GetCell<double>(3,i);
//            tick.time = doc.GetCell<uint64_t>(4,i);
//
//            output.push_back(tick);
//        }
//
//    } catch(std::exception exception) {
//        assert(false && "Failed to load CSV file: ");
//    }
//
//    return output;
//}
//
//int main(){
//
//    Interval interval = Interval::Renko_1_Percent;
//    std::string filePath = "../../tests/BTCBUSD-trades-372.csv";
//    std::vector<TickData> testData = loadTicks(filePath);
//
//    Ticker ticker(interval);
//    auto mockTickable = std::make_shared<MockTickable>();
//
//    ticker.addTickable(mockTickable);
//
//    for (const auto& tick : testData) {
//        ticker.tick(tick);
//        std::cout << "Tick count: " << mockTickable->onTickCount << "\n";
//    }
//
//    return 0;
//}