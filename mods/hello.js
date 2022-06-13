"use strict"

/**
 * @file Very basic mod example.
 */

/// <reference path="api.d.ts" />

game.addMod({
    name: 'Hello',
    description: 'Very basic mod example',

    onLoad: function (mod) {
        mod.log('The basic mod is loading...');

        // :see_no_evil:
        game.sv_cheats = 1;

        mod.log('The basic mod has loaded, enjoy!');
    },
    onUnload: function (mod) {
        mod.log('The basic mod has unloaded :(');
    }
});

game.addMod({
    name: 'Secondary',
    description: 'The second mod, for testing',

    onLoad: function (mod) {
        mod.log('Loading mod #' + mod.id);
    },
    onUnload: function (mod) {
        mod.log('Unloading mod #' + mod.id);
    }
});
