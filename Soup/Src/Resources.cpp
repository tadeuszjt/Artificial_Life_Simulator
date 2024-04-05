#include "../Resources.hpp"

sf::Texture&
Resources_Ship() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Ship.png");
		tex.setSmooth(true);
		tex.generateMipmap();
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Boat() {
	static sf::Texture tex;
	static bool loaded;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Boat.png");
		tex.setSmooth(true);
		tex.generateMipmap();
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Arrow() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Arrow.png");
		tex.setSmooth(true);
		tex.generateMipmap();
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Circle() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Circle.png");
		tex.setSmooth(true);
		tex.generateMipmap();
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Ring() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Ring.png");
		tex.setSmooth(true);
		tex.generateMipmap();
		loaded = true;
	}
	return tex;
}

sf::Font&
Resources_Sans() {
	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
		font.loadFromFile("Soup/Resources/LiberationSans-Regular.ttf");
	return font;
}

sf::Font&
Resources_Serif() {
	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
		font.loadFromFile("Soup/Resources/LiberationSerif-Regular.ttf");
	return font;
}

sf::Font&
Resources_Mono() {
	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
		font.loadFromFile("Soup/Resources/LiberationMono-Regular.ttf");
	return font;
}


sf::Texture&
Resources_Panel1() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Panel1.png");
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Panel2() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Panel2.png");
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Panel3() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Panel3.png");
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_Panel4() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/Panel4.png");
		loaded = true;
	}
	return tex;
}

sf::Texture&
Resources_TitleBar() {
	static sf::Texture tex;
	static bool loaded = false;
	if (!loaded) {
		tex.loadFromFile("Soup/Resources/TitleBar.png");
		tex.setRepeated(true);
		loaded = true;
	}
	return tex;
}
