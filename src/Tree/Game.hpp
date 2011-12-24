#pragma once

#include <list>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "Settings.hpp"
#include "Console.hpp"
#include "GameDebug.hpp"
#include "Singleton.hpp"
#include "Vec2D.hpp"
#include "Butler.hpp"
#include "Tweaks.hpp"
#include "Loghelper.hpp"
#include "VisualDebug.hpp"
#include "WindowManager.hpp"
#include "Rect.hpp"

#define GAME Tree::Game::Instance()

namespace Tree
{
    class Game : public Singleton<Game> {
    public:
        Game();
        ~Game();

        void Draw( const sf::Drawable &obj );

        void PortionRedrawn( const Tree::Rect &rect );
        void ClearWindow( const sf::Color color );

        //if we're drawing lazy and something has been drawn in front
        //borked
        bool NeedRedraw() const;
        bool NeedRedraw( const Tree::Rect &rect ) const;

        void DrawLazy();
        void DrawNormal();
        bool DrawingLazy();

        void NeverClear();
        void SetClear();

        float GetFPS();
        const sf::Input &GetInput();

        Vec2f GetMousePos() const;
        void SetMousePos( float x, float y );

        int GetWindowWidth();
        int GetWindowHeight();

        void Init(
            int width,
            int height,
            bool windowed,
            std::string title,
            std::string settings_file = "",
            bool drawn_lazy = false
        );
        void Start();

        void Pop();
        void Push( boost::shared_ptr<GameState> state );
        boost::shared_ptr<GameState> Top();

        void Exit();
        bool ShallExit() const;
    private:
        typedef std::list<boost::shared_ptr<GameState> > StateList;
        StateList state_list;

        bool exit_called;

        bool state_changed;
        boost::shared_ptr<GameState> curr_state;

        boost::shared_ptr<Tree::WindowManager> window_manager;
        boost::shared_ptr<sf::RenderWindow> window;

        boost::shared_ptr<Console> console;
        boost::shared_ptr<Tree::GameDebug> game_debug;

        boost::shared_ptr<Tree::InputChain> input_chain;

        void UpdateFPS( float dt );
        float fps;
        float fps_buff;
        int fps_frame_count;

        Vec2f mpos;

        bool drawn_lazy;
        bool need_redraw;
        bool shall_clear_window;
        bool clear_allowed;
        sf::Color clear_color;

        typedef std::vector<Tree::Rect> Rects;
        Rects portions_redrawn;

    //encapsulate them in Game instead of being their own Singleton
    public:
        boost::shared_ptr<Settings> GetSettings() const { return settings; }
        boost::shared_ptr<Butler> GetButler() const { return butler; }
        boost::shared_ptr<Tweaks> GetTweaks() const { return tweaks; }
        boost::shared_ptr<LogHelper> GetLogHelper() const { return log_helper; }
        boost::shared_ptr<VisualDebug> GetVisualDebug() const { return visual_debug; }
    private:
        boost::shared_ptr<Settings> settings;
        boost::shared_ptr<Butler> butler;
        boost::shared_ptr<Tweaks> tweaks;
        boost::shared_ptr<LogHelper> log_helper;
        boost::shared_ptr<VisualDebug> visual_debug;
    };
}

