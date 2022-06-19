/**
 * @file Bomberman Modding API Definitions (ES5-compatible).
 */

interface Game {
    /** Set this to a non-zero value to enable cheat mode. */
    sv_cheats: number;

    /** The game screen width, in pixels. */
    width: number;

    /** The game screen height, in pixels. */
    height: number;

    /**
     * Debug mode, disabled by default.
     * 
     * When enabled, extra information will be displayed on screen, such as the game FPS counter.
    */
    debugMode: boolean;

    /**
     * Prints a message using the game's logging facility.
     * 
     * @param message The message to print.
     */
    log(message: string): void;

    /**
     * Prints a message to the error output.
     * 
     * @param message The message to print.
     */
    error(message: string): void;

    /**
     * Prints a message to the warning output.
     * 
     * @param message The message to print.
     */
    warn(message: string): void;

    /**
     * Prints a message to the debug output.
     * 
     * @param message The message to print.
     */
    debug(message: string): void;

    /**
     * Registers a new mod.
     * 
     * @param mod The mod to register.
     */
    addMod(mod: ModDefinition): void;

    /**
     * Changes the currenly active colorblind filter.
     * 
     * @param filter The filter to set.
     */
    setColorblindFilter(filter?: 'none' | 'protanopia' | 'deuteranopia' | 'tritanopia' | number): void;

    getPlayer(slot: number): Player;
}

/** Game global variable. */
declare var game: Game;

/** Mod declaration data. */
interface ModDefinition {
    /** The name of the mod, required. */
    name: string;
    /** The description of the mod, required. */
    description: string;

    /** A function to call when the mod gets initialized, optional. */
    onLoad?: (mod: Mod) => void;

    /** A function to call when the mod gets unloaded, optional. */
    onUnload?: (mod: Mod) => void;
}

/** Mod instance. */
interface Mod {
    /** The mod's id. */
    id: number;

    /**
     * Prints a message in the mod's logger.
     * 
     * @param message The message to print.
     */
    log(message: string): void;

    /**
     * Prints a message in the mod's error logger.
     * 
     * @param message The message to print.
     */
    error(message: string): void;

    /**
     * Prints a message in the mod's warning logger.
     * 
     * @param message The message to print.
     */
    warn(message: string): void;

    /**
     * Prints a message in the mod's debug logger.
     * 
     * @param message The message to print.
     */
    debug(message: string): void;
}

interface Player {
    x: number;
    y: number;

    setPos(x: number, y: number): void;
    moveTo(x: number, y: number): void;
    stop(): void;
}
