//
// Created by Arthur Motelevicz on 10/12/23.
//

#include <botb2.h>
#include "rapidcsv.h"

using namespace botb2;

std::vector<TickData> loadTestData(const std::string& filePath, Interval interval) {

    std::vector<TickData> output;

    try {
        rapidcsv::Document doc(filePath, rapidcsv::LabelParams(-1, -1));

        for(int i = 0; i < doc.GetRowCount(); i++)
        {
            TickData data_open;
            TickData data_high;
            TickData data_low;
            TickData data_close;

            auto intervalTime = toMilliseconds(interval).value();
            //converting ms to sec and add simulated time for the sub tick on the bars
            uint64_t timeInMs = doc.GetCell<uint64_t>(0,i);
            data_open.time   = timeInMs;
            data_high.time   = timeInMs + 20000;//simulate 20 sec after
            data_low.time    = timeInMs + 40000;//simulate 40 sec after
            data_close.time  = timeInMs + intervalTime - 1;//simulate 1 ms before the close time

            data_open.value = doc.GetCell<double>(1,i);
            data_high.value = doc.GetCell<double>(2,i);
            data_low.value = doc.GetCell<double>(3,i);
            data_close.value = doc.GetCell<double>(4,i);

            //0.25 volume for each tick
            double volume = doc.GetCell<double>(5,i)*0.25;
            data_open.volume = volume;
            data_high.volume = volume;
            data_low.volume = volume;
            data_close.volume = volume;

            output.push_back(data_open);
            output.push_back(data_high);
            output.push_back(data_low);
            output.push_back(data_close);
        }

    } catch(std::exception exception) {
        std::cout << "Troubles loading csv file." << "\n";
    }

    return output;
}


int main(){
    loadTestData("../tests/BTCUSDT-1m-20.csv", Interval::OneMinute);
    return 0;
}