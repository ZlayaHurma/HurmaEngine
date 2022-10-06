#include "LayersStack.h"
#include "Hurma/Layer.h"

namespace Hurma
{

    LayersStack::~LayersStack() 
    {
        for(Layer* layer : mLayers)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void LayersStack::pushLayer(Layer* layer) 
    {
        mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
        ++mLayerInsertIndex;
    }

    void LayersStack::pushOverlay(Layer* overlay) 
    {
        mLayers.emplace_back(overlay);
    }

    void LayersStack::popLayer(Layer* layer) 
    {
        const auto firstOverlayIt = mLayers.begin() + mLayerInsertIndex;
        const auto foundIt = std::find(mLayers.begin(), firstOverlayIt, layer);

        if(foundIt == firstOverlayIt)
            return;

        layer->onDetach();
        mLayers.erase(foundIt);
        --mLayerInsertIndex;
    }

    void LayersStack::popOverlay(Layer* overlay) 
    {
        const auto foundIt = std::find(mLayers.begin() + mLayerInsertIndex, mLayers.end(), overlay);

        if(foundIt == mLayers.end())
            return;

        overlay->onDetach();
        mLayers.erase(foundIt);
    }

}  // namespace Hurma

   
