//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include "catch.hpp"
//
//unsigned int Factorial( unsigned int number ) {
//    return number <= 1 ? number : Factorial(number-1)*number;
//}
//
//TEST_CASE( "Factorials are computed", "[factorial]" ) {
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//}
//

#define CATCH_CONFIG_MAIN  // Este define diz ao Catch para fornecer uma função main
#include "catch.hpp"
#include <botb2.h>
#include "rapidcsv.h"

#include "MockTickable.h"

using namespace botb2;

std::vector<TickData> loadTicksFromBarData(const std::string& filePath, Interval interval) {

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
        FAIL("Failed to load CSV file: " + std::string(exception.what()));
    }

    return output;
}


std::vector<TickData> loadTicks(const std::string& filePath) {

    std::vector<TickData> output;

    try {
        rapidcsv::Document doc(filePath, rapidcsv::LabelParams(-1, -1));

        for(int i = 1; i < doc.GetRowCount(); i++)
        {
            TickData tick;

            tick.value = doc.GetCell<double>(1,i);
            tick.volume = doc.GetCell<double>(3,i);
            tick.time = doc.GetCell<uint64_t>(4,i);

            output.push_back(tick);
        }

    } catch(std::exception exception) {
        FAIL("Failed to load CSV file: " + std::string(exception.what()));
    }

    return output;
}



struct TestInfo{
    std::string filePath;
    Interval interval;
    uint64_t  expectedTicksCount;       // the amount of ticks to be loaded
    uint64_t  expectedOnCloseCount;
    uint64_t  expectedOnOpenCount;
    uint64_t  expectedOnTickCount;
};

TEST_CASE("TimeBasedStrategy Processing Candles CSVs", "[time_based]") {

    Interval interval = Interval::OneMinute;

    std::vector<TestInfo> tests;

    TestInfo t1,t2, t3;

    t1.filePath = "../../tests/BTCUSDT-1m-20.csv";
    t1.interval = Interval::OneMinute;
    t1.expectedTicksCount =  20*4;
    t1.expectedOnCloseCount =  19;
    t1.expectedOnOpenCount =  20;
    t1.expectedOnTickCount =  20*4;

    t2.filePath = "../../tests/BTCUSDT-1m-100.csv";
    t2.interval = Interval::OneMinute;
    t2.expectedTicksCount =  100*4;
    t2.expectedOnCloseCount =  99;
    t2.expectedOnOpenCount =  100;
    t2.expectedOnTickCount =  100*4;

    t3.filePath = "../../tests/BTCUSDT-1m-2023-11.csv";
    t3.interval = Interval::OneMinute;
    t3.expectedTicksCount =  43200*4;
    t3.expectedOnCloseCount =  43199;
    t3.expectedOnOpenCount =  43200;
    t3.expectedOnTickCount =  43200*4;

    tests.push_back(t1);
    tests.push_back(t2);
    tests.push_back(t3);

    for(auto &t : tests){
        // Configurar os dados do teste
        std::vector<TickData> testData = loadTicksFromBarData(t.filePath, t.interval);

        Ticker ticker(interval);
        auto mockTickable = std::make_shared<MockTickable>();
        // Adicione o MockTickable ao Ticker
        ticker.addTickable(mockTickable);

        // Simule o processamento de ticks
        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);
    }
}


TEST_CASE("TimeBasedStrategy Processing Ticks CSVs", "[time_based]") {

    std::vector<TestInfo> tests;

    TestInfo t1;

    t1.filePath = "../../tests/BTCBUSD-trades-372.csv";
    t1.interval = Interval::OneMinute;
    t1.expectedTicksCount =  371;
    t1.expectedOnCloseCount =  4;
    t1.expectedOnOpenCount =  5;
    t1.expectedOnTickCount =  371;

    tests.push_back(t1);


    for(auto &t : tests){

        std::vector<TickData> testData = loadTicks(t.filePath);

        Ticker ticker(t.interval);
        auto mockTickable = std::make_shared<MockTickable>();

        ticker.addTickable(mockTickable);

        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);
    }
}


TEST_CASE("TickBasedStrategy Processing 5 Ticks CSVs", "[tick_based]") {

    std::vector<TestInfo> tests;

    TestInfo t1;

    t1.filePath = "../../tests/BTCBUSD-trades-372.csv";
    t1.interval = Interval::FiveTicks;
    t1.expectedTicksCount =  371;
    t1.expectedOnCloseCount =  74;
    t1.expectedOnOpenCount =  75;
    t1.expectedOnTickCount =  371;

    tests.push_back(t1);

    for(auto &t : tests){

        std::vector<TickData> testData = loadTicks(t.filePath);

        Ticker ticker(t.interval);
        auto mockTickable = std::make_shared<MockTickable>();

        ticker.addTickable(mockTickable);

        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);
    }
}


TEST_CASE("TickBasedStrategy Processing 10 Ticks CSVs", "[tick_based]") {

    std::vector<TestInfo> tests;

    TestInfo t1;

    t1.filePath = "../../tests/BTCBUSD-trades-372.csv";
    t1.interval = Interval::TenTicks;
    t1.expectedTicksCount =  371;
    t1.expectedOnCloseCount =  37;
    t1.expectedOnOpenCount =  38;
    t1.expectedOnTickCount =  371;

    tests.push_back(t1);

    for(auto &t : tests){

        std::vector<TickData> testData = loadTicks(t.filePath);

        Ticker ticker(t.interval);
        auto mockTickable = std::make_shared<MockTickable>();

        ticker.addTickable(mockTickable);

        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);
    }
}


TEST_CASE("TickBasedStrategy Processing 1000 Ticks CSVs", "[tick_based]") {

    std::vector<TestInfo> tests;

    TestInfo t1;

    t1.filePath = "../../tests/BTCBUSD-trades-372.csv";
    t1.interval = Interval::ThousandTicks;
    t1.expectedTicksCount =  371;
    t1.expectedOnCloseCount =  0;
    t1.expectedOnOpenCount =  1;
    t1.expectedOnTickCount =  371;

    tests.push_back(t1);

    for(auto &t : tests){

        std::vector<TickData> testData = loadTicks(t.filePath);

        Ticker ticker(t.interval);
        auto mockTickable = std::make_shared<MockTickable>();

        ticker.addTickable(mockTickable);

        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);
    }
}

TEST_CASE("PriceChangeBasedStrategy Processing 1 % CSVs", "[tick_based]") {

    std::vector<TestInfo> tests;

    TestInfo t1;

    t1.filePath = "../../tests/BTCBUSD-trades-2.csv";
    t1.interval = Interval::Renko_1_Percent;
    t1.expectedTicksCount =  3;
    t1.expectedOnCloseCount =  7;
    t1.expectedOnOpenCount =  8;
    t1.expectedOnTickCount =  3;

    tests.push_back(t1);

    for(auto &t : tests){

        std::vector<TickData> testData = loadTicks(t.filePath);

        Ticker ticker(t.interval);
        auto mockTickable = std::make_shared<MockTickable>();

        ticker.addTickable(mockTickable);

        for (const auto& tick : testData) {
            ticker.tick(tick);
        }

        REQUIRE(testData.size() == t.expectedTicksCount);
        REQUIRE(mockTickable->onOpenCount == t.expectedOnOpenCount);
        REQUIRE(mockTickable->onCloseCount == t.expectedOnCloseCount);
        REQUIRE(mockTickable->onTickCount == t.expectedOnTickCount);

        //check internal BarData values
        //should be 454,16...
        REQUIRE(mockTickable->accumulatedOnTickVolume == mockTickable->accumulatedVolume);
    }
}
