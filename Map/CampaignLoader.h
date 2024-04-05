#pragma once

#include "Campaign.h"

class CampaignLoader {
public:
    CampaignLoader();
    ~CampaignLoader();
    bool saveCampaign();
    bool loadCampaign();

private:
    bool writeMap(Map* map, std::string directory);
    Campaign* campaign;
    std::string directory;

};
