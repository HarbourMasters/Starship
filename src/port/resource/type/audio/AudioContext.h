#pragma once
#include <cstdint>
#include "Sample.h"

namespace SF64 {
struct TunedSample {
    SampleData* sample;
    float tuning;
};

enum class AudioTableType {
    SAMPLE_TABLE,
    SEQ_TABLE,
    FONT_TABLE
};
}