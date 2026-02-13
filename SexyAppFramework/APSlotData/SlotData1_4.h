#include "SlotData1_3.h"

class SlotData1_4 : public SlotData1_3
{
public:
    explicit SlotData1_4(nlohmann::json slot_data) : SlotData1_3(std::move(slot_data)) {}
    
    std::string version() override
    {
        return "1.4";
    }
};
