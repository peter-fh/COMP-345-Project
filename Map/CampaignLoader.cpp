#include "CampaignLoader.h"
#include <filesystem>
#include <fstream>
#include <sys/stat.h>

namespace fs = std::filesystem;

CampaignLoader::CampaignLoader() {
    campaign = nullptr;
    directory = "saves/campaigns";
}

CampaignLoader::~CampaignLoader() {
    delete campaign;
}

bool CampaignLoader::saveCampaign() {
    if (campaign == nullptr) {
		return false;
    }
    
    std::string campaignDir = directory + "/" + campaign->getName();
    if (!fs::exists(campaignDir)) {
	if (!fs::create_directories(campaignDir)){
	    return false;
	}
    }






    return true;
}
