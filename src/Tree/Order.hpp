#pragma once

namespace Tree
{
    class Order {
    public:
        virtual ~Order() { }
    };

    class OrderHandler {
    public:
        virtual ~OrderHandler() { }
        virtual void HandleOrder( Order order ) = 0;
    };
}

