#pragma once

#include "Campaign.h"

class CampaignLoader {
public:
    CampaignLoader();
    ~CampaignLoader();
    bool writeCampaign();
    bool loadCampaign();

private:
    bool writeMap(Map* map);
    Campaign* campaign;
    std::string directory = "Campaigns/";

};
