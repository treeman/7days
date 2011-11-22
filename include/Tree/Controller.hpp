#pragma once

#include <list>
#include <boost/foreach.hpp>

#include "InputHandler.hpp"
#include "Order.hpp"

namespace Tree
{
    class Controller : public Tree::InputHandler {
    public:
        virtual ~Controller() { }

        void AddOrderHandler( OrderHandler *handler )
        {
            order_handlers.push_back( handler );
        }
        void RemoveOrderHandler( OrderHandler *handler )
        {
            OrderHandlers::iterator it = std::find(
                order_handlers.begin(),
                order_handlers.end(),
                handler
            );

            if( it != order_handlers.end() ) {
                order_handlers.erase( it );
            }
        }

        virtual void Done() { }

        virtual bool HandleEvent( sf::Event & ) { return true; }
        virtual void Update( float ) { }
    protected:
        typedef std::list<OrderHandler*> OrderHandlers;
        OrderHandlers order_handlers;

        void SendOrder( Order order )
        {
            BOOST_FOREACH( OrderHandler *handler, order_handlers ) {
                handler->HandleOrder( order );
            }
        }
    };
}

