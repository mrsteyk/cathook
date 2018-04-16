/*
 * tfmm.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: nullifiedcat
 */

#include "common.hpp"

CatCommand cmd_queue_start("mm_queue_casual", "Start casual queue",
                           []() { tfmm::queue_start(); });

CatCommand cmd_abandon("mm_abandon", "Abandon match",
                       []() { tfmm::abandon(); });
static CatEnum queue_mode({ "MvmPractice", "MvmMannup", "LadderMatch6v6",
                            "LadderMatch9v9", "LadderMatch12v12",
                            "CasualMatch6v6", "CasualMatch9v9",
                            "CasualMatch12v12", "CompetitiveEventMatch12v12" });
static CatVar queue(queue_mode, "autoqueue_mode", "7",
                    "Autoqueue for this mode", "");

CatCommand get_state("mm_state", "Get party state", []() {
#ifndef __clang__
    re::CTFParty *party = re::CTFParty::GetParty();
    if (!party)
    {
        logging::Info("Party == NULL");
        return;
    }
    logging::Info("State: %d", re::CTFParty::state_(party));
#endif
});

namespace tfmm
{

void queue_start()
{
#ifndef __clang__
    re::CTFPartyClient *client = re::CTFPartyClient::GTFPartyClient();
    if (client)
    {
        if (queue == 7)
            client->LoadSavedCasualCriteria();
        client->RequestQueueForMatch((int) queue);
    }
    else
        logging::Info("queue_start: CTFPartyClient == null!");
#endif
}
void queue_leave()
{
#ifndef __clang__
    re::CTFPartyClient *client = re::CTFPartyClient::GTFPartyClient();
    if (client)
        client->RequestLeaveForMatch((int) queue);
    else
        logging::Info("queue_start: CTFPartyClient == null!");
#endif
}

void abandon()
{
#ifndef __clang__
    re::CTFGCClientSystem *gc = re::CTFGCClientSystem::GTFGCClientSystem();
    if (gc != nullptr)
        gc->AbandonCurrentMatch();
    else
        logging::Info("abandon: CTFGCClientSystem == null!");
#endif
}
}
