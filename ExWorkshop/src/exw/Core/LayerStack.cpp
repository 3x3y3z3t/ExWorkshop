/*  LayerStack.cpp
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "LayerStack.h"

namespace exw
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            layer->detach();
            delete layer;
        }
    }

    void LayerStack::push_layer(Layer* _layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_Top_layer_index, _layer);
        ++m_Top_layer_index;
    }

    void LayerStack::pop_layer(Layer* _layer)
    {
        auto iterator = std::find(m_Layers.begin(), m_Layers.begin() + m_Top_layer_index, _layer);
        if (iterator != m_Layers.begin() + m_Top_layer_index)
        {
            _layer->detach();
            m_Layers.erase(iterator);
            --m_Top_layer_index;
        }
    }

    void LayerStack::push_overlay(Layer* _overlay)
    {
        m_Layers.emplace_back(_overlay);
    }

    void LayerStack::pop_overlay(Layer* _overlay)
    {
        auto iterator = std::find(m_Layers.begin() + m_Top_layer_index, m_Layers.end(), _overlay);
        if (iterator != m_Layers.end())
        {
            _overlay->detach();
            m_Layers.erase(iterator);
        }
    }

}
