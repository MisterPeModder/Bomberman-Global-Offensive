"use strict"

/**
 * @file Very basic mod example.
 */

/// <reference path="api.d.ts" />

bm.common.callMeBack(function (value) {
    game.log("JS: " + value);
    throw "hdede";
    return value * 2;
})

bm.common.callMeBack(function (value) {
    game.log("TSX: " + value);
    return value * 4;
})
game.log('The basic mod is loading...');

// :see_no_evil:
game.sv_cheats = 1;

game.log('The basic mod has loaded, enjoy!');
