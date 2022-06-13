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
    function readOnly(object, name, value) {
        Object.defineProperty(object, name, {
            value: value,
            writable: false
        });
    }

    Object.defineProperty(game, 'sv_cheats', {
        get: function () { return bm.common.getCVar('sv_cheats'); },
        set: function (value) { bm.common.setCVar('sv_cheats', Number(value)); }
    });

    readOnly(game, 'log', bm.common.log);

    game.addMod = function (/** @type {ModDefinition} */ modDef) {
        /** @type {Mod} */
        var mod = {};

        // Define the read-only properties of the mod object
        readOnly(mod, 'id', bm.mods.create(modDef.name, modDef.description));
        readOnly(mod, 'log', function (message) {
            bm.mods.log(mod.id, String(message));
        });

        if ('onLoad' in modDef) {
            bm.mods.setLoadCallback(mod.id, function () {
                modDef.onLoad(mod);
            });
        }
        if ('onUnload' in modDef) {
            bm.mods.setUnloadCallback(mod.id, function () {
                modDef.onUnload(mod);
            });
        }

        bm.mods.enable(mod.id);
    }

    game.callMeBack = bm.common.callMeBack;
})(game || (game = {}));
