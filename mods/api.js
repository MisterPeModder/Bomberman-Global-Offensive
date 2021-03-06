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
    /**
     * Result of the typeof expression.
     * 
     * @typedef {'boolean' | 'function' | 'number' | 'object' | 'string' } TypeofResult
     */


    /**
     * Adds a read-only property called `name` to the `object`.
     * 
     * @param {Object} object 
     * @param {string} name 
     * @param {*} value 
     */
    function readOnly(object, name, value) {
        Object.defineProperty(object, name, {
            value: value,
            writable: false
        });
    }

    /**
     * Checks the type of given argument, or throws if it doesn't match the `type` parameter.
     * 
     * @param {string} funcName The name of the function, used in the generated exception.
     * @param {number} index
     * @param {TypeofResult} type The type 
     * @param {*} arg The argument to check
     */
    function checkArg(funcName, index, type, arg) {
        if (typeof arg !== type)
            throw funcName + ' expected argument of type ' + type + ' at index ' + index;
    }

    ///////////////////////////////////////////////////////////////////////////

    Object.defineProperty(game, 'sv_cheats', {
        get: function () { return bm.common.getCVar('sv_cheats'); },
        set: function (value) { bm.common.setCVar('sv_cheats', Number(value)); }
    });

    Object.defineProperty(game, 'width', {
        get: function () { return bm.common.getWidth(); },
        set: function (value) {
            checkArg('game.width', 0, 'number', value);
            bm.common.setWidth(Number(value));
        }
    });
    Object.defineProperty(game, 'height', {
        get: function () { return bm.common.getHeight(); },
        set: function (value) {
            checkArg('game.height', 0, 'number', value);
            bm.common.setHeight(Number(value));
        }
    });
    Object.defineProperty(game, "debugMode", {
        get: function () { return Boolean(bm.common.getDebugMode()); },
        set: function (value) {
            checkArg('game.debugMode', 0, 'boolean', value);
            bm.common.setDebugMode(Boolean(value));
        }
    })

    readOnly(game, 'log', function (msg) { bm.common.log(String(msg)); });
    readOnly(game, 'error', function (msg) { bm.common.error(String(msg)); });
    readOnly(game, 'warn', function (msg) { bm.common.warn(String(msg)); });
    readOnly(game, 'debug', function (msg) { bm.common.debug(String(msg)); });

    readOnly(game, 'addMod', function (/** @type {ModDefinition} */ modDef) {
        /** @type {Mod} */
        var mod = {};

        if (!('name' in modDef) || modDef.name == null)
            throw 'Missing mod name';
        if (!('description' in modDef) || modDef.description == null)
            throw 'Missing mod description';

        // Define the read-only properties of the mod object
        readOnly(mod, 'id', bm.mods.create(String(modDef.name), String(modDef.description)));

        readOnly(mod, 'log', function (message) { bm.mods.log(mod.id, String(message)); });
        readOnly(mod, 'error', function (message) { bm.mods.error(mod.id, String(message)); });
        readOnly(mod, 'warn', function (message) { bm.mods.warn(mod.id, String(message)); });
        readOnly(mod, 'debug', function (message) { bm.mods.debug(mod.id, String(message)); });

        if ('onLoad' in modDef && typeof modDef.onLoad === 'function') {
            bm.mods.setLoadCallback(mod.id, function () {
                modDef.onLoad(mod);
            });
        }
        if ('onUnload' in modDef && typeof modDef.onUnload === 'function') {
            bm.mods.setUnloadCallback(mod.id, function () {
                modDef.onUnload(mod);
            });
        }

        bm.mods.enable(mod.id);
    });

    readOnly(game, 'setColorblindFilter', function (filter) {
        if (filter === undefined)
            filter = 'none';
        if (typeof filter === 'number') {
            if (number < 0 || number > 3)
                filter = 'none';
            else
                filter = ['none', 'protanopia', 'deuteranopia', 'tritanopia'][number];
        }
        bm.common.setColorblindFilter(filter.toLowerCase());
    });

    ///////////////////////////////////////////////////////////////////////////

    /**
     * @param {number} id 
     * @return {Player}
     */
    function makePlayer(id) {
        var player = {};

        Object.defineProperty(player, 'x', {
            get: function () { return bm.players.getX(id); },
            set: function (x) {
                checkArg('player.x', 0, 'number', x);
                bm.players.setX(id, x);
            }
        });
        Object.defineProperty(player, 'y', {
            get: function () { return bm.players.getY(id); },
            set: function (y) {
                checkArg('player.y', 0, 'number', y);
                bm.players.setY(id, y);
            }
        });

        readOnly(player, 'setPos', function (x, y) {
            checkArg('player.setPos', 0, 'number', x);
            checkArg('player.setPos', 1, 'number', y);

            bm.players.setPos(id, x, y);
        });

        readOnly(player, 'moveTo', function (x, y) {
            checkArg('player.moveTo', 0, 'number', x);
            checkArg('player.moveTo', 1, 'number', y);

            bm.players.moveTo(id, x, y);
        });

        readOnly(player, 'stop', function () {
            bm.players.stop(id);
        });
        return player;
    }

    /**
     * Player objects cache
     * @type {Player[]}
    */
    var players = []

    readOnly(game, 'getPlayer', function (slot) {
        checkArg('game.getPlayer', 0, 'number', slot);
        if (bm.players.exists(slot) === 0)
            throw 'player ' + slot + ' does not exist';
        if (players[slot] === undefined)
            players[slot] = makePlayer(slot);
        return players[slot];
    });

    readOnly(game, 'spawnItem', function (x, y, name) {
        if (name == null || name === '')
            name = 'random';
        bm.common.spawnItem(x, y, name);
    })
})(game || (game = {}));
