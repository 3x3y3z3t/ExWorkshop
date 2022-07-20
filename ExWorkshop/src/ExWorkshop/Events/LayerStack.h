/*  LayerStack.h
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "Layer.h"

namespace exw
{
    namespace events
    {
        class LayerStack
        {
        public:
            LayerStack() = default;
            ~LayerStack();

            void push_layer(Layer* _layer);
            void pop_layer(Layer* _layer);

            void push_overlay(Layer* _overlay);
            void pop_overlay(Layer* _overlay);

            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }
            std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
            std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

            std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
            std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
            std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
            std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

        private:
            uint32_t m_Top_layer_index = 0;
            std::vector<Layer*> m_Layers;
        };

    }
}
