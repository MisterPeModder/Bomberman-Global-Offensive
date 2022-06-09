"use strict"

/**
 * @file Bomberman Modding API (ES5-compatible).
 * 
 * Refer to the 'api.d.ts' file for more information.
 */

/// <reference path="api.d.ts" />

/** @type {Game} */
var game;

(function (game) {
    Object.defineProperty(game, 'sv_cheats', {
        get: function () { return bm.common.getCVar('sv_cheats'); },
        set: function (value) { bm.common.setCVar('sv_cheats', Number(value)); }
    });

    game.log = bm.common.log

    game.callMeBack = bm.common.callMeBack;
})(game || (game = {}));
