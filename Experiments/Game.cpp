
#include <imgui.h>
#include <array>
#include <vector>
#include <random>
#include <numeric>

#include "C.hpp"
#include "Game.hpp"

#include "HotReloadShader.hpp"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
	return new uint8_t[size];
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	return _aligned_malloc(size,alignment);
}

static int cols = 1280 / C::GRID_SIZE;
static int lastLine = 720 / C::GRID_SIZE - 1;

Game::Game(sf::RenderWindow * win) {
	this->win = win;
	bg = sf::RectangleShape(Vector2f(win->getSize().x, win->getSize().y));

	bool isOk = tex.loadFromFile("res/white.png");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));

	bgShader = new HotReloadShader("res/bg.vert", "res/bg.frag");
	if (!font.loadFromFile("res/MAIAN.TTF")) {
		printf("ERROR NO FONT\n");
	}
}

void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == sf::Event::KeyReleased) {
		
	
	}
}

static double g_time = 0.0;
static double g_tickTimer = 0.0;

void Game::pollInput(double dt) {

	float lateralSpeed = 8.0;
	float maxSpeed = 40.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!wasPressed) {
			onSpacePressed();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

}

static RenderStates vaRs;
static float		vaAlpha = 1.0;
static int			vaSize = 13;

static bool s_RectShapeFlood = false;
static std::vector<sf::RectangleShape> rects;

int blendModeIndex(sf::BlendMode bm) {
	if (bm == sf::BlendAlpha) return 0;
	if (bm == sf::BlendAdd) return 1;
	if (bm == sf::BlendNone) return 2;
	if (bm == sf::BlendMultiply) return 3;
	return 4;
};

static unsigned int xor32()
{
	static unsigned int y = 2463534242UL;
	y ^= (y << 13); y ^= (y >> 17); return (y ^= (y << 15));
};

void Game::update(double dt) {
	pollInput(dt);

	g_time += dt;
	if (bgShader) bgShader->update(dt);

	beforeParts.update(dt);
	afterParts.update(dt);

	texts.clear();

	bool isTick = false;
	g_tickTimer -= dt;
	if (g_tickTimer <= 0.0) {
		onFileTick();
		isTick = true;
		g_tickTimer = 0.1;
	}

	static int samples = 500;

	if (ImGui::TreeNodeEx("Random Distribs Viewer", ImGuiTreeNodeFlags_DefaultOpen)) {
		using namespace ImGui;
		static std::random_device r;
		static std::default_random_engine e1(r());
		static std::uniform_int_distribution<int> uniform_dist(0, 20000000);

		enum randCats {
			cpp_lin,
			cpp_substract_carry,
			cpp_mersen,
			cpp_shuffle_order,
			c_srand,
			c_xorshift32,
			randCats_count,
		};
		static bool s_cats[randCats_count] = {};

		static bool s_recompute = true;
		static std::vector<int> s_cppLinHits;
		static std::unordered_map<int, int> s_cppLinData;
		distrib.clear();

		s_cppLinHits.clear();
		for (int i = 0; i < 21; ++i)
			s_cppLinHits.push_back(0);

		static double timeStart = 0.0;
		static double timeCur = 0.0;
		static int speed = 1;
		int whereAreWe = timeCur * 20 * speed;
		if (whereAreWe > s_cppLinData.size())
			whereAreWe = s_cppLinData.size();

		if (Button("recompute")) {
			s_recompute = true;
			timeStart = timeCur = 0;
		}

		int s_min = 1024 * 1024;
		int s_max = -1;
		static int curCat = 0;

		static const char* cats[] = { "cpp_lin","cpp_substract_carry","cpp_mersen","cpp_shuffle_order","c_srand","xorshift32"};

		// later in your code...
		if (ImGui::BeginCombo("Random Engine", cats[curCat])) {
			for (int i = 0; i < IM_ARRAYSIZE(cats); ++i) {
				bool isSelected = (curCat == i);
				if (ImGui::Selectable(cats[i], isSelected)) {
					curCat = i;
					s_recompute = true; timeStart = timeCur = 0; s_cppLinData.clear();
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (Button("x1")) {
			speed = 1;
		} SameLine();

		if (Button("x2")) {
			speed = 2;
		} SameLine();

		if (Button("x5")) {
			speed = 5;
		} SameLine();

		if (Button("x50")) {
			speed = 50;
		} SameLine();

		NewLine();

		static int nbSamples = 500;
		if (Button("20")) {
			nbSamples = 20; s_recompute = true; timeStart = timeCur = 0; s_cppLinData.clear();
		} SameLine();
		if (Button("50")) {
			nbSamples = 50; s_recompute = true; timeStart = timeCur = 0; s_cppLinData.clear();
		} SameLine();
		if (Button("100")) {
			nbSamples = 100; s_recompute = true; timeStart = timeCur = 0; s_cppLinData.clear();
		} SameLine();
		if (Button("500")) {
			nbSamples = 500; s_recompute = true; timeStart = timeCur = 0; s_cppLinData.clear();
		} SameLine();

		if (curCat == cpp_lin) {
			if (s_recompute) {
				std::seed_seq				seed{ r(), r(), r(), r(), r(), r(), r(), r() };
				std::minstd_rand0			e2(seed);
				std::uniform_int_distribution<int>	normal_dist(1, 20);
				for (int n = 0; n < nbSamples; ++n)
					s_cppLinData[n] = normal_dist(e2);
				s_recompute = false; s_min = 0; s_max = 0;
			}

			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " Linear Congruence");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}

		if (curCat == cpp_substract_carry) {
			int curCat = 1;
			if (s_recompute) {
				std::seed_seq				seed{ r(), r(), r(), r(), r(), r(), r(), r() };
				std::ranlux48_base 			e2(seed);
				std::uniform_int_distribution<int>	normal_dist(1, 20);
				for (int n = 0; n < nbSamples; ++n)
					s_cppLinData[n] = normal_dist(e2);
				s_recompute = false; s_min = 0; s_max = 0;
			}

			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " substract_carry");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}

		if (curCat == cpp_mersen) {
			if (s_recompute) {
				std::seed_seq				seed{ r(), r(), r(), r(), r(), r(), r(), r() };
				std::mt19937 				e2(seed);
				std::uniform_int_distribution<int>	normal_dist(1, 20);
				for (int n = 0; n < nbSamples; ++n)
					s_cppLinData[n] = normal_dist(e2);
				s_recompute = false; s_min = 0; s_max = 0;
			}
			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " Mersen Twister");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}

		if (curCat == cpp_shuffle_order) {
			if (s_recompute) {
				std::seed_seq				seed{ r(), r(), r(), r(), r(), r(), r(), r() };
				std::knuth_b  				e2(seed);
				std::uniform_int_distribution<int>	normal_dist(1, 20);
				for (int n = 0; n < nbSamples; ++n)
					s_cppLinData[n] = normal_dist(e2);
				s_recompute = false; s_min = 0; s_max = 0;
			}
			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " Shuffle order");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}

		if (curCat == c_srand) {
			if (s_recompute) {
				srand(r());
				for (int n = 0; n < nbSamples; ++n) {
					s_cppLinData[n] = 1 + rand() % 20;
				}
				s_recompute = false; s_min = 0; s_max = 0;
			}
			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " C random");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}
		
		if (curCat == c_xorshift32) {
			if (s_recompute) {
				for (int n = 0; n < nbSamples; ++n) {
					s_cppLinData[n] = 1 + xor32() % 20;
				}
				s_recompute = false; s_min = 0; s_max = 0;
			}
			sf::Text total;
			total.setPosition(100, 50);
			total.setString("Showing "s + std::to_string(whereAreWe) + " xorshift32");
			total.setFillColor(sf::Color::Black);
			total.setFont(font);;

			texts.push_back(total);
			for (int i = 0; i < whereAreWe && i < s_cppLinData.size(); ++i) {
				auto p = RectangleShape(Vector2f(8, 8));
				p.setOrigin(-4, -4);
				p.setFillColor(sf::Color(0xff0000ff));

				int val = s_cppLinData[i];
				sf::Vector2f pos;
				pos.x = 100 + val * 30;
				pos.y = 500 + 30 * curCat - s_cppLinHits[val] * 10;
				p.setPosition(pos);
				s_cppLinHits[val]++;
				distrib.push_back(p);
			}
		}


		if (ImGui::TreeNode("Values")) {
			for (auto& v : s_cppLinData)
				Value("val", v.second);
			ImGui::TreePop();
		}
		static bool s_paused = false;

		for (int i = 1; i < 21; ++i) {
			auto& v = s_cppLinHits[i];
			if (v < s_min)
				s_min = v;
			if (v > s_max)
				s_max = v;
		}
		Value("maximum times of value hit ", s_max);
		Value("minimum times of value hit ", s_min);
		Value("spread of times a value is hit ", (s_max - s_min));

		auto hits = s_cppLinHits;
		if (hits.size()) {
			hits.erase(hits.begin());
			std::sort(hits.begin(), hits.end());
			int s_med = hits[hits.size() >> 1];
			Value("median times of value hit ", s_med);
		}
		Checkbox("Pause", &s_paused);
		if( !s_paused)
			timeCur += dt;
		
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Random Disc Viewer")) {

		ImGui::TreePop();
	}

	
}

 void Game::draw(sf::RenderWindow & win) {
	if (closing) return;

	sf::RenderStates states = sf::RenderStates::Default;
	sf::Shader * sh = &bgShader->sh;
	states.blendMode = sf::BlendAdd;
	states.shader = sh;
	states.texture = &tex;
	sh->setUniform("texture", tex);
	win.draw(bg, states);

	beforeParts.draw(win);
	for (auto& p : distrib) 
		win.draw(p);

	for (auto& p : texts)
		win.draw(p);
	afterParts.draw(win);
}


void Game::onSpacePressed() {
	
}

void Game::onFileTick() {
	
}


void Game::im()
{

}

