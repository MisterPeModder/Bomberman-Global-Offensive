/**
 * @file Bomberman Modding API Definitions (ES5-compatible).
 */

interface Game {
    /** Set this to a non-zero value to enable cheat mode. */
    sv_cheats: number

    /**
     * Prints a message using the game's logging facility.
     * 
     * @param message The message to print.
     */
    log(message: string): void

    /**
     * Registers a new mod.
     * 
     * @param mod The mod to register.
     */
    addMod(mod: ModDefinition): void
}

/** Game global variable. */
declare var game: Game;

/** Mod declaration data. */
interface ModDefinition {
    /** The name of the mod, required. */
    name: string,
    /** The description of the mod, required. */
    description: string,

    /** A function to call when the mod gets initialized, optional. */
    onLoad?: (mod: Mod) => void,

    /** A function to call when the mod gets unloaded, optional. */
    onUnload?: (mod: Mod) => void,
}

/** Mod instance. */
interface Mod {
    /** The mod's id. */
    id: number,

    /**
     * Prints a message in the mod's logger.
     * 
     * @param message The message to print.
     */
    log(message: string): void
}
