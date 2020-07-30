#pragma once
#include <string>

class Constants {

	static Constants* instance;

	public:

		Constants();

		// GAME TITLE
		inline static const std::string GAME_TITLE = "Zombieland";

		// ASSET PATHS
		inline static const std::string PLAYER_PNG = "graphics/player.png";
		inline static const std::string BACKGROUND_SHEET_PNG = "graphics/background_sheet.png";
		inline static const std::string ZOMBIE_CRAWLER_PNG = "graphics/crawler.png";
		inline static const std::string ZOMBIE_BLOATER_PNG = "graphics/bloater.png";
		inline static const std::string ZOMBIE_CHASER_PNG = "graphics/chaser.png";
		inline static const std::string CROSSHAIR_PNG = "graphics/crosshair.png";
		inline static const std::string HEALTH_PICKUP_PNG = "graphics/health_pickup.png";
		inline static const std::string AMMO_PICKUP_PNG = "graphics/ammo_pickup.png";
		inline static const std::string BACKGROUND_PNG = "graphics/background.png";
		inline static const std::string AMMO_ICON_PNG = "graphics/ammo_icon.png";
		inline static const std::string FONT_PATH = "fonts/zombiecontrol.ttf";
		inline static const std::string HISCORE_FILE = "gamedata/scores.txt";

		// GAME AUDIO
		inline static const std::string SOUND_HIT = "sound/hit.wav";
		inline static const std::string SOUND_SPLAT = "sound/splat.wav";
		inline static const std::string SOUND_SHOOT = "sound/shoot.wav";
		inline static const std::string SOUND_POWERUP = "sound/powerup.wav";
		inline static const std::string SOUND_PICKUP = "sound/pickup.wav";
		inline static const std::string SOUND_RELOAD = "sound/reload.wav";
		inline static const std::string SOUND_RELOAD_FAILED = "sound/reload_failed.wav";

		// GAME STATES
		enum class State {
			PAUSED, GAME_OVER, LEVELING_UP, PLAYING
		};

};
