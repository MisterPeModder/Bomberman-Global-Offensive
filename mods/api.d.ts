/**
 * @file Bomberman Modding API Definitions.
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
}

declare var game: Game;
