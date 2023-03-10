/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/HookAPI.h>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/GameMode.hpp>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/ServerPlayer.hpp>

std::map<INT64, int> data{};

TInstanceHook(void, "?startUsingItem@Player@@QEAAXAEBVItemStack@@H@Z", Player, ItemStack const& a1, int a2) {
    data[getUniqueID()] = getSelectedItemSlot();
    original(this, a1, a2);
}

TInstanceHook(void, "?stopUsingItem@Player@@QEAAXXZ", Player) {
    data.erase(getUniqueID());
    original(this);
}

TInstanceHook(void, "?releaseUsingItem@GameMode@@UEAAXXZ", GameMode) {
    ServerPlayer* player = getPlayer();
    player->setSelectedSlot(data[player->getUniqueID()]);
    original(this);
}
