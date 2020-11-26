// ;
#include "expch.h"
#include "exw\layers\LayerStack.h"

namespace exw
{
    LayerStack::~LayerStack()
    {
        for each (Layer* layer in m_Layers)
        {
            layer->detach();
            delete layer;
        }
    }

    void LayerStack::push_layer(Layer* _layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_Insertion_index, _layer);
        ++m_Insertion_index;
    }

    void LayerStack::push_overlay(Layer* _overlay)
    {
        m_Layers.emplace_back(_overlay);
    }

    void LayerStack::pop_layer(Layer* _layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_Insertion_index, _layer);
        if (it != m_Layers.begin() + m_Insertion_index)
        {
            _layer->detach();
            m_Layers.erase(it);
            --m_Insertion_index;
        }
    }

    void LayerStack::pop_overlay(Layer* _overlay)
    {
        auto it = std::find(m_Layers.begin() + m_Insertion_index, m_Layers.end(), _overlay);
        if (it != m_Layers.end())
        {
            _overlay->detach();
            m_Layers.erase(it);
        }
    }
}
