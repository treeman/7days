#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>
#include <map>
#include <list>

#include "Exceptions.hpp"
#include "Singleton.hpp"
#include "BaseDator.hpp"
#include "Dator.hpp"
#include "Util.hpp"

/*
 * Settings is a class used for keeping track of basic settings inside the game.
 * We can change and view them through a console and parse settings files on them etc
 * If we want we can register a function callback or keep track of their
 * value through the use of a Dator.
 */

namespace Tree
{
    class SettingsListener {
    public:
        virtual ~SettingsListener() { }
        virtual void HearSetting( std::string setting, std::string value,
            std::string return_val ) = 0;
    };

    class Settings {
    public:
        Settings();
        virtual ~Settings();

        // Register new values. Will not override already parsed ones.
        template<typename T>
        void Register( std::string name, T val );
        void RegisterVariable( std::string name, boost::weak_ptr<BaseDator> dator );
        void Unregister( std::string name );

        // Get value of setting. Need to specify format.
        template<typename T>
        T GetValue( std::string name ) throw( Tree::setting_not_found );
        // Override settings value.
        template<typename T>
        void SetValue( std::string name, T value );

        // Get raw settings value.
        std::string GetSetting( std::string name );

        // Check out all settings.
        std::vector<std::string> GetSettings();
        std::map<std::string, std::string> GetSettingsValues();

        // Parse settings.
        void ParseFile( std::string path ) throw( Tree::resource_load_error );
        void ParseSetting( std::string str ) throw();

        // Generate a default settings file if it's been deleted.
        void CreateSettingsFile( std::string path );

        // Add in a listener which listens to all setting changes.
        void AddListener( SettingsListener *listener );
    private:
        // References to correct dator.
        typedef std::multimap<std::string, boost::weak_ptr<BaseDator> > DatorMap;
        DatorMap dator_map;

        // These are simply containers which hold a setting forever
        typedef std::vector<boost::shared_ptr<BaseDator> > MyDators;
        MyDators my_dators;

        // If we find a setting but we haven't registered it yet,
        // store here and we parse it later.
        typedef std::map<std::string, std::string> StringMap;
        StringMap unparsed_settings_map;

        void SetVariable( std::string name, std::string value );

        typedef std::list<SettingsListener*> ListenerList;
        ListenerList listener_list;

        void UpdateListeners( std::string setting, std::string value,
            std::string return_val );
    };
}

template<typename T>
void Tree::Settings::Register( std::string name, T val )
{
    boost::shared_ptr<BaseDator> dator( new Dator<T>( val ) );
    my_dators.push_back( dator );

    RegisterVariable( name, dator );
}

template<typename T>
T Tree::Settings::GetValue( std::string name ) throw( Tree::setting_not_found )
{
    DatorMap::iterator it = dator_map.find( name );
    if( it != dator_map.end() ) {
        boost::shared_ptr<BaseDator> other_dator = it->second.lock();
        if( other_dator ) {
            return boost::lexical_cast<T>( other_dator->Get() );
        }
        else {
            dator_map.erase( it );
        }
    }
    std::string s = "Setting '" + name + "' not found";
    throw( Tree::setting_not_found( s.c_str() ) );
}

template<typename T>
void Tree::Settings::SetValue( std::string name, T value )
{
    try {
        SetVariable( name, boost::lexical_cast<std::string>( value ) );
    }
    catch( boost::bad_lexical_cast &e ) { }
}

